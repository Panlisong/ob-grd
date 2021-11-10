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
#include "sql/parser/parse_defs.h"
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
      Tuple product;
      product.append(outer);
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

static void col_to_string(SelectExpr *expr, std::string &res, bool multi) {
  assert(expr->is_attr == 1);
  RelAttr *attr = expr->attr;
  const char *table_name = attr->relation_name;
  const char *field_name = attr->attribute_name;
  if (strcmp("*", field_name) == 0) {
    assert(expr->func == COUNT_FUNC);
    if (table_name == nullptr) {
      res = func[expr->func] + "(" + field_name + ")";
    } else {
      res = func[expr->func] + "(" + table_name + "." + field_name + ")";
    }
  } else {
    std::string pre = multi ? table_name + std::string(".") : "";
    if (expr->func != COLUMN) {
      res = func[expr->func] + "(" + pre + field_name + ")";
    } else {
      res = pre + field_name;
    }
  }
}

TupleConDescNode *create_project_desc_node(SelectExpr *expr,
                                           const TupleSchema &product,
                                           std::string &alias, bool multi) {
  if (expr->has_subexpr == 1) {
    TupleConDescNode *left =
        create_project_desc_node(expr->left, product, alias, multi);
    alias += op_str_table[expr->arithOp];
    TupleConDescNode *right =
        create_project_desc_node(expr->right, product, alias, multi);
    return new TupleConDescInternal(expr->arithOp, left, right);
  }
  // 非表达式
  // COLUMN: 'T.A' 'A'
  // FUNC: 'func(T.A)' 'func(A)' 'func(T.*)' 'func(*)'
  if (expr->is_attr) {
    // 初始化别名
    std::string name;
    col_to_string(expr, name, multi);
    alias += name;

    RelAttr *attr = expr->attr;
    const char *table_name = attr->relation_name;
    const char *field_name = attr->attribute_name;
    if (strcmp("*", field_name) == 0) {
      assert(expr->func == COUNT_FUNC);
      return new TupleConDescAttr(INTS, -1);
    }

    int idx = product.index_of_field(table_name, field_name);
    return new TupleConDescAttr(product.field(idx).type(), idx);
  } else {
    TupleConDescValue *node = new TupleConDescValue(expr->value);
    alias += node->to_string();
    return node;
  }
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

ProjectionDesc *ProjectionDesc::get_projection_desc(SelectExpr *expr,
                                                    TupleSet &in) {
  ProjectionDesc *projection_desc = nullptr;
  switch (expr->func) {
  case COLUMN:
    projection_desc = new ProjectionDesc;
    break;
  case MAX_FUNC:
    projection_desc = new MaxDesc;
    break;
  case MIN_FUNC:
    projection_desc = new MinDesc;
    break;
  case AVG_FUNC:
  case COUNT_FUNC: {
    int total;
    const RelAttr *attr = expr->attr;
    const char *table_name = attr->relation_name;
    const char *field_name = attr->attribute_name;
    if (strcmp("*", field_name) == 0) {
      total = in.size();
    } else {
      int idx = in.get_schema().index_of_field(table_name, field_name);
      total = in.not_null_size(idx);
    }
    if (expr->func == AVG_FUNC) {
      projection_desc = new AvgDesc(total);
    } else {
      projection_desc = new CountDesc(total);
    }
  } break;
  default:
    LOG_ERROR("Unkown aggregate function type %d", func);
    break;
  }
  return projection_desc;
}

/////////////////////////////////////////////////////////////////////////////
ProjectExeNode::~ProjectExeNode() {
  for (ProjectionDesc *&desc : descs_) {
    delete desc;
  }
  descs_.clear();
}

RC ProjectExeNode::init(TupleSet &&in, std::vector<ProjectionDesc *> &&descs) {
  RC rc = RC::SUCCESS;
  in_ = std::move(in);
  descs_ = std::move(descs);
  for (auto *&desc : descs_) {
    out_schema_.add(desc->type(), COLUMN, "", "", desc->to_string().c_str());
    auto is_aggregate = dynamic_cast<AggregateDesc *>(desc);
    if (is_aggregate != nullptr) {
      has_aggregate_ = true;
      auto is_count = dynamic_cast<CountDesc *>(desc);
      if (is_count == nullptr) {
        only_count_ = false;
      }
    }
  }
  return rc;
}

RC ProjectExeNode::execute(TupleSet &tuple_set) {
  tuple_set.clear();

  for (auto &t : in_.tuples()) {
    Tuple tuple;
    for (auto *&desc : descs_) {
      tuple.add(desc->execute(t));
    }
    tuple_set.add(std::move(tuple));
  }

  if (has_aggregate_) {
    Tuple tuple;
    tuple.append(tuple_set.get(tuple_set.size() - 1));
    tuple_set.clear();
    tuple_set.add(std::move(tuple));
  }

  tuple_set.set_schema(out_schema_);
  return RC::SUCCESS;
}
