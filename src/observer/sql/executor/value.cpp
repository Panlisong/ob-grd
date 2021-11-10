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

void IntValue::compute(TupleValue *rhs, TupleValue *&res, ArithOp op) {
  float lvalue = float(value_);
  float rvalue;
  if (rhs->type() == FLOATS) {
    rhs->get_value(&rvalue);
  } else {
    int int_rvalue;
    rhs->get_value(&int_rvalue);
    rvalue = float(int_rvalue);
  }
  if (op == DIV && (1e-6 < rvalue && rvalue < 1e-6)) {
    res = new NullValue();
    return;
  }

  float result = 0.0;
  switch (op) {
  case ADD:
    result = lvalue + rvalue;
    break;
  case SUB:
    result = lvalue - rvalue;
    break;
  case MUL:
    result = lvalue * rvalue;
    break;
  case DIV:
    result = lvalue / rvalue;
    break;
  default:
    LOG_PANIC("Unkown arithop type: %d", op);
    break;
  }

  if (rhs->type() == INTS) {
    res = new IntValue(int(result));
  } else {
    res = new FloatValue(result);
  }
}

void FloatValue::compute(TupleValue *rhs, TupleValue *&res, ArithOp op) {
  float lvalue = value_;
  float rvalue;
  if (rhs->type() == FLOATS) {
    rhs->get_value(&rvalue);
  } else {
    int int_rvalue;
    rhs->get_value(&int_rvalue);
    rvalue = float(int_rvalue);
  }
  if (op == DIV && (1e-6 < rvalue && rvalue < 1e-6)) {
    res = new NullValue();
    return;
  }

  float result = 0.0;
  switch (op) {
  case ADD:
    result = lvalue + rvalue;
    break;
  case SUB:
    result = lvalue - rvalue;
    break;
  case MUL:
    result = lvalue * rvalue;
    break;
  case DIV:
    result = lvalue / rvalue;
    break;
  default:
    LOG_PANIC("Unkown arithop type: %d", op);
    break;
  }

  res = new FloatValue(result);
}

void StringValue::compute(TupleValue *rhs, TupleValue *&res, ArithOp op) {
  res = new NullValue();
}

void DateValue::compute(TupleValue *rhs, TupleValue *&res, ArithOp op) {
  res = new NullValue();
}

void NullValue::compute(TupleValue *rhs, TupleValue *&res, ArithOp op) {
  res = new NullValue();
}
