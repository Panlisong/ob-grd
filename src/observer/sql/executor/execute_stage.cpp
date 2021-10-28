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

RC create_selection_executor(
    Trx *trx, const Selects &selects, Table *table,
    std::unordered_map<std::string, TupleSchema> &mini_schema,
    SelectExeNode &select_node, bool multi_flag);
RC create_join_executor(Trx *trx, const Condition conds[], size_t cond_num,
                        TupleSet &tl, TupleSet &tr, JoinExeNode &join_node);

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
  const char *current_db =
      session_event->get_client()->session->get_current_db().c_str();

  CompletionCallback *cb = new (std::nothrow) CompletionCallback(this, nullptr);
  if (cb == nullptr) {
    LOG_ERROR("Failed to new callback for ExecutionPlanEvent");
    exe_event->done_immediate();
    return;
  }
  exe_event->push_callback(cb);

  switch (sql->flag) {
  case SCF_SELECT: { // select
    do_select(current_db, sql, exe_event->sql_event()->session_event());
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

static RC schema_add_field(Table *table, FuncName func, const char *field_name,
                           TupleSchema &schema) {
  // '*'的情况在外面考虑了，一定是最简SelectExeNode+JoinExeNode结果的schema
  if (func == COLUMN && strcmp(field_name, "*") == 0) {
    // 列名'T.*'
    TupleSchema::from_table(table, schema, true);
    return RC::SUCCESS;
  }

  if (func == COUNT_FUNC && strcmp(field_name, "*") == 0) {
    // 特殊情况：count(*)
    schema.add(INTS, func, table->name(), field_name);
    return RC::SUCCESS;
  }

  // func(A) 或 func(T.A) 或 A 或 T.A
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  assert(field_meta != nullptr); // 语义检查后这不应该发生
  schema.add(field_meta->type(), func, table->name(), field_meta->name());
  return RC::SUCCESS;
}

// 必须在语义检查后调用
static RC schema_add_field(Table *table, const char *field_name,
                           TupleSchema &schema) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  schema.add_if_not_exists(field_meta->type(), COLUMN, table->name(),
                           field_meta->name());
  return RC::SUCCESS;
}

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分.
static bool match_field(Table *table, const char *field_name) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return false;
  }
  return true;
}

static RC
check_select_clause(const std::unordered_map<std::string, Table *> &relations,
                    const Selects &selects) {
  bool multi_flag = relations.size() > 1;
  int single_star = 0;
  bool error = false;
  for (int i = selects.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.attributes[i];
    const char *table_name = attr.relation_name;
    const char *field_name = attr.attribute_name;
    Table *table = relations.begin()->second;
    // (1) 特殊情况：'*'
    if (table_name == nullptr && strcmp(field_name, "*") == 0) {
      if (attr.func != COLUMN) {
        // 'COUNT(*)'在任何时候一定正确
        continue;
      }
      if (single_star > 1) {
        // 出现 '*, ..., *'报错
        LOG_ERROR("SQL syntax error: more than one star in select clause");
        error = true;
        break;
      }
      single_star++;
      continue;
    }

    // (2) 检查表，字段是否存在
    if (multi_flag) { // 多表情况
      if (table_name == nullptr) {
        LOG_ERROR("SQL syntax error: need to write relation name explicitly");
        error = true;
        break;
      }
      auto res = relations.find(table_name);
      if (res == relations.end()) {
        error = true;
        LOG_ERROR("SQL semantic error: table %s does not exist", table_name);
        break;
      }
      table = res->second;
    } // 单表情况是table的初值

    // 到这里Table存在性已经检验
    if (strcmp(field_name, "*") == 0) {
      // 多表：'T.*'一定正确；作为聚合函数参数也正确，
      // 单表：非聚合函数的 '*' 已经检测，作为聚合函数不用检测一定正确
      // PS：在parser层面只允许'COUNT(T.*)'或COUNT(*)，所以无需检查
      continue;
    }

    // 到这里字段名一定不为'*'
    if (!match_field(table, field_name)) {
      error = true;
      break;
    }

    // (3) AVG参数要匹配
    if (attr.func == AVG_FUNC) { /* 聚合函数 */
      const FieldMeta *field_meta =
          table->table_meta().field(attr.attribute_name);
      if (field_meta->type() != INTS && field_meta->type() != FLOATS) {
        error = true;
        LOG_ERROR("SQL syntax error: AVG's arg cannot be %d",
                  field_meta->type());
        break;
      }
    }
  }

  if (error) {
    return RC::GENERIC_ERROR;
  }
  return RC::SUCCESS;
}

static bool
check_condition_attr(const std::unordered_map<std::string, Table *> &relations,
                     const char *table_name, const char *field_name) {
  bool multi_flag = relations.size() > 1;
  Table *table = nullptr;
  if (multi_flag) {
    if (table_name == nullptr) {
      LOG_ERROR("SQL syntax error: need to write relation name explicitly");
      return false;
    }
    auto res = relations.find(table_name);
    if (res == relations.end()) {
      LOG_ERROR("SQL semantic error: table %s does not exist", table_name);
      return false;
    }
    table = res->second;
  } else { // 单表情况
    table = relations.begin()->second;
  }
  if (!match_field(table, field_name)) {
    return false;
  }
  return true;
}

static RC
check_condtions(std::unordered_map<std::string, Table *> &relations,
                std::unordered_map<std::string, TupleSchema> &mini_schema,
                const Condition conds[], size_t cond_num) {
  bool error = false;
  for (size_t i = 0; i < cond_num; i++) {
    const Condition &cond = conds[i];
    if (cond.left_is_attr == 1) {
      const char *table_name = cond.left_attr.relation_name;
      const char *field_name = cond.left_attr.attribute_name;
      if (!check_condition_attr(relations, table_name, field_name)) {
        error = true;
        break;
      }
    }
    if (cond.right_is_attr == 1) {
      const char *table_name = cond.right_attr.relation_name;
      const char *field_name = cond.right_attr.attribute_name;
      if (!check_condition_attr(relations, table_name, field_name)) {
        error = true;
        break;
      }
    }
    // 该条件元数据检查通过
    if (relations.size() > 1 && cond.right_is_attr == 1 &&
        cond.left_is_attr == 1) {
      // 如果两表名字不同，说明最底层映射不可丢弃该列
      const char *left_table = cond.left_attr.relation_name;
      const char *right_table = cond.right_attr.relation_name;
      if (strcmp(left_table, right_table) == 0) {
        continue;
      }

      const char *left_field = cond.left_attr.attribute_name;
      const char *right_field = cond.right_attr.attribute_name;
      schema_add_field(relations[left_table], left_field,
                       mini_schema[left_table]);
      schema_add_field(relations[right_table], right_field,
                       mini_schema[right_table]);
    }
  }

  if (error) {
    return RC::GENERIC_ERROR;
  }
  return RC::SUCCESS;
}

static RC
check_join_table(const TableRef *ref, const char *db,
                 std::unordered_map<std::string, Table *> &relations,
                 std::unordered_map<std::string, TupleSchema> &mini_schema) {
  RC rc = RC::SUCCESS;
  if (ref == nullptr) {
    return rc;
  }

  // 1. 右结点表是否存在
  const char *table_name = ref->relation_name;
  Table *table = DefaultHandler::get_default().find_table(db, table_name);
  if (table == nullptr) {
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  relations[table_name] = table;

  // 2. 再查左结点
  rc = check_join_table(ref->child, db, relations, mini_schema);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  // 子结点中的表信息已经收集完毕
  // 3. 检查 join condition
  return check_condtions(relations, mini_schema, ref->conditions,
                         ref->cond_num);
}

RC ExecuteStage::resolve_select(
    const char *db, const Selects &selects,
    std::unordered_map<std::string, Table *> &relations,
    std::unordered_map<std::string, TupleSchema> &mini_schema) {
  RC rc = RC::SUCCESS;
  // 1. 检查 from clause
  // 关系一定要存在
  for (int i = selects.ref_num - 1; i >= 0; i--) {
    const TableRef &ref = selects.references[i];
    const char *table_name = ref.relation_name;
    if (ref.is_join) {
      check_join_table(&ref, db, relations, mini_schema);
    } else {
      // normal table reference
      Table *table = DefaultHandler::get_default().find_table(db, table_name);
      if (table == nullptr) {
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }
      relations[table_name] = table;
    }
  }

  // 其实不用检查，因为SQL parser不允许from clause为空
  if (relations.size() == 0) {
    return RC::SQL_SYNTAX;
  }
  // 2. 检查 select clause
  // 属性名：多表必须T.A，T.*；单表A, *，单表情况下不允许多个*
  // 聚合函数参数：另有规定，例如AVG()不能测日期和字符串
  rc = check_select_clause(relations, selects);
  if (rc != RC::SUCCESS) {
    return RC::SQL_SYNTAX;
  }
  // 3. 检查condition
  // ConditionFilter中有类型转换和检查，这里不用做
  return check_condtions(relations, mini_schema, selects.conditions,
                         selects.condition_num);
}

static void
get_mini_schema(std::unordered_map<std::string, Table *> &relations,
                std::unordered_map<std::string, TupleSchema> &mini_schema,
                const Selects &selects) {
  Table *table = nullptr;
  // 扫描select clause，这是一定要添加的
  for (int i = selects.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.attributes[i];
    const char *table_name = attr.relation_name;
    const char *field_name = attr.attribute_name;
    // 特殊情况：多表 '*' 'COUNT(*)'
    // 这里不能将COUNT(*)优化为COUNT(col)，不然NULL可能出错
    if (strcmp("*", field_name) == 0 && table_name == nullptr) {
      for (auto &p : relations) {
        TupleSchema::from_table(p.second, mini_schema[p.first], false);
      }
      break;
    }
    table = relations.begin()->second;
    if (relations.size() > 1) {
      table = relations[attr.relation_name];
    }
    // 'T.*'
    if (strcmp("*", field_name) == 0) {
      TupleSchema::from_table(table, mini_schema[table->name()], false);
      continue;
    }
    // 'T.A' 'A' 'func(T.A)' 'func(A)'
    schema_add_field(table, field_name, mini_schema[table->name()]);
  }
}

RC ExecuteStage::do_join_table(
    const TableRef *ref, Trx *trx, const Selects &selects,
    std::unordered_map<std::string, SelectExeNode *> &nodes, TupleSet &res) {
  RC rc = RC::SUCCESS;
  if (ref->child == nullptr) {
    // 叶子节点
    nodes[ref->relation_name]->execute(res);
    return rc;
  }
  // 内部节点
  rc = do_join_table(ref->child, trx, selects, nodes, res);
  TupleSet tr;
  nodes[ref->relation_name]->execute(tr);
  // 连接res和tr
  JoinExeNode *join_node = new JoinExeNode;
  rc = create_join_executor(trx, ref->conditions, ref->cond_num, res, tr,
                            *join_node);
  if (rc != RC::SUCCESS) {
    delete join_node;
    return rc;
  }
  join_node->execute(res);
  delete join_node;
  // JoinExeNode都是用完立刻释放
  return rc;
}

// 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql,
                           SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;

  // 0.1 优先检查元数据
  std::unordered_map<std::string, Table *> relations;
  std::unordered_map<std::string, TupleSchema> mini_schema;
  rc = resolve_select(db, selects, relations, mini_schema);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
    return rc;
  }
  // 0.2 收集所有关系的最简底层schema
  // condition部分已在resolve_select中顺便收集
  get_mini_schema(relations, mini_schema, selects);

  // 1.1 生成所有出现relation的最简select执行节点
  std::unordered_map<std::string, SelectExeNode *> select_nodes;
  for (auto &p : relations) {
    Table *table = p.second;
    SelectExeNode *select_node = new SelectExeNode;
    rc = create_selection_executor(trx, selects, table, mini_schema,
                                   *select_node, relations.size() > 1);
    if (rc != RC::SUCCESS) {
      delete select_node;
      for (auto &tmp_node : select_nodes) {
        delete tmp_node.second;
      }
      return rc;
    }
    select_nodes[p.first] = select_node;
  }

  // 1.2 按照from clasue执行ExecutionNode
  // （Join table实质是SelectExeNode + JoinExeNode）
  std::vector<TupleSet> tuple_sets;
  for (int i = selects.ref_num - 1; i >= 0; i--) {
    const TableRef &ref = selects.references[i];
    TupleSet tuple_set;
    if (ref.is_join != 1) {
      rc = select_nodes[ref.relation_name]->execute(tuple_set);
    } else {
      rc = do_join_table(&ref, trx, selects, select_nodes, tuple_set);
    }
    if (rc != RC::SUCCESS) {
      // 有一个失败则释放所有底层select节点
      for (auto &tmp_node : select_nodes) {
        delete tmp_node.second;
      }
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  std::stringstream ss;
  TupleSet tuple_set = std::move(tuple_sets[0]);
  if (tuple_sets.size() > 1) {
    // *2. 本次查询了多张表（不一定是不同表），需要做join操作
    for (size_t i = 0; i + 1 < tuple_sets.size(); i++) {
      JoinExeNode *join_node = new JoinExeNode;
      rc = create_join_executor(trx, selects.conditions, selects.condition_num,
                                tuple_set, tuple_sets[i + 1], *join_node);
      join_node->execute(tuple_set);
      delete join_node;
    }
  }
  // 3. 重读一边select clasue得到最后的输出范式(out_schema)做映射
  // （程序运行到这里不会有select clause语义错误）
  TupleSchema out_schema;
  out_schema.set_multi_flag(relations.size() > 1);
  for (int i = selects.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.attributes[i];
    const char *table_name = attr.relation_name;
    if (attr.func == COLUMN && table_name == nullptr &&
        strcmp("*", attr.attribute_name) == 0) {
      // 特殊情况：*
      // 所有关系的属性都要包含，恰好等于笛卡尔积的结果schema
      out_schema.append(tuple_set.get_schema());
      continue;
    }
    // 该schema_add_field可重添加字段
    Table *table = relations.begin()->second;
    if (table_name != nullptr) {

      table = relations[table_name];
    }
    schema_add_field(table, attr.func, attr.attribute_name, out_schema);
  }
  ProjectExeNode project_node;
  project_node.init(trx, tuple_set, std::move(out_schema));
  project_node.execute(tuple_set);
  tuple_set.print(ss);

  for (auto &tmp_node : select_nodes) {
    delete tmp_node.second;
  }
  session_event->set_response(ss.str());
  return rc;
}

RC create_join_executor(Trx *trx, const Condition conds[], size_t cond_num,
                        TupleSet &tl, TupleSet &tr, JoinExeNode &join_node) {
  // 列出和这两张表相关的condition
  std::vector<TupleFilter *> filters;
  for (size_t i = 0; i < cond_num; i++) {
    const Condition &cond = conds[i];
    if (cond.left_is_attr == 0 || cond.right_is_attr == 0) {
      continue;
    }
    int left_attr_idx_in_tl = tl.get_schema().index_of_field(
        cond.left_attr.relation_name, cond.left_attr.attribute_name);
    int left_atrr_idx_in_tr = tr.get_schema().index_of_field(
        cond.left_attr.relation_name, cond.left_attr.attribute_name);

    // 如果cond的左属性，
    // 1. 既在leftTupleSet（简记为tl）又在tr中，说明不是join考虑的cond
    // 2. 既不在tl又不在tr中，说明该cond与两个中间表无关
    if ((left_atrr_idx_in_tr == -1 && left_attr_idx_in_tl == -1) ||
        (left_atrr_idx_in_tr != -1 && left_attr_idx_in_tl != -1)) {
      continue;
    }
    int right_attr_idx_in_tl = tl.get_schema().index_of_field(
        cond.right_attr.relation_name, cond.right_attr.attribute_name);
    int right_attr_idx_in_tr = tr.get_schema().index_of_field(
        cond.right_attr.relation_name, cond.right_attr.attribute_name);

    if (left_attr_idx_in_tl != -1 && right_attr_idx_in_tr != -1) {
      filters.push_back(new TupleFilter(left_attr_idx_in_tl,
                                        right_attr_idx_in_tr, cond.comp));
    } else if (left_atrr_idx_in_tr != -1 && right_attr_idx_in_tl != -1) {
      filters.push_back(new TupleFilter(right_attr_idx_in_tl,
                                        left_atrr_idx_in_tr, cond.comp));
    }
  }
  return join_node.init(trx, std::move(tl), std::move(tr), std::move(filters));
}

bool match_table(bool multi_flag, const char *table_name_in_condition,
                 const char *table_name_to_match) {
  if (table_name_in_condition != nullptr) {
    return 0 == strcmp(table_name_in_condition, table_name_to_match);
  }
  // 没有显式表名
  return multi_flag == true;
}

static RC add_filter(const Condition conds[], size_t cond_num, Table *table,
                     std::vector<DefaultConditionFilter *> &cond_filters,
                     bool multi_flag) {
  RC rc = RC::SUCCESS;
  for (size_t i = 0; i < cond_num; i++) {
    const Condition &cond = conds[i];
    if ((cond.left_is_attr == 0 && cond.right_is_attr == 0) || // 两边都是值
        (cond.left_is_attr == 1 && cond.right_is_attr == 0 &&
         match_table(multi_flag, cond.left_attr.relation_name,
                     table->name())) || // 左边是属性右边是值
        (cond.left_is_attr == 0 && cond.right_is_attr == 1 &&
         match_table(multi_flag, cond.right_attr.relation_name,
                     table->name())) || // 左边是值，右边是属性名
        (cond.left_is_attr == 1 && cond.right_is_attr == 1 &&
         match_table(multi_flag, cond.left_attr.relation_name, table->name()) &&
         match_table(multi_flag, cond.right_attr.relation_name,
                     table->name())) // 左右都是属性名，并且表名都符合
    ) {
      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      rc = condition_filter->init(*table, cond);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter *&filter : cond_filters) {
          delete filter;
        }
        return rc;
      }
      cond_filters.push_back(condition_filter);
    }
  }
  return rc;
}

static RC create_filters_in_join_table(
    const TableRef *ref, Table *table,
    std::vector<DefaultConditionFilter *> &cond_filters, bool multi_flag) {
  RC rc = RC::SUCCESS;
  if (ref->child == nullptr) {
    return rc;
  }
  rc = add_filter(ref->conditions, ref->cond_num, table, cond_filters,
                  multi_flag);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  return create_filters_in_join_table(ref->child, table, cond_filters,
                                      multi_flag);
}

// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_selection_executor(
    Trx *trx, const Selects &selects, Table *table,
    std::unordered_map<std::string, TupleSchema> &mini_schema,
    SelectExeNode &select_node, bool multi_flag) {
  const char *table_name = table->name();
  std::vector<DefaultConditionFilter *> cond_filters;
  // 找出仅与此表相关的过滤条件
  // 1. join table中
  for (int i = selects.ref_num - 1; i >= 0; i--) {
    const TableRef &ref = selects.references[i];
    if (ref.is_join == 1) {
      create_filters_in_join_table(&ref, table, cond_filters, multi_flag);
    }
  }

  // 2. where clause中
  add_filter(selects.conditions, selects.condition_num, table, cond_filters,
             multi_flag);
  TupleSchema scm = mini_schema[table_name];
  return select_node.init(trx, table, std::move(scm), std::move(cond_filters));
}
