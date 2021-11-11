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
#include <stddef.h>

using namespace common;

extern RC do_select(Trx *trx, Selects &selects, TupleSet &res);

ConDescNode *create_cond_desc_node(ConditionExpr *expr,
                                   const TableMeta &table_meta);

//////////////////////////////////////////////////////////////////////////////
ConDescNode::~ConDescNode() {
  if (value_ != nullptr) {
    free(value_);
    value_ = nullptr;
  }
}

ConDescInternal::ConDescInternal(ArithOp op, ConDescNode *left,
                                 ConDescNode *right)
    : op_(op), left_(left), right_(right) {
  auto left_type = left->type();
  auto right_type = right->type();
  if (!is_computable(left_type, right_type)) {
    // TODO: 不可计算类型如何处理
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
    LOG_PANIC("Unkown arithop type: %d", op_);
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

void *ConDescInternal::execute(const Record &rec) {
  void *left = left_->execute(rec);
  void *right = right_->execute(rec);
  void *res = compute(left, right);
  set_value(res);
  return res;
}

ConDescInternal::~ConDescInternal() {
  delete left_;
  delete right_;
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

void *ConDescAttr::execute(const Record &rec) {
  void *value = nullptr;
  get_value_from_data(rec.data + offset_, value);
  set_value(value);
  if (Table::record_data_is_null(rec, column_)) {
    set_type(ATTR_NULL);
  } else {
    set_type(get_init_type());
  }
  return value;
}

ConDescAttr::~ConDescAttr() {}

void *ConDescValue::execute(const Record &rec) { return value(); }

ConDescValue::~ConDescValue() {}

RC ConDescSubquery::init(TupleSet &&subquery, CompOp op) {
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

void *ConDescSubquery::execute(const Record &rec) { return nullptr; }

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

bool ConDescSubquery::contains(AttrType type, const char *value) {
  std::shared_ptr<TupleValue> tuple_value = get_tuple_value(type, value);
  return contains(tuple_value);
}

bool ConDescSubquery::contains(std::shared_ptr<TupleValue> tuple_value) {
  for (auto value : values_) {
    if (tuple_value->compare(*value) == 0) {
      return true;
    }
  }
  return false;
}

int ConDescSubquery::compare(char *lvalue, AttrType type) {
  std::shared_ptr<TupleValue> left_value = get_tuple_value(type, lvalue);

  return compare(left_value);
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

ConDescNode *create_cond_desc_node(ConditionExpr *expr,
                                   const TableMeta &table_meta) {
  if (expr->has_subexpr == 0) {
    if (expr->is_attr) {
      auto field = table_meta.field(expr->attr->attribute_name);
      if (field == nullptr)
        return nullptr;
      //新增了没有找到attribute的情况
      int offset = field->offset(); /////////////////////
      // TODO: const pointer.
      TableMeta tmp = table_meta;
      return new ConDescAttr(field->type(), field->len(), offset,
                             tmp.find_column_by_offset(offset));
    } else {
      return new ConDescValue(expr->value->type, expr->value->data);
    }
  }
  ConDescNode *left = create_cond_desc_node(expr->left, table_meta);
  ConDescNode *right = create_cond_desc_node(expr->right, table_meta);
  return new ConDescInternal(expr->op, left, right);
}

RC DefaultConditionFilter::init(Table &table, const Condition &condition,
                                TupleSet &&left_subquey,
                                TupleSet &&right_subquey) {
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
    rc = left_node->init(std::move(left_subquey), condition.comp);
    if (rc != RC::SUCCESS) {
      delete left_node;
      return rc;
    }
    left = left_node;
  }
  if (condition.right_subquery != nullptr) {
    ConDescSubquery *right_node = new ConDescSubquery();
    rc = right_node->init(std::move(right_subquey), condition.comp);
    if (rc != RC::SUCCESS) {
      delete right_node;
      return rc;
    }
    right = right_node;
  }

  if (left == nullptr || right == nullptr) {
    return RC::SCHEMA_FIELD_NOT_EXIST;
    //这里做了初步的处理，可以进一步完善RC的分类
  }

  AttrType type_left = left->type();
  AttrType type_right = right->type();
  // 校验和转换
  //  if (!field_type_compare_compatible_table[type_left][type_right]) {
  //    // 不能比较的两个字段， 要把信息传给客户端
  //    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  //  }
  // NOTE：这里没有实现不同类型的数据比较，比如整数跟浮点数之间的对比
  // 但是选手们还是要实现。这个功能在预选赛中会出现
  if (!is_comparable(type_left, type_right)) {
    LOG_ERROR("Type dismatching.");
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  return init(left, right, condition.comp);
}

bool DefaultConditionFilter::non_subquery_filter(const Record &rec) const {
  char *lvalue = (char *)left_->execute(rec);
  char *rvalue = (char *)right_->execute(rec);

  if (left_->is_null() && right_->is_null()) {
    // null is/is not null
    return comp_op_ == OP_IS;
  }

  if (left_->is_null() || right_->is_null()) {
    if (comp_op_ != OP_IS && comp_op_ != OP_IS_NOT) {
      // return false unless is/is not.
      return false;
    }
    if (left_->is_null()) {
      // null is/is not attr.
      return false;
    }
    // attr is/is not null.
    return comp_op_ == OP_IS ? left_->is_null() : !left_->is_null();
  }

  std::shared_ptr<TupleValue> left_value =
      get_tuple_value(left_->type(), lvalue);
  std::shared_ptr<TupleValue> right_value =
      get_tuple_value(right_->type(), rvalue);

  if (left_->type() == ATTR_NULL && right_->type() == ATTR_NULL) {
    return comp_op_ == OP_IS;
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

bool DefaultConditionFilter::subquery_filter(const Record &rec) const {
  ConDescSubquery *left_cond_desc_subquery =
      dynamic_cast<ConDescSubquery *>(left_);
  ConDescSubquery *right_cond_desc_subquery =
      dynamic_cast<ConDescSubquery *>(right_);

  if (left_cond_desc_subquery != nullptr &&
      right_cond_desc_subquery != nullptr) {
  }

  return one_subquery_filter(rec);
}

bool DefaultConditionFilter::two_subquery_filter(const Record &rec) const {
  ConDescSubquery *left_cond_desc_subquery =
      dynamic_cast<ConDescSubquery *>(left_);
  ConDescSubquery *right_cond_desc_subquery =
      dynamic_cast<ConDescSubquery *>(right_);

  if (left_cond_desc_subquery->subquery_size() != 1) {
    return false;
  }

  std::shared_ptr<TupleValue> left_tuple_value =
      left_cond_desc_subquery->get_value_in(0);

  if (comp_op_ == MEM_IN || comp_op_ == MEM_NOT_IN) {
    bool contains = right_cond_desc_subquery->contains(left_tuple_value);
    return comp_op_ == MEM_IN ? contains : !contains;
  }

  if (right_cond_desc_subquery->subquery_size() != 1) {
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

bool DefaultConditionFilter::one_subquery_filter(const Record &rec) const {
  char *lvalue = (char *)left_->execute(rec);
  ConDescSubquery *right_cond_desc_subquery =
      dynamic_cast<ConDescSubquery *>(right_);

  if (comp_op_ == MEM_IN || comp_op_ == MEM_NOT_IN) {
    bool contains = right_cond_desc_subquery->contains(left_->type(), lvalue);
    return comp_op_ == MEM_IN ? contains : !contains;
  }

  if (right_cond_desc_subquery->subquery_size() != 1) {
    return false;
  }

  if (left_->is_null()) {
    // null arithop something.
    return false;
  }

  switch (comp_op_) {
  case EQUAL_TO:
    return right_cond_desc_subquery->compare(lvalue, left_->type()) == 0;
  case LESS_EQUAL:
    return right_cond_desc_subquery->compare(lvalue, left_->type()) <= 0;
  case NOT_EQUAL:
    return right_cond_desc_subquery->compare(lvalue, left_->type()) != 0;
  case LESS_THAN:
    return right_cond_desc_subquery->compare(lvalue, left_->type()) < 0;
  case GREAT_EQUAL:
    return right_cond_desc_subquery->compare(lvalue, left_->type()) >= 0;
  case GREAT_THAN:
    return right_cond_desc_subquery->compare(lvalue, left_->type()) > 0;
  default:
    LOG_PANIC("Unkown operator type: %d", comp_op_);
    break;
  }
  return false;
}

bool DefaultConditionFilter::filter(const Record &rec) const {
  bool res = false;
  auto is_subquery = dynamic_cast<ConDescSubquery *>(right_);
  if (is_subquery != nullptr) {
    res = subquery_filter(rec);
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
    const Condition &cond = conditions->at(i);
    TupleSet left;
    if (cond.left_subquery != nullptr) {
      do_select(trx, *cond.left_subquery, left);
    }
    TupleSet right;
    if (cond.right_subquery != nullptr) {
      do_select(trx, *cond.right_subquery, right);
    }
    rc = default_condition_filter->init(table, cond, std::move(left),
                                        std::move(right));
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

bool CompositeConditionFilter::filter(const Record &rec) const {
  for (int i = 0; i < filter_num_; i++) {
    if (!filters_[i]->filter(rec)) {
      return false;
    }
  }
  return true;
}
