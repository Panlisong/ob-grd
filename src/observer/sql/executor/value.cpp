/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "value.h"
#include <climits>
#include <cmath>

void IntValue::compute(TupleValue *rhs, TupleValue *res, ArithOp op) {
  auto string = dynamic_cast<StringValue *>(rhs);
  auto date = dynamic_cast<DateValue *>(rhs);
  if (string != nullptr || date != nullptr) {
    res = nullptr;
    return;
  }
  auto int_value = dynamic_cast<IntValue *>(rhs);
  auto float_value = dynamic_cast<FloatValue *>(rhs);
  if (int_value != nullptr) {
    // rhs为Int
    int result = 0;
    switch (op) {
    case ADD:
      result = value_ + int_value->value_;
      break;
    case SUB:
      result = value_ - int_value->value_;
      break;
    case MUL:
      result = value_ * int_value->value_;
      break;
    case DIV:
      if (int_value->value_ == 0) {
        // TODO: 运算异常
        // 目前返回INT类型的null值
        res = new IntValue(value_ > 0 ? INT_MAX : INT_MIN, true);
        return;
      }
      result = value_ * int_value->value_;
      break;
    default:
      LOG_PANIC("Unkown arithop type: %d", op);
      break;
    }
    res = new IntValue(result, false);
  } else {
    // rhs为float
    float f, result = 0;
    float_value->get_value(&f);
    switch (op) {
    case ADD:
      result = (float)value_ + f;
      break;
    case SUB:
      result = (float)value_ - f;
      break;
    case MUL:
      result = (float)value_ * f;
      break;
    case DIV:
      if (int_value->value_ == 0) {
        // TODO: 运算异常
        // 目前返回FLOAT类型的null值
        res = new FloatValue(value_ > 0 ? INFINITY : -INFINITY, true);
        return;
      }
      result = (float)value_ / f;
      break;
    default:
      LOG_PANIC("Unkown arithop type: %d", op);
      break;
    }
    res = new FloatValue(result, false);
  }
}

void FloatValue::compute(TupleValue *rhs, TupleValue *res, ArithOp op) {
  auto string = dynamic_cast<StringValue *>(rhs);
  auto date = dynamic_cast<DateValue *>(rhs);
  if (string != nullptr || date != nullptr) {
    res = nullptr;
    return;
  }
  auto float_value = dynamic_cast<FloatValue *>(rhs);
  auto int_value = dynamic_cast<IntValue *>(rhs);
  if (float_value != nullptr) {
    // rhs为Int
    int result = 0;
    switch (op) {
    case ADD:
      result = value_ + float_value->value_;
      break;
    case SUB:
      result = value_ - float_value->value_;
      break;
    case MUL:
      result = value_ * float_value->value_;
      break;
    case DIV:
      if (float_value->value_ == 0) {
        // TODO: 运算异常
        // 目前返回INT类型的null值
        res = new FloatValue(value_ > 0 ? INFINITY : -INFINITY, true);
        return;
      }
      result = value_ * float_value->value_;
      break;
    default:
      LOG_PANIC("Unkown arithop type: %d", op);
      break;
    }
    res = new FloatValue(result, false);
  } else {
    int_value->compute(this, res, op);
  }
}

void StringValue::compute(TupleValue *rhs, TupleValue *res, ArithOp op) {
  // TODO: 运算异常
}

void DateValue::compute(TupleValue *rhs, TupleValue *res, ArithOp op) {
  // TODO: 运算异常
}