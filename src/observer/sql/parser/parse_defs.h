/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its
affiliates. All rights reserved. miniob is licensed under Mulan PSL v2. You can
use this software according to the terms and conditions of the Mulan PSL v2. You
may obtain a copy of Mulan PSL v2 at: http://license.coscl.org.cn/MulanPSL2 THIS
SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai.wyl on 2021/6/7.
//

#ifndef __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
#define __OBSERVER_SQL_PARSER_PARSE_DEFS_H__

#include <deque>
#include <stddef.h>
#include <string>
#include <time.h>
#include <unordered_map>
#include <vector>

class Table;
typedef std::unordered_map<std::string, Table *> RelationTable;

#define MAX_NUM 20
#define MAX_REL_NAME 20
#define MAX_ATTR_NAME 20
#define MAX_ERROR_MESSAGE 20
#define MAX_DATA 50

typedef struct _Selects Selects;
typedef struct _SelectExpr SelectExpr;
typedef struct _RelAttr RelAttr;
typedef struct _Value Value;
typedef struct _TableRef TableRef;
typedef struct _Condition Condition;
typedef struct _ConditionExpr ConditionExpr;
typedef struct _OrderCol OrderCol;
typedef std::deque<Condition> ConditionList;
typedef std::deque<SelectExpr *> SelectExprList;
typedef std::deque<TableRef *> TableRefList;
typedef std::deque<OrderCol *> OrderColList;
typedef std::deque<RelAttr *> GroupByList;

// Built-in Function类型
typedef enum _FuncName {
  COLUMN,
  EXPR,
  MAX_FUNC,
  MIN_FUNC,
  COUNT_FUNC,
  AVG_FUNC,
  FUNC_NUM
} FuncName;

//属性结构体
typedef struct _RelAttr {
  char *relation_name;  // relation name (may be NULL) 表名
  char *attribute_name; // attribute name              属性名
} RelAttr;

typedef enum _CompOp {
  EQUAL_TO,    //"="       0
  LESS_EQUAL,  //"<="      1
  NOT_EQUAL,   //"<>"      2
  LESS_THAN,   //"<"       3
  GREAT_EQUAL, //">="      4
  GREAT_THAN,  //">"       5
  OP_IS,       //"is"      6
  OP_IS_NOT,   //"is not"  7
  MEM_IN,      //"in"      8
  MEM_NOT_IN,  //"not in"  9
  NO_OP
} CompOp;

typedef enum _ArithOp {
  ADD, //"+"         0
  SUB, //"-"         1
  MUL, //"*"         2
  DIV, //"/"         3
  NEG, // UNARYMINUS 4
  NO_ARITH_OP,
} ArithOp;

//属性值类型
typedef enum {
  UNDEFINED,
  CHARS,
  INTS,
  FLOATS,
  ATTR_NULL,
  ATTR_TEXT,
  DATES
} AttrType;

//属性值
struct _Value {
  AttrType type; // type of value
  void *data;    // value
  int len;
};

/**
 * PS: 标志位优先级：has_subexpr > is_attr
 */
struct _ConditionExpr {
  int has_subexpr;
  ConditionExpr *left;
  ConditionExpr *right;
  ArithOp op;
  /* ConditionExpr叶子节点 */
  int is_attr;
  Value *value;
  RelAttr *attr;
};

/**
 * Condition 有两种情况
 * 1. is_subquery = 1
 *    left op subquery
 * 2. is_subquery = 0
 * => left comOp right
 *
 * PS: 其余情况均非法
 */
struct _Condition {
  int is_used = 0; // 生成Filter时避免重复选取
  int is_subquery;
  Selects *left_subquery;
  Selects *right_subquery;
  ConditionExpr *left;
  ConditionExpr *right;
  CompOp comp; // comparison operator
};

/** TableRef结构体
 *  表引用有两种类型：join table和普通table
 ×  （分别简记为J, T）
 *  1. join table 树结构
 *           J--R(relation_name: 右结点表名)
 *  child<--/
 *         J--R
 *        /
 *       T
 *  2. normal table
 *      T--R(relation_name: 当前表名)
 *      |
 *     null
 */
struct _TableRef {
  int is_join;         // 是否为join table
  char *relation_name; // 表名，具体含义见上面注释
  TableRef *child;     // 子结点
  size_t cond_num;
  ConditionList *conditions;
};

/**
 * PS: 标志位优先级：has_subexpr > is_attr
 */
struct _SelectExpr {
  int has_subexpr;
  int has_brace;
  ArithOp arithOp;
  SelectExpr *left;
  SelectExpr *right;
  /* Expression叶子节点 */
  int is_attr;
  Value *value;
  FuncName func;
  RelAttr *attr;
};

struct _OrderCol {
  RelAttr *attr;
  int asc; // 1: 升序；0：降序
};

// struct of select
struct _Selects {
  size_t expr_num;           // Length of attrs in Expression clause
  SelectExprList *exprs;     // Select expression in Select clause
  size_t ref_num;            // Length of table references in From clause
  TableRefList *references;  // Table references in From clause
  size_t cond_num;           // Length of conditions in Where clause
  ConditionList *conditions; // conditions in Where clause
  size_t group_num;          // Length of groups
  GroupByList *groups;       // cols in Group List
  size_t order_num;          // Length of orders
  OrderColList *orders;      // cols in OrderBy List
  ///////////////////////////////////////////////////////////////////////////
  RelationTable *context;
};

typedef struct {
  size_t value_num;       // Length of values
  Value *values[MAX_NUM]; // values to insert
} Tuples;

// struct of insert
typedef struct {
  char *relation_name;    // Relation to insert into
  size_t tuple_num;       // Length of tuple list
  Tuples tuples[MAX_NUM]; // tuples to insert
} Inserts;

// struct of delete
typedef struct {
  char *relation_name;       // Relation to delete from
  size_t condition_num;      // Length of conditions in Where clause
  ConditionList *conditions; // conditions in Where clause
} Deletes;

// struct of update
typedef struct {
  char *relation_name;       // Relation to update
  char *attribute_name;      // Attribute to update
  Value *value;              // update value
  size_t condition_num;      // Length of conditions in Where clause
  ConditionList *conditions; // conditions in Where clause
} Updates;

typedef struct {
  char *name;    // Attribute name
  AttrType type; // Type of attribute
  size_t length; // Length of attribute
  int nullable;  // nullable
} AttrInfo;

// struct of craete_table
typedef struct {
  char *relation_name;          // Relation name
  size_t attribute_count;       // Length of attribute
  AttrInfo attributes[MAX_NUM]; // attributes
} CreateTable;

// struct of drop_table
typedef struct {
  char *relation_name; // Relation name
} DropTable;

// struct of create_index
typedef struct {
  char *index_name;              // Index name
  char *relation_name;           // Relation name
  char *attribute_name[MAX_NUM]; // Attribute name
  size_t attr_num;               // # of attr
  int unique;                    // 1 is unique index, otherwise is not
} CreateIndex;

// struct of  drop_index
typedef struct {
  const char *index_name; // Index name
} DropIndex;

typedef struct {
  const char *relation_name;
} DescTable;

typedef struct {
  const char *relation_name;
  const char *file_name;
} LoadData;

union Queries {
  Selects selection;
  Inserts insertion;
  Deletes deletion;
  Updates update;
  CreateTable create_table;
  DropTable drop_table;
  CreateIndex create_index;
  DropIndex drop_index;
  DescTable desc_table;
  LoadData load_data;
  const char *errors;
};

// 修改yacc中相关数字编码为宏定义
enum SqlCommandFlag {
  SCF_ERROR = 0,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,
  SCF_COMMIT,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT
};
// struct of flag and sql_struct
typedef struct Query {
  enum SqlCommandFlag flag;
  union Queries sstr;
} Query;

//////////////////////////////////////////////////////
bool is_computable(AttrType left, AttrType right);
bool is_comparable(AttrType lt, AttrType rt);
CompOp get_neg_comp_op(CompOp op);

//////////////////////////////////////////////////////
void table_ref_init(TableRef *ref, int is_join, const char *relation_name,
                    TableRef *child, ConditionList *cond_list);
void table_ref_destory(TableRef *ref);

//////////////////////////////////////////////////////
void append_subexpr(SelectExpr *expr, SelectExpr *left, SelectExpr *righ,
                    ArithOp op);
void aggregate_function_init(SelectExpr *expr, FuncName func, RelAttr *attr);
void select_attr_init(SelectExpr *expr, RelAttr *attr);
void select_value_init(SelectExpr *expr, Value *value);
void select_expr_destroy(SelectExpr *expr);

//////////////////////////////////////////////////////
void attr_init(RelAttr *relation_attr, const char *relation_name,
               const char *attribute_name);
void attr_destroy(RelAttr *relation_attr);

void order_col_init(OrderCol *col, RelAttr *attr, int asc_flag);
void order_col_destory(OrderCol *col);

//////////////////////////////////////////////////////
void value_init_integer(Value *value, int v);
void value_init_float(Value *value, float v);
void value_init_string(Value *value, const char *v);
void value_init_date(Value *value, time_t v);
void value_init_null(Value *value);

int check_date(int year, int month, int day);
void value_destroy(Value *value);
void tuple_destory(Tuples *tuple);

//////////////////////////////////////////////////////
void non_subquery_cond_init(Condition *cond, ConditionExpr *left,
                            ConditionExpr *right, CompOp op);
void com_subquery_init(Condition *cond, Selects *left, Selects *right,
                       CompOp op);
void com_subquery_init(Condition *cond, ConditionExpr *left, Selects *subquery,
                       CompOp op);
void membership_subquery_init(Condition *cond, ConditionExpr *left,
                              Selects *subquery, CompOp op);
void membership_subquery_init(Condition *cond, Selects *left, Selects *right,
                              CompOp op);
void condition_destory(Condition *condition);

//////////////////////////////////////////////////////
void append_cond_expr(ConditionExpr *expr, ConditionExpr *left,
                      ConditionExpr *right, ArithOp op);
void cond_attr_init(ConditionExpr *expr, RelAttr *attr);
void cond_value_init(ConditionExpr *expr, Value *v);
void condition_init(Condition *condition, CompOp comp, int left_is_attr,
                    RelAttr *left_attr, Value *left_value, int right_is_attr,
                    RelAttr *right_attr, Value *right_value);
void condition_expr_destory(ConditionExpr *expr);

///////////////////////////////////////////////////////
void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type,
                    size_t length, int nullable);
void attr_info_destroy(AttrInfo *attr_info);

///////////////////////////////////////////////////////
void selects_append_conditions(Selects *selects, ConditionList *cond_list);
void selects_append_group(Selects *selects, GroupByList *groups);
void selects_append_order(Selects *selects, OrderColList *ocol);
void selects_destroy(Selects *selects);

void insert_value_append(Inserts *inserts, Value *v);
void inserts_init(Inserts *inserts, const char *relation_name);
void inserts_destroy(Inserts *inserts);

void deletes_init_relation(Deletes *deletes, const char *relation_name);
void deletes_set_conditions(Deletes *deletes, ConditionList *conditions);
void deletes_destroy(Deletes *deletes);

void updates_init(Updates *updates, const char *relation_name,
                  const char *attribute_name, Value *value,
                  ConditionList *cond_list);
void updates_destroy(Updates *updates);

void create_table_append_attribute(CreateTable *create_table,
                                   AttrInfo *attr_info);
void create_table_init_name(CreateTable *create_table,
                            const char *relation_name);
void create_table_destroy(CreateTable *create_table);

void drop_table_init(DropTable *drop_table, const char *relation_name);
void drop_table_destroy(DropTable *drop_table);

void create_index_init(CreateIndex *create_index, const char *index_name,
                       const char *relation_name, int unique_flag);
void create_index_append_attr(CreateIndex *create_index, const char *attr_name);
void create_index_destroy(CreateIndex *create_index);

void drop_index_init(DropIndex *drop_index, const char *index_name);
void drop_index_destroy(DropIndex *drop_index);

void desc_table_init(DescTable *desc_table, const char *relation_name);
void desc_table_destroy(DescTable *desc_table);

void load_data_init(LoadData *load_data, const char *relation_name,
                    const char *file_name);
void load_data_destroy(LoadData *load_data);

void query_init(Query *query);
Query *query_create(); // create and init
void query_reset(Query *query);
void query_destroy(Query *query); // reset and delete

#endif // __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
