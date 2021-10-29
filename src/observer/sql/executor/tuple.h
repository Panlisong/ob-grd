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
  void add(int value, bool is_null);
  void add(float value, bool is_null);
  void add(time_t value, bool is_null);
  void add(const char *s, int len, bool is_null);

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
             const char *field_name)
      : type_(type), func_(func), table_name_(table_name),
        field_name_(field_name) {}

  AttrType type() const { return type_; }
  FuncName func() const { return func_; }

  const char *table_name() const { return table_name_.c_str(); }
  const char *field_name() const { return field_name_.c_str(); }

  std::string to_string() const;

private:
  AttrType type_;
  FuncName func_;
  std::string table_name_;
  std::string field_name_;
};

class TupleSchema {
public:
  TupleSchema() = default;
  ~TupleSchema() = default;

  void add(AttrType type, FuncName func, const char *table_name,
           const char *field_name);
  void add_if_not_exists(AttrType type, FuncName func, const char *table_name,
                         const char *field_name);
  // void merge(const TupleSchema &other);
  void append(const TupleSchema &other);

  const std::vector<TupleField> &fields() const { return fields_; }

  const TupleField &field(int index) const { return fields_[index]; }

  int index_of_field(const char *table_name, const char *field_name) const;
  void clear() { fields_.clear(); }

  void print(std::ostream &os) const;

  void set_multi_flag(bool flag) { multi_flag_ = flag; }

public:
  static void from_table(const Table *table, TupleSchema &schema,
                         bool repeatable);

private:
  std::vector<TupleField> fields_;
  bool multi_flag_ = false;
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

  void print(std::ostream &os) const;

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

      switch (field_meta->type()) {
      case INTS: {
        int value = *(int *)(record + offset);
        tuple.add(value, is_null);
      } break;
      case FLOATS: {
        float value = *(float *)(record + offset);
        tuple.add(value, is_null);
      } break;
      case CHARS: {
        const char *s = record + offset; // 现在当做Cstring来处理
        tuple.add(s, strlen(s), is_null);
      } break;
      case DATES: {
        time_t value = *(time_t *)(record + offset);
        tuple.add(value, is_null);
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

class TupleFilter {
public:
  TupleFilter(int left_index, int right_index, CompOp op);
  bool filter(const Tuple &tl, const Tuple &tr);

private:
  // 一个TupleFilter处理一个Condition，类似ConditionFilter
  // 用于处理形如"R.x op S.y"这样的Condition

  int left_index_;  // 属性x在左Tuple中的索引
  int right_index_; // 属性y在右Tuple中的索引
  CompOp op_;
};
#endif //__OBSERVER_SQL_EXECUTOR_TUPLE_H_
