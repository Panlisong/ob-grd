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

TupleConDescNode *create_project_desc_node(SelectExpr *expr,
                                           TupleSchema &product,
                                           std::string &alias, bool multi);

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
  tuple_schema_ = std::move(tuple_schema);
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

RC JoinExeNode::init(TupleSet &&tl, TupleSet &&tr,
                     std::vector<TupleFilter *> &&tuple_filters) {
  tl_ = std::move(tl);
  tr_ = std::move(tr);
  TupleSchema scm = tl_.get_schema();
  scm.append(tr_.get_schema());
  tuple_schema_ = std::move(scm);
  tuple_filters_ = std::move(tuple_filters);
  return RC::SUCCESS;
}

RC JoinExeNode::execute(TupleSet &tuple_set) {
  tuple_set.clear();
  tuple_set.set_schema(tuple_schema_);
  for (auto &outer : tl_.tuples()) {
    for (auto &inner : tr_.tuples()) {
      Tuple product = outer;
      product.append(inner);
      bool is_result = true;
      // 遍历所有与两个TupleSet相关的过滤条件
      for (auto &tuple_filter : tuple_filters_) {
        if (!tuple_filter->filter(product)) {
          is_result = false;
          break;
        }
      }
      if (is_result) {
        // Tuple tuple;
        // for (const TupleField &field : tuple_schema_.fields()) {
        //   int field_idx_in_outer = tl_.get_schema().index_of_field(
        //       field.table_name(), field.field_name());
        //   int feild_idx_in_inner = tr_.get_schema().index_of_field(
        //       field.table_name(), field.field_name());
        //   if (field_idx_in_outer != -1) {
        //     tuple.add(outer.get_pointer(field_idx_in_outer));
        //   } else {
        //     tuple.add(inner.get_pointer(feild_idx_in_inner));
        //   }
        // }
        tuple_set.add(std::move(product));
      }
    }
  }
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////
ProjectionDesc::~ProjectionDesc() { delete desc_; }

static std::string op_str_table[NO_ARITH_OP] = {"+", "-", "*", "/"};
static std::string func[FUNC_NUM] = {"", "", "MAX", "MIN", "COUNT", "AVG"};

TupleConDescNode *create_project_desc_node(SelectExpr *expr,
                                           const TupleSchema &product,
                                           std::string &alias, bool multi) {
  if (expr->has_subexpr == 0) {
    // 非表达式 不可能为EXPR
    // COLUMN: 'T.A' 'A'
    // FUNC: 'func(T.A)' 'func(A)'
    if (expr->is_attr) {
      RelAttr *attr = expr->attr;
      const char *table_name = attr->relation_name;
      const char *field_name = attr->attribute_name;
      // 初始化别名
      std::string pre = multi ? table_name + std::string(".") : "";
      if (expr->func != COLUMN) {
        alias += func[expr->func] + "(" + pre + field_name + ")";
      } else {
        alias += pre + field_name;
      }
      int idx = product.index_of_field(table_name, field_name);
      return new TupleConDescAttr(product.field(idx).type(), idx);
    } else {
      TupleConDescValue *node = new TupleConDescValue(&expr->value);
      alias += node->to_string();
      return node;
    }
  }
  TupleConDescNode *left =
      create_project_desc_node(expr->left, product, alias, multi);
  alias += op_str_table[expr->arithOp];
  TupleConDescNode *right =
      create_project_desc_node(expr->right, product, alias, multi);
  return new TupleConDescInternal(expr->arithOp, left, right);
}

RC ProjectionDesc::init(SelectExpr *expr, const TupleSchema &product,
                        bool multi) {
  desc_ = create_project_desc_node(expr, product, alias_, multi);
  return RC::SUCCESS;
}

RC ProjectionDesc::from_table(Table *table, const TupleSchema &product,
                              std::vector<ProjectionDesc *> &descs,
                              bool multi) {
  RC rc = RC::SUCCESS;
  const char *table_name = table->name();
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = 0; i < field_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      SelectExpr expr;
      RelAttr attr;
      attr_init(&attr, table_name, field_meta->name());
      select_attr_init(&expr, &attr);
      ProjectionDesc *desc = new ProjectionDesc;
      rc = desc->init(&expr, product, multi);
      if (rc != RC::SUCCESS) {
        delete desc;
        return rc;
      }
      descs.push_back(desc);
    }
  }
  return rc;
}

/////////////////////////////////////////////////////////////////////////////
RC ProjectExeNode::init(TupleSet &&in, std::vector<ProjectionDesc *> &&descs) {
  RC rc = RC::SUCCESS;
  in_ = std::move(in);
  descs_ = std::move(descs);
  for (auto *&desc : descs_) {
    out_schema_.add(desc->type(), COLUMN, "", "", desc->to_string().c_str());
  }
  return rc;
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
      if (strcmp(field.field_name(), "*") == 0) {
        // count(*)
        cur.add(in_.size(), false);
      } else {
        // count(field)
        int column = in_.get_schema().index_of_field(field.table_name(),
                                                     field.field_name());
        cur.add(in_.not_null_size(column), false);
      }
    } else {
      // max min avg 以及普通列初值都是第一个值
      // 且除count外max min avg参数均不可能为
      int column = in_.get_schema().index_of_field(field.table_name(),
                                                   field.field_name());
      auto &t = in_.get(0);
      assert(column != -1);

      if (field.func() == AVG_FUNC && field.type() == INTS) {
        // avg()参数为INT时，需要转换
        int v;
        t.get(column).get_value(&v);
        cur.add((float)v, false);
      } else {
        cur.add(t.get_pointer(column));
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
      int column = in_.get_schema().index_of_field(field.table_name(),
                                                   field.field_name());
      switch (field.func()) {
      case AVG_FUNC: {
        // 上面的初始化确保AVG列一定为float
        float v1;
        float v2 = get_float_value(next.get(column), field);
        const TupleValue &value = cur.get(j);
        if (value.is_null()) {
          continue;
        }
        value.get_value(&v1);

        float ans = v1 + v2;
        if (i + 1 == in_.size()) {
          ans /= in_.not_null_size(column);
        }
        tmp.add(ans, false);
      } break;
      case MAX_FUNC: {
        const TupleValue &value = cur.get(j);
        if (value.is_null()) {
          continue;
        }
        if (next.get(column).compare(value) > 0) {
          tmp.add(next.get_pointer(column));
        } else {
          tmp.add(cur.get_pointer(j)); // 保持不变
        }
      } break;
      case MIN_FUNC: {
        const TupleValue &value = cur.get(j);
        if (value.is_null()) {
          continue;
        }
        if (next.get(column).compare(value) < 0) {
          tmp.add(next.get_pointer(column));
          break;
        }
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
    for (auto *&desc : descs_) {
      tuple.add(desc->execute(t));
    }
    tuple_set.add(std::move(tuple));
  }
  return RC::SUCCESS;
}
