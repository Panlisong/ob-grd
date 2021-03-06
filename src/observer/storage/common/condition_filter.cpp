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

#include "condition_filter.h"
#include "common/log/log.h"
#include "record_manager.h"
#include "sql/parser/parse_defs.h"
#include "storage/common/table.h"
#include <cmath>
#include <cstdlib>
#include <stddef.h>

using namespace common;

extern RC do_select(Trx *trx, Selects &selects, TupleSet &res);

std::shared_ptr<TupleValue> get_tuple_value(AttrType type, const char *value) {
  switch (type) {
  case CHARS: {
    return std::make_shared<StringValue>(value);
  } break;
  case INTS: {
    int int_value = *(int *)value;
    return std::make_shared<IntValue>(int_value);
  } break;
  case FLOATS: {
    float float_value = *(float *)value;
    return std::make_shared<FloatValue>(float_value);
  } break;
  case DATES: {
    time_t time_value = *(time_t *)value;
    return std::make_shared<DateValue>(time_value);
  } break;
  case ATTR_NULL: {
    return std::make_shared<NullValue>();
  } break;
  default: {
    LOG_PANIC("Unkown attr type: %d", type);
    return nullptr;
  } break;
  }
}

ConDescNode *create_cond_desc_node(ConditionExpr *expr,
                                   const TableMeta &table_meta);
ConDescNode *create_cond_desc_attr(RelAttr *attr, const TableMeta &table_meta);

//////////////////////////////////////////////////////////////////////////////
ConDescNode::~ConDescNode() {}

ConDescInternal::ConDescInternal(ArithOp op, ConDescNode *left,
                                 ConDescNode *right)
    : op_(op), left_(left), right_(right) {
  auto left_type = left->type();
  auto right_type = right->type();
  if (!is_computable(left_type, right_type)) {
    set_type(ATTR_NULL);
    return;
  }

  if (op == DIV) {
    set_type(FLOATS);
  } else if (left_type == right_type) {
    set_type(left_type);
  } else {
    set_type(FLOATS);
  }
}

void *ConDescInternal::compute(void *lv, void *rv) {
  float lvalue, rvalue;
  if (left_->type() == INTS) {
    lvalue = float(*(int *)lv);
  } else {
    lvalue = *(float *)lv;
  }
  if (right_->type() == INTS) {
    rvalue = float(*(int *)rv);
  } else {
    rvalue = *(float *)rv;
  }

  if (op_ == DIV && -1e-6 < rvalue && rvalue < 1e-6) {
    set_type(ATTR_NULL);
    return nullptr;
  }

  float res = 0.0;
  switch (op_) {
  case ADD:
    res = lvalue + rvalue;
    break;
  case SUB:
    res = lvalue - rvalue;
    break;
  case MUL:
    res = lvalue * rvalue;
    break;
  case DIV:
    res = lvalue / rvalue;
    break;
  default:
    LOG_INFO("Unkown arithop type: %d", op_);
    break;
  }

  if (left_->type() == INTS && right_->type() == INTS && op_ != DIV) {
    int *r = (int *)malloc(sizeof(int));
    *r = (int)res;
    return r;
  }
  float *r = (float *)malloc(sizeof(float));
  *r = res;
  return r;
}

std::shared_ptr<TupleValue> ConDescInternal::execute(const Record &rec) {
  std::shared_ptr<TupleValue> left = left_->execute(rec);
  std::shared_ptr<TupleValue> right = right_->execute(rec);
  TupleValue *res;
  left->compute(right.get(), res, op_);
  std::shared_ptr<TupleValue> res_tuple_value;
  res_tuple_value.reset(res);
  return res_tuple_value;
}

ConDescInternal::~ConDescInternal() {
  if (left_ != nullptr) {
    delete left_;
  }
  if (right_ != nullptr) {
    delete right_;
  }
}

ConDescUnary::ConDescUnary(ArithOp op, ConDescNode *expr)
    : op_(op), expr_(expr) {
  set_type(expr->type());
}

std::shared_ptr<TupleValue> ConDescUnary::execute(const Record &rec) {
  std::shared_ptr<TupleValue> operand = expr_->execute(rec);
  IntValue *zero = new IntValue(0);
  TupleValue *res;
  zero->compute(operand.get(), res, SUB);
  std::shared_ptr<TupleValue> res_tuple_value;
  res_tuple_value.reset(res);
  return res_tuple_value;
}

ConDescUnary::~ConDescUnary() {
  if (expr_ != nullptr) {
    delete expr_;
  }
}

void ConDescAttr::get_value_from_data(char *data, void *&value) {
  switch (type()) {
  case INTS:
    value = (int *)malloc(sizeof(length_));
    *(int *)value = *(int *)data;
    break;
  case FLOATS:
    value = (float *)malloc(sizeof(length_));
    *(float *)value = *(float *)data;
    break;
  case DATES:
    value = (time_t *)malloc(sizeof(length_));
    *(time_t *)value = *(time_t *)data;
    break;
  case CHARS:
    value = (char *)malloc(sizeof(length_));
    memcpy(value, data, length_);
    break;
  case ATTR_NULL:
    break;
  default:
    LOG_PANIC("Unkown attr type: %d", type());
    break;
  }
}

std::shared_ptr<TupleValue> ConDescAttr::execute(const Record &rec) {
  if (Table::record_data_is_null(rec, column_)) {
    return std::make_shared<NullValue>();
  }

  char *value = rec.data + offset_;
  switch (type()) {
  case INTS: {
    int int_value = *(int *)value;
    return std::make_shared<IntValue>(int_value);
  } break;
  case FLOATS: {
    float float_value = *(float *)value;
    return std::make_shared<FloatValue>(float_value);
  } break;
  case DATES: {
    time_t time_value = *(time_t *)value;
    return std::make_shared<DateValue>(time_value);
  } break;
  case CHARS: {
    return std::make_shared<StringValue>(value);
  } break;
  case ATTR_NULL: {
    return std::make_shared<NullValue>();
  } break;
  default: {
    LOG_PANIC("Unkown attr type: %d", type());
  } break;
  }
  return nullptr;
}

ConDescAttr::~ConDescAttr() {}

std::shared_ptr<TupleValue> ConDescValue::execute(const Record &rec) {
  return value_;
}

ConDescValue::~ConDescValue() {}

RC ConDescSubquery::init(Trx *trx, Selects *subquery) {
  trx_ = trx;
  if (subquery->exprs->size() > 1) {
    LOG_ERROR("subquery return multi columns");
    return RC::GENERIC_ERROR;
  }
  auto first_expr = subquery->exprs->at(0);
  if (first_expr->is_attr == 1 &&
      0 == strcmp("*", first_expr->attr->attribute_name)) {
    LOG_ERROR("subquery return multi columns");
    return RC::GENERIC_ERROR;
  }
  set_type(first_expr->type);
  select_ = subquery;
  return RC::SUCCESS;
}

std::shared_ptr<TupleValue> ConDescSubquery::execute(const Record &rec) {
  TupleSet res;
  for (size_t i = 0; i < select_->conditions->size(); i++) {
    // ?????????????????????Condition???????????????
    select_->conditions->at(i)->is_used = 0;
  }
  do_select(trx_, *select_, res);
  const auto schema = res.get_schema();
  set_type(schema.fields().begin()->type());
  values_.clear();
  for (auto &tuple : res.tuples()) {
    values_.emplace_back(tuple.get_pointer(0));
  }
  return nullptr;
}

bool ConDescSubquery::contains(std::shared_ptr<TupleValue> tuple_value) {
  for (auto value : values_) {
    if (tuple_value->compare(*value) == 0) {
      return true;
    }
  }
  return false;
}

int ConDescSubquery::compare(std::shared_ptr<TupleValue> left_value) {
  TupleValue *right_value = get_value_in(0).get();
  return left_value->compare(*right_value);
}

ConDescSubquery::~ConDescSubquery() {}

///////////////////////////////////////////////////////////////////////////////
ConditionFilter::~ConditionFilter() {}

DefaultConditionFilter::DefaultConditionFilter(Table &table) : table_(table) {
  left_ = nullptr;
  right_ = nullptr;
}
DefaultConditionFilter::~DefaultConditionFilter() {
  delete left_;
  delete right_;
}

RC DefaultConditionFilter::init(ConDescNode *left, ConDescNode *right,
                                CompOp comp_op) {
  if (left->type() < CHARS || left->type() > DATES) {
    LOG_ERROR("Invalid condition with unsupported attribute type: %d",
              left->type());
    return RC::INVALID_ARGUMENT;
  }
  if (right->type() < CHARS || right->type() > DATES) {
    LOG_ERROR("Invalid condition with unsupported attribute type: %d",
              right->type());
    return RC::INVALID_ARGUMENT;
  }

  if (comp_op < EQUAL_TO || comp_op >= NO_OP) {
    LOG_ERROR("Invalid condition with unsupported compare operation: %d",
              comp_op);
    return RC::INVALID_ARGUMENT;
  }

  left_ = left;
  right_ = right;
  comp_op_ = comp_op;
  return RC::SUCCESS;
}

ConDescNode *create_cond_desc_attr(RelAttr *attr, const TableMeta &table_meta) {
  auto field = table_meta.field(attr->attribute_name);
  if (field == nullptr) {
    return nullptr;
  }
  int offset = field->offset();
  return new ConDescAttr(field->type(), field->len(), offset,
                         table_meta.find_column_by_offset(offset));
}

ConDescNode *create_cond_desc_node(ConditionExpr *expr,
                                   const TableMeta &table_meta) {
  if (expr->has_subexpr == 0) {
    if (!expr->binded && expr->is_attr) {
      return create_cond_desc_attr(expr->attr, table_meta);
    } else {
      auto v = get_tuple_value(expr->value->type, (char *)expr->value->data);
      return new ConDescValue(expr->value->type, v);
    }
  }
  ConDescNode *right = create_cond_desc_node(expr->right, table_meta);
  if (expr->left == nullptr) {
    return new ConDescUnary(expr->op, right);
  }
  ConDescNode *left = create_cond_desc_node(expr->left, table_meta);
  return new ConDescInternal(expr->op, left, right);
}

RC DefaultConditionFilter::init(Table &table, const Condition &condition,
                                Trx *trx) {
  RC rc = RC::SUCCESS;
  const TableMeta &table_meta = table.table_meta();
  ConDescNode *left = nullptr;
  ConDescNode *right = nullptr;
  if (condition.left != nullptr) {
    left = create_cond_desc_node(condition.left, table_meta);
  }
  if (condition.right != nullptr) {
    right = create_cond_desc_node(condition.right, table_meta);
  }
  if (condition.left_subquery != nullptr) {
    ConDescSubquery *left_node = new ConDescSubquery();
    rc = left_node->init(trx, condition.left_subquery);
    if (rc != RC::SUCCESS) {
      delete left_node;
      return rc;
    }
    left = left_node;
  }
  if (condition.right_subquery != nullptr) {
    ConDescSubquery *right_node = new ConDescSubquery();
    rc = right_node->init(trx, condition.right_subquery);
    if (rc != RC::SUCCESS) {
      delete right_node;
      return rc;
    }
    right = right_node;
  }

  // ????????????non-subquery or ?????????????????????deque
  for (size_t i = 0; i < condition.binded_conds->size(); i++) {
    ConditionExpr *expr = condition.binded_conds->at(i);
    ConDescNode *node = create_cond_desc_attr(expr->attr, table_meta);
    assert(node != nullptr);
    bind_cond_exprs_.push_back({node, expr});
  }

  for (size_t i = 0; i < condition.binded_exprs->size(); i++) {
    SelectExpr *expr = condition.binded_exprs->at(i);
    ConDescNode *node = create_cond_desc_attr(expr->attr, table_meta);
    assert(node != nullptr);
    bind_select_exprs_.push_back({node, expr});
  }

  if (left == nullptr || right == nullptr) {
    return RC::SCHEMA_FIELD_NOT_EXIST;
    //???????????????????????????????????????????????????RC?????????
  }

  AttrType type_left = left->type();
  AttrType type_right = right->type();
  // ???????????????
  //  if (!field_type_compare_compatible_table[type_left][type_right]) {
  //    // ?????????????????????????????? ???????????????????????????
  //    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  //  }
  // NOTE??????????????????????????????????????????????????????????????????????????????????????????
  // ?????????????????????????????????????????????????????????????????????
  if (!is_comparable(type_left, type_right)) {
    LOG_ERROR("Type dismatching.");
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  return init(left, right, condition.comp);
}

bool DefaultConditionFilter::non_subquery_filter(const Record &rec) const {
  std::shared_ptr<TupleValue> left_value = left_->execute(rec);
  std::shared_ptr<TupleValue> right_value = right_->execute(rec);

  if (left_value->is_null() && right_value->is_null()) {
    // null is/is not null
    return comp_op_ == OP_IS;
  }

  if (left_value->is_null() || right_value->is_null()) {
    if (comp_op_ != OP_IS && comp_op_ != OP_IS_NOT) {
      // return false unless is/is not.
      return false;
    }
    if (left_value->is_null()) {
      // null is/is not attr.
      return false;
    }
    // attr is/is not null.
    return comp_op_ == OP_IS ? left_value->is_null() : !left_value->is_null();
  }

  if (!left_value->comparable(*right_value)) {
    LOG_ERROR("can not compare");
    return false;
  }

  int cmp_result = left_value->compare(*right_value);

  switch (comp_op_) {
  case EQUAL_TO:
    return 0 == cmp_result;
  case NOT_EQUAL:
    return cmp_result != 0;
  case LESS_EQUAL:
    return cmp_result <= 0;
  case LESS_THAN:
    return cmp_result < 0;
  case GREAT_EQUAL:
    return cmp_result >= 0;
  case GREAT_THAN:
    return cmp_result > 0;
  default:
    LOG_PANIC("Unkown compOp type: %d", comp_op_);
    break;
  }

  LOG_PANIC("Never should print this.");
  return cmp_result; // should not go here
}

static void *malloc_value(AttrType type) {
  switch (type) {
  case INTS:
    return (int *)malloc(sizeof(int));
  case FLOATS:
    return (float *)malloc(sizeof(float));
  case DATES:
    return (time_t *)malloc(sizeof(time_t));
  case CHARS:
    return (char *)malloc(4 * sizeof(char));
  default:
    return nullptr;
  }
}

bool DefaultConditionFilter::subquery_filter(const Record &rec, RC &ret) const {
  // ???????????????
  for (size_t i = 0; i < bind_cond_exprs_.size(); i++) {
    auto bind_attr_expr = bind_cond_exprs_.at(i).second;
    auto execution_node =
        reinterpret_cast<ConDescAttr *>(bind_cond_exprs_.at(i).first);
    Value *v = (Value *)malloc(sizeof(Value));
    v->type = execution_node->type();
    std::shared_ptr<TupleValue> outer_tuple_value =
        execution_node->execute(rec);
    v->data = malloc_value(v->type);
    outer_tuple_value->get_value(v->data);
    v->len = execution_node->length();
    if (bind_attr_expr->value != nullptr) {
      free(bind_attr_expr->value);
    }
    bind_attr_expr->value = v;
  }

  for (size_t i = 0; i < bind_select_exprs_.size(); i++) {
    auto bind_attr_expr = bind_select_exprs_.at(i).second;
    auto execution_node =
        reinterpret_cast<ConDescAttr *>(bind_cond_exprs_.at(i).first);
    Value *v = (Value *)malloc(sizeof(Value));
    v->type = execution_node->type();
    std::shared_ptr<TupleValue> outer_tuple_value =
        execution_node->execute(rec);
    v->data = malloc_value(v->type);
    outer_tuple_value->get_value(v->data);
    v->len = execution_node->length();
    if (bind_attr_expr->value != nullptr) {
      free(bind_attr_expr->value);
    }
    bind_attr_expr->value = v;
  }

  ConDescSubquery *left_cond_desc_subquery =
      dynamic_cast<ConDescSubquery *>(left_);
  ConDescSubquery *right_cond_desc_subquery =
      dynamic_cast<ConDescSubquery *>(right_);

  if (left_cond_desc_subquery != nullptr &&
      right_cond_desc_subquery != nullptr) {
    return two_subquery_filter(rec, ret);
  }

  return one_subquery_filter(rec, ret);
}

bool DefaultConditionFilter::two_subquery_filter(const Record &rec,
                                                 RC &ret) const {
  ConDescSubquery *left_cond_desc_subquery =
      dynamic_cast<ConDescSubquery *>(left_);
  ConDescSubquery *right_cond_desc_subquery =
      dynamic_cast<ConDescSubquery *>(right_);

  left_cond_desc_subquery->execute(rec);
  right_cond_desc_subquery->execute(rec);

  if (left_cond_desc_subquery->subquery_size() == 0) {
    return false;
  }

  if (left_cond_desc_subquery->subquery_size() > 1) {
    ret = RC::GENERIC_ERROR;
    return false;
  }

  std::shared_ptr<TupleValue> left_tuple_value =
      left_cond_desc_subquery->get_value_in(0);

  if (comp_op_ == MEM_IN || comp_op_ == MEM_NOT_IN) {
    bool contains = right_cond_desc_subquery->contains(left_tuple_value);
    return comp_op_ == MEM_IN ? contains : !contains;
  }

  if (right_cond_desc_subquery->subquery_size() == 0) {
    return false;
  }
  if (right_cond_desc_subquery->subquery_size() > 1) {
    ret = RC::GENERIC_ERROR;
    return false;
  }

  switch (comp_op_) {
  case EQUAL_TO:
    return right_cond_desc_subquery->compare(left_tuple_value) == 0;
  case LESS_EQUAL:
    return right_cond_desc_subquery->compare(left_tuple_value) <= 0;
  case NOT_EQUAL:
    return right_cond_desc_subquery->compare(left_tuple_value) != 0;
  case LESS_THAN:
    return right_cond_desc_subquery->compare(left_tuple_value) < 0;
  case GREAT_EQUAL:
    return right_cond_desc_subquery->compare(left_tuple_value) >= 0;
  case GREAT_THAN:
    return right_cond_desc_subquery->compare(left_tuple_value) > 0;
  default:
    LOG_PANIC("Unkown operator type: %d", comp_op_);
    break;
  }
  return false;

  return true;
}

bool DefaultConditionFilter::one_subquery_filter(const Record &rec,
                                                 RC &ret) const {
  std::shared_ptr<TupleValue> left_value = left_->execute(rec);
  ConDescSubquery *right_cond_desc_subquery =
      dynamic_cast<ConDescSubquery *>(right_);
  right_cond_desc_subquery->execute(rec);

  if (comp_op_ == MEM_IN || comp_op_ == MEM_NOT_IN) {
    bool contains = right_cond_desc_subquery->contains(left_value);
    return comp_op_ == MEM_IN ? contains : !contains;
  }

  if (right_cond_desc_subquery->subquery_size() == 0) {
    return false;
  }

  if (right_cond_desc_subquery->subquery_size() > 1) {
    ret = RC::GENERIC_ERROR;
    return false;
  }

  if (left_value->is_null()) {
    // null arithop something.
    return false;
  }

  // right_value is null.
  std::shared_ptr<TupleValue> right_value =
      right_cond_desc_subquery->get_value_in(0);
  if (left_value->comparable(*right_value) == false) {
    return false;
  }
  LOG_INFO("%d", right_value->type());

  switch (comp_op_) {
  case EQUAL_TO:
    return right_cond_desc_subquery->compare(left_value) == 0;
  case LESS_EQUAL:
    return right_cond_desc_subquery->compare(left_value) <= 0;
  case NOT_EQUAL:
    return right_cond_desc_subquery->compare(left_value) != 0;
  case LESS_THAN:
    return right_cond_desc_subquery->compare(left_value) < 0;
  case GREAT_EQUAL:
    return right_cond_desc_subquery->compare(left_value) >= 0;
  case GREAT_THAN:
    return right_cond_desc_subquery->compare(left_value) > 0;
  default:
    LOG_PANIC("Unkown operator type: %d", comp_op_);
    break;
  }
  return false;
}

bool DefaultConditionFilter::filter(const Record &rec, RC &ret) const {
  bool res = false;
  auto is_subquery = dynamic_cast<ConDescSubquery *>(right_);
  if (is_subquery != nullptr) {
    res = subquery_filter(rec, ret);
  } else {
    res = non_subquery_filter(rec);
  }
  return res;
}

CompositeConditionFilter::~CompositeConditionFilter() {
  if (memory_owner_) {
    delete[] filters_;
    filters_ = nullptr;
  }
}

RC CompositeConditionFilter::init(const ConditionFilter *filters[],
                                  int filter_num, bool own_memory) {
  filters_ = filters;
  filter_num_ = filter_num;
  memory_owner_ = own_memory;
  return RC::SUCCESS;
}

RC CompositeConditionFilter::init(const ConditionFilter *filters[],
                                  int filter_num) {
  return init(filters, filter_num, false);
}

RC CompositeConditionFilter::init(Trx *trx, Table &table,
                                  const ConditionList *conditions,
                                  int condition_num) {
  if (condition_num == 0) {
    return RC::SUCCESS;
  }
  if (conditions == nullptr) {
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;
  ConditionFilter **condition_filters = new ConditionFilter *[condition_num];
  for (int i = 0; i < condition_num; i++) {
    DefaultConditionFilter *default_condition_filter =
        new DefaultConditionFilter(table);
    const Condition &cond = *conditions->at(i);
    rc = default_condition_filter->init(table, cond, trx);
    if (rc != RC::SUCCESS) {
      delete default_condition_filter;
      for (int j = i - 1; j >= 0; j--) {
        delete condition_filters[j];
        condition_filters[j] = nullptr;
      }
      delete[] condition_filters;
      condition_filters = nullptr;
      return rc;
    }
    condition_filters[i] = default_condition_filter;
  }
  return init((const ConditionFilter **)condition_filters, condition_num, true);
}

bool CompositeConditionFilter::filter(const Record &rec, RC &ret) const {
  for (int i = 0; i < filter_num_; i++) {
    if (!filters_[i]->filter(rec, ret)) {
      return false;
    }
  }
  return true;
}
