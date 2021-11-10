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

struct Record;
class Table;

typedef enum ConvertFlag { NO_CONVERT, INT_TO_FLOATS } ConvertFlag;

class ConDescNode {
public:
  ConDescNode() = default;
  virtual ~ConDescNode() = 0;
  virtual void *execute(const Record &rec) = 0;

  void set_init_type(AttrType type) { init_type_ = type; }
  AttrType get_init_type() { return init_type_; }

  void set_type(AttrType type) { type_ = type; }
  const AttrType type() const { return type_; }
  bool is_null() { return type_ == ATTR_NULL; }

  void set_value(void *value) {
    if (value_ != nullptr) {
      free(value_);
      value_ = nullptr;
    }
    value_ = value;
  }
  void *value() const { return value_; }

private:
  AttrType type_;
  AttrType init_type_;
  void *value_ = nullptr;
};

class ConDescInternal : public ConDescNode {
public:
  ConDescInternal(ArithOp op, ConDescNode *left, ConDescNode *right);
  virtual ~ConDescInternal();
  void *execute(const Record &rec) override;

  void *compute(void *lv, void *rv);

private:
  ArithOp op_;
  ConDescNode *left_;
  ConDescNode *right_;
};

class ConDescAttr : public ConDescNode {
public:
  ConDescAttr(AttrType type, int length, int offset, int column)
      : length_(length), offset_(offset), column_(column) {
    set_init_type(type);
    set_type(type);
  }
  virtual ~ConDescAttr();
  void *execute(const Record &rec) override;

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
  ConDescValue(AttrType type, void *value) {
    set_init_type(type);
    set_type(type);
    set_value(value);
  }
  virtual ~ConDescValue();
  void *execute(const Record &rec) override;
};

class ConDescSubquery : public ConDescNode {
public:
  ConDescSubquery() = default;
  virtual ~ConDescSubquery();
  void *execute(const Record &rec) override;

  RC init(TupleSet &&subquery);

  bool contains(AttrType type, const char *value);

  int subquery_size() { return values_.size(); }

  int compare(char *lvalue, AttrType type);

private:
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
  virtual bool filter(const Record &rec) const = 0;
};

class DefaultConditionFilter : public ConditionFilter {
public:
  DefaultConditionFilter(Table &table);
  virtual ~DefaultConditionFilter();

  RC init(ConDescNode *left, ConDescNode *right, CompOp comp_op);
  RC init(Table &table, const Condition &condition, TupleSet &&left,
          TupleSet &&right);

  virtual bool filter(const Record &rec) const;
  bool subquery_filter(const Record &rec) const;
  bool non_subquery_filter(const Record &rec) const;

public:
  const ConDescNode *left() const { return left_; }

  const ConDescNode *right() const { return right_; }

  CompOp comp_op() const { return comp_op_; }

private:
  ConDescNode *left_;
  ConDescNode *right_;
  CompOp comp_op_ = NO_OP;
  Table &table_;
};

class CompositeConditionFilter : public ConditionFilter {
public:
  CompositeConditionFilter() = default;
  virtual ~CompositeConditionFilter();

  RC init(const ConditionFilter *filters[], int filter_num);
  RC init(Trx *trx, Table &table, const ConditionList *conditions,
          int condition_num);
  virtual bool filter(const Record &rec) const;

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
