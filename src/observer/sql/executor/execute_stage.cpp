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
                        ConditionList *conds, size_t cond_num, TupleSet &tl,
                        TupleSet &tr, JoinExeNode &join_node);
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

// 必须在语义检查后调用
// 将table中名为field_name的Field不重复地添加进schema中
static RC schema_add_field(Table *table, const char *field_name,
                           TupleSchema &schema) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  schema.add_if_not_exists(field_meta->type(), COLUMN, table->name(),
                           field_meta->name());
  return RC::SUCCESS;
}

///////////////////////////////////////////////////////////////////////////
static bool match_field(Table *table, const char *field_name) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return false;
  }
  return true;
}

static bool check_column_attr(RelationTable &outer, RelationTable &cur,
                              RelAttr *attr, TableRef *&ref, bool multi) {
  Table *table = cur.begin()->second;
  if (attr->relation_name == nullptr) {
    if (multi) {
      LOG_ERROR("SQL syntax error: need to write relation name explicitly");
      return false;
    }
    // 单表缺省relation的情况
    attr->relation_name = strdup(table->name());
    return match_field(table, attr->attribute_name);
  }

  auto cur_res = cur.find(attr->relation_name);
  auto outer_res = outer.find(attr->relation_name);
  if (cur_res == cur.end()) {
    if (outer_res == outer.end()) {
      LOG_ERROR("SQL semantic error: table %s does not exist",
                attr->relation_name);
      return false;
    } else {
      table = outer_res->second;
      cur[table->name()] = table;
      ref = (TableRef *)malloc(sizeof(TableRef));
      table_ref_init(ref, 0, table->name(), nullptr, new ConditionList);
    }
  } else {
    table = cur_res->second;
  }

  return match_field(table, attr->attribute_name);
}

// 用于检查SelectExpr
static bool check_select_expr(SelectExpr *expr, RelationTable &outer,
                              RelationTable &cur, Selects &selects,
                              bool multi) {
  if (expr->has_subexpr) {
    if (!check_select_expr(expr->left, outer, cur, selects, multi)) {
      return false;
    }
    if (!check_select_expr(expr->right, outer, cur, selects, multi)) {
      return false;
    }
    return true;
  }

  if (expr->is_attr) {
    TableRef *ref = nullptr;
    if (!check_column_attr(outer, cur, expr->attr, ref, multi)) {
      if (ref != nullptr) {
        free(ref);
      }
      return false;
    }
    if (ref != nullptr) {
      // check_cloumn_attr返回的TableRef非空，说明缺少上文信息
      selects.references->push_back(ref);
      selects.ref_num++;
    }
    // AVG参数要匹配
    if (expr->func == AVG_FUNC) { /* 聚合函数 */
      const char *table_name = expr->attr->relation_name;
      const char *field_name = expr->attr->attribute_name;
      Table *table = cur.begin()->second;
      if (table_name != nullptr) {
        table = cur[table_name];
      }

      const FieldMeta *field_meta = table->table_meta().field(field_name);
      if (field_meta->type() != INTS && field_meta->type() != FLOATS) {
        LOG_ERROR("SQL syntax error: AVG's arg cannot be %d",
                  field_meta->type());
        return RC::GENERIC_ERROR;
      }
    }
  }
  // Value无需另外检查语法
  return true;
}

RC ExecuteStage::resolve_select_clause(Selects &selects, RelationTable &outer,
                                       RelationTable &cur, bool multi) {
  RC rc = RC::SUCCESS;
  int single_star = 0;
  bool error = false;

  // 1. 检查 '*' 是否是否使用正确
  for (size_t i = 0; i < selects.expr_num; i++) {
    SelectExpr *expr = selects.exprs->at(i);
    if (expr->has_subexpr == 1) {
      continue;
    }
    const RelAttr *attr = expr->attr;
    const char *table_name = attr->relation_name;
    const char *field_name = attr->attribute_name;
    bool is_star = strcmp(field_name, "*") == 0;
    // (1) '*'或'func(*)'
    if (table_name == nullptr && is_star) {
      if (expr->func != COLUMN) {
        // 'COUNT(*)'在任何时候一定正确
        // 其余函数在语法层面禁止参数为'*'
        continue;
      }
      single_star++;
      if (single_star > 1) {
        // 出现 '*, ..., *'报错
        LOG_ERROR("SQL syntax error: more than one star in select clause");
        error = true;
        break;
      }
    }
    // (2) 'T.*'或'func(T.*)'
    if (table_name != nullptr && is_star) {
      if (expr->func != COLUMN) {
        // 同上
        continue;
      }
      // 'T.*'只需检查T是否存在
      auto res = cur.find(table_name);
      auto outer_res = outer.find(table_name);
      if (res == cur.end()) {
        if (outer_res == outer.end()) {
          error = true;
          LOG_ERROR("SQL semantic error: table %s does not exist", table_name);
          break;
        } else {
          TableRef *ref = new TableRef;
          table_ref_init(ref, 0, table_name, nullptr, nullptr);
          selects.references->push_back(ref);
          selects.ref_num++;
          cur[table_name] = outer[table_name];
        }
      }
    }
  }

  if (error) {
    return RC::GENERIC_ERROR;
  }

  // 2. 检查 col 用法：'T.A' 'A'
  for (size_t i = 0; i < selects.expr_num; i++) {
    SelectExpr *expr = selects.exprs->at(i);
    if (expr->has_subexpr == 0) {
      if (strcmp(expr->attr->attribute_name, "*") == 0) {
        // 跳过'T.*' '*'
        continue;
      }
    }
    // 如果是表达式，语法层面保证不会出现：
    // 'T.*' 或 '*' 作为运算的操作数
    if (!check_select_expr(expr, outer, cur, selects, multi)) {
      rc = RC::SQL_SYNTAX;
      break;
    }
  }
  return rc;
}

/////////////////////////////////////////////////////////////////////////////
/**
 * refs@out: 需补充的上文信息
 * PS: 对于
 *  1. select的select clause和where clause而言，补充的信息直接放入from clause
 *  2. join table的on clause而言，补充的信息作为当前join table节点的子孙
 */
static bool check_condition_expr(const ConditionExpr *expr,
                                 RelationTable &outer, RelationTable &cur,
                                 std::vector<TableRef *> &refs, bool multi) {
  if (expr->has_subexpr == 1) {
    if (!check_condition_expr(expr->left, outer, cur, refs, multi)) {
      return false;
    }
    if (!check_condition_expr(expr->right, outer, cur, refs, multi)) {
      return false;
    }
    return true;
  }
  // 叶子节点只有 'T.A' 或 'A'
  if (expr->is_attr) {
    TableRef *ref = nullptr;
    if (!check_column_attr(outer, cur, expr->attr, ref, multi)) {
      if (ref != nullptr) {
        free(ref);
      }
      return false;
    }
    if (ref != nullptr) {
      refs.push_back(ref);
    }
  }
  return true;
}

RC ExecuteStage::resolve_condtions(RelationTable &outer, RelationTable &cur,
                                   std::vector<TableRef *> &refs,
                                   const ConditionList *conds, bool multi) {
  RC rc = RC::SUCCESS;
  for (size_t i = 0; i < conds->size(); i++) {
    const Condition &cond = conds->at(i);
    // 1. 先检查left ConditionExpr
    if (!check_condition_expr(cond.left, outer, cur, refs, multi)) {
      rc = RC::SQL_SYNTAX;
      break;
    }
    // 2. 子查询或右表达式
    if (cond.is_subquery == 1) { // 子查询
      // 合并 outer 和 cur 作为子查询的outer
      RelationTable cur_outer = outer;
      for (auto &p : cur) {
        cur_outer[p.first] = p.second;
      }
      rc = resolve_select(*cond.subquery, cur_outer);
      if (rc != RC::SUCCESS) {
        break;
      }
    } else { // 右表达式
      if (!check_condition_expr(cond.right, outer, cur, refs, multi)) {
        rc = RC::SQL_SYNTAX;
        break;
      }
    }
  }
  return rc;
}

/////////////////////////////////////////////////////////////////////////////
RC ExecuteStage::resolve_join_table(TableRef *ref, RelationTable &outer,
                                    RelationTable &cur) {
  RC rc = RC::SUCCESS;
  if (ref->child == nullptr) {
    cur[ref->relation_name] = relations_[ref->relation_name];
    return rc;
  }
  // 递归地处理左节点
  rc = resolve_join_table(ref->child, outer, cur);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  // 右节点加入本层RelationTable
  cur[ref->relation_name] = relations_[ref->relation_name];

  std::vector<TableRef *> refs;
  rc = resolve_condtions(outer, cur, refs, ref->conditions, ref->cond_num);
  if (rc != RC::SUCCESS) {
    for (auto t : refs) {
      free(t);
    }
    return rc;
  }
  // make join table
  auto cur_node = ref;
  for (auto t : refs) {
    t->is_join = 1;
    t->child = cur_node->child;
    cur_node->child = t;
    cur_node = t;
  }

  return rc;
}

/////////////////////////////////////////////////////////////////////////////
RC ExecuteStage::resolve_select(Selects &selects, RelationTable &outer) {
  RC rc = RC::SUCCESS;
  // 1. 建立本层的RelationTable
  auto &cur = *selects.context;
  bool multi = selects.ref_num > 1;
  for (size_t i = 0; i < selects.ref_num; i++) {
    TableRef *ref = selects.references->at(i);
    const char *table_name = ref->relation_name;
    if (ref->is_join) {
      multi = true;
      rc = resolve_join_table(ref, outer, cur);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } else {
      cur[table_name] = relations_[table_name];
    }
  }

  // 2. 检查condition，必要时候补充上文信息到from clause
  // ConditionFilter中有类型转换和检查，这里不用做
  std::vector<TableRef *> refs;
  rc = resolve_condtions(outer, cur, refs, selects.conditions, multi);
  if (rc != RC::SUCCESS) {
    for (auto t : refs) {
      free(t);
    }
    return rc;
  }
  // 加入from clause
  for (auto t : refs) {
    selects.references->push_back(t);
    selects.ref_num++;
  }
  // 3. 检查 select clause，必要时补充上文信息到from clause
  // 属性名：多表必须T.A，T.*；单表A, *，单表情况下不允许多个*
  // 聚合函数参数：另有规定，例如AVG()不能测日期和字符串
  return resolve_select_clause(selects, outer, cur, multi);
}

/////////////////////////////////////////////////////////////////////////////
RC ExecuteStage::join_table_relations_init(const TableRef *ref) {
  RC rc = RC::SUCCESS;
  if (ref == nullptr) {
    return rc;
  }

  // 1. 右结点表是否存在
  const char *table_name = ref->relation_name;
  Table *table =
      DefaultHandler::get_default().find_table(cur_db_.c_str(), table_name);
  if (table == nullptr) {
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  relations_[table_name] = table;

  // 2. 再查左结点
  rc = join_table_relations_init(ref->child);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  // 子结点中的表信息已经收集完毕
  // 3. 检查 join condition
  for (int i = ref->cond_num - 1; i >= 0; i--) {
    const Condition &cond = ref->conditions->at(i);
    if (cond.is_subquery) {
      rc = relations_init(*cond.subquery);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }
  return rc;
}

RC ExecuteStage::relations_init(const Selects &selects) {
  for (size_t i = 0; i < selects.ref_num; i++) {
    const TableRef *ref = selects.references->at(i);
    const char *table_name = ref->relation_name;
    if (ref->is_join) {
      join_table_relations_init(ref);
    } else {
      // normal table reference
      Table *table =
          DefaultHandler::get_default().find_table(cur_db_.c_str(), table_name);
      if (table == nullptr) {
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }
      relations_[table_name] = table;
    }
  }

  RC rc = RC::SUCCESS;
  for (int i = selects.cond_num - 1; i >= 0; i--) {
    const Condition &cond = selects.conditions->at(i);
    if (cond.is_subquery) {
      rc = relations_init(*cond.subquery);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }
  return rc;
}

///////////////////////////////////////////////////////////////////////
static void get_mini_schema(const SelectExpr *expr, RelationTable &relations,
                            RelAttrTable &mini_schema) {
  if (expr->has_subexpr == 1) {
    get_mini_schema(expr->left, relations, mini_schema);
    get_mini_schema(expr->right, relations, mini_schema);
    return;
  }
  Table *table = nullptr;
  const RelAttr *attr = expr->attr;
  const char *table_name = attr->relation_name;
  const char *field_name = attr->attribute_name;
  // 特殊情况：多表 '*' 'COUNT(*)'
  // 这里不能将COUNT(*)优化为COUNT(col)，不然NULL可能出错
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
    get_mini_schema(expr->left, relations, rel_attr_table);
    get_mini_schema(expr->right, relations, rel_attr_table);
    return;
  }
  if (expr->is_attr) {
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
  // 扫描左表达式
  counter.clear();
  get_mini_schema(cond.left, relations, counter);
  int left_cnt = counter.size();
  if (cond.is_subquery == 0) {
    get_mini_schema(cond.right, relations, counter);
  }
  if (left_cnt > 1) {
    // 左表达式已经涉及超过1个关系
    for (auto &t : counter) {
      mini_schema[t.first].merge(t.second);
    }
  } else {
    // 否则，只有左右表达式涉及两个以上关系才需添加进mini_schema
    if (counter.size() > 1) {
      for (auto &t : counter) {
        mini_schema[t.first].merge(t.second);
      }
    }
  }
}

static void get_mini_schema(const TableRef *ref, RelationTable &relations,
                            RelAttrTable &mini_schema) {
  if (ref->child == nullptr) {
    return;
  }
  get_mini_schema(ref->child, relations, mini_schema);
  for (int i = ref->cond_num - 1; i >= 0; i--) {
    const Condition &cond = ref->conditions->at(i);
    get_mini_schema(cond, relations, mini_schema);
  }
}

static void get_mini_schema(const Selects &selects, RelationTable &relations,
                            RelAttrTable &mini_schema) {
  // 扫描select clause，这是一定要添加的
  for (size_t i = 0; i < selects.expr_num; i++) {
    const SelectExpr *expr = selects.exprs->at(i);
    get_mini_schema(expr, relations, mini_schema);
  }
  // 扫描where clause
  for (int i = selects.cond_num - 1; i >= 0; i--) {
    const Condition &cond = selects.conditions->at(i);
    get_mini_schema(cond, relations, mini_schema);
  }
  // 扫描join的on clause
  for (size_t i = 0; i < selects.ref_num; i++) {
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
    // 叶子节点
    nodes[ref->relation_name]->execute(res);
    return rc;
  }
  // 内部节点
  rc = do_join_table(ref->child, trx, relations, nodes, res);
  TupleSet tr;
  nodes[ref->relation_name]->execute(tr);
  // 连接res和tr
  JoinExeNode *join_node = new JoinExeNode;
  rc = create_join_executor(trx, relations, ref->conditions, ref->cond_num, res,
                            tr, *join_node);
  if (rc != RC::SUCCESS) {
    delete join_node;
    return rc;
  }
  join_node->execute(res);
  delete join_node;
  // JoinExeNode都是用完立刻释放
  return rc;
}

RC do_select(Trx *trx, Selects &selects, TupleSet &res) {
  RelationTable &relations = *selects.context;
  // 0.1 收集所有关系的底层最简schema
  RelAttrTable mini_schema;
  get_mini_schema(selects, relations, mini_schema);

  // 0.2 生成该Select语句涉及到的所有关系的最底层Select执行节点
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

  // 1 按照from clause生成带连接中间表
  // 依次执行ExecutionNode
  // （Join table实质是SelectExeNode + JoinExeNode）
  std::vector<TupleSet> tuple_sets;
  for (size_t i = 0; i < selects.ref_num; i++) {
    TableRef *ref = selects.references->at(i);
    TupleSet tuple_set;
    if (ref->is_join != 1) {
      rc = select_nodes[ref->relation_name]->execute(tuple_set);
    } else {
      rc = do_join_table(ref, trx, relations, select_nodes, tuple_set);
    }
    if (rc != RC::SUCCESS) {
      // 有一个失败则释放所有底层select节点
      for (auto &tmp_node : select_nodes) {
        delete tmp_node.second;
      }
      LOG_ERROR("Failed to do basic select.");
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  // 2 将中间表连接
  TupleSet tuple_set = std::move(tuple_sets[0]);
  if (tuple_sets.size() > 1) {
    // *2. 本次查询了多张表（不一定是不同表），需要做join操作
    for (size_t i = 0; i + 1 < tuple_sets.size(); i++) {
      JoinExeNode *join_node = new JoinExeNode;
      rc = create_join_executor(trx, relations, selects.conditions,
                                selects.cond_num, tuple_set, tuple_sets[i + 1],
                                *join_node);
      join_node->execute(tuple_set);
      delete join_node;
    }
  }

  // 3 根据select clause生成输出schema
  ProjectExeNode *project_node = new ProjectExeNode;
  rc = create_projection_executor(selects, tuple_set, tuple_set.get_schema(),
                                  *project_node);
  project_node->execute(tuple_set);
  res = std::move(tuple_set);

  // 释放资源
  for (auto &tmp_node : select_nodes) {
    delete tmp_node.second;
  }

  return rc;
}

RC ExecuteStage::do_select(Query *sql, SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  Selects &selects = sql->sstr.selection;

  // 0.1 初始化[关系名->Table Object]表
  rc = relations_init(selects);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  // 0.2 优先检查元数据
  RelationTable relations;
  rc = resolve_select(selects, relations);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  std::stringstream ss;
  TupleSet tuple_set;
  ::do_select(trx, selects, tuple_set);

  tuple_set.print(ss, selects.context->size() > 1);
  session_event->set_response(ss.str());
  return rc;
}

/////////////////////////////////////////////////////////////////////////////////
static RC add_join_table(TableRef *ref, RelationTable relations,
                         const TupleSchema &product,
                         std::vector<ProjectionDesc *> &descs) {
  if (ref->child == nullptr) {
    return ProjectionDesc::from_table(relations[ref->relation_name], product,
                                      descs, relations.size() > 1);
  }
  add_join_table(ref->child, relations, product, descs);
  return ProjectionDesc::from_table(relations[ref->relation_name], product,
                                    descs, relations.size() > 1);
}

static RC add_all_relations(const Selects &selects, const TupleSchema &product,
                            std::vector<ProjectionDesc *> &descs) {
  RC rc = RC::SUCCESS;
  RelationTable &relations = *selects.context;
  bool multi = relations.size() > 1;
  for (size_t i = 0; i < selects.ref_num; i++) {
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

RC create_projection_executor(const Selects &selects, TupleSet &tuple_set,
                              const TupleSchema &product,
                              ProjectExeNode &project) {
  RC rc = RC::SUCCESS;
  RelationTable &relations = *selects.context;
  bool multi = relations.size() > 1;
  std::vector<ProjectionDesc *> descs;
  for (size_t i = 0; i < selects.expr_num; i++) {
    SelectExpr *expr = selects.exprs->at(i);
    if (expr->is_attr == 1 && expr->func == COLUMN) {
      // 处理'*'情况
      RelAttr *attr = expr->attr;
      const char *table_name = attr->relation_name;
      const char *field_name = attr->attribute_name;
      if (strcmp("*", field_name) == 0) {
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
    // 一般情况
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
static void get_one_mini_schema(const ConditionExpr *expr,
                                RelationTable &relations, TupleSchema &schema) {
  if (expr->has_subexpr == 1) {
    get_one_mini_schema(expr->left, relations, schema);
    get_one_mini_schema(expr->right, relations, schema);
    return;
  }
  if (expr->is_attr) {
    const RelAttr *attr = expr->attr;
    const char *table_name = attr->relation_name;
    const char *field_name = attr->attribute_name;
    schema_add_field(relations[table_name], field_name, schema);
  }
}

RC create_join_executor(Trx *trx, RelationTable &relations,
                        ConditionList *conds, size_t cond_num, TupleSet &tl,
                        TupleSet &tr, JoinExeNode &join_node) {
  RC rc = RC::SUCCESS;
  // 列出和这两张表相关的condition
  std::vector<TupleFilter *> filters;
  TupleSchema product_schema = tl.get_schema();
  // 使用append即可，因为tl, tr始终不可能有交集
  product_schema.append(tr.get_schema());

  TupleSchema collector;
  for (size_t i = 0; i < cond_num; i++) {
    Condition &cond = conds->at(i);
    if (cond.is_used == 1) {
      continue;
    }
    collector.clear();
    // 只与一个表相关的条件一定已经使用
    get_one_mini_schema(cond.left, relations, collector);
    if (!product_schema.contains_all(collector)) {
      continue;
    }

    TupleSet subquery;
    if (cond.is_subquery == 0) {
      get_one_mini_schema(cond.right, relations, collector);
      if (!product_schema.contains_all(collector)) {
        continue;
      }
    } else {
      rc = do_select(trx, *cond.subquery, subquery);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
    cond.is_used = 1;
    TupleFilter *filter = new TupleFilter();
    rc = filter->init(product_schema, cond, std::move(subquery));
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
                     ConditionList *conds, size_t cond_num,
                     std::vector<DefaultConditionFilter *> &cond_filters) {
  RC rc = RC::SUCCESS;
  TupleSchema table_schema;
  TupleSchema::from_table(table, table_schema, false);
  TupleSchema counter;
  for (size_t i = 0; i < cond_num; i++) {
    Condition &cond = conds->at(i);
    if (cond.is_used == 1) {
      // 使用过的条件直接跳过
      continue;
    }
    counter.clear();
    get_one_mini_schema(cond.left, relations, counter);
    if (!table_schema.contains_all(counter)) {
      continue;
    }

    TupleSet subquery;
    if (cond.is_subquery == 0) {
      get_one_mini_schema(cond.right, relations, counter);
      if (!table_schema.contains_all(counter)) {
        continue;
      }
    } else {
      do_select(trx, *cond.subquery, subquery);
    }
    cond.is_used = 1;

    Table &t = *table;
    DefaultConditionFilter *condition_filter = new DefaultConditionFilter(t);
    rc = condition_filter->init(*table, cond, std::move(subquery));
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
  rc = add_filter(trx, relations, table, ref->conditions, ref->cond_num,
                  cond_filters);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  return create_filters_in_join_table(ref->child, trx, relations, table,
                                      cond_filters);
}

// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_selection_executor(Trx *trx, Selects &selects, Table *table,
                             RelAttrTable &mini_schema,
                             SelectExeNode &select_node) {
  RC rc = RC::SUCCESS;
  RelationTable &relations = *selects.context;
  const char *table_name = table->name();
  std::vector<DefaultConditionFilter *> cond_filters;
  // 找出仅与此表相关的过滤条件
  // 1. join table中
  for (size_t i = 0; i < selects.ref_num; i++) {
    TableRef *ref = selects.references->at(i);
    if (ref->is_join == 1) {
      create_filters_in_join_table(ref, trx, relations, table, cond_filters);
    }
  }

  // 2. where clause中
  rc = add_filter(trx, relations, table, selects.conditions, selects.cond_num,
                  cond_filters);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  TupleSchema scm = mini_schema[table_name];
  return select_node.init(trx, table, std::move(scm), std::move(cond_filters));
}
