/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/13.
//

#ifndef __OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_
#define __OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_

#include "sql/executor/tuple.h"
#include "storage/common/condition_filter.h"
#include <vector>

class Table;
class Trx;

class ExecutionNode {
public:
  ExecutionNode() = default;
  virtual ~ExecutionNode() = default;

  virtual RC execute(TupleSet &tuple_set) = 0;
};

class SelectExeNode : public ExecutionNode {
public:
  SelectExeNode();
  virtual ~SelectExeNode();

  RC init(Trx *trx, Table *table, TupleSchema &&tuple_schema,
          std::vector<DefaultConditionFilter *> &&condition_filters);

  RC execute(TupleSet &tuple_set) override;

private:
  Trx *trx_ = nullptr;
  Table *table_;
  TupleSchema tuple_schema_;
  std::vector<DefaultConditionFilter *> condition_filters_;
};

class JoinExeNode : public ExecutionNode {
public:
  JoinExeNode();
  virtual ~JoinExeNode();

  RC init(Trx *trx, TupleSet &tl, TupleSet &tr, TupleSchema &&tuple_schema,
          std::vector<TupleFilter *> &&tuple_filters);

  RC execute(TupleSet &tuple_set) override;

private:
  Trx *trx_ = nullptr;
  TupleSet tl_;              //   left tuple set: 待合并的左TupleSet
  TupleSet tr_;              //  right tuple set: 待合并的右TupleSet
  TupleSchema tuple_schema_; //    output schema：输出按照tuple_schema映射
  std::vector<TupleFilter *> tuple_filters_; // Tuple过滤器
};

class ProjectExeNode : public ExecutionNode {
public:
  ProjectExeNode() = default;
  ~ProjectExeNode() = default;

  RC init(Trx *trx, TupleSet &in, TupleSchema &&tuple_schema);

  RC execute(TupleSet &tuple_set) override;

private:
  Trx *trx_ = nullptr;
  TupleSet in_;            //  input tuple set：待映射的TupleSet
  TupleSchema out_schema_; //    output schema：输出按照tuple_schema映射
};
#endif //__OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_
