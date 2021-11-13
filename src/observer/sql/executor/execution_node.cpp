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

static std::string op_str_table[NO_ARITH_OP] = {"+", "-", "*", "/", "-"};
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
    TupleConDescNode *left = nullptr;
    TupleConDescNode *right = nullptr;

    // 双元运算
    if (expr->left != nullptr && expr->right != nullptr) {
      std::string lalias;
      std::string ralias;
      left = create_project_desc_node(expr->left, product, lalias, multi);
      right = create_project_desc_node(expr->right, product, ralias, multi);
      alias = lalias + op_str_table[expr->arithOp] + ralias;
    } else {
      // 单元运算
      std::string child;
      right = create_project_desc_node(expr->right, product, child, multi);
      alias = op_str_table[expr->arithOp] + child;
    }

    if (expr->has_brace == 1) {
      alias = "(" + alias + ")";
    }

    if (left == nullptr) {
      return new TupleConDescUnary(expr->arithOp, right);
    }
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
  case EXPR:
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


void sort_tuple(TupleSet &tuple_set , std::vector<int>indexes , std::vector<int>ascs){
  int cur_size = tuple_set.size();
  // for(size_t i = 0 ; i < tuple_set.tuples().size() ; ++i){
  //   tmp_tuple.append(tuple_set.tuples()[i]);
  //   cur_tuples.add(tmp_tuple);
  // }
  int compare=0,val1,val2;
  float f1,f2;
  std::string s1,s2;
  time_t t1,t2;
  Tuple swaptuple;
  size_t index,id,cur_asc;
  for(int i = 0 ; i < cur_size - 1 ; ++i){
    for(int j = i + 1 ; j < cur_size ; ++j){
      compare=index=0;
      while(compare==0 && index < indexes.size()){
        id=indexes[index];
        cur_asc=ascs[index];
        AttrType tmp=tuple_set.get_schema().field(id).type();
        switch(tmp){
          case INTS:
          {
            tuple_set.tuples()[i].get(id).get_value(&val1);
            tuple_set.tuples()[j].get(id).get_value(&val2);
            if (val1 - val2 < -1e-6) {
              compare =-1;
            } else if (val1- val2 > 1e-6) {
              compare = 1;
            } else {
              compare = 0;
            }
            break;
          }
          case CHARS:
          {
            tuple_set.tuples()[i].get(id).get_value(&s1);
            tuple_set.tuples()[j].get(id).get_value(&s2);
            compare = strcmp(s1.c_str(), s2.c_str());
            break;
          }
          case FLOATS:
          {
            tuple_set.tuples()[i].get(id).get_value(&f1);
            tuple_set.tuples()[j].get(id).get_value(&f2);
            if (f1 - f2 < -1e-6) {
              compare = -1;
            } else if (f1- f2 > 1e-6) {
              compare = 1;
            } else {
              compare = 0;
            }
            break;
          }
          case DATES:
          {
            tuple_set.tuples()[i].get(id).get_value(&t1);
            tuple_set.tuples()[j].get(id).get_value(&t2);
            long long res = t1 - t2;
            if(res > 0LL) {
              compare = 1;
            } else if (res < 0LL) {
              compare = -1;
            }
            compare = 0;
            break;
          }
          default:
          {
            LOG_ERROR("Unsupported sort type.\n");
            return;
          }
        
        }
        ++index;
      }
      if((compare < 0 && cur_asc == 0) || (compare > 0 && cur_asc == 1)){
        swaptuple.update(tuple_set.tuples()[i]);
        tuple_set.update(i,tuple_set.tuples()[j]);
        tuple_set.update(j,swaptuple);
      }
    }
  }
  return;
}

RC GroupExeNode::execute(TupleSet &tuple_set){
  RC rc = RC::SUCCESS;
  size_t group_num = GroupExeNode::get_group_num();
  GroupByList* group_list = GroupExeNode::get_groups();
  RelAttr* cur_attr;
  int index = -1 ;
  TupleSchema cur_schema=tuple_set.schema();
  std::vector<TupleField> cur_field;
  std::vector<int>group_indexes;
  std::vector<int>flags;
  for (size_t i = 0; i < group_num ; ++i){
    index = -1;
    flags.push_back(0);
    cur_attr = group_list->at(i);
    if(cur_attr->relation_name==nullptr){
      //sort by the first paired attr in the tuple schema 
      cur_field = cur_schema.fields();
      for(size_t i = 0; i < cur_field.size() ; ++i){
        if(strcmp(cur_field[i].field_name() , cur_attr->attribute_name) == 0){
          index = i;
          break;
        }
      }
    } else {
      index = cur_schema.index_of_field(cur_attr->relation_name, 
                                         cur_attr->attribute_name);
    }
    if(index != -1){
      group_indexes.push_back(index);
    } else {
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
  }
  sort_tuple(tuple_set, group_indexes, flags); 
  return rc; 
}

RC OrderExeNode::execute(TupleSet &tuple_set){
  //TupleSet::TupleSchema::index_of_field
  //TupleValue::compare
  // CHARS,
  // INTS,
  // FLOATS,
  // ATTR_NULL,
  // ATTR_TEXT,
  // DATES
  //firstly implement those first 4 in the value.h that have compare()
  RC rc = RC::SUCCESS;
  size_t order_num = OrderExeNode::get_order_num();
  OrderCol* cur_col;
  OrderColList* cur_list = OrderExeNode::get_orders();
  int index = -1 ;
  std::vector<int> flags; //1:升序，0：降序
  TupleSchema cur_schema=tuple_set.schema();
  std::vector<TupleField> cur_field;
  std::vector<int>compare_indexes;
  for (size_t i = 0; i < order_num ; ++i){
    index = -1;
    cur_col = cur_list->at(i);
    flags.push_back(cur_col->asc);
    if(cur_col->attr->relation_name==nullptr){
      //sort by the first paired attr in the tuple schema 
      cur_field = cur_schema.fields();
      for(size_t i = 0; i < cur_field.size() ; ++i){
        if(strcmp(cur_field[i].field_name() , cur_col->attr->attribute_name) == 0){
          index = i;
          break;
        }
      }
    } else {
      index = cur_schema.index_of_field(cur_col->attr->relation_name, 
                                         cur_col->attr->attribute_name);
    }
    if(index != -1){
      compare_indexes.push_back(index);
    } else {
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
  }
  sort_tuple(tuple_set, compare_indexes, flags); 
  return rc; 
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

  if (has_aggregate_ && tuple_set.size() > 0) {
    Tuple tuple;
    tuple.append(tuple_set.get(tuple_set.size() - 1));
    tuple_set.clear();
    tuple_set.add(std::move(tuple));
  }

  tuple_set.set_schema(out_schema_);
  return RC::SUCCESS;
}
