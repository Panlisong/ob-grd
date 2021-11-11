/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/14.
//

#ifndef __OBSERVER_SQL_EXECUTOR_TUPLE_H_
#define __OBSERVER_SQL_EXECUTOR_TUPLE_H_

#include <memory>
#include <vector>

#include "common/log/log.h"
#include "sql/executor/value.h"
#include "sql/parser/parse.h"
#include "storage/common/table.h"

class Table;

class Tuple {
public:
  Tuple() = default;

  Tuple(const Tuple &other);

  ~Tuple();

  Tuple(Tuple &&other) noexcept;
  Tuple &operator=(Tuple &&other) noexcept;

  void add(TupleValue *value);
  void add(const std::shared_ptr<TupleValue> &other);
  void add(int value);
  void add(float value);
  void add(time_t value);
  void add(const char *s, int len);
  void add();

  void append(const Tuple &other);

  const std::vector<std::shared_ptr<TupleValue>> &values() const {
    return values_;
  }

  int size() const { return values_.size(); }

  const TupleValue &get(int index) const { return *values_[index]; }

  const std::shared_ptr<TupleValue> &get_pointer(int index) const {
    return values_[index];
  }

private:
  std::vector<std::shared_ptr<TupleValue>> values_;
};

class TupleField {
public:
  TupleField(AttrType type, FuncName func, const char *table_name,
             const char *field_name, const char *alias = "")
      : type_(type), func_(func), table_name_(table_name),
        field_name_(field_name), alias_(alias) {}

  AttrType type() const { return type_; }
  FuncName func() const { return func_; }

  const char *table_name() const { return table_name_.c_str(); }
  const char *field_name() const { return field_name_.c_str(); }
  const char *alias() const { return alias_.c_str(); }
  void set_alias(std::string alias) { alias_ = alias; }

  std::string to_string() const;

private:
  AttrType type_;
  FuncName func_;
  std::string table_name_;
  std::string field_name_;
  std::string alias_;
};

class TupleSchema {
public:
  TupleSchema() = default;
  ~TupleSchema() = default;

  void add(AttrType type, FuncName func, const char *table_name,
           const char *field_name, const char *alias = "");
  void add_if_not_exists(AttrType type, FuncName func, const char *table_name,
                         const char *field_name, const char *alias = "");

  void merge(const TupleSchema &other);

  void append(const TupleSchema &other);

  const std::vector<TupleField> &fields() const { return fields_; }

  const TupleField &field(int index) const { return fields_[index]; }

  bool contains_all(const TupleSchema &other) const;
  int index_of_field(const char *table_name, const char *field_name) const;
  void clear() { fields_.clear(); }

  void print(std::ostream &os, bool multi) const;

public:
  static void from_table(const Table *table, TupleSchema &schema,
                         bool repeatable);

private:
  std::vector<TupleField> fields_;
};

class TupleSet {
public:
  TupleSet() = default;
  TupleSet(TupleSet &&other);
  explicit TupleSet(const TupleSchema &schema) : schema_(schema) {}
  TupleSet &operator=(TupleSet &&other);

  ~TupleSet() = default;

  void set_schema(const TupleSchema &schema);

  const TupleSchema &get_schema() const;

  void add(Tuple &&tuple);

  void clear();

  bool is_empty() const;
  int size() const;
  int not_null_size(int column) const;

  const Tuple &get(int index) const;
  const std::vector<Tuple> &tuples() const;

  void print(std::ostream &os, bool multi) const;

public:
  const TupleSchema &schema() const { return schema_; }

private:
  std::vector<Tuple> tuples_;
  TupleSchema schema_;
};

class TupleRecordConverter {
public:
  TupleRecordConverter(Table *table, TupleSet &tuple_set);

  static Tuple get_tuple(const char *record, Table *table,
                         const TupleSchema &schema) {
    Tuple tuple;
    const TableMeta &table_meta = table->table_meta();
    for (const TupleField &field : schema.fields()) {
      const FieldMeta *field_meta = table_meta.field(field.field_name());
      assert(field_meta != nullptr);
      int offset = field_meta->offset();
      int column = table->find_column_by_offset(offset);
      int32_t *null_field = (int32_t *)(record + table->null_field_offset());
      bool is_null = ((*null_field) & (1 << column)) != 0;

      if (is_null) {
        tuple.add();
        continue;
      }

      switch (field_meta->type()) {
      case INTS: {
        int value = *(int *)(record + offset);
        tuple.add(value);
      } break;
      case FLOATS: {
        float value = *(float *)(record + offset);
        tuple.add(value);
      } break;
      case CHARS: {
        const char *s = record + offset; // 现在当做Cstring来处理
        tuple.add(s, strlen(s));
      } break;
      case DATES: {
        time_t value = *(time_t *)(record + offset);
        tuple.add(value);
      } break;
      case ATTR_TEXT: {
        char *s = new char[4096];
        memset(s, 0, 4096);
        int remain_len = 4;
        memcpy(s, record + offset, remain_len);
        int len = strlen(s);
        if (len < remain_len) {
          tuple.add(s, len);
        } else {
          int page_id = (*(int *)(record + offset + remain_len)) & 0x7FFFFFFF;
          table->select_text(s + remain_len, page_id);
          tuple.add(s, strlen(s));
        }
      } break;
      default: {
        LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
      }
      }
    }
    return tuple;
  }
  void add_record(const char *record);

private:
  Table *table_;
  TupleSet &tuple_set_;
};

class TupleConDescNode {
public:
  TupleConDescNode() = default;
  virtual ~TupleConDescNode() = 0;
  virtual std::shared_ptr<TupleValue> execute(const Tuple &tuple) = 0;

  const AttrType type() const { return type_; }
  void set_type(AttrType type) { type_ = type; }

  std::shared_ptr<TupleValue> value() const { return value_; }
  void set_value(TupleValue *value) { value_.reset(value); }
  void set_value(std::shared_ptr<TupleValue> value) { value_ = value; }

private:
  AttrType type_;
  std::shared_ptr<TupleValue> value_ = nullptr;
};

class TupleConDescInternal : public TupleConDescNode {
public:
  TupleConDescInternal() = default;
  TupleConDescInternal(ArithOp op, TupleConDescNode *left,
                       TupleConDescNode *right);
  virtual ~TupleConDescInternal();
  std::shared_ptr<TupleValue> execute(const Tuple &tuple) override;

private:
  ArithOp op_;
  TupleConDescNode *left_;
  TupleConDescNode *right_;
};

class TupleConDescUnary : public TupleConDescInternal {
public:
  TupleConDescUnary(ArithOp op, TupleConDescNode *expr);
  virtual ~TupleConDescUnary();
  std::shared_ptr<TupleValue> execute(const Tuple &tuple) override;

private:
  ArithOp op_;
  TupleConDescNode *expr_;
};

class TupleConDescAttr : public TupleConDescNode {
public:
  TupleConDescAttr(AttrType type, int index);
  virtual ~TupleConDescAttr();
  std::shared_ptr<TupleValue> execute(const Tuple &tuple) override;

private:
  int index_;
};

class TupleConDescValue : public TupleConDescNode {
public:
  TupleConDescValue(Value *value);
  virtual ~TupleConDescValue();
  std::shared_ptr<TupleValue> execute(const Tuple &tuple) override;
  std::string to_string() { return value()->to_string(); }

private:
};

class TupleConDescSubquery : public TupleConDescNode {
public:
  TupleConDescSubquery() = default;
  virtual ~TupleConDescSubquery();
  std::shared_ptr<TupleValue> execute(const Tuple &tuple) override;

  RC init(TupleSet &&subquery, CompOp op);

  bool is_contains(std::shared_ptr<TupleValue> tuple_value);

  int subquery_size() const { return values_.size(); }

  int compare(std::shared_ptr<TupleValue> tuple_value);

private:
  std::vector<std::shared_ptr<TupleValue>> values_;
};

class TupleFilter {
public:
  TupleFilter();
  virtual ~TupleFilter();
  RC init(TupleSchema &product, const Condition &cond, TupleSet &&left,
          TupleSet &&right);
  bool filter(const Tuple &t);
  bool non_subquery_filter(const Tuple &tuple);
  bool subquery_filter(const Tuple &tuple);

private:
  // 一个TupleFilter处理一个Condition，类似ConditionFilter
  // 用于处理形如"R.x op S.y"这样的Condition

  CompOp op_;
  TupleConDescNode *left_;
  TupleConDescNode *right_;
};
#endif //__OBSERVER_SQL_EXECUTOR_TUPLE_H_
