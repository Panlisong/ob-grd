/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/12.
//

#ifndef __OBSERVER_STORAGE_COMMON_INDEX_META_H__
#define __OBSERVER_STORAGE_COMMON_INDEX_META_H__

#include "rc.h"
#include <string>
#include <vector>

class TableMeta;
class FieldMeta;

namespace Json {
class Value;
} // namespace Json

class IndexMeta {
public:
  IndexMeta() = default;

  RC init(const char *name, const std::vector<std::string> &fields,
          bool unique = false);

public:
  const char *name() const;
  int field_num() const;
  const char *field(int index) const;
  bool is_unique() const;

  void desc(std::ostream &os) const;

public:
  void to_json(Json::Value &json_value) const;
  static RC from_json(const TableMeta &table, const Json::Value &json_value,
                      IndexMeta &index);

private:
  std::string name_;
  std::vector<std::string> fields_;
  bool unique_;
};
#endif // __OBSERVER_STORAGE_COMMON_INDEX_META_H__