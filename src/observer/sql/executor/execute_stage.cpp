/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//

#include <cstddef>
#include <sstream>
#include <string>

#include "execute_stage.h"

#include "common/io/io.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"
#include "event/execution_plan_event.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "event/storage_event.h"
#include "session/session.h"
#include "sql/parser/parse_defs.h"
#include "storage/common/condition_filter.h"
#include "storage/default/default_handler.h"
#include "storage/trx/trx.h"

using namespace common;

RC create_selection_executor(Trx *trx, Selects &selects, Table *table,
                             RelAttrTable &mini_schema,
                             SelectExeNode &select_node);
RC create_join_executor(Trx *trx, RelationTable &relations,
                        ConditionList *conds, TupleSet &tl, TupleSet &tr,
                        JoinExeNode &join_node);
RC create_group_executor(const Selects &selects, TupleSet &tuple_set,
                         GroupExeNode &order);
RC create_order_executor(const Selects &selects, TupleSet &tuple_set,
                         OrderExeNode &order);
RC create_projection_executor(const Selects &selects, TupleSet &tuple_set,
                              const TupleSchema &product,
                              ProjectExeNode &project);

RC do_join_table(TableRef *ref, Trx *trx, RelationTable &relations,
                 std::unordered_map<std::string, SelectExeNode *> &nodes,
                 TupleSet &res);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag) {}

//! Destructor
ExecuteStage::~ExecuteStage() {}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag) {
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties() {
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event) {
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SQLStageEvent *sql_event = exe_event->sql_event();
  sql_event->done_immediate();

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event) {
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SessionEvent *session_event = exe_event->sql_event()->session_event();
  Query *sql = exe_event->sqls();
  cur_db_ = session_event->get_client()->session->get_current_db();

  CompletionCallback *cb = new (std::nothrow) CompletionCallback(this, nullptr);
  if (cb == nullptr) {
    LOG_ERROR("Failed to new callback for ExecutionPlanEvent");
    exe_event->done_immediate();
    return;
  }
  exe_event->push_callback(cb);

  switch (sql->flag) {
  case SCF_SELECT: { // select
    do_select(sql, exe_event->sql_event()->session_event());
    exe_event->done_immediate();
  } break;
  case SCF_INSERT:
  case SCF_UPDATE:
  case SCF_DELETE:
  case SCF_CREATE_TABLE:
  case SCF_SHOW_TABLES:
  case SCF_DESC_TABLE:
  case SCF_DROP_TABLE:
  case SCF_CREATE_INDEX:
  case SCF_DROP_INDEX:
  case SCF_LOAD_DATA: {
    StorageEvent *storage_event = new (std::nothrow) StorageEvent(exe_event);
    if (storage_event == nullptr) {
      LOG_ERROR("Failed to new StorageEvent");
      event->done_immediate();
      return;
    }
    default_storage_stage_->handle_event(storage_event);
  } break;
  case SCF_SYNC: {
    RC rc = DefaultHandler::get_default().sync();
    char response[10];
    snprintf(response, sizeof response,
             rc == RC::SUCCESS ? "SUCCESS\n" : "FAILURE\n");
    session_event->set_response(response);
    exe_event->done_immediate();
  } break;
  case SCF_BEGIN: {
    session_event->get_client()->session->set_trx_multi_operation_mode(true);
    session_event->set_response("SUCCESS\n");
    exe_event->done_immediate();
  } break;
  case SCF_COMMIT: {
    Trx *trx = session_event->get_client()->session->current_trx();
    RC rc = trx->commit();
    session_event->get_client()->session->set_trx_multi_operation_mode(false);
    char response[10];
    snprintf(response, sizeof response,
             rc == RC::SUCCESS ? "SUCCESS\n" : "FAILURE\n");
    session_event->set_response(response);
    exe_event->done_immediate();
  } break;
  case SCF_ROLLBACK: {
    Trx *trx = session_event->get_client()->session->current_trx();
    trx->rollback();
    session_event->get_client()->session->set_trx_multi_operation_mode(false);
    session_event->set_response(strrc(RC::SUCCESS));
    exe_event->done_immediate();
  } break;
  case SCF_HELP: {
    const char *response =
        "show tables;\n"
        "desc `table name`;\n"
        "create table `table name` (`column name` `column type`, ...);\n"
        "create index `index name` on `table` (`column`);\n"
        "insert into `table` values(`value1`,`value2`);\n"
        "update `table` set column=value [where `column`=`value`];\n"
        "delete from `table` [where `column`=`value`];\n"
        "select [ * | `columns` ] from `table`;\n"
        "exit;\n";
    session_event->set_response(response);
    exe_event->done_immediate();
  } break;
  case SCF_EXIT: {
    // do nothing
    const char *response = "Unsupported\n";
    session_event->set_response(response);
    exe_event->done_immediate();
  } break;
  default: {
    exe_event->done_immediate();
    LOG_ERROR("Unsupported command=%d\n", sql->flag);
  }
  }
}

// ??????????????????????????????
// ???table?????????field_name???Field?????????????????????schema???
static RC schema_add_field(Table *table, const char *field_name,
                           TupleSchema &schema) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  schema.add_if_not_exists(field_meta->type(), COLUMN, table->name(),
                           field_meta->name());
  return RC::SUCCESS;
}

///////////////////////////////////////////////////////////////////////////
static bool match_field(Table *table, const char *field_name, AttrType &type) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return false;
  }
  type = field_meta->type();
  return true;
}

static bool check_column_attr(SelectContext &context, RelAttr *attr,
                              Selects *&to_bind, bool multi, AttrType &type) {
  auto relations = context.head()->begin()->second->relations;
  Table *table = relations->begin()->second;
  if (attr->relation_name == nullptr) {
    if (multi) {
      LOG_ERROR("SQL syntax error: need to write relation name explicitly");
      return false;
    }
    // ????????????relation?????????
    attr->relation_name = strdup(table->name());
    return match_field(table, attr->attribute_name, type);
  }

  auto res = relations->find(attr->relation_name);
  if (res == relations->end()) {
    to_bind = context.lookup(attr->relation_name);
    if (to_bind == nullptr) {
      LOG_ERROR("SQL semantic error: table %s does not exist",
                attr->relation_name);
      return false;
    } else {
      // ???????????????????????????????????????
      table = to_bind->relations->at(attr->relation_name);
    }
  } else {
    table = res->second;
  }

  return match_field(table, attr->attribute_name, type);
}

static Condition *get_condition(Selects *parent, SelectExpr *ancestor) {
  auto cond = ancestor->parent->parent;
  while (cond != nullptr && cond->parent != parent) {
    cond = cond->parent->parent;
  }
  return cond;
}

// ????????????SelectExpr
static bool check_select_expr(SelectExpr *expr, SelectContext &context,
                              bool multi) {
  if (expr->has_subexpr) {
    if (expr->left != nullptr &&
        !check_select_expr(expr->left, context, multi)) {
      return false;
    }
    if (expr->right != nullptr &&
        !check_select_expr(expr->right, context, multi)) {
      return false;
    }
    expr->type = expr->right->type;
    if (expr->left != nullptr) {
      if (!is_computable(expr->left->type, expr->type)) {
        return false;
      }
      if (expr->left->type == FLOATS || expr->right->type == FLOATS) {
        expr->type = FLOATS;
      }
    }
    return true;
  }

  if (expr->is_attr) {
    Selects *to_bind = nullptr;
    AttrType type;
    if (!check_column_attr(context, expr->attr, to_bind, multi, type)) {
      return false;
    }
    expr->type = type;
    if (to_bind != nullptr) {
      expr->binded = true;
      auto belong_to = get_condition(to_bind, expr);
      assert(belong_to != nullptr);
      belong_to->binded_exprs->push_back(expr);
    }

    // AVG???????????????
    if (expr->func == AVG_FUNC) { /* ???????????? */
      const char *table_name = expr->attr->relation_name;
      const char *field_name = expr->attr->attribute_name;
      auto relations = context.head()->begin()->second->relations;
      Table *table = relations->at(table_name);

      const FieldMeta *field_meta = table->table_meta().field(field_name);
      if (field_meta->type() != INTS && field_meta->type() != FLOATS) {
        LOG_ERROR("SQL syntax error: AVG's arg cannot be %d",
                  field_meta->type());
        return RC::GENERIC_ERROR;
      }
    }
  } else {
    // Value????????????????????????
    expr->type = expr->value->type;
  }
  return true;
}

RC ExecuteStage::resolve_select_clause(Selects &selects, bool multi) {
  RC rc = RC::SUCCESS;
  int single_star = 0;
  bool error = false;
  auto &relations = *selects.relations;

  // 1. ?????? '*' ????????????????????????
  for (size_t i = 0; i < selects.exprs->size(); i++) {
    SelectExpr *expr = selects.exprs->at(i);
    if (expr->has_subexpr == 1) {
      continue;
    }
    const RelAttr *attr = expr->attr;
    const char *table_name = attr->relation_name;
    const char *field_name = attr->attribute_name;
    bool is_star = strcmp(field_name, "*") == 0;
    // (1) '*'???'func(*)'
    if (table_name == nullptr && is_star) {
      if (expr->func != COLUMN) {
        // 'COUNT(*)'???????????????????????????
        // ??????????????????????????????????????????'*'
        continue;
      }
      single_star++;
      if (single_star > 1) {
        // ?????? '*, ..., *'??????
        LOG_ERROR("SQL syntax error: more than one star in select clause");
        error = true;
        break;
      }
    }
    // (2) 'T.*'???'func(T.*)'
    if (table_name != nullptr && is_star) {
      if (expr->func != COLUMN) {
        // ??????
        continue;
      }
      // 'T.*'????????????T????????????
      auto res = relations.find(table_name);
      if (res == relations.end()) {
        // auto outer_select = selects.context->lookup(table_name);
        // if (outer_select == nullptr) {
        //   error = true;
        //   LOG_ERROR("SQL semantic error: table %s does not exist",
        //   table_name); break;
        // } else {
        //   // WARNING: ?????????????????????????????????????????????
        //   error = true;
        //   LOG_ERROR("SQL semantic error: subquery returns multi columns");
        //   break;
        // }
        error = true;
        break;
      }
    }
  }

  if (error) {
    return RC::GENERIC_ERROR;
  }

  // 2. ?????? col ?????????'T.A' 'A'
  for (size_t i = 0; i < selects.exprs->size(); i++) {
    SelectExpr *expr = selects.exprs->at(i);
    if (expr->has_subexpr == 0) {
      if (strcmp(expr->attr->attribute_name, "*") == 0) {
        // ??????'T.*' '*'
        continue;
      }
    }
    // ??????????????????????????????????????????????????????
    // 'T.*' ??? '*' ????????????????????????
    if (!check_select_expr(expr, *selects.context, multi)) {
      rc = RC::SQL_SYNTAX;
      break;
    }
  }
  return rc;
}

/////////////////////////////////////////////////////////////////////////////
static Condition *get_condition(Selects *parent, ConditionExpr *ancestor) {
  auto cond = ancestor->parent;
  while (cond != nullptr && *cond->parent != *parent) {
    cond = cond->parent->parent;
  }
  return cond;
}
static bool check_condition_expr(ConditionExpr *expr, SelectContext &context,
                                 bool multi) {
  if (expr->has_subexpr == 1) {
    if (expr->left != nullptr &&
        !check_condition_expr(expr->left, context, multi)) {
      return false;
    }
    if (expr->right != nullptr &&
        !check_condition_expr(expr->right, context, multi)) {
      return false;
    }
    expr->type = expr->right->type;
    if (expr->left != nullptr) {
      if (!is_computable(expr->left->type, expr->type)) {
        return false;
      }
      if (expr->left->type == FLOATS || expr->right->type == FLOATS) {
        expr->type = FLOATS;
      }
    }
    return true;
  }
  // ?????????????????? 'T.A' ??? 'A'
  if (expr->is_attr) {
    Selects *to_bind = nullptr;
    AttrType type;
    if (!check_column_attr(context, expr->attr, to_bind, multi, type)) {
      return false;
    }
    expr->type = type;
    if (to_bind != nullptr) {
      expr->binded = true;
      auto belong_to = get_condition(to_bind, expr);
      assert(belong_to != nullptr);
      belong_to->binded_conds->push_back(expr);
    }
  } else {
    expr->type = expr->value->type;
  }
  return true;
}

RC ExecuteStage::resolve_condtions(const ConditionList *conds,
                                   SelectContext &context, bool multi) {
  RC rc = RC::SUCCESS;
  for (size_t i = 0; i < conds->size(); i++) {
    const Condition &cond = *conds->at(i);
    // 1. ?????????
    if (cond.left_subquery != nullptr) {
      rc = resolve_select(*cond.left_subquery);
    }
    if (cond.right_subquery != nullptr) {
      rc = resolve_select(*cond.right_subquery);
    }
    if (rc != RC::SUCCESS) {
      break;
    }

    // 2. ??????ConditionExpr
    if (cond.left != nullptr &&
        !check_condition_expr(cond.left, context, multi)) {
      rc = RC::SQL_SYNTAX;
      break;
    }
    if (cond.right != nullptr &&
        !check_condition_expr(cond.right, context, multi)) {
      rc = RC::SQL_SYNTAX;
      break;
    }
  }

  return rc;
}

/////////////////////////////////////////////////////////////////////////////
RC ExecuteStage::resolve_join_table(TableRef *ref, Selects &selects,
                                    bool multi) {
  RC rc = RC::SUCCESS;
  auto &cur = *selects.relations;
  if (ref->child == nullptr) {
    cur[ref->relation_name] = relations_[ref->relation_name];
    return rc;
  }
  // ????????????????????????
  rc = resolve_join_table(ref->child, selects, multi);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  // ?????????????????????RelationTable
  cur[ref->relation_name] = relations_[ref->relation_name];

  rc = resolve_condtions(ref->conditions, *selects.context, multi);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return rc;
}

/////////////////////////////////////////////////////////////////////////////
RC ExecuteStage::resolve_select(Selects &selects) {
  RC rc = RC::SUCCESS;
  // 1. ???????????????RelationTable
  auto &cur = *selects.relations;
  bool multi = selects.references->size() > 1;
  for (size_t i = 0; i < selects.references->size(); i++) {
    TableRef *ref = selects.references->at(i);
    const char *table_name = ref->relation_name;
    if (ref->is_join) {
      multi = true;
      rc = resolve_join_table(ref, selects, multi);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } else {
      cur[table_name] = relations_[table_name];
    }
  }

  // 2. ??????condition?????????????????????????????????
  // ConditionFilter?????????????????????????????????????????????
  rc = resolve_condtions(selects.conditions, *selects.context, multi);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // 3. ?????? select clause??????????????????????????????
  // ????????????T.A???T.*??????????????????????????????A, *
  // ??????????????????????????????*?????????????????????????????????
  // ??????????????????????????????????????????AVG()???????????????????????????
  return resolve_select_clause(selects, multi);
}

/////////////////////////////////////////////////////////////////////////////
RC ExecuteStage::join_table_relations_init(const TableRef *ref,
                                           Selects &selects) {
  RC rc = RC::SUCCESS;
  if (ref == nullptr) {
    return rc;
  }

  // 1. ????????????????????????
  const char *table_name = ref->relation_name;
  Table *table =
      DefaultHandler::get_default().find_table(cur_db_.c_str(), table_name);
  if (table == nullptr) {
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  relations_[table_name] = table;
  relations_symtab_.add_id(table_name, &selects);

  // 2. ???????????????
  rc = join_table_relations_init(ref->child, selects);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  // ??????????????????????????????????????????
  // 3. ?????? join condition
  for (size_t i = 0; i < ref->conditions->size(); i++) {
    const Condition &cond = *ref->conditions->at(i);
    if (cond.is_subquery == 1) {
      if (cond.left_subquery != nullptr) {
        rc = relations_init(*cond.left_subquery);
      }
      if (cond.right_subquery != nullptr) {
        rc = relations_init(*cond.right_subquery);
      }
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }
  return rc;
}

RC ExecuteStage::relations_init(Selects &selects) {
  relations_symtab_.enterscope();
  for (size_t i = 0; i < selects.references->size(); i++) {
    const TableRef *ref = selects.references->at(i);
    const char *table_name = ref->relation_name;
    if (ref->is_join) {
      join_table_relations_init(ref, selects);
    } else {
      // normal table reference
      Table *table =
          DefaultHandler::get_default().find_table(cur_db_.c_str(), table_name);
      if (table == nullptr) {
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }
      relations_[table_name] = table;
      relations_symtab_.add_id(table_name, &selects);
    }
  }
  *selects.context = relations_symtab_;

  RC rc = RC::SUCCESS;
  for (size_t i = 0; i < selects.conditions->size(); i++) {
    const Condition &cond = *selects.conditions->at(i);
    if (cond.is_subquery) {
      if (cond.left_subquery != nullptr) {
        rc = relations_init(*cond.left_subquery);
      }
      if (cond.right_subquery != nullptr) {
        rc = relations_init(*cond.right_subquery);
      }
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }
  relations_symtab_.exitscope();
  return rc;
}

///////////////////////////////////////////////////////////////////////
static void get_mini_schema(const SelectExpr *expr, RelationTable &relations,
                            RelAttrTable &mini_schema) {
  if (expr->has_subexpr == 1) {
    if (expr->left != nullptr) {
      get_mini_schema(expr->left, relations, mini_schema);
    }
    if (expr->right != nullptr) {
      get_mini_schema(expr->right, relations, mini_schema);
    }
    return;
  }

  if (expr->is_attr == 0) {
    // Skip value
    return;
  }

  Table *table = nullptr;
  const RelAttr *attr = expr->attr;
  const char *table_name = attr->relation_name;
  const char *field_name = attr->attribute_name;
  // ????????????????????? '*' 'COUNT(*)'
  // ???????????????COUNT(*)?????????COUNT(col)?????????NULL????????????
  if (strcmp("*", field_name) == 0 && table_name == nullptr) {
    for (auto &p : relations) {
      TupleSchema::from_table(p.second, mini_schema[p.first], false);
    }
    return;
  }
  table = relations.begin()->second;
  if (relations.size() > 1) {
    table = relations[table_name];
  }
  // 'T.*'
  if (strcmp("*", field_name) == 0) {
    TupleSchema::from_table(table, mini_schema[table->name()], false);
    return;
  }
  // 'T.A' 'A' 'func(T.A)' 'func(A)'
  schema_add_field(table, field_name, mini_schema[table->name()]);
}

static void get_mini_schema(const ConditionExpr *expr, RelationTable &relations,
                            RelAttrTable &rel_attr_table) {
  if (expr->has_subexpr == 1) {
    if (expr->left != nullptr) {
      get_mini_schema(expr->left, relations, rel_attr_table);
    }
    if (expr->right != nullptr) {
      get_mini_schema(expr->right, relations, rel_attr_table);
    }
    return;
  }
  if (expr->is_attr && !expr->binded) {
    // bind attr ??????Value ??????????????????
    const RelAttr *attr = expr->attr;
    const char *table_name = attr->relation_name;
    const char *field_name = attr->attribute_name;
    schema_add_field(relations[table_name], field_name,
                     rel_attr_table[table_name]);
  }
}

static void get_mini_schema(const Condition &cond, RelationTable &relations,
                            RelAttrTable &mini_schema) {
  RelAttrTable counter;
  // ??????????????????
  counter.clear();
  if (cond.left != nullptr) {
    get_mini_schema(cond.left, relations, counter);
  }
  if (cond.right != nullptr) {
    get_mini_schema(cond.right, relations, counter);
  }
  for (size_t i = 0; i < cond.binded_conds->size(); i++) {
    get_mini_schema(cond.binded_conds->at(i), relations, counter);
  }
  for (size_t i = 0; i < cond.binded_exprs->size(); i++) {
    get_mini_schema(cond.binded_exprs->at(i), relations, counter);
  }
  if (counter.size() > 1) {
    // ?????????????????????????????????????????????????????????????????????mini_schema
    for (auto &t : counter) {
      mini_schema[t.first].merge(t.second);
    }
  }
}

static void get_mini_schema(const TableRef *ref, RelationTable &relations,
                            RelAttrTable &mini_schema) {
  if (ref->child == nullptr) {
    return;
  }
  get_mini_schema(ref->child, relations, mini_schema);
  for (size_t i = 0; i < ref->conditions->size(); i++) {
    const Condition &cond = *ref->conditions->at(i);
    get_mini_schema(cond, relations, mini_schema);
  }
}

static void get_mini_schema(const Selects &selects, RelAttrTable &mini_schema) {
  RelationTable &relations = *selects.relations;
  // ??????select clause???????????????????????????
  for (size_t i = 0; i < selects.exprs->size(); i++) {
    const SelectExpr *expr = selects.exprs->at(i);
    get_mini_schema(expr, relations, mini_schema);
  }
  // ??????where clause
  for (size_t i = 0; i < selects.conditions->size(); i++) {
    const Condition &cond = *selects.conditions->at(i);
    get_mini_schema(cond, relations, mini_schema);
  }
  // ??????join???on clause
  for (size_t i = 0; i < selects.references->size(); i++) {
    const TableRef *ref = selects.references->at(i);
    if (ref->is_join) {
      get_mini_schema(ref, relations, mini_schema);
    }
  }
}

/////////////////////////////////////////////////////////////////////
RC do_join_table(TableRef *ref, Trx *trx, RelationTable &relations,
                 std::unordered_map<std::string, SelectExeNode *> &nodes,
                 TupleSet &res) {
  RC rc = RC::SUCCESS;
  if (ref->child == nullptr) {
    // ????????????
    nodes[ref->relation_name]->execute(res);
    return rc;
  }
  // ????????????
  rc = do_join_table(ref->child, trx, relations, nodes, res);
  TupleSet tr;
  nodes[ref->relation_name]->execute(tr);
  // ??????res???tr
  JoinExeNode *join_node = new JoinExeNode;
  rc = create_join_executor(trx, relations, ref->conditions, res, tr,
                            *join_node);
  if (rc != RC::SUCCESS) {
    delete join_node;
    return rc;
  }
  join_node->execute(res);
  delete join_node;
  // JoinExeNode????????????????????????
  return rc;
}

RC do_select(Trx *trx, Selects &selects, TupleSet &res) {
  RelationTable &relations = *selects.relations;
  // 0.1 ?????????????????????????????????schema
  RelAttrTable mini_schema;
  get_mini_schema(selects, mini_schema);

  // 0.2 ?????????Select??????????????????????????????????????????Select????????????
  RC rc = RC::SUCCESS;
  NodeTable select_nodes;
  for (auto &p : relations) {
    Table *table = p.second;
    SelectExeNode *select_node = new SelectExeNode;
    rc = create_selection_executor(trx, selects, table, mini_schema,
                                   *select_node);
    if (rc != RC::SUCCESS) {
      delete select_node;
      for (auto &tmp_node : select_nodes) {
        delete tmp_node.second;
      }
      return rc;
    }
    select_nodes[p.first] = select_node;
  }

  // 1 ??????from clause????????????????????????
  // ????????????ExecutionNode
  // ???Join table?????????SelectExeNode + JoinExeNode???
  std::vector<TupleSet> tuple_sets;
  for (size_t i = 0; i < selects.references->size(); i++) {
    TableRef *ref = selects.references->at(i);
    TupleSet tuple_set;
    if (ref->is_join != 1) {
      rc = select_nodes[ref->relation_name]->execute(tuple_set);
    } else {
      rc = do_join_table(ref, trx, relations, select_nodes, tuple_set);
    }
    if (rc != RC::SUCCESS) {
      // ????????????????????????????????????select??????
      for (auto &tmp_node : select_nodes) {
        delete tmp_node.second;
      }
      LOG_ERROR("Failed to do basic select.");
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  // 2 ??????????????????
  TupleSet tuple_set = std::move(tuple_sets[0]);
  if (tuple_sets.size() > 1) {
    // *2. ????????????????????????????????????join??????
    for (size_t i = 0; i + 1 < tuple_sets.size(); i++) {
      JoinExeNode *join_node = new JoinExeNode;
      rc = create_join_executor(trx, relations, selects.conditions, tuple_set,
                                tuple_sets[i + 1], *join_node);
      rc = join_node->execute(tuple_set);
      if (rc != RC::SUCCESS) {
        delete join_node;
        return rc;
      }
      delete join_node;
    }
  }

  // 3 ??????group clause???tuple_set????????????
  if (selects.group_num != 0) {
    GroupExeNode *group_node = new GroupExeNode;
    rc=create_group_executor(selects , tuple_set, *group_node);
    if(rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create group-by executor node.");
      return rc;
    }
    rc = group_node->execute(tuple_set);
    if(rc != RC::SUCCESS) {
      LOG_ERROR("Failed to execute group-by executor node.");
      return rc;
    }
  }

  // 4 ??????order clause???tuple_set????????????
  //   ???projection?????????????????????projection???????????????attribute??????
  if (selects.order_num != 0) {
    OrderExeNode *order_node = new OrderExeNode;
    rc = create_order_executor(selects, tuple_set, *order_node);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create order-by executor node.");
      return rc;
    }
    rc = order_node->execute(tuple_set);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to execute order-by executor node.");
      return rc;
    }
  }

  // 5 ??????select clause????????????schema
  if(selects.group_num != 0){
    TupleSet tmp_group;
    ProjectExeNode *project_node1 = new ProjectExeNode;
    res.set_schema(tuple_set.get_schema());
    rc = create_projection_executor(selects, tuple_set, tuple_set.get_schema(),
                                    *project_node1);
    project_node1->execute(tuple_set);
    int size=tuple_set.group_size();
    res.tuple_clear();
    for(int i=0; i < size; ++i){
      ProjectExeNode *project_node = new ProjectExeNode;
      tmp_group.clear();
      tmp_group=std::move(tuple_set.newget(i));
      tmp_group.set_schema(res.get_schema());
      rc = create_projection_executor(selects, tmp_group, tmp_group.get_schema(),
                                      *project_node);
      if(rc != RC::SUCCESS){
        LOG_ERROR("Failed to create projection node under group by case.");
        return rc;
      }
      project_node->execute(tmp_group);
      res.set_push_back(tmp_group.get(tmp_group.size()-1));
    }
    res.set_schema((project_node1->getout()));
  } else {
    ProjectExeNode *project_node = new ProjectExeNode;
    rc = create_projection_executor(selects, tuple_set, tuple_set.get_schema(),
                                    *project_node);
    project_node->execute(tuple_set);
    res = std::move(tuple_set);
  }
  // ????????????
  for (auto &tmp_node : select_nodes) {
    delete tmp_node.second;
  }
  // delete project_node;

  return rc;
}

RC ExecuteStage::do_select(Query *sql, SessionEvent *session_event) {
  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  Selects &selects = sql->sstr.selection;

  // 0.1 ?????????Context
  // (1) RelationTable [table_name->Table Object]
  //     ????????????????????????????????????????????????relation
  // (2) SelectContext <table_name, Selects Object>?????????
  rc = relations_init(selects);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  // 0.2 ?????????????????????
  rc = resolve_select(selects);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  std::stringstream ss;
  TupleSet tuple_set;
  rc = ::do_select(trx, selects, tuple_set);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
    return rc;
  }
  tuple_set.print(ss);
  session_event->set_response(ss.str());
  return rc;
}

/////////////////////////////////////////////////////////////////////////////////
static RC add_join_table(TableRef *ref, RelationTable relations,
                         const TupleSchema &product,
                         std::vector<ProjectionDesc *> &descs) {
  RC rc = RC::SUCCESS;
  if (ref->child == nullptr) {
    return ProjectionDesc::from_table(relations[ref->relation_name], product,
                                      descs, relations.size() > 1);
  }
  rc = add_join_table(ref->child, relations, product, descs);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  return ProjectionDesc::from_table(relations[ref->relation_name], product,
                                    descs, relations.size() > 1);
}

static RC add_all_relations(const Selects &selects, const TupleSchema &product,
                            std::vector<ProjectionDesc *> &descs) {
  RC rc = RC::SUCCESS;
  RelationTable &relations = *selects.relations;
  bool multi = relations.size() > 1;
  for (size_t i = 0; i < selects.references->size(); i++) {
    auto ref = selects.references->at(i);
    if (ref->is_join == 1) {
      add_join_table(ref, relations, product, descs);
    } else {
      rc = ProjectionDesc::from_table(relations[ref->relation_name], product,
                                      descs, multi);
    }
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  return rc;
}

RC create_group_executor(const Selects &selects, TupleSet &tuple_set,
                         GroupExeNode &group) {
  RC rc = RC::SUCCESS;
  GroupByList *groups = selects.groups;
  RelAttr *cur_attr;
  std::string table_name;
  Table *cur_table;
  int flag = 0;
  for (size_t i = 0; i < groups->size(); ++i) {
    cur_attr = groups->at(i);
    if (cur_attr->attribute_name == nullptr) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    if (cur_attr->relation_name == nullptr) {
      table_name.clear();
    } else {
      table_name = groups->at(i)->relation_name;
    }
    if (!table_name.empty()) {
      cur_table = (*selects.relations)[table_name];
      if (cur_table->table_meta().field(cur_attr->attribute_name) == nullptr) {
        return RC::SCHEMA_FIELD_NOT_EXIST;
      }
    } else {
      flag = 0;
      // find if there exists a table in the context that has this attr
      // first paired first group
      for (std::unordered_map<std::string, Table *>::iterator i =
               selects.relations->begin();
           i != selects.relations->end(); ++i) {
        cur_table = (*i).second;
        if (cur_table->table_meta().field(cur_attr->attribute_name) !=
            nullptr) {
          flag = 1;
          break;
        }
      }
      if (flag == 0) {
        return RC::SCHEMA_FIELD_NOT_EXIST;
      }
    }
  }
  group.set_group_num(selects.group_num);
  group.set_groups(selects.groups);

  return rc;
}

RC create_order_executor(const Selects &selects, TupleSet &tuple_set,
                         OrderExeNode &order) {
  //???????????????????????????attr????????????????????????????????????
  //?????????????????????execute()??????????????????
  //???????????????????????????????????????order-by?????????????????????
  RC rc = RC::SUCCESS;
  OrderColList *orders = selects.orders;
  RelAttr *cur_attr;
  std::string table_name;
  Table *cur_table;
  int flag = 0;
  for (size_t i = 0; i < orders->size(); ++i) {
    cur_attr = orders->at(i)->attr;
    if (cur_attr->attribute_name == nullptr) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    if (cur_attr->relation_name == nullptr) {
      table_name.clear();
    } else {
      table_name = orders->at(i)->attr->relation_name;
    }
    if (!table_name.empty()) {
      cur_table = (*selects.relations)[table_name];
      if (cur_table->table_meta().field(cur_attr->attribute_name) == nullptr) {
        return RC::SCHEMA_FIELD_NOT_EXIST;
      }
    } else {
      flag = 0;
      // find if there exists a table in the context that has this attr
      // first paired first sort
      for (std::unordered_map<std::string, Table *>::iterator i =
               selects.relations->begin();
           i != selects.relations->end(); ++i) {
        cur_table = (*i).second;
        if (cur_table->table_meta().field(cur_attr->attribute_name) !=
            nullptr) {
          flag = 1;
          break;
        }
      }
      if (flag == 0) {
        return RC::SCHEMA_FIELD_NOT_EXIST;
      }
    }
  }
  order.set_order_num(selects.order_num);
  order.set_orders(selects.orders);

  return rc;
}

RC create_projection_executor(const Selects &selects, TupleSet &tuple_set,
                              const TupleSchema &product,
                              ProjectExeNode &project) {
  RC rc = RC::SUCCESS;
  RelationTable &relations = *selects.relations;
  bool multi = relations.size() > 1;
  std::vector<ProjectionDesc *> descs;
  for (size_t i = 0; i < selects.exprs->size(); i++) {
    SelectExpr *expr = selects.exprs->at(i);
    if (expr->is_attr == 1 && expr->func == COLUMN) {
      // ??????'*'??????
      RelAttr *attr = expr->attr;
      const char *table_name = attr->relation_name;
      const char *field_name = attr->attribute_name;
      if (strcmp("*", field_name) == 0) {
        if(selects.group_num != 0)
          return RC::SCHEMA_TABLE_NAME_ILLEGAL;
        if (table_name == nullptr) {
          rc = add_all_relations(selects, product, descs);
        } else {
          Table *table = relations[table_name];
          rc = ProjectionDesc::from_table(table, product, descs, multi);
        }
        if (rc != RC::SUCCESS) {
          for (ProjectionDesc *&d : descs) {
            delete d;
          }
          return rc;
        }
        continue;
      }
    }
    // ????????????
    ProjectionDesc *desc = ProjectionDesc::get_projection_desc(expr, tuple_set);
    rc = desc->init(expr, product, multi);
    if (rc != RC::SUCCESS) {
      delete desc;
      for (ProjectionDesc *&d : descs) {
        delete d;
      }
      return rc;
    }
    descs.push_back(desc);
  }
  return project.init(std::move(tuple_set), std::move(descs));
}

/////////////////////////////////////////////////////////////////////////////////
static void get_one_mini_schema(const RelAttr *attr, RelationTable &relations,
                                TupleSchema &schema) {
  const char *table_name = attr->relation_name;
  const char *field_name = attr->attribute_name;
  schema_add_field(relations[table_name], field_name, schema);
}

static void get_one_mini_schema(const ConditionExpr *expr,
                                RelationTable &relations, TupleSchema &schema) {
  if (expr->has_subexpr == 1) {
    if (expr->left != nullptr) {
      get_one_mini_schema(expr->left, relations, schema);
    }
    if (expr->right != nullptr) {
      get_one_mini_schema(expr->right, relations, schema);
    }
    return;
  }
  if (expr->is_attr && !expr->binded) {
    // binded attr??????Value????????????
    get_one_mini_schema(expr->attr, relations, schema);
  }
}

static bool check_condition_usable(const Condition &cond,
                                   RelationTable &relations,
                                   TupleSchema &mask) {
  TupleSchema collector;
  collector.clear();
  if (cond.left != nullptr) {
    get_one_mini_schema(cond.left, relations, collector);
    if (!mask.contains_all(collector)) {
      return false;
    }
  }
  if (cond.right != nullptr) {
    get_one_mini_schema(cond.right, relations, collector);
    if (!mask.contains_all(collector)) {
      return false;
    }
  }
  for (size_t i = 0; i < cond.binded_conds->size(); i++) {
    get_one_mini_schema(cond.binded_conds->at(i)->attr, relations, collector);
    if (!mask.contains_all(collector)) {
      return false;
    }
  }
  for (size_t i = 0; i < cond.binded_exprs->size(); i++) {
    get_one_mini_schema(cond.binded_exprs->at(i)->attr, relations, collector);
    if (!mask.contains_all(collector)) {
      return false;
    }
  }
  return true;
}

RC create_join_executor(Trx *trx, RelationTable &relations,
                        ConditionList *conds, TupleSet &tl, TupleSet &tr,
                        JoinExeNode &join_node) {
  RC rc = RC::SUCCESS;
  // ??????????????????????????????condition
  std::vector<TupleFilter *> filters;
  TupleSchema product_schema = tl.get_schema();
  // ??????append???????????????tl, tr????????????????????????
  product_schema.append(tr.get_schema());

  for (size_t i = 0; i < conds->size(); i++) {
    Condition &cond = *conds->at(i);
    if (cond.is_used == 1) {
      continue;
    }
    if (!check_condition_usable(cond, relations, product_schema)) {
      continue;
    }
    cond.is_used = 1;
    TupleFilter *filter = new TupleFilter();
    rc = filter->init(trx, product_schema, cond);
    if (rc != RC::SUCCESS) {
      delete filter;
      for (TupleFilter *&filter : filters) {
        delete filter;
      }
      return rc;
    }
    filters.push_back(filter);
  }
  return join_node.init(std::move(tl), std::move(tr), std::move(filters));
}

/////////////////////////////////////////////////////////////////////////////////
static RC add_filter(Trx *trx, RelationTable &relations, Table *table,
                     ConditionList *conds,
                     std::vector<DefaultConditionFilter *> &cond_filters) {
  RC rc = RC::SUCCESS;
  TupleSchema table_schema;
  TupleSchema::from_table(table, table_schema, false);
  for (size_t i = 0; i < conds->size(); i++) {
    Condition &cond = *conds->at(i);
    if (cond.is_used == 1) {
      // ??????????????????????????????
      continue;
    }
    if (!check_condition_usable(cond, relations, table_schema)) {
      continue;
    }
    cond.is_used = 1;

    Table &t = *table;
    DefaultConditionFilter *condition_filter = new DefaultConditionFilter(t);
    rc = condition_filter->init(*table, cond, trx);
    if (rc != RC::SUCCESS) {
      delete condition_filter;
      for (DefaultConditionFilter *&filter : cond_filters) {
        delete filter;
      }
      return rc;
    }
    cond_filters.push_back(condition_filter);
  }
  return rc;
}

static RC create_filters_in_join_table(
    TableRef *ref, Trx *trx, RelationTable &relations, Table *table,
    std::vector<DefaultConditionFilter *> &cond_filters) {
  RC rc = RC::SUCCESS;
  if (ref->child == nullptr) {
    return rc;
  }
  rc = add_filter(trx, relations, table, ref->conditions, cond_filters);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  return create_filters_in_join_table(ref->child, trx, relations, table,
                                      cond_filters);
}

// ??????????????????????????????????????????condition?????????????????????????????????select ????????????
RC create_selection_executor(Trx *trx, Selects &selects, Table *table,
                             RelAttrTable &mini_schema,
                             SelectExeNode &select_node) {
  RC rc = RC::SUCCESS;
  RelationTable &relations = *selects.relations;
  const char *table_name = table->name();
  std::vector<DefaultConditionFilter *> cond_filters;
  // ???????????????????????????????????????
  // 1. join table???
  for (size_t i = 0; i < selects.references->size(); i++) {
    TableRef *ref = selects.references->at(i);
    if (ref->is_join == 1) {
      create_filters_in_join_table(ref, trx, relations, table, cond_filters);
    }
  }

  // 2. where clause???
  rc = add_filter(trx, relations, table, selects.conditions, cond_filters);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  TupleSchema scm = mini_schema[table_name];
  return select_node.init(trx, table, std::move(scm), std::move(cond_filters));
}
