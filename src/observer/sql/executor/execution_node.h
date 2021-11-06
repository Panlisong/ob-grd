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

  const TupleSchema get_schema() { return tuple_schema_; }

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

  RC init(TupleSet &&tl, TupleSet &&tr,
          std::vector<TupleFilter *> &&tuple_filters);

  RC execute(TupleSet &tuple_set) override;

private:
  TupleSet tl_;              //   left tuple set: 待合并的左TupleSet
  TupleSet tr_;              //  right tuple set: 待合并的右TupleSet
  TupleSchema tuple_schema_; //    output schema：输出按照tuple_schema映射
  std::vector<TupleFilter *> tuple_filters_; // Tuple过滤器
};

class ProjectionDesc {
public:
  ProjectionDesc() = default;
  virtual ~ProjectionDesc();

  RC init(SelectExpr *expr, TupleSchema &product, bool multi);
  const std::string to_string() const { return alias_; }
  const AttrType type() const { return desc_->type(); }
  TupleValue *execute(const Tuple &tuple) { return desc_->execute(tuple); }

private:
  TupleConDescNode *desc_;
  std::string alias_;
};

class ProjectExeNode : public ExecutionNode {
public:
  ProjectExeNode() = default;
  ~ProjectExeNode() = default;

  RC init(TupleSet &&in, TupleSchema &&output,
          std::vector<ProjectionDesc *> &&descs);

  RC execute(TupleSet &tuple_set) override;

private:
  RC execute_aggregate(TupleSet &tuple_set);

  TupleSet in_;            //  input tuple set：待映射的TupleSet
  TupleSchema out_schema_; //  output schema：输出按照tuple_schema映射
  std::vector<ProjectionDesc *> descs_;
  bool has_aggregate_ = false; //  select clasue 中是否有聚合函数
  bool only_count_ = true;
};
#endif //__OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_
