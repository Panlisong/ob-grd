/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//

#include "sql/parser/parse.h"
#include "common/log/log.h"
#include "rc.h"
#include "sql/parser/parse_defs.h"
#include <mutex>

RC parse(char *st, Query *sqln);

/*************************** Helper ******************************/
bool is_comparable(AttrType lt, AttrType rt) {
  if (lt == ATTR_NULL || rt == ATTR_NULL) {
    return true;
  }
  if (lt == DATES || rt == DATES || lt == CHARS || rt == CHARS) {
    return lt == rt;
  }
  return true;
}
bool is_computable(AttrType left, AttrType right) {
  if (left == ATTR_NULL || right == ATTR_NULL) {
    return false;
  }
  if (left == DATES || right == DATES || left == CHARS || right == CHARS) {
    return false;
  }
  return true;
}

CompOp get_neg_comp_op(CompOp op) {
  switch (op) {
  case GREAT_EQUAL:
    return LESS_EQUAL;
  case LESS_EQUAL:
    return GREAT_EQUAL;
  case GREAT_THAN:
    return LESS_THAN;
  case LESS_THAN:
    return GREAT_THAN;
  default:
    /* '==' / '<>' / 'in' / 'not in' / 'is' / 'is not' */
    return op;
  }
}

int check_date(int year, int month, int day) {
  int day_max[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  bool leap = false;
  if (year % 100) {
    leap = (year % 4) == 0;
  } else {
    leap = (year % 400) == 0;
  }
  if (leap) {
    day_max[2] = 29;
  }
  // check day
  return day <= day_max[month];
}

void set_expr_parent(ConditionExpr *expr, Condition *cond) {
  if (expr == nullptr) {
    return;
  }
  if (expr->left != nullptr) {
    set_expr_parent(expr->left, cond);
  }
  if (expr->right != nullptr) {
    set_expr_parent(expr->right, cond);
  }
  expr->parent = cond;
}

void set_expr_parent(SelectExpr *expr, Selects *select) {
  if (expr == nullptr) {
    return;
  }
  if (expr->left != nullptr) {
    set_expr_parent(expr->left, select);
  }
  if (expr->right != nullptr) {
    set_expr_parent(expr->right, select);
  }
  expr->parent = select;
}
/*************************** Initialize ******************************/
void table_ref_init(TableRef *ref, int is_join, const char *relation_name,
                    TableRef *child, ConditionList *cond_list) {
  ref->is_join = is_join;
  ref->relation_name = strdup(relation_name);
  ref->child = child;
  ref->conditions = cond_list;
  ref->cond_num = cond_list->size();
}

void attr_init(RelAttr *relation_attr, const char *relation_name,
               const char *attribute_name) {
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
}

void value_init_integer(Value *value, int v) {
  value->type = INTS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_float(Value *value, float v) {
  value->type = FLOATS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_string(Value *value, const char *v) {
  value->type = CHARS;
  value->data = strdup(v);
  value->len = strlen(v);
}

void value_init_date(Value *value, time_t v) {
  value->type = DATES;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_null(Value *value) {
  value->type = ATTR_NULL;
  value->data = nullptr;
}

/////////////////////////////// Condition  ////////////////////////////////////
void non_subquery_cond_init(Condition *cond, ConditionExpr *left,
                            ConditionExpr *right, CompOp op) {
  cond->left = left;
  cond->right = right;
  cond->comp = op;
  set_expr_parent(left, cond);
  set_expr_parent(right, cond);
  cond->binded_conds = new CondExprList;
  cond->binded_exprs = new SelectExprList;
  ////////////////////////
  cond->is_subquery = 0;
  cond->left_subquery = nullptr;
  cond->right_subquery = nullptr;
}
void com_subquery_init(Condition *cond, Selects *left, Selects *right,
                       CompOp op) {
  cond->is_subquery = 1;
  cond->left_subquery = left;
  cond->right_subquery = right;
  cond->comp = op;
  left->parent = cond;
  right->parent = cond;
  cond->binded_conds = new CondExprList;
  cond->binded_exprs = new SelectExprList;
  //////////////////////////
  cond->left = nullptr;
  cond->right = nullptr;
}

// 优先将子查询放入右侧
void com_subquery_init(Condition *cond, ConditionExpr *left, Selects *subquery,
                       CompOp op) {
  cond->is_subquery = 1;
  cond->left = left;
  cond->right_subquery = subquery;
  cond->comp = op;
  subquery->parent = cond;
  set_expr_parent(left, cond);
  cond->binded_conds = new CondExprList;
  cond->binded_exprs = new SelectExprList;
  //////////////////////////
  cond->right = nullptr;
  cond->left_subquery = nullptr;
}

// 优先将子查询放入右侧
void membership_subquery_init(Condition *cond, ConditionExpr *left,
                              Selects *subquery, CompOp op) {
  cond->is_subquery = 1;
  cond->left = left;
  cond->right_subquery = subquery;
  cond->comp = op;
  subquery->parent = cond;
  set_expr_parent(left, cond);
  cond->binded_conds = new CondExprList;
  cond->binded_exprs = new SelectExprList;
  ///////////////////////////
  cond->right = nullptr;
  cond->left_subquery = nullptr;
}

void membership_subquery_init(Condition *cond, Selects *left, Selects *right,
                              CompOp op) {
  cond->is_subquery = 1;
  cond->left_subquery = left;
  cond->right_subquery = right;
  cond->comp = op;
  left->parent = cond;
  right->parent = cond;
  cond->binded_conds = new CondExprList;
  cond->binded_exprs = new SelectExprList;
  ///////////////////////////
  cond->left = nullptr;
  cond->right = nullptr;
}

/////////////////////////////// ConditionExpr //////////////////////////////////
void append_cond_expr(ConditionExpr *expr, ConditionExpr *left,
                      ConditionExpr *right, ArithOp op) {
  expr->has_subexpr = 1;
  expr->left = left;
  expr->right = right;
  expr->op = op;
  ///////////////////////////
  expr->is_attr = 0;
  expr->attr = nullptr;
  expr->value = nullptr;
  expr->parent = nullptr;
}

void cond_attr_init(ConditionExpr *expr, RelAttr *attr) {
  expr->is_attr = 1;
  expr->attr = attr;
  ///////////////////////////
  expr->has_subexpr = 0;
  expr->left = nullptr;
  expr->right = nullptr;
  expr->op = NO_ARITH_OP;
  expr->value = nullptr;
  expr->parent = nullptr;
}

void cond_value_init(ConditionExpr *expr, Value *v) {
  expr->value = v;
  ///////////////////////////
  expr->has_subexpr = 0;
  expr->left = nullptr;
  expr->right = nullptr;
  expr->op = NO_ARITH_OP;
  expr->is_attr = 0;
  expr->attr = nullptr;
  expr->parent = nullptr;
}

//////////////////////////////// CREATE TABLE ///////////////////////////////
void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type,
                    size_t length, int nullable) {
  attr_info->name = strdup(name);
  attr_info->type = type;
  attr_info->length = length;
  attr_info->nullable = nullable;
}

///////////////////////////////// SelectExpr ////////////////////////////////
void append_subexpr(SelectExpr *expr, SelectExpr *left, SelectExpr *right,
                    ArithOp op) {
  expr->has_subexpr = 1;
  expr->left = left;
  expr->right = right;
  expr->arithOp = op;
  expr->func = EXPR;
  expr->has_brace = 0;
  ///////////////////
  expr->is_attr = 0;
  expr->attr = nullptr;
  expr->parent = nullptr;
  expr->value = nullptr;
}

void aggregate_function_init(SelectExpr *expr, FuncName func, RelAttr *attr) {
  expr->func = func;
  expr->attr = attr;
  expr->is_attr = 1;

  expr->has_subexpr = 0;
  expr->has_brace = 0;
  expr->arithOp = NO_ARITH_OP;
  expr->value = nullptr;
  expr->left = nullptr;
  expr->right = nullptr;
  expr->parent = nullptr;
}

void select_attr_init(SelectExpr *expr, RelAttr *attr) {
  expr->attr = attr;
  expr->is_attr = 1;

  expr->has_subexpr = 0;
  expr->has_brace = 0;
  expr->func = COLUMN;
  expr->arithOp = NO_ARITH_OP;
  expr->value = nullptr;
  expr->left = nullptr;
  expr->right = nullptr;
  expr->parent = nullptr;
}

void select_value_init(SelectExpr *expr, Value *value) {
  expr->value = value;

  expr->has_brace = 0;
  expr->is_attr = 0;
  expr->attr = nullptr;
  expr->has_subexpr = 0;
  expr->func = COLUMN;
  expr->arithOp = NO_ARITH_OP;
  expr->left = nullptr;
  expr->right = nullptr;
  expr->parent = nullptr;
}

void selects_append_conditions(Selects *selects, ConditionList *cond_list) {
  for (size_t i = 0; i < cond_list->size(); i++) {
    cond_list->at(i)->parent = selects;
  }
  selects->conditions = cond_list;
  selects->cond_num = cond_list->size();
}
void selects_append_group(Selects *selects, GroupByList *groups) {
  selects->groups = groups;
  selects->group_num = groups->size();
}

void selects_append_order(Selects *selects, OrderColList *ocolist) {
  selects->orders = ocolist;
  selects->order_num = ocolist->size();
}

void order_col_init(OrderCol *col, RelAttr *attr, int asc_flag) {
  col->attr = attr;
  col->asc = asc_flag;
}

void insert_value_append(Inserts *inserts, Value *v) {
  Tuples *tuple = &inserts->tuples[inserts->tuple_num];
  tuple->values[tuple->value_num++] = v;
}

void inserts_init(Inserts *inserts, const char *relation_name) {
  inserts->relation_name = strdup(relation_name);
}

void deletes_init_relation(Deletes *deletes, const char *relation_name) {
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, ConditionList *cond_list) {
  deletes->conditions = cond_list;
  deletes->condition_num = cond_list->size();
}

void updates_init(Updates *updates, const char *relation_name,
                  const char *attribute_name, Value *value,
                  ConditionList *cond_list) {
  updates->relation_name = strdup(relation_name);
  updates->attribute_name = strdup(attribute_name);
  updates->value = value;
  updates->conditions = cond_list;
  updates->condition_num = cond_list->size();
}

void create_table_append_attribute(CreateTable *create_table,
                                   AttrInfo *attr_info) {
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}
void create_table_init_name(CreateTable *create_table,
                            const char *relation_name) {
  create_table->relation_name = strdup(relation_name);
}

void drop_table_init(DropTable *drop_table, const char *relation_name) {
  drop_table->relation_name = strdup(relation_name);
}

void create_index_init(CreateIndex *create_index, const char *index_name,
                       const char *relation_name, int unique_flag) {
  create_index->index_name = strdup(index_name);
  create_index->relation_name = strdup(relation_name);
  create_index->unique = unique_flag;
}
void create_index_append_attr(CreateIndex *create_index,
                              const char *attr_name) {
  create_index->attribute_name[create_index->attr_num++] = strdup(attr_name);
}

void drop_index_init(DropIndex *drop_index, const char *index_name) {
  drop_index->index_name = strdup(index_name);
}

void desc_table_init(DescTable *desc_table, const char *relation_name) {
  desc_table->relation_name = strdup(relation_name);
}

void load_data_init(LoadData *load_data, const char *relation_name,
                    const char *file_name) {
  load_data->relation_name = strdup(relation_name);

  if (file_name[0] == '\'' || file_name[0] == '\"') {
    file_name++;
  }
  char *dup_file_name = strdup(file_name);
  int len = strlen(dup_file_name);
  if (dup_file_name[len - 1] == '\'' || dup_file_name[len - 1] == '\"') {
    dup_file_name[len - 1] = 0;
  }
  load_data->file_name = dup_file_name;
}

void query_init(Query *query) {
  query->flag = SCF_ERROR;
  memset(&query->sstr, 0, sizeof(query->sstr));
}

Query *query_create() {
  Query *query = (Query *)malloc(sizeof(Query));
  if (nullptr == query) {
    LOG_ERROR("Failed to alloc memroy for query. size=%ld", sizeof(Query));
    return nullptr;
  }

  query_init(query);
  return query;
}

/*************************** Destory ******************************/
////////////////////////// CREATE TABLE ////////////////////////////
void attr_info_destroy(AttrInfo *attr_info) {
  free(attr_info->name);
  attr_info->name = nullptr;
}

void create_table_destroy(CreateTable *create_table) {
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

/////////////////////////// DROP TABLE /////////////////////////////
void drop_table_destroy(DropTable *drop_table) {
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
}

////////////////////////// CREATE INDEX ////////////////////////////
void create_index_destroy(CreateIndex *create_index) {
  // 1. free index name & relation name
  free(create_index->index_name);
  free(create_index->relation_name);
  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;

  // 2. free index column name
  for (size_t i = 0; i < create_index->attr_num; i++) {
    free(create_index->attribute_name[i]);
    create_index->attribute_name[i] = nullptr;
  }
  create_index->attr_num = 0;

  create_index->unique = 0;
}

////////////////////////// DROP INDEX ////////////////////////////
void drop_index_destroy(DropIndex *drop_index) {
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

//////////////////////////// Select ////////////////////////////////
void select_expr_destroy(SelectExpr *expr) {
  if (expr->has_subexpr == 1) {
    select_expr_destroy(expr->left);
    select_expr_destroy(expr->right);
  } else {
    if (expr->attr != nullptr) {
      attr_destroy(expr->attr);
    }
    if (expr->value != nullptr) {
      value_destroy(expr->value);
      free(expr->value);
      expr->value = nullptr;
    }
  }
  free(expr);
}

void table_ref_destory(TableRef *ref) {
  if (ref->is_join) {
    table_ref_destory(ref->child);
  }
  // 1. free relation name
  free(ref->relation_name);
  ref->relation_name = nullptr;

  // 2. free on cluase
  for (auto cond : *ref->conditions) {
    condition_destory(cond);
  }
  delete ref->conditions;
  ref->conditions = nullptr;
  ref->cond_num = 0;

  // 3. free join node
  free(ref);
}

void condition_expr_destory(ConditionExpr *expr) {
  if (expr->has_subexpr) {
    condition_expr_destory(expr->left);
    condition_expr_destory(expr->right);
  } else {
    if (expr->attr != nullptr) {
      attr_destroy(expr->attr);
      expr->attr = nullptr;
    }
    if (expr->value != nullptr) {
      value_destroy(expr->value);
      free(expr->value);
      expr->value = nullptr;
    }
  }
  free(expr);
}

void condition_destory(Condition *condition) {
  condition_expr_destory(condition->left);
  if (condition->is_subquery) {
    if (condition->left_subquery != nullptr) {
      selects_destroy(condition->left_subquery);
      free(condition->left_subquery);
      condition->left_subquery = nullptr;
    }
    if (condition->right_subquery != nullptr) {
      selects_destroy(condition->right_subquery);
      free(condition->right_subquery);
      condition->right_subquery = nullptr;
    }
  } else {
    condition_expr_destory(condition->right);
  }
  free(condition);
}

void attr_destroy(RelAttr *relation_attr) {
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
  free(relation_attr);
}

void order_col_destory(OrderCol *col) {
  attr_destroy(col->attr);
  free(col);
}

void selects_destroy(Selects *selects) {
  // 1. free select clause
  for (auto expr : *selects->exprs) {
    select_expr_destroy(expr);
  }
  delete selects->exprs;
  selects->exprs = nullptr;

  // 2. free from clause
  for (auto ref : *selects->references) {
    table_ref_destory(ref);
  }
  delete selects->references;
  selects->references = nullptr;

  // 3. free where clause
  for (auto cond : *selects->conditions) {
    condition_destory(cond);
  }
  delete selects->conditions;
  selects->conditions = nullptr;
  selects->cond_num = 0;

  // 4. free group by list
  for (auto group : *selects->groups) {
    attr_destroy(group);
  }
  delete selects->groups;
  selects->groups = nullptr;
  selects->group_num = 0;

  // 5. free order by list
  for (auto ocol : *selects->orders) {
    order_col_destory(ocol);
  }
  delete selects->orders;
  selects->orders = nullptr;
  selects->order_num = 0;

  // 6. free context
  delete selects->relations;
}

//////////////////////////// Insert ////////////////////////////////
void value_destroy(Value *value) {
  value->type = UNDEFINED;
  free(value->data);
  value->data = nullptr;
}

void tuple_destory(Tuples *tuple) {
  for (size_t i = 0; i < tuple->value_num; i++) {
    value_destroy(tuple->values[i]);
    free(tuple->values[i]);
    tuple->values[i] = nullptr;
  }
}

void inserts_destroy(Inserts *inserts) {
  free(inserts->relation_name);
  inserts->relation_name = nullptr;

  for (size_t i = 0; i < inserts->tuple_num; i++) {
    tuple_destory(&inserts->tuples[i]);
  }
  inserts->tuple_num = 0;
}

//////////////////////////// Delete ////////////////////////////////
void deletes_destroy(Deletes *deletes) {
  // 1. free where clause
  for (auto cond : *deletes->conditions) {
    condition_destory(cond);
  }
  delete deletes->conditions;
  deletes->conditions = nullptr;
  deletes->condition_num = 0;

  // 2. free relation name
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
}

//////////////////////////// Update ////////////////////////////////
void updates_destroy(Updates *updates) {
  // 1. free relation name & attribute name
  free(updates->relation_name);
  free(updates->attribute_name);
  updates->relation_name = nullptr;
  updates->attribute_name = nullptr;

  // 2. free update value
  value_destroy(updates->value);
  for (auto cond : *updates->conditions) {
    condition_destory(cond);
  }

  // 3. free where clause
  delete updates->conditions;
  updates->conditions = nullptr;
  updates->condition_num = 0;
}

////////////////////////// DESC TABLE /////////////////////////////
void desc_table_destroy(DescTable *desc_table) {
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
}

////////////////////////// LOAD DATA //////////////////////////////
void load_data_destroy(LoadData *load_data) {
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
}

//////////////////////////// Query ////////////////////////////////
void query_reset(Query *query) {
  switch (query->flag) {
  case SCF_SELECT: {
    selects_destroy(&query->sstr.selection);
  } break;
  case SCF_INSERT: {
    inserts_destroy(&query->sstr.insertion);
  } break;
  case SCF_DELETE: {
    deletes_destroy(&query->sstr.deletion);
  } break;
  case SCF_UPDATE: {
    updates_destroy(&query->sstr.update);
  } break;
  case SCF_CREATE_TABLE: {
    create_table_destroy(&query->sstr.create_table);
  } break;
  case SCF_DROP_TABLE: {
    drop_table_destroy(&query->sstr.drop_table);
  } break;
  case SCF_CREATE_INDEX: {
    create_index_destroy(&query->sstr.create_index);
  } break;
  case SCF_DROP_INDEX: {
    drop_index_destroy(&query->sstr.drop_index);
  } break;
  case SCF_SYNC: {

  } break;
  case SCF_SHOW_TABLES:
    break;

  case SCF_DESC_TABLE: {
    desc_table_destroy(&query->sstr.desc_table);
  } break;

  case SCF_LOAD_DATA: {
    load_data_destroy(&query->sstr.load_data);
  } break;
  case SCF_BEGIN:
  case SCF_COMMIT:
  case SCF_ROLLBACK:
  case SCF_HELP:
  case SCF_EXIT:
  case SCF_ERROR:
    break;
  }
}

void query_destroy(Query *query) {
  query_reset(query);
  free(query);
}

////////////////////////////////////////////////////////////////////////////////

extern int sql_parse(const char *st, Query *sqls);

RC parse(const char *st, Query *sqln) {
  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else
    return SUCCESS;
}
