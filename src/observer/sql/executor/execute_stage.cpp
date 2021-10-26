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
#include "sql/executor/execution_node.h"
#include "sql/executor/tuple.h"
#include "sql/parser/parse_defs.h"
#include "storage/common/condition_filter.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/trx/trx.h"

using namespace common;

RC create_selection_executor(Trx *trx, const Selects &selects, const char *db,
                             const char *table_name, SelectExeNode &select_node,
                             TupleSchema &projection);
RC create_join_executor(Trx *trx, const Selects &selects, TupleSet &tl,
                        TupleSet &tr, TupleSchema &tuple_schema,
                        JoinExeNode &join_node);

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

static RC schema_add_field(const char *db, const char *table_name,
                           FuncName func, const char *field_name,
                           TupleSchema &schema) {
  // 先找Table Object
  Table *table = DefaultHandler::get_default().find_table(db, table_name);
  if (nullptr == table) {
    LOG_WARN("No such table [%s] in db [%s]", table_name, db);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  if (func == COLUMN && strcmp(field_name, "*") == 0) {
    // 列名 '*' 或 'T.*'
    TupleSchema::from_table(table, schema);
    return RC::SUCCESS;
  }

  if (func == COUNT_FUNC && strcmp(field_name, "*") == 0) {
    // 特殊情况：count(*)
    schema.add(INTS, func, table->name(), field_name);
    return RC::SUCCESS;
  }

  // func(A) 或 func(T.A) 或 A 或 T.A
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }
  // TODO: 对于聚合函数，参数类型检查应该提前！！
  schema.add(field_meta->type(), func, table->name(), field_meta->name());
  return RC::SUCCESS;
}

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分.
// 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql,
                           SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;
  // 1. 生成与每个关系表的最简select执行节点
  std::vector<SelectExeNode *> select_nodes;
  std::vector<TupleSchema> join_schemas;
  for (int i = selects.relation_num - 1; i >= 0; i--) {
    const char *table_name = selects.relations[i];
    SelectExeNode *select_node = new SelectExeNode;
    TupleSchema schema;
    rc = create_selection_executor(trx, selects, db, table_name, *select_node,
                                   schema);
    if (rc != RC::SUCCESS) {
      delete select_node;
      for (SelectExeNode *&tmp_node : select_nodes) {
        delete tmp_node;
      }
      return rc;
    }
    select_nodes.push_back(select_node);
    join_schemas.push_back(schema);
  }

  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
    return RC::SQL_SYNTAX;
  }

  std::vector<TupleSet> tuple_sets;
  for (SelectExeNode *&node : select_nodes) {
    TupleSet tuple_set;
    rc = node->execute(tuple_set);
    if (rc != RC::SUCCESS) {
      for (SelectExeNode *&tmp_node : select_nodes) {
        delete tmp_node;
      }
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  std::stringstream ss;
  TupleSet tuple_set = std::move(tuple_sets[0]);
  if (tuple_sets.size() > 1) {
    // *2. 本次查询了多张表，需要做join操作
    for (size_t i = 0; i + 1 < tuple_sets.size(); i++) {
      JoinExeNode *join_node = new JoinExeNode;
      join_schemas[0].append(join_schemas[i + 1]);
      TupleSchema scm = join_schemas[0];
      rc = create_join_executor(trx, selects, tuple_set, tuple_sets[i + 1], scm,
                                *join_node);
      join_node->execute(tuple_set);
    }
  }
  // 3. 重读一边RelAttr List得到最后的输出范式(out_schema)做映射
  TupleSchema out_schema;
  for (int i = selects.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.attributes[i];
    if (attr.func == COLUMN && attr.relation_name == nullptr &&
        strcmp("*", attr.attribute_name) == 0) {
      // 特殊情况：*
      // 所有关系的属性都要包含，恰好等于笛卡尔积的结果schema
      out_schema.append(tuple_set.get_schema());
      continue;
    }
    // 该schema_add_field可重添加字段
    const char *table_name = attr.relation_name;
    if (table_name == nullptr) {
      // 程序运行到这里不会有RelAttr List语义错误
      // 说明是单表查询
      table_name = selects.relations[0];
    }
    schema_add_field(db, table_name, attr.func, attr.attribute_name,
                     out_schema);
  }
  ProjectExeNode project_node;
  project_node.init(trx, tuple_set, std::move(out_schema));
  project_node.execute(tuple_set);
  tuple_set.print(ss);

  for (SelectExeNode *&tmp_node : select_nodes) {
    delete tmp_node;
  }
  session_event->set_response(ss.str());
  return rc;
}

bool match_table(const Selects &selects, const char *table_name_in_condition,
                 const char *table_name_to_match) {
  if (table_name_in_condition != nullptr) {
    return 0 == strcmp(table_name_in_condition, table_name_to_match);
  }

  return selects.relation_num == 1;
}

static RC schema_add_field(Table *table, const char *field_name,
                           TupleSchema &schema) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }

  // 生成初始Select执行节点使用，只生成最简schema
  schema.add_if_not_exists(field_meta->type(), COLUMN, table->name(),
                           field_meta->name());
  return RC::SUCCESS;
}

RC create_join_executor(Trx *trx, const Selects &selects, TupleSet &tl,
                        TupleSet &tr, TupleSchema &tuple_schema,
                        JoinExeNode &join_node) {
  // 列出和这两张表相关的condition
  std::vector<TupleFilter *> filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &cond = selects.conditions[i];
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
  return join_node.init(trx, tl, tr, std::move(tuple_schema),
                        std::move(filters));
}

// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_selection_executor(Trx *trx, const Selects &selects, const char *db,
                             const char *table_name, SelectExeNode &select_node,
                             TupleSchema &projection) {
  // 列出跟这张表关联的Attr
  TupleSchema schema;
  Table *table = DefaultHandler::get_default().find_table(db, table_name);
  if (nullptr == table) {
    LOG_WARN("No such table [%s] in db [%s]", table_name, db);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  for (int i = selects.attr_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects.attributes[i];
    if (nullptr == attr.relation_name ||
        0 == strcmp(table_name, attr.relation_name)) {
      if (0 == strcmp("*", attr.attribute_name)) {
        // 列出这张表所有字段
        TupleSchema::from_table(table, schema);
        // 由SQL语法可以看出，'*'前后都不可能出现RelAtrr
        // 但是可能出现 "A1, A2, ..., An, *"
        break;
      } else {
        // 不会重复添加
        RC rc = schema_add_field(table, attr.attribute_name, schema);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
    }
  }
  projection = schema;
  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    // 修正schema
    if (condition.left_is_attr == 1 && condition.right_is_attr == 1) {
      bool left_match =
          match_table(selects, condition.left_attr.relation_name, table_name);
      if (left_match ^ match_table(selects, condition.right_attr.relation_name,
                                   table_name)) { // 只有不同是匹配才会进入
        const char *attr_name = left_match
                                    ? condition.left_attr.attribute_name
                                    : condition.right_attr.attribute_name;
        schema_add_field(table, attr_name, schema); // 不会重复添加
      }
    }
    if ((condition.left_is_attr == 0 &&
         condition.right_is_attr == 0) || // 两边都是值
        (condition.left_is_attr == 1 && condition.right_is_attr == 0 &&
         match_table(selects, condition.left_attr.relation_name,
                     table_name)) || // 左边是属性右边是值
        (condition.left_is_attr == 0 && condition.right_is_attr == 1 &&
         match_table(selects, condition.right_attr.relation_name,
                     table_name)) || // 左边是值，右边是属性名
        (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
         match_table(selects, condition.left_attr.relation_name, table_name) &&
         match_table(selects, condition.right_attr.relation_name,
                     table_name)) // 左右都是属性名，并且表名都符合
    ) {
      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      RC rc = condition_filter->init(*table, condition);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter *&filter : condition_filters) {
          delete filter;
        }
        return rc;
      }
      condition_filters.push_back(condition_filter);
    }
  }

  return select_node.init(trx, table, std::move(schema),
                          std::move(condition_filters));
}
