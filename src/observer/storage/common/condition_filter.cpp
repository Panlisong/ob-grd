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
#include "storage/common/table.h"
#include <cmath>
#include <stddef.h>

using namespace common;

extern RC do_select(Trx *trx, Selects &selects, TupleSet &res);

ConDescNode *create_cond_desc_node(ConditionExpr *expr,
                                   const TableMeta &table_meta);

static bool isComputable(AttrType left, AttrType right) {
  if (left == ATTR_NULL || right == ATTR_NULL) {
    return false;
  }
  if (left == DATES || right == DATES || left == CHARS || right == CHARS) {
    return false;
  }
  return true;
}

static bool isComparable(AttrType lt, AttrType rt) {
  if (lt == DATES || rt == DATES || lt == CHARS || rt == CHARS) {
    return lt == rt;
  }
  return true;
}
//////////////////////////////////////////////////////////////////////////////
ConDescNode::~ConDescNode() {
  if (value_ != nullptr) {
    free(value_);
  }
}

ConDescInternal::ConDescInternal(ArithOp op, ConDescNode *left,
                                 ConDescNode *right)
    : op_(op), left_(left), right_(right) {
  auto left_type = left->type();
  auto right_type = right->type();
  if (!isComputable(left_type, right_type)) {
    // TODO: 不可计算类型如何处理
    set_type(ATTR_NULL);
    return;
  }

  // 当前处理：
  // 操作数出现一个float则整个表达式为float
  if (left_type == FLOATS || right_type == FLOATS) {
    set_type(FLOATS);
  } else {
    set_type(INTS);
  }
}

// INT op INT
void *ConDescInternal::compute(int lv, int rv) {
  int *res = (int *)malloc(sizeof(int));
  switch (op_) {
  case ADD:
    *res = lv + rv;
    break;
  case SUB:
    *res = lv - rv;
    break;
  case MUL:
    *res = lv * rv;
    break;
  case DIV:
    *res = lv / rv;
    break;
  default:
    LOG_PANIC("Unkown arithop type: %d", op_);
    break;
  }
  return res;
}

// INT op FLOAT
void *ConDescInternal::compute(int lv, float rv) {
  float *res = (float *)malloc(sizeof(float));
  switch (op_) {
  case ADD:
    *res = (float)lv + rv;
    break;
  case SUB:
    *res = (float)lv - rv;
    break;
  case MUL:
    *res = (float)lv * rv;
    break;
  case DIV:
    *res = (float)lv / rv;
    break;
  default:
    LOG_PANIC("Unkown arithop type: %d", op_);
    break;
  }
  return res;
}

// FLOAT op FLOAT
void *ConDescInternal::compute(float lv, float rv) {
  float *res = (float *)malloc(sizeof(float));
  switch (op_) {
  case ADD:
    *res = lv + rv;
    break;
  case SUB:
    *res = lv - rv;
    break;
  case MUL:
    *res = lv * rv;
    break;
  case DIV:
    *res = lv / rv;
    break;
  default:
    LOG_PANIC("Unkown arithop type: %d", op_);
    break;
  }
  return res;
}

void *ConDescInternal::compute(void *lv, void *rv) {
  // 由于使用void*，仿照b+树写法
  // TODO: 处理运算异常
  int i1 = 0, i2 = 0;
  float f1 = 0, f2 = 0;
  void *res = nullptr;
  switch (left_->type()) {
  case INTS:
    i1 = *(int *)lv;
    switch (right_->type()) {
    case INTS:
      i2 = *(int *)rv;
      res = compute(i1, i2);
      break;
    case FLOATS:
      f2 = *(float *)rv;
      res = compute(i1, f2);
      break;
    default:
      LOG_PANIC("Incomputable attr type: %d", right_->type());
    }
    break;
  case FLOATS:
    f1 = *(float *)lv;
    switch (right_->type()) {
    case INTS:
      i2 = *(int *)rv;
      res = compute(i2, f1);
      break;
    case FLOATS:
      f2 = *(float *)rv;
      res = compute(f1, f2);
      break;
    default:
      LOG_PANIC("Incomputable attr type: %d", right_->type());
    }
    break;
  default:
    LOG_PANIC("Incomputable attr type: %d", left_->type());
  }
  return res;
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
  default:
    LOG_PANIC("Unkown attr type: %d", type());
    break;
  }
}

void *ConDescAttr::execute(const Record &rec) {
  void *value = nullptr;
  get_value_from_data(rec.data + offset_, value);
  set_value(value);
  return value;
}

ConDescAttr::~ConDescAttr() {}

void *ConDescValue::execute(const Record &rec) { return value(); }

ConDescValue::~ConDescValue() {}

RC ConDescSubquery::init(TupleSet &&subquery) {
  const auto schema = subquery.get_schema();
  if (schema.fields().size() > 1) {
    // TODO: 子查询列数>1
    return RC::GENERIC_ERROR;
  }
  set_type(schema.fields().begin()->type());
  for (auto &tuple : subquery.tuples()) {
    values_.emplace_back(tuple.get_pointer(0));
  }
  return RC::SUCCESS;
}

void *ConDescSubquery::execute(const Record &rec) { return nullptr; }

bool ConDescSubquery::is_contains(int i) {
  // TODO: 当前实现默认非null值
  IntValue v = IntValue(i, false);
  for (const auto &value : values_) {
    if (v.compare(*value) == 0) {
      return true;
    }
  }
  return false;
}

bool ConDescSubquery::is_contains(float f) {
  FloatValue v = FloatValue(f, false);
  for (const auto &value : values_) {
    if (v.compare(*value) == 0) {
      return true;
    }
  }
  return true;
}

bool ConDescSubquery::is_contains(time_t t) {
  DateValue v = DateValue(t, false);
  for (const auto &value : values_) {
    if (v.compare(*value) == 0) {
      return true;
    }
  }
  return true;
}

bool ConDescSubquery::is_contains(const char *s, int len) {
  StringValue v = StringValue(s, len, false);
  for (const auto &value : values_) {
    if (v.compare(*value) == 0) {
      return true;
    }
  }
  return true;
}

int ConDescSubquery::is_contains(AttrType type, const char *value) {
  int res = 0;
  switch (type) {
  case CHARS: {
    res = is_contains(value, strlen(value));
  } break;
  case INTS: {
    res = is_contains(*(int *)value);
  } break;
  case FLOATS: {
    res = is_contains(*(float *)value);
  } break;
  case DATES: {
    res = is_contains(*(time_t *)value);
  } break;
  default:
    LOG_PANIC("Unkown attr type: %d", type);
    break;
  }
  return res;
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
                                AttrType attr_type, CompOp comp_op) {
  if (attr_type < CHARS || attr_type > DATES) {
    LOG_ERROR("Invalid condition with unsupported attribute type: %d",
              attr_type);
    return RC::INVALID_ARGUMENT;
  }

  if (comp_op < EQUAL_TO || comp_op >= NO_OP) {
    LOG_ERROR("Invalid condition with unsupported compare operation: %d",
              comp_op);
    return RC::INVALID_ARGUMENT;
  }

  left_ = left;
  right_ = right;
  attr_type_ = attr_type;
  comp_op_ = comp_op;
  return RC::SUCCESS;
}

ConDescNode *create_cond_desc_node(ConditionExpr *expr,
                                   const TableMeta &table_meta) {
  if (expr->has_subexpr == 0) {
    if (expr->is_attr) {
      auto field = table_meta.field(expr->attr->attribute_name);
      return new ConDescAttr(field->type(), field->len(), field->offset());
    } else {
      return new ConDescValue(expr->value.type, expr->value.data);
    }
  }
  ConDescNode *left = create_cond_desc_node(expr->left, table_meta);
  ConDescNode *right = create_cond_desc_node(expr->right, table_meta);
  return new ConDescInternal(expr->op, left, right);
}

RC DefaultConditionFilter::init(Table &table, const Condition &condition,
                                TupleSet &&subquery) {
  const TableMeta &table_meta = table.table_meta();
  ConDescNode *left = create_cond_desc_node(condition.left, table_meta);
  ConDescNode *right = nullptr;
  if (condition.is_subquery == 1) {
    ConDescSubquery *cond_node = new ConDescSubquery();
    cond_node->init(std::move(subquery));
    right = cond_node;
  } else {
    right = create_cond_desc_node(condition.right, table_meta);
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
  if (!isComparable(type_left, type_right)) {
    LOG_ERROR("Type dismatching.");
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  if (type_left != type_right) {
    // 可比较且类型不同，说明要发生类型转换
    // 目前实现只有INF和FLOAT类型转换
    // R(F) op V(I) / V(I) op R(F) => V(I) 转 V(F)
    // R(I) op V(F) / V(F) op R(I) => R(I) 转 R(F)
    // R(F) op R(I) / R(I) op R(F) => R(I) 转 R(F)
    // V(F) op V(I) / V(I) op V(F) => V(I) 转 V(F)
    if (type_left == INTS) {
    }
    if (type_right == INTS) {
    }
    //   // 1. 常量直接更改
    //   if (condition.left_is_attr == 0 && type_left == INTS) {
    //     float v = *(int *)left.value;
    //     // memcpy(left.value, &v, sizeof(v));
    //     // // 同步cond
    //     // condition.left_value.type = FLOATS;
    //     // 由于cond为const， 无法同步类型转换，所以上面的写法不推荐
    //     left.value = new float(v); // WARNING：注意释放内存
    //   }
    //   if (condition.right_is_attr == 0 && type_right == INTS) {
    //     float v = *(int *)right.value;
    //     // memcpy(right.value, &v, sizeof(v));
    //     right.value = new float(v); // WARNING：注意释放内存
    //   }
    //   // 2. 属性，做标记延后转换
    //   if (condition.left_is_attr == 1 && type_left == INTS) {
    //     left_attr_convert_ = true;
    //   }
    //   if (condition.right_is_attr == 1 && type_right == INTS) {
    //     right_attr_convert_ = true;
    //   }
    type_left = FLOATS;
  }

  return init(left, right, type_left, condition.comp);
}

bool DefaultConditionFilter::filter(const Record &rec) const {
  // TODO: null
  // null op null
  // if (left_.is_null && right_.is_null) {
  //   return comp_op_ == OP_IS;
  // }

  // if (left_.is_null || right_.is_null) {
  //   if (comp_op_ != OP_IS && comp_op_ != OP_IS_NOT) {
  //     // return false unless is/is not.
  //     return false;
  //   }
  //   if (left_.is_null) {
  //     // null is/is not attr.
  //     return false;
  //   }
  //   // attr is/is not attr.
  //   int column = table_.find_column_by_offset(left_.attr_offset);
  //   int32_t *null_field = (int32_t *)(rec.data + table_.null_field_offset());
  //   bool is_null = (((*null_field) & (1 << column)) != 0);
  //   return comp_op_ == OP_IS ? is_null : !is_null;
  // }

  char *lvalue = (char *)left_->execute(rec);
  char *rvalue = (char *)right_->execute(rec);

  int cmp_result = 0;
  if (rvalue == nullptr) {
    auto subquery_node = dynamic_cast<ConDescSubquery *>(right_);
    assert(subquery_node != nullptr);
    cmp_result = subquery_node->is_contains(attr_type_, lvalue);
  } else {
    switch (attr_type_) {
    case CHARS: { // 字符串都是定长的，直接比较
      // 按照C字符串风格来定
      cmp_result = strcmp(lvalue, rvalue);
    } break;
    case INTS: {
      // 没有考虑大小端问题
      // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
      int left = *(int *)lvalue;
      int right = *(int *)rvalue;
      cmp_result = left - right;
    } break;
    case FLOATS: {
      bool left_convert = left_attr_convert_;
      bool right_convert = right_attr_convert_;
      float left = left_convert ? *(int *)lvalue : *(float *)lvalue;
      float right = right_convert ? *(int *)rvalue : *(float *)rvalue;
      double res = (double)left - right;
      double ep = 1e-6;
      cmp_result = fabs(res) < ep ? 0 : (res < -ep ? -1 : 1);
    } break;
    case DATES: {
      time_t left = *(time_t *)lvalue;
      time_t right = *(time_t *)rvalue;
      long long res = left - right;
      cmp_result = res == 0LL ? 0 : (res < 0LL ? -1 : 1);
    }
    default: {
    }
    }
  }

  switch (comp_op_) {
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
  case MEM_IN:
    return cmp_result == 1;
  case MEM_NOT_IN:
    return cmp_result == 0;
  default:
    break;
  }

  LOG_PANIC("Never should print this.");
  return cmp_result; // should not go here
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
                                  const Condition *conditions,
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
    TupleSet subquery;
    if (conditions[i].is_subquery == 1) {
      do_select(trx, *conditions[i].subquery, subquery);
    }
    rc = default_condition_filter->init(table, conditions[i],
                                        std::move(subquery));
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
