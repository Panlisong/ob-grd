/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/7.
//

#ifndef __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_
#define __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_

#include "rc.h"
#include "sql/executor/tuple.h"
#include "sql/parser/parse.h"
#include <memory>

struct Record;
class Table;

class ConDescNode {
public:
  ConDescNode() = default;
  virtual ~ConDescNode() = 0;
  virtual std::shared_ptr<TupleValue> execute(const Record &rec) = 0;

  void set_init_type(AttrType type) { init_type_ = type; }
  AttrType get_init_type() { return init_type_; }

  void set_type(AttrType type) { type_ = type; }
  const AttrType type() const { return type_; }
  bool is_null() { return type_ == ATTR_NULL; }

private:
  AttrType type_;
  AttrType init_type_;
};

class ConDescInternal : public ConDescNode {
public:
  ConDescInternal() = default;
  ConDescInternal(ArithOp op, ConDescNode *left, ConDescNode *right);
  virtual ~ConDescInternal();
  virtual std::shared_ptr<TupleValue> execute(const Record &rec) override;

  void *compute(void *lv, void *rv);

private:
  ArithOp op_;
  ConDescNode *left_ = nullptr;
  ConDescNode *right_ = nullptr;
};

class ConDescUnary : public ConDescInternal {
public:
  ConDescUnary(ArithOp op, ConDescNode *expr);
  virtual ~ConDescUnary();
  virtual std::shared_ptr<TupleValue> execute(const Record &rec) override;

private:
  ArithOp op_;
  ConDescNode *expr_ = nullptr;
};

class ConDescAttr : public ConDescNode {
public:
  ConDescAttr(AttrType type, int length, int offset, int column)
      : length_(length), offset_(offset), column_(column) {
    set_init_type(type);
    set_type(type);
  }
  virtual ~ConDescAttr();
  virtual std::shared_ptr<TupleValue> execute(const Record &rec) override;

  const int length() const { return length_; }
  const int offset() const { return offset_; }

  void get_value_from_data(char *data, void *&value);

private:
  int length_; // 如果是属性，表示属性值长度
  int offset_; // 如果是属性，表示在记录中的偏移量
  int column_;
};

class ConDescValue : public ConDescNode {
public:
  ConDescValue(AttrType type, std::shared_ptr<TupleValue> value) {
    set_init_type(type);
    set_type(type);
    value_ = value;
  }
  virtual ~ConDescValue();
  virtual std::shared_ptr<TupleValue> execute(const Record &rec) override;

private:
  std::shared_ptr<TupleValue> value_;
};

class ConDescSubquery : public ConDescNode {
public:
  ConDescSubquery() = default;
  virtual ~ConDescSubquery();
  virtual std::shared_ptr<TupleValue> execute(const Record &rec) override;

  RC init(Trx *trx, Selects *subquery);

  bool contains(std::shared_ptr<TupleValue> tuple_value);

  int subquery_size() { return values_.size(); }

  int compare(std::shared_ptr<TupleValue> tuple_value);

  std::shared_ptr<TupleValue> get_value_in(int index) { return values_[index]; }

private:
  Trx *trx_;
  Selects *select_;
  std::vector<std::shared_ptr<TupleValue>> values_;
};

class ConditionFilter {
public:
  virtual ~ConditionFilter();

  /**
   * Filter one record
   * @param rec
   * @return true means match condition, false means failed to match.
   */
  virtual bool filter(const Record &rec, RC &ret) const = 0;
};

class DefaultConditionFilter : public ConditionFilter {
public:
  DefaultConditionFilter(Table &table);
  virtual ~DefaultConditionFilter();

  RC init(ConDescNode *left, ConDescNode *right, CompOp comp_op);
  RC init(Table &table, const Condition &condition, Trx *trx);

  virtual bool filter(const Record &rec, RC &ret) const;
  bool subquery_filter(const Record &rec, RC &ret) const;
  bool two_subquery_filter(const Record &rec, RC &ret) const;
  bool one_subquery_filter(const Record &rec, RC &ret) const;
  bool non_subquery_filter(const Record &rec) const;

public:
  const ConDescNode *left() const { return left_; }

  const ConDescNode *right() const { return right_; }

  CompOp comp_op() const { return comp_op_; }

private:
  typedef std::pair<ConDescNode *, SelectExpr *> DSEP;
  typedef std::pair<ConDescNode *, ConditionExpr *> DCEP;
  ConDescNode *left_ = nullptr;
  ConDescNode *right_ = nullptr;
  CompOp comp_op_ = NO_OP;
  std::vector<DSEP> bind_select_exprs_;
  std::vector<DCEP> bind_cond_exprs_;
  Table &table_;
};

class CompositeConditionFilter : public ConditionFilter {
public:
  CompositeConditionFilter() = default;
  virtual ~CompositeConditionFilter();

  RC init(const ConditionFilter *filters[], int filter_num);
  RC init(Trx *trx, Table &table, const ConditionList *conditions,
          int condition_num);
  virtual bool filter(const Record &rec, RC &ret) const;

public:
  int filter_num() const { return filter_num_; }
  const ConditionFilter &filter(int index) const { return *filters_[index]; }

private:
  RC init(const ConditionFilter *filters[], int filter_num, bool own_memory);

private:
  const ConditionFilter **filters_ = nullptr;
  int filter_num_ = 0;
  bool memory_owner_ = false; // filters_的内存是否由自己来控制
};

#endif // __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_
