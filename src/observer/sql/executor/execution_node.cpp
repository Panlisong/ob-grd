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

#include "sql/executor/execution_node.h"
#include "common/log/log.h"
#include "storage/common/table.h"

SelectExeNode::SelectExeNode() : table_(nullptr) {}

SelectExeNode::~SelectExeNode() {
  for (DefaultConditionFilter *&filter : condition_filters_) {
    delete filter;
  }
  condition_filters_.clear();
}

RC SelectExeNode::init(
    Trx *trx, Table *table, TupleSchema &&tuple_schema,
    std::vector<DefaultConditionFilter *> &&condition_filters) {
  trx_ = trx;
  table_ = table;
  tuple_schema_ = tuple_schema;
  condition_filters_ = std::move(condition_filters);
  return RC::SUCCESS;
}

void record_reader(const char *data, void *context) {
  TupleRecordConverter *converter = (TupleRecordConverter *)context;
  converter->add_record(data);
}
RC SelectExeNode::execute(TupleSet &tuple_set) {
  CompositeConditionFilter condition_filter;
  condition_filter.init((const ConditionFilter **)condition_filters_.data(),
                        condition_filters_.size());

  tuple_set.clear();
  tuple_set.set_schema(tuple_schema_);
  TupleRecordConverter converter(table_, tuple_set);
  return table_->scan_record(trx_, &condition_filter, -1, (void *)&converter,
                             record_reader);
}

/////////////////////////////////////////////////////////////////////////////
JoinExeNode::JoinExeNode() {}

JoinExeNode::~JoinExeNode() {
  for (TupleFilter *&filter : tuple_filters_) {
    delete filter;
  }
  tuple_filters_.clear();
}

RC JoinExeNode::init(Trx *trx, TupleSet &tl, TupleSet &tr,
                     TupleSchema &&tuple_schema,
                     std::vector<TupleFilter *> &&tuple_filters) {
  trx_ = trx;
  tl_ = std::move(tl);
  tr_ = std::move(tr);
  tuple_schema_ = tuple_schema;
  tuple_filters_ = std::move(tuple_filters);
  return RC::SUCCESS;
}

RC JoinExeNode::execute(TupleSet &tuple_set) {
  tuple_set.clear();
  tuple_set.set_schema(tuple_schema_);
  for (auto &outer : tl_.tuples()) {
    for (auto &inner : tr_.tuples()) {
      bool is_result = true;
      // 遍历所有与两个TupleSet相关的过滤条件
      for (auto &tuple_filter : tuple_filters_) {
        if (!tuple_filter->filter(outer, inner)) {
          is_result = false;
          break;
        }
      }
      if (is_result) {
        Tuple tuple;
        for (const TupleField &field : tuple_schema_.fields()) {
          int field_idx_in_outer = tl_.get_schema().index_of_field(
              field.table_name(), field.field_name());
          int feild_idx_in_inner = tr_.get_schema().index_of_field(
              field.table_name(), field.field_name());
          if (field_idx_in_outer != -1) {
            tuple.add(outer.get_pointer(field_idx_in_outer));
          } else {
            tuple.add(inner.get_pointer(feild_idx_in_inner));
          }
        }
        tuple_set.add(std::move(tuple));
      }
    }
  }
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////
RC ProjectExeNode::init(Trx *trx, TupleSet &in, TupleSchema &&tuple_schema) {
  trx_ = trx;
  in_ = std::move(in);
  out_schema_ = tuple_schema;
  for (size_t i = 0; i < out_schema_.fields().size(); i++) {
    auto func = out_schema_.field(i).func();
    if (func != COLUMN) {
      has_aggregate_ = true;
      if (func != COUNT_FUNC) {
        only_count_ = false;
        break;
      }
    }
  }
  return RC::SUCCESS;
}

static float get_float_value(const TupleValue &tuple, const TupleField &field) {
  if (field.func() == AVG_FUNC && field.type() == INTS) {
    // avg()参数为INT时，需要转换
    int v;
    tuple.get_value(&v);
    return (float)v;
  }
  float v;
  tuple.get_value(&v);
  return v;
}

RC ProjectExeNode::execute_aggregate(TupleSet &tuple_set) {
  // 目前TupleSet只有一组所以直接保留第一个tuple然后迭代即可
  Tuple cur;
  // 1. 初始化
  for (const TupleField &field : out_schema_.fields()) {
    if (field.func() == COUNT_FUNC) {
      // TODO：支持NULL时需要修正
      cur.add(in_.size());
    } else {
      // max min avg 以及普通列初值都是第一个值
      // 且除count外max min avg参数均不可能为
      int field_in_tuple = in_.get_schema().index_of_field(field.table_name(),
                                                           field.field_name());
      auto &t = in_.get(0);
      assert(field_in_tuple != -1);

      if (field.func() == AVG_FUNC && field.type() == INTS) {
        // avg()参数为INT时，需要转换
        int v;
        t.get(field_in_tuple).get_value(&v);
        cur.add((float)v);
      } else {
        cur.add(t.get_pointer(field_in_tuple));
      }
    }
  }

  // 如果只有COUNT则无需迭代
  if (only_count_) {
    tuple_set.add(std::move(cur));
    return RC::SUCCESS;
  }

  // 2.从第二行开始迭代
  for (int i = 1; i < in_.size(); i++) {
    Tuple tmp;
    auto &next = in_.get(i);
    for (size_t j = 0; j < out_schema_.fields().size(); j++) {
      const TupleField &field = out_schema_.field(j);
      int field_in_tuple = in_.get_schema().index_of_field(field.table_name(),
                                                           field.field_name());
      assert(field_in_tuple != -1);
      auto &next_value = next.get(field_in_tuple);
      switch (field.func()) {
      case AVG_FUNC: {
        // 上面的初始化确保AVG列一定为float
        float v1;
        float v2 = get_float_value(next_value, field);
        cur.get(j).get_value(&v1);

        float ans = v1 + v2;
        if (i + 1 == in_.size()) {
          ans /= in_.size();
        }
        tmp.add(ans);
      } break;
      case MAX_FUNC:
        if (next_value.compare(cur.get(j)) > 0) {
          tmp.add(next.get_pointer(j));
        } else {
          tmp.add(cur.get_pointer(j)); // 保持不变
        }
        break;
      case MIN_FUNC:
        if (next_value.compare(cur.get(j)) < 0) {
          tmp.add(next.get_pointer(field_in_tuple));
          break;
        }
      case COUNT_FUNC:
      case COLUMN:
        tmp.add(cur.get_pointer(j)); // 保持不变
      default:
        break;
      }
    }
    cur = std::move(tmp);
  }
  tuple_set.add(std::move(cur));
  return RC::SUCCESS;
}

RC ProjectExeNode::execute(TupleSet &tuple_set) {
  tuple_set.clear();
  tuple_set.set_schema(out_schema_);

  if (has_aggregate_) {
    return execute_aggregate(tuple_set);
  }

  for (auto &t : in_.tuples()) {
    Tuple tuple;
    for (const TupleField &field : out_schema_.fields()) {
      int field_in_tuple = in_.get_schema().index_of_field(field.table_name(),
                                                           field.field_name());
      assert(field_in_tuple != -1);
      tuple.add(t.get_pointer(field_in_tuple));
    }
    tuple_set.add(std::move(tuple));
  }
  return RC::SUCCESS;
}