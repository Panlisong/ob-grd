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
#include "sql/executor/value.h"
#include "sql/parser/parse_defs.h"
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

  /**
   * expr@param: select clause中的元素
   * product@param: 需映射Tuple的schema
   * multi@param: 是否为多表（关系到该Projection Description的别名）
   */
  RC init(SelectExpr *expr, const TupleSchema &product, bool multi);
  const std::string to_string() const { return alias_; }
  const AttrType type() const { return desc_->type(); }

  /**
   * tuple@param: 需做映射的tuple
   */
  virtual std::shared_ptr<TupleValue> execute(const Tuple &tuple) {
    return desc_->execute(tuple);
  }

public:
  static RC from_table(Table *table, const TupleSchema &product,
                       std::vector<ProjectionDesc *> &descs, bool multi);
  static ProjectionDesc *get_projection_desc(SelectExpr *expr, TupleSet &in);

private:
  TupleConDescNode *desc_;
  std::string alias_;
};

class AggregateDesc : public ProjectionDesc {
public:
  AggregateDesc() = default;
  virtual std::shared_ptr<TupleValue> execute(const Tuple &tuple) override = 0;
  const std::shared_ptr<TupleValue> value() const { return value_; }
  void set_value(std::shared_ptr<TupleValue> value) { value_ = value; }
  void set_value(TupleValue *value) { value_.reset(value); }

private:
  std::shared_ptr<TupleValue> value_ = nullptr;
};

class MaxDesc : public AggregateDesc {
public:
  MaxDesc() = default;
  std::shared_ptr<TupleValue> execute(const Tuple &tuple) override {
    auto cur = ProjectionDesc::execute(tuple);
    if (value() == nullptr) {
      set_value(cur);
    }
    if (cur->type() == ATTR_NULL) {
      return value();
    }
    if (cur->compare(*value()) > 0) {
      set_value(cur);
    }
    return value();
  }
};

class MinDesc : public AggregateDesc {
public:
  MinDesc() = default;
  std::shared_ptr<TupleValue> execute(const Tuple &tuple) override {
    auto cur = ProjectionDesc::execute(tuple);
    if (value() == nullptr) {
      set_value(cur);
    }
    if (cur->type() == ATTR_NULL) {
      return value();
    }
    if (cur->compare(*value()) < 0) {
      set_value(cur);
    }
    return value();
  }
};

class AvgDesc : public AggregateDesc {
public:
  AvgDesc(int total) : count_(0), total_(total) {
    if (total == 0) {
      set_value(new NullValue());
    } else {
      set_value(new FloatValue(0.0));
    }
  }
  std::shared_ptr<TupleValue> execute(const Tuple &tuple) override {
    auto cur = ProjectionDesc::execute(tuple);
    if (cur->type() == ATTR_NULL) {
      return value();
    }
    // 累加
    count_++;
    TupleValue *res = nullptr;
    if (type() == INTS) {
      int i;
      cur->get_value(&i);
      cur.reset(new FloatValue((float)i));
    }
    cur->compute(value().get(), res, ADD);
    set_value(res);

    if (count_ == total_) {
      // 达到数量时求平均
      FloatValue fv = FloatValue((float)total_);
      value()->compute(&fv, res, DIV);
      set_value(res);
    }
    return value();
  }

private:
  int count_;
  int total_;
};

class CountDesc : public AggregateDesc {
public:
  CountDesc(int count) { set_value(new IntValue(count)); }
  std::shared_ptr<TupleValue> execute(const Tuple &tuple) override {
    return value();
  }
};

class ProjectExeNode : public ExecutionNode {
public:
  ProjectExeNode() = default;
  virtual ~ProjectExeNode();

  RC init(TupleSet &&in, std::vector<ProjectionDesc *> &&descs);

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
