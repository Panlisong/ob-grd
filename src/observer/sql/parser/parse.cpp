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

// #ifdef __cplusplus
// extern "C" {
// #endif // __cplusplus
bool is_comparable(AttrType lt, AttrType rt) {
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

void table_ref_init(TableRef *ref, int is_join, const char *relation_name,
                    TableRef *child, ConditionList *cond_list) {
  ref->is_join = is_join;
  ref->relation_name = strdup(relation_name);
  ref->child = child;
  ref->conditions = cond_list;
  ref->cond_num = cond_list->size();
}

void table_ref_destory(TableRef *ref) {
  if (ref->is_join) {
    table_ref_destory(ref->child);
  }
  free(ref->relation_name);

  delete ref->conditions;
  ref->cond_num = 0;

  free(ref);
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

void attr_destroy(RelAttr *relation_attr) {
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
  free(relation_attr);
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
void value_init_date(Value *value, time_t v) {
  value->type = DATES;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_null(Value *value) {
  value->type = ATTR_NULL;
  value->data = nullptr;
}

void value_destroy(Value *value) {
  value->type = UNDEFINED;
  free(value->data);
  value->data = nullptr;
}

void tuple_destory(Tuples *tuple) {
  for (size_t i = 0; i < tuple->value_num; i++) {
    value_destroy(tuple->values[i]);
  }
}

/////////////////////////////////////////////////////////////////////////
void condition_expr_destory(ConditionExpr *expr) {
  if (expr->has_subexpr) {
    condition_expr_destory(expr->left);
    condition_expr_destory(expr->right);
  } else {
    if (expr->is_attr) {
      attr_destroy(expr->attr);
    } else {
      value_destroy(expr->value);
    }
  }
  free(expr);
}

void non_subquery_cond_init(Condition *cond, ConditionExpr *left,
                            ConditionExpr *right, CompOp op) {
  cond->left = left;
  cond->right = right;
  cond->comp = op;
  ////////////////////////
  cond->is_subquery = 0;
  cond->subquery = nullptr;
}
void com_subquery_init(Condition *cond, ConditionExpr *left, Selects *subquery,
                       CompOp op) {
  cond->is_subquery = 1;
  cond->left = left;
  cond->subquery = subquery;
  cond->comp = op;
  //////////////////////////
  cond->right = nullptr;
}
void membership_subquery_init(Condition *cond, ConditionExpr *left,
                              Selects *subquery, CompOp op) {
  cond->is_subquery = 1;
  cond->left = left;
  cond->subquery = subquery;
  cond->comp = op;
  ///////////////////////////
  cond->right = nullptr;
}

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
}

void condition_destroy(Condition *condition) {
  condition_expr_destory(condition->left);
  if (condition->is_subquery) {
    selects_destroy(condition->subquery);
  } else {
    condition_expr_destory(condition->right);
  }
  free(condition);
}

///////////////////////////////////////////////////////
void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type,
                    size_t length, int nullable) {
  attr_info->name = strdup(name);
  attr_info->type = type;
  attr_info->length = length;
  attr_info->nullable = nullable;
}
void attr_info_destroy(AttrInfo *attr_info) {
  free(attr_info->name);
  attr_info->name = nullptr;
}

///////////////////////////////////////////////////////
void append_subexpr(SelectExpr *expr, SelectExpr *left, SelectExpr *right,
                    ArithOp op) {
  expr->has_subexpr = 1;
  expr->left = left;
  expr->right = right;
  expr->arithOp = op;
  expr->func = EXPR;
  ///////////////////
  expr->is_attr = 0;
  memset(&expr->value, 0, sizeof(Value));
  expr->attr = nullptr;
}

void select_expr_destroy(SelectExpr *expr) {
  if (expr->has_subexpr == 1) {
    select_expr_destroy(expr->left);
    select_expr_destroy(expr->right);
  } else {
    if (expr->is_attr) {
      attr_destroy(expr->attr);
    } else {
      value_destroy(expr->value);
    }
  }
  free(expr);
}

void aggregate_function_init(SelectExpr *expr, FuncName func, RelAttr *attr) {
  expr->func = func;
  expr->attr = attr;
  expr->is_attr = 1;
  ///////////////////
  expr->has_subexpr = 0;
  expr->arithOp = NO_ARITH_OP;
  expr->value = nullptr;
  expr->left = nullptr;
  expr->right = nullptr;
}

void select_attr_init(SelectExpr *expr, RelAttr *attr) {
  expr->attr = attr;
  expr->is_attr = 1;
  ///////////////////
  expr->has_subexpr = 0;
  expr->func = COLUMN;
  expr->arithOp = NO_ARITH_OP;
  expr->value = nullptr;
  expr->left = nullptr;
  expr->right = nullptr;
}

void select_value_init(SelectExpr *expr, Value *value) {
  expr->value = value;
  ///////////////////
  expr->is_attr = 0;
  expr->attr = nullptr;
  expr->has_subexpr = 0;
  expr->func = COLUMN;
  expr->arithOp = NO_ARITH_OP;
  expr->left = nullptr;
  expr->right = nullptr;
}

void selects_append_conditions(Selects *selects, ConditionList *cond_list) {
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

void order_col_destroy(OrderCol *col) {
  attr_destroy(col->attr);
  free(col);
}

void selects_destroy(Selects *selects) {

  delete selects->exprs;
  selects->expr_num = 0;

  delete selects->references;
  selects->ref_num = 0;

  delete selects->conditions;
  selects->cond_num = 0;

  delete selects->groups;
  selects->group_num = 0;

  delete selects->orders;
  selects->order_num = 0;
}

void insert_value_append(Inserts *inserts, Value *v) {
  Tuples *tuple = &inserts->tuples[inserts->tuple_num];
  tuple->values[tuple->value_num++] = v;
}

void inserts_init(Inserts *inserts, const char *relation_name) {
  inserts->relation_name = strdup(relation_name);
}
void inserts_destroy(Inserts *inserts) {
  free(inserts->relation_name);
  inserts->relation_name = nullptr;

  for (size_t i = 0; i < inserts->tuple_num; i++) {
    tuple_destory(&inserts->tuples[i]);
  }
  inserts->tuple_num = 0;
}

void deletes_init_relation(Deletes *deletes, const char *relation_name) {
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, ConditionList *cond_list) {
  deletes->conditions = cond_list;
  deletes->condition_num = cond_list->size();
}
void deletes_destroy(Deletes *deletes) {
  if (deletes->conditions != nullptr) {
    delete deletes->conditions;
  }
  deletes->condition_num = 0;
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
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

void updates_destroy(Updates *updates) {
  free(updates->relation_name);
  free(updates->attribute_name);
  updates->relation_name = nullptr;
  updates->attribute_name = nullptr;
  value_destroy(updates->value);
  if (updates->conditions != nullptr) {
    delete updates->conditions;
  }
  updates->condition_num = 0;
}

void create_table_append_attribute(CreateTable *create_table,
                                   AttrInfo *attr_info) {
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}
void create_table_init_name(CreateTable *create_table,
                            const char *relation_name) {
  create_table->relation_name = strdup(relation_name);
}
void create_table_destroy(CreateTable *create_table) {
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

void drop_table_init(DropTable *drop_table, const char *relation_name) {
  drop_table->relation_name = strdup(relation_name);
}
void drop_table_destroy(DropTable *drop_table) {
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
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
void create_index_destroy(CreateIndex *create_index) {
  free(create_index->index_name);
  free(create_index->relation_name);
  for (size_t i = 0; i < create_index->attr_num; i++) {
    free(create_index->attribute_name);
  }
  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;
  create_index->attr_num = 0;
  create_index->unique = 0;
}

void drop_index_init(DropIndex *drop_index, const char *index_name) {
  drop_index->index_name = strdup(index_name);
}
void drop_index_destroy(DropIndex *drop_index) {
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

void desc_table_init(DescTable *desc_table, const char *relation_name) {
  desc_table->relation_name = strdup(relation_name);
}

void desc_table_destroy(DescTable *desc_table) {
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
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

void load_data_destroy(LoadData *load_data) {
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
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
// #ifdef __cplusplus
// } // extern "C"
// #endif // __cplusplus

////////////////////////////////////////////////////////////////////////////////

extern int sql_parse(const char *st, Query *sqls);

RC parse(const char *st, Query *sqln) {
  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else
    return SUCCESS;
}
