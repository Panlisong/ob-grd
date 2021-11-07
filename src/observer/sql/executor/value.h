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

#ifndef __OBSERVER_SQL_EXECUTOR_VALUE_H_
#define __OBSERVER_SQL_EXECUTOR_VALUE_H_

#include <cassert>
#include <string.h>
#include <time.h>

#include <iomanip>
#include <ostream>
#include <string>

#include "common/log/log.h"
#include "sql/parser/parse.h"

class TupleValue {
public:
  TupleValue() = default;
  virtual ~TupleValue() = default;

  virtual void get_value(void *data) const = 0;
  virtual void to_string(std::ostream &os) const = 0;
  virtual std::string to_string() const = 0;
  virtual int compare(const TupleValue &other) const = 0;
  virtual bool is_null() const = 0;
  virtual void compute(TupleValue *rhs, TupleValue *&res, ArithOp op) = 0;

private:
};

class IntValue : public TupleValue {
public:
  explicit IntValue(int value, bool is_null)
      : value_(value), is_null_(is_null) {}

  void get_value(void *data) const override { *(int *)data = value_; }

  void to_string(std::ostream &os) const override {
    if (is_null_) {
      os << "null";
      return;
    }
    os << value_;
  }
  std::string to_string() const override {
    if (is_null_) {
      return "null";
    }
    return std::to_string(value_);
  }

  int compare(const TupleValue &other) const override {
    if (is_null() && other.is_null()) {
      return 0;
    }
    const IntValue &int_other = (const IntValue &)other;
    return value_ - int_other.value_;
  }

  bool is_null() const override { return is_null_; }

  void compute(TupleValue *rhs, TupleValue *&res, ArithOp op) override;

private:
  int value_;
  bool is_null_;
};

class FloatValue : public TupleValue {
public:
  explicit FloatValue(float value, bool is_null)
      : value_(value), is_null_(is_null) {}

  void get_value(void *data) const override { *(float *)data = value_; }

  std::string float_string() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << value_;
    std::string str = ss.str();

    assert(str.find('.') != std::string::npos);
    // Remove trailing zeroes
    str = str.substr(0, str.find_last_not_of('0') + 1);
    // If the decimal point is now the last character, remove that as well
    if (str.find('.') == str.size() - 1) {
      str = str.substr(0, str.size() - 1);
    }
    return str;
  }
  void to_string(std::ostream &os) const override {
    if (is_null_) {
      os << "null";
      return;
    }
    os << float_string();
  }
  std::string to_string() const override {
    if (is_null_) {
      return "null";
    }
    return float_string();
  }

  int compare(const TupleValue &other) const override {
    if (is_null() == other.is_null()) {
      return 0;
    }
    const FloatValue &float_other = (const FloatValue &)other;
    float result = value_ - float_other.value_;
    if (result > 0) { // 浮点数没有考虑精度问题
      return 1;
    }
    if (result < 0) {
      return -1;
    }
    return 0;
  }

  bool is_null() const override { return is_null_; }

  void compute(TupleValue *rhs, TupleValue *&res, ArithOp op) override;

private:
  float value_;
  bool is_null_;
};

class StringValue : public TupleValue {
public:
  StringValue(const char *value, int len, int is_null)
      : value_(value, len), is_null_(is_null) {}
  explicit StringValue(const char *value) : value_(value) {}

  void get_value(void *data) const override { *(std::string *)data = value_; }

  void to_string(std::ostream &os) const override {
    if (is_null_) {
      os << "null";
      return;
    }
    os << value_;
  }
  std::string to_string() const override {
    if (is_null_) {
      return "null";
    }
    return value_;
  }

  int compare(const TupleValue &other) const override {
    if (is_null() == other.is_null()) {
      return 0;
    }
    const StringValue &string_other = (const StringValue &)other;
    return strcmp(value_.c_str(), string_other.value_.c_str());
  }

  bool is_null() const override { return is_null_; }

  void compute(TupleValue *rhs, TupleValue *&res, ArithOp op) override;

private:
  std::string value_;
  bool is_null_;
};

class DateValue : public TupleValue {
public:
  explicit DateValue(time_t value, bool is_null)
      : value_(value), is_null_(is_null) {}

  void get_value(void *data) const override { *(time_t *)data = value_; }

  std::string date_string() const {
    tm *tp = gmtime(&value_);
    char s[36];
    memset(s, 0, sizeof s);
    std::snprintf(s, sizeof(s), "%04d-%02d-%02d", tp->tm_year + 1900,
                  tp->tm_mon + 1, tp->tm_mday);
    return std::string(s);
  }
  void to_string(std::ostream &os) const override {
    if (is_null_) {
      os << "null";
      return;
    }
    os << date_string();
  }
  std::string to_string() const override {
    if (is_null_) {
      return "null";
    }
    return date_string();
  }

  int compare(const TupleValue &other) const override {
    if (is_null() == other.is_null()) {
      return 0;
    }
    const DateValue &timestamp_other = (const DateValue &)other;
    long long res = value_ - timestamp_other.value_;
    if (res > 0LL) {
      return 1;
    } else if (res < 0LL) {
      return -1;
    }
    return 0;
  }

  bool is_null() const override { return is_null_; }

  void compute(TupleValue *rhs, TupleValue *&res, ArithOp op) override;

private:
  time_t value_;
  bool is_null_;
};

#endif //__OBSERVER_SQL_EXECUTOR_VALUE_H_
