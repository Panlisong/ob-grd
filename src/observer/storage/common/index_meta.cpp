/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString UNIQUE_FLAG("is_unique");

RC IndexMeta::init(const char *name, const std::vector<std::string> &fields,
                   bool unique) {
  if (nullptr == name || common::is_blank(name)) {
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  fields_ = fields;
  unique_ = unique;
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const {
  json_value[FIELD_NAME] = name_;

  // 索引属性字段
  if (fields_.size() == 1) {
    json_value[FIELD_FIELD_NAME] = fields_.front();
  } else {
    // multi column index
    Json::Value attrs;
    for (int i = 0; i < static_cast<int>(fields_.size()); i++) {
      attrs[i] = fields_.at(i);
    }
    json_value[FIELD_FIELD_NAME] = attrs;
  }

  // unique标识
  json_value[UNIQUE_FLAG] = unique_;
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value,
                        IndexMeta &index) {
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  const Json::Value &unique = json_value[UNIQUE_FLAG];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s",
              name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!field_value.isString() && !field_value.isArray()) {
    LOG_ERROR(
        "Field name of index [%s] is not a string/string array. json value=%s",
        name_value.asCString(), field_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!unique.isBool()) {
    LOG_ERROR("unique flag is not a boolean value. json value=%s",
              unique.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  std::vector<std::string> fields;
  if (field_value.isString()) {
    const FieldMeta *field = table.field(field_value.asCString());
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s",
                name_value.asCString(), field_value.asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields.push_back(field->name());
  } else if (field_value.isArray()) {
    for (int i = 0; i < field_value.size(); i++) {
      fields.push_back(field_value[i].asString());
    }
  }

  return index.init(name_value.asCString(), fields, unique.asBool());
}

const char *IndexMeta::name() const { return name_.c_str(); }

int IndexMeta::field_num() const { return fields_.size(); }

const char *IndexMeta::field(int i) const { return fields_[i].c_str(); }

bool IndexMeta::is_unique() const { return unique_; }

void IndexMeta::desc(std::ostream &os) const {
  os << "index name=" << name_ << ", field=" << fields_.front();
  for (size_t i = 1; i < fields_.size(); i++) {
    os << ", " << fields_.at(i);
  }
}