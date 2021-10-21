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
#include "storage/common/condition_filter.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/trx/trx.h"

using namespace common;

void end_trx_if_need(Session *session, Trx *trx, bool all_right);

RC create_selection_executor(Trx *trx, const Selects &selects, const char *db,
                             const char *table_name,
                             SelectExeNode &select_node);

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
  case SCF_INSERT: {
    do_insert(current_db, sql, exe_event->sql_event()->session_event());
    exe_event->done_immediate();
  } break;
  case SCF_UPDATE: {
    do_update(current_db, sql, exe_event->sql_event()->session_event());
    exe_event->done_immediate();
  } break;
  case SCF_DELETE: {
    do_delete(current_db, sql, exe_event->sql_event()->session_event());
    exe_event->done_immediate();
  } break;
  case SCF_CREATE_TABLE: {
    do_create_table(current_db, sql);
    exe_event->done_immediate();
  } break;
  case SCF_SHOW_TABLES: {
    std::string response;
    do_show_tables(current_db, response);
    session_event->set_response(response.c_str());
    exe_event->done_immediate();
  } break;
  case SCF_DESC_TABLE: {
    do_desc_table(current_db, sql, exe_event->sql_event()->session_event());
    exe_event->done_immediate();
  } break;
  case SCF_DROP_TABLE: {
    RC rc = do_drop_table(current_db, sql);
    const char *table_name = sql->sstr.drop_table.relation_name;
    char response[100];

    if (rc == RC::SUCCESS) {
      snprintf(response, 100, "drop table %s success\n", table_name);
    } else if (rc == RC::SCHEMA_TABLE_NOT_EXIST) {
      snprintf(response, 100, "table %s not exists\n", table_name);
    } else {
      snprintf(response, 100, "drop table %s failed but drop it at last\n",
               table_name);
    }
    session_event->set_response(response);
    exe_event->done_immediate();
  } break;
  case SCF_CREATE_INDEX: {
    do_create_index(current_db, sql, exe_event->sql_event()->session_event());
    exe_event->done_immediate();
  } break;
  case SCF_DROP_INDEX: {
    do_drop_index(current_db, sql, exe_event->sql_event()->session_event());
    exe_event->done_immediate();
  } break;
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
    session_event->set_response(strrc(rc));
    exe_event->done_immediate();
  } break;
  case SCF_BEGIN: {
    session_event->get_client()->session->set_trx_multi_operation_mode(true);
    session_event->set_response(strrc(RC::SUCCESS));
    exe_event->done_immediate();
  } break;
  case SCF_COMMIT: {
    Trx *trx = session_event->get_client()->session->current_trx();
    RC rc = trx->commit();
    session_event->get_client()->session->set_trx_multi_operation_mode(false);
    session_event->set_response(strrc(rc));
    exe_event->done_immediate();
  } break;
  case SCF_ROLLBACK: {
    Trx *trx = session_event->get_client()->session->current_trx();
    RC rc = trx->rollback();
    session_event->get_client()->session->set_trx_multi_operation_mode(false);
    session_event->set_response(strrc(rc));
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
        "select [ * | `columns` ] from `table`;\n";
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

void end_trx_if_need(Session *session, Trx *trx, bool all_right) {
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
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
  // 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
  std::vector<SelectExeNode *> select_nodes;
  for (size_t i = 0; i < selects.relation_num; i++) {
    const char *table_name = selects.relations[i];
    SelectExeNode *select_node = new SelectExeNode;
    rc = create_selection_executor(trx, selects, db, table_name, *select_node);
    if (rc != RC::SUCCESS) {
      delete select_node;
      for (SelectExeNode *&tmp_node : select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    }
    select_nodes.push_back(select_node);
  }

  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
    end_trx_if_need(session, trx, false);
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
      end_trx_if_need(session, trx, false);
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  std::stringstream ss;
  if (tuple_sets.size() > 1) {
    // 本次查询了多张表，需要做join操作
  } else {
    // 当前只查询一张表，直接返回结果即可
    tuple_sets.front().print(ss);
  }

  for (SelectExeNode *&tmp_node : select_nodes) {
    delete tmp_node;
  }
  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);
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

  schema.add_if_not_exists(field_meta->type(), table->name(),
                           field_meta->name());
  return RC::SUCCESS;
}

// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_selection_executor(Trx *trx, const Selects &selects, const char *db,
                             const char *table_name,
                             SelectExeNode &select_node) {
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
        break; // 没有校验，给出* 之后，再写字段的错误
      } else {
        // 列出这张表相关字段
        RC rc = schema_add_field(table, attr.attribute_name, schema);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
    }
  }

  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
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

RC ExecuteStage::do_insert(const char *db, Query *sql,
                           SessionEvent *session_event) {
  Inserts insert = sql->sstr.insertion;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  RC rc = DefaultHandler::get_default().insert_record(
      trx, db, insert.relation_name, insert.value_num, insert.values);
  end_trx_if_need(session, trx, rc == RC::SUCCESS);
  return rc;
}

RC ExecuteStage::do_update(const char *db, Query *sql,
                           SessionEvent *session_event) {
  Updates update = sql->sstr.update;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  int updated_count;
  RC rc = DefaultHandler::get_default().update_record(
      trx, db, update.relation_name, update.attribute_name, &update.value,
      update.condition_num, update.conditions, &updated_count);
  end_trx_if_need(session, trx, rc == RC::SUCCESS);
  return rc;
}

RC ExecuteStage::do_delete(const char *db, Query *sql,
                           SessionEvent *session_event) {
  Deletes deletion = sql->sstr.deletion;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  int deleted_count;
  RC rc = DefaultHandler::get_default().delete_record(
      trx, db, deletion.relation_name, deletion.condition_num,
      deletion.conditions, &deleted_count);
  end_trx_if_need(session, trx, rc == RC::SUCCESS);
  return rc;
}

RC ExecuteStage::do_create_table(const char *db, Query *sql) {
  CreateTable create_table = sql->sstr.create_table;
  return DefaultHandler::get_default().create_table(
      db, create_table.relation_name, create_table.attribute_count,
      create_table.attributes);
}

RC ExecuteStage::do_show_tables(const char *db, std::string &result) {
  return DefaultHandler::get_default().show_tables(db, result);
}

RC ExecuteStage::do_desc_table(const char *db, Query *sql,
                               SessionEvent *session_event) {}

RC ExecuteStage::do_drop_table(const char *db, Query *sql) {
  DropTable drop_table = sql->sstr.drop_table;
  return DefaultHandler::get_default().drop_table(db, drop_table.relation_name);
}

RC ExecuteStage::do_create_index(const char *db, Query *sql,
                                 SessionEvent *session_event) {
  CreateIndex create_index = sql->sstr.create_index;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  RC rc = DefaultHandler::get_default().create_index(
      trx, db, create_index.relation_name, create_index.index_name,
      create_index.attribute_name);
  end_trx_if_need(session, trx, rc == RC::SUCCESS);
  return rc;
}

RC ExecuteStage::do_drop_index(const char *db, Query *sql,
                               SessionEvent *session_event) {
  DropIndex drop_index = sql->sstr.drop_index;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  // TODO: drop_index relation_name
  RC rc = DefaultHandler::get_default().drop_index(trx, db, "",
                                                   drop_index.index_name);
  end_trx_if_need(session, trx, rc == RC::SUCCESS);
  return rc;
}