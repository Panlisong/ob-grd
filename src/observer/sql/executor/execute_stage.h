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

#ifndef __OBSERVER_SQL_EXECUTE_STAGE_H__
#define __OBSERVER_SQL_EXECUTE_STAGE_H__

#include "common/seda/stage.h"
#include "rc.h"
#include "sql/executor/execution_node.h"
#include "sql/executor/tuple.h"
#include "sql/parser/parse.h"
#include "storage/common/table.h"
#include <unordered_map>

class SessionEvent;
typedef std::unordered_map<std::string, TupleSchema> RelAttrTable;
typedef std::unordered_map<std::string, Table *> RelationTable;
typedef std::unordered_map<std::string, SelectExeNode *> NodeTable;

class ExecuteStage : public common::Stage {
public:
  ~ExecuteStage();
  static Stage *make_stage(const std::string &tag);

protected:
  // common function
  ExecuteStage(const char *tag);
  bool set_properties() override;

  bool initialize() override;
  void cleanup() override;
  void handle_event(common::StageEvent *event) override;
  void callback_event(common::StageEvent *event,
                      common::CallbackContext *context) override;

  void handle_request(common::StageEvent *event);

  /**
   * 先收集Select语句中出现的所有关系，建立RelationTable
   * 关系名->Table Object
   */
  RC join_table_relations_init(const TableRef *ref);
  RC relations_init(const Selects &selects);

  RC resolve_select_clause(Selects &selects, RelationTable &outer,
                           RelationTable &cur, bool multi);
  RC resolve_join_table(TableRef *ref, RelationTable &outer,
                        RelationTable &cur);
  RC resolve_condtions(RelationTable &outer, RelationTable &cur,
                       std::vector<TableRef *> &refs,
                       const ConditionList *conds, bool multi);
  RC resolve_select(Selects &selects, RelationTable &relations);

  RC do_select(Query *sql, SessionEvent *session_event);

protected:
private:
  Stage *default_storage_stage_ = nullptr;
  Stage *mem_storage_stage_ = nullptr;
  std::string cur_db_;
  RelationTable relations_;
};

#endif //__OBSERVER_SQL_EXECUTE_STAGE_H__
