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

#include "sql/executor/tuple.h"
#include "sql/executor/value.h"
#include <memory>
#include <string>

TupleConDescNode *create_cond_desc_node(ConditionExpr *expr,
                                        TupleSchema &product);

Tuple::Tuple(const Tuple &other) {
  LOG_PANIC("Copy constructor of tuple is not supported");
  exit(1);
}

Tuple::Tuple(Tuple &&other) noexcept : values_(std::move(other.values_)) {}

Tuple &Tuple::operator=(Tuple &&other) noexcept {
  if (&other == this) {
    return *this;
  }

  values_.clear();
  values_.swap(other.values_);
  return *this;
}

Tuple::~Tuple() {}

// add (Value && value)
void Tuple::add(TupleValue *value) { values_.emplace_back(value); }
void Tuple::add(const std::shared_ptr<TupleValue> &other) {
  values_.emplace_back(other);
}

void Tuple::add(int value) { add(new IntValue(value)); }

void Tuple::add(float value) { add(new FloatValue(value)); }

void Tuple::add(time_t value) { add(new DateValue(value)); }

void Tuple::add(const char *s, int len) { add(new StringValue(s, len)); }

void Tuple::add() { add(new NullValue()); }

void Tuple::append(const Tuple &other) {
  values_.insert(values_.end(), other.values_.begin(), other.values_.end());
}

////////////////////////////////////////////////////////////////////////////////

std::string TupleField::to_string() const {
  return std::string(table_name_) + "." + field_name_ + std::to_string(type_);
}

////////////////////////////////////////////////////////////////////////////////
void TupleSchema::from_table(const Table *table, TupleSchema &schema,
                             bool repeatable) {
  const char *table_name = table->name();
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = 0; i < field_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      if (repeatable) {
        schema.add(field_meta->type(), COLUMN, table_name, field_meta->name());
      } else {
        schema.add_if_not_exists(field_meta->type(), COLUMN, table_name,
                                 field_meta->name());
      }
    }
  }
}

void TupleSchema::add(AttrType type, FuncName func, const char *table_name,
                      const char *field_name, const char *alias) {
  fields_.emplace_back(type, func, table_name, field_name, alias);
}

void TupleSchema::add_if_not_exists(AttrType type, FuncName func,
                                    const char *table_name,
                                    const char *field_name, const char *alias) {
  for (const auto &field : fields_) {
    if (func == field.func() && 0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
      return;
    }
  }

  add(type, func, table_name, field_name, alias);
}

void TupleSchema::append(const TupleSchema &other) {
  fields_.reserve(fields_.size() + other.fields_.size());
  for (const auto &field : other.fields_) {
    fields_.emplace_back(field);
  }
}

void TupleSchema::merge(const TupleSchema &other) {
  for (const auto &field : other.fields_) {
    add_if_not_exists(field.type(), field.func(), field.table_name(),
                      field.field_name());
  }
}

bool TupleSchema::contains_all(const TupleSchema &other) const {
  for (const auto &field : other.fields_) {
    if (-1 == index_of_field(field.table_name(), field.field_name())) {
      return false;
    }
  }
  return true;
}

int TupleSchema::index_of_field(const char *table_name,
                                const char *field_name) const {
  const int size = fields_.size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = fields_[i];
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
      return i;
    }
  }
  return -1;
}

void TupleSchema::print(std::ostream &os, bool multi) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }
  // TODO: 应该有更好的处理办法
  // 判断有多张表还是只有一张表
  for (auto it = fields_.begin(), end = --fields_.end(); it != end; ++it) {
    os << it->alias() << " | ";
  }

  auto last = fields_.back();
  os << last.alias() << std::endl;
}

/////////////////////////////////////////////////////////////////////////////
TupleSet::TupleSet(TupleSet &&other)
    : tuples_(std::move(other.tuples_)), schema_(other.schema_) {
  other.schema_.clear();
}

TupleSet &TupleSet::operator=(TupleSet &&other) {
  if (this == &other) {
    return *this;
  }

  schema_.clear();
  schema_.append(other.schema_);
  other.schema_.clear();

  tuples_.clear();
  tuples_.swap(other.tuples_);
  return *this;
}

void TupleSet::add(Tuple &&tuple) { tuples_.emplace_back(std::move(tuple)); }

void TupleSet::clear() {
  tuples_.clear();
  schema_.clear();
}

void TupleSet::print(std::ostream &os, bool multi) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }

  schema_.print(os, multi);

  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator
             iter = values.begin(),
             end = --values.end();
         iter != end; ++iter) {
      (*iter)->to_string(os);
      os << " | ";
    }
    values.back()->to_string(os);
    os << std::endl;
  }
}

void TupleSet::set_schema(const TupleSchema &schema) { schema_ = schema; }

const TupleSchema &TupleSet::get_schema() const { return schema_; }

bool TupleSet::is_empty() const { return tuples_.empty(); }

int TupleSet::size() const { return tuples_.size(); }

int TupleSet::not_null_size(int column) const {
  int not_null_size = 0;
  for (auto iter = tuples_.begin(), end = tuples_.end(); iter != end; iter++) {
    if ((*iter).get(column).type() == ATTR_NULL) {
      continue;
    }
    not_null_size++;
  }

  return not_null_size;
}

const Tuple &TupleSet::get(int index) const { return tuples_[index]; }

const std::vector<Tuple> &TupleSet::tuples() const { return tuples_; }

/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table *table, TupleSet &tuple_set)
    : table_(table), tuple_set_(tuple_set) {}

void TupleRecordConverter::add_record(const char *record) {
  Tuple tuple = get_tuple(record, table_, tuple_set_.get_schema());
  tuple_set_.add(std::move(tuple));
}

/////////////////////////////////////////////////////////////////////////////
TupleConDescNode::~TupleConDescNode() {}

TupleConDescInternal::TupleConDescInternal(ArithOp op, TupleConDescNode *left,
                                           TupleConDescNode *right)
    : op_(op), left_(left), right_(right) {
  AttrType lt = left_->type();
  AttrType rt = right_->type();
  if (!is_computable(lt, rt)) {
    // TODO: 不可计算类型如何处理
    set_type(UNDEFINED);
    return;
  }

  if (lt == rt) {
    set_type(lt);
  } else {
    set_type(FLOATS);
  }
}

std::shared_ptr<TupleValue> TupleConDescInternal::execute(const Tuple &tuple) {
  auto lv = left_->execute(tuple);
  auto rv = right_->execute(tuple);
  TupleValue *res = nullptr;
  lv->compute(rv.get(), res, op_);
  set_value(res);
  return value();
}

TupleConDescInternal::~TupleConDescInternal() {
  delete left_;
  delete right_;
}

TupleConDescUnary::TupleConDescUnary(ArithOp op, TupleConDescNode *expr)
    : op_(op), expr_(expr) {}

std::shared_ptr<TupleValue> TupleConDescUnary::execute(const Tuple &tuple) {
  auto v = expr_->execute(tuple);
  TupleValue *res = nullptr;
  IntValue zero = IntValue(0);
  zero.compute(v.get(), res, SUB);
  set_value(res);
  return value();
}

TupleConDescUnary::~TupleConDescUnary() { delete expr_; }

TupleConDescAttr::TupleConDescAttr(AttrType type, int index) : index_(index) {
  set_type(type);
}

std::shared_ptr<TupleValue> TupleConDescAttr::execute(const Tuple &tuple) {
  set_value(tuple.get_pointer(index_));
  std::shared_ptr<TupleValue> v = value();
  return value();
}

TupleConDescAttr::~TupleConDescAttr() {}

TupleConDescValue::TupleConDescValue(Value *value) {
  TupleValue *v = nullptr;
  switch (value->type) {
  case INTS:
    v = new IntValue(*(int *)value->data);
    break;
  case FLOATS:
    v = new FloatValue(*(float *)value->data);
    break;
  case CHARS: {
    const char *str = (char *)value->data;
    v = new StringValue(str, strlen(str));
  } break;
  case DATES:
    v = new DateValue(*(time_t *)value->data);
    break;
  case ATTR_NULL:
    // TODO: null value
    break;
  default:
    LOG_PANIC("Unkown attr type: %d", value->type);
    break;
  }
  set_value(v);
  set_type(value->type);
}

std::shared_ptr<TupleValue> TupleConDescValue::execute(const Tuple &tuple) {
  return value();
}

TupleConDescValue::~TupleConDescValue() {}

RC TupleConDescSubquery::init(TupleSet &&subquery, CompOp op) {
  const auto schema = subquery.get_schema();
  if (schema.fields().size() > 1) {
    // TODO: 子查询列数>1
    return RC::GENERIC_ERROR;
  }

  if (op != MEM_IN && op != MEM_NOT_IN) {
    if (subquery.size() > 1) {
      LOG_ERROR("subquery return multi rows");
      return RC::GENERIC_ERROR;
    }
  }

  set_type(schema.fields().begin()->type());
  for (auto &tuple : subquery.tuples()) {
    values_.emplace_back(tuple.get_pointer(0));
  }
  return RC::SUCCESS;
}

std::shared_ptr<TupleValue> TupleConDescSubquery::execute(const Tuple &tuple) {
  return nullptr;
}

bool TupleConDescSubquery::is_contains(
    std::shared_ptr<TupleValue> tuple_value) {
  for (auto value : values_) {
    if (tuple_value->compare(*value) == 0) {
      return true;
    }
  }
  return false;
}
int TupleConDescSubquery::compare(std::shared_ptr<TupleValue> left_value) {
  TupleValue *right_value = values_[0].get();
  return left_value->compare(*right_value);
}

TupleConDescSubquery::~TupleConDescSubquery() {}

/////////////////////////////////////////////////////////////////////////////
TupleConDescNode *create_cond_desc_node(ConditionExpr *expr,
                                        TupleSchema &product) {
  if (expr->has_subexpr == 0) {
    if (expr->is_attr) {
      RelAttr *attr = expr->attr;
      int i = product.index_of_field(attr->relation_name, attr->attribute_name);
      return new TupleConDescAttr(product.field(i).type(), i);
    } else {
      return new TupleConDescValue(expr->value);
    }
  }
  TupleConDescNode *right = create_cond_desc_node(expr->right, product);
  if (expr->left == nullptr) {
    return new TupleConDescUnary(expr->op, right);
  }
  TupleConDescNode *left = create_cond_desc_node(expr->left, product);
  return new TupleConDescInternal(expr->op, left, right);
}

TupleFilter::TupleFilter() {}

TupleFilter::~TupleFilter() {
  delete left_;
  delete right_;
}

RC TupleFilter::init(TupleSchema &product, const Condition &cond,
                     TupleSet &&left, TupleSet &&right) {
  RC rc = RC::SUCCESS;
  op_ = cond.comp;
  if (cond.left != nullptr) {
    left_ = create_cond_desc_node(cond.left, product);
  }
  if (cond.right != nullptr) {
    right_ = create_cond_desc_node(cond.right, product);
  }
  if (cond.left_subquery != nullptr) {
    TupleConDescSubquery *left_node = new TupleConDescSubquery();
    rc = left_node->init(std::move(left), cond.comp);
    if (rc != RC::SUCCESS) {
      delete left_node;
      return rc;
    }
    left_ = left_node;
  }
  if (cond.right_subquery != nullptr) {
    TupleConDescSubquery *right_node = new TupleConDescSubquery();
    rc = right_node->init(std::move(right), cond.comp);
    if (rc != RC::SUCCESS) {
      delete right_node;
      return rc;
    }
    right_ = right_node;
  }

  if (left_->type() == UNDEFINED || right_->type() == UNDEFINED) {
    return RC::SCHEMA_FIELD_MISSING;
  }
  if (!is_comparable(left_->type(), right_->type())) {
    LOG_ERROR("Type dismatching.");
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }
  return rc;
}

bool TupleFilter::non_subquery_filter(const Tuple &t) {
  auto lv = left_->execute(t);
  auto rv = right_->execute(t);

  if (lv->type() == ATTR_NULL && rv->type() == ATTR_NULL) {
    return op_ == OP_IS;
  }

  if (lv->type() == ATTR_NULL || rv->type() == ATTR_NULL) {
    if (op_ != OP_IS && op_ != OP_IS_NOT) {
      return false;
    }
    if (lv->type() == ATTR_NULL) {
      return false;
    }
    return op_ == OP_IS ? lv->type() == ATTR_NULL : lv->type() != ATTR_NULL;
  }

  int cmp_result = lv->compare(*rv);
  switch (op_) {
  case EQUAL_TO:
    return 0 == cmp_result;
  case LESS_EQUAL:
    return cmp_result <= 0;
  case NOT_EQUAL:
    return cmp_result != 0;
  case LESS_THAN:
    return cmp_result < 0;
  case GREAT_EQUAL:
    return cmp_result >= 0;
  case GREAT_THAN:
    return cmp_result > 0;
  default:
    LOG_PANIC("Unkown compOp type: %d", op_);
    break;
  }
  return false;
}

bool TupleFilter::subquery_filter(const Tuple &t) {
  auto lv = left_->execute(t);
  auto cond_desc_subquery = dynamic_cast<TupleConDescSubquery *>(right_);
  if (op_ == MEM_IN || op_ == MEM_NOT_IN) {
    bool contains = cond_desc_subquery->is_contains(lv);
    return op_ == MEM_IN ? contains : !contains;
  }

  if (cond_desc_subquery->subquery_size() != 1) {
    return false;
  }

  switch (op_) {
  case EQUAL_TO:
    return cond_desc_subquery->compare(lv) == 0;
  case LESS_EQUAL:
    return cond_desc_subquery->compare(lv) <= 0;
  case NOT_EQUAL:
    return cond_desc_subquery->compare(lv) != 0;
  case LESS_THAN:
    return cond_desc_subquery->compare(lv) < 0;
  case GREAT_EQUAL:
    return cond_desc_subquery->compare(lv) >= 0;
  case GREAT_THAN:
    return cond_desc_subquery->compare(lv) > 0;
  default:
    LOG_PANIC("Unkown operator type: %d", op_);
    break;
  }
  return false;
}

bool TupleFilter::filter(const Tuple &t) {
  bool res = false;
  auto is_subquery = dynamic_cast<TupleConDescSubquery *>(right_);
  if (is_subquery != nullptr) {
    res = subquery_filter(t);
  } else {
    res = non_subquery_filter(t);
  }
  return res;
}
