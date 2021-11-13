
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.hpp"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<cstdio>
#include<stdlib.h>
#include<cstring>

typedef struct ParserContext {
  Query *ssql;
  int query_id;
} ParserContext;

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->ssql->sstr.insertion.tuple_num = 0;
  printf("parse sql failed. error=%s\n", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%code requires{
#include <deque>
typedef struct _Selects Selects;
typedef struct _SelectExpr SelectExpr;
typedef struct _RelAttr RelAttr;
typedef struct _Value Value;
typedef struct _TableRef TableRef;
typedef struct _Condition Condition;
typedef struct _ConditionExpr ConditionExpr;
typedef struct _OrderCol OrderCol;
typedef std::deque<Condition *> ConditionList;
typedef std::deque<SelectExpr *> SelectExprList;
typedef std::deque<TableRef *> TableRefList;
typedef std::deque<OrderCol *> OrderColList;
typedef std::deque<RelAttr *> GroupByList;
}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
		MAX_F
		MIN_F
		COUNT_F
		AVG_F
		INNER
		JOIN
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
		UNIQUE
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
		DATE_T
        FLOAT_T
		TEXT_T
        HELP
        EXIT
		IS
		NOT
		NULL_T
		NULLABLE
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
		GROUP
		ORDER
		BY
		ASC
		ADD_OP
		SUB_OP
		DIV_OP
        EQ
        LT
        GT
        LE
        GE
        NE
		IN

%union {
  Selects *select;		// select
  TableRef *ref;		// Table reference
  SelectExpr *sexpr;	// select expr
  Condition *cond;		// condition
  ConditionExpr *cexpr; // condition expr
  RelAttr *attr;
  Value *val;			// value
  OrderCol *ocol; 		// order column
  char *string;
  int number;
  float floats;
  char *position;

  ConditionList *cond_list;
  SelectExprList *sexpr_list;
  TableRefList *ref_list;
  OrderColList *ocol_list;
  GroupByList *group_list;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> DATE
%token <string> STAR
%token <string> STRING_V

//非终结符
%type <select> select
%type <select> subquery

%type <number> membershipOp
%type <number> comOp

%type <ref>	table_ref
%type <ref>	join_table
%type <ref_list> table_ref_list
%type <sexpr> select_expr
%type <sexpr> select_func
%type <sexpr> select_arith_expr
%type <sexpr_list> select_expr_list
%type <attr> col
%type <group_list> group
%type <group_list> group_by_list
%type <val> value
%type <val> const_value
%type <ocol> order_col
%type <ocol_list> order
%type <ocol_list> order_col_list

%type <cexpr> non_subquery
%type <cond> condition
%type <cond_list> where
%type <cond_list> condition_list
%type <cond_list> join_condition

%type <number> type
%type <number> is_nullable
%type <number> aggregate_func
%type <number> number

// 优先级以及结合性
// 优先级：按照声明顺序优先级由低到高
%left ADD_OP SUB_OP
%left STAR DIV_OP
%left UNARYMINUS

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  selects  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index	
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID attr_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, $7);
			create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5, 0);
		}
    | CREATE UNIQUE INDEX ID ON ID LBRACE ID attr_list RBRACE SEMICOLON 
		{	// 由于只用支持UNIQUE，采用最简单写法
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_unique_index";
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, $8);
			create_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6, 1);
		}
	;

attr_list:
	/* empty */
	| COMMA ID attr_list {
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, $2);
	}

drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON {
		CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
		drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
	}
    ;

create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON {
		CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
		create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
	}	
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE is_nullable{
		AttrInfo attribute;
		AttrType type = static_cast<AttrType>($2);
		attr_info_init(&attribute, $1, type, $4, $6);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
    |ID type is_nullable {
		AttrInfo attribute;
		AttrType type = static_cast<AttrType>($2);
		attr_info_init(&attribute, $1, type, (type == DATES || type == ATTR_TEXT) ? 8 : 4, $3);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
    ;

number:
	NUMBER {$$ = $1;}
	;

type:
	INT_T      { $$=INTS; }
	| STRING_T { $$=CHARS; }
	| FLOAT_T  { $$=FLOATS; }
	| DATE_T   { $$=DATES; }
  | TEXT_T   { $$=ATTR_TEXT; }
	;

is_nullable:
	/* empty */ { $$ = 0; }
  	| NOT NULL_T{ $$ = 0; } 
	| NULLABLE  { $$ = 1; }
	;
	
insert:				/*insert   语句的语法解析树*/
	INSERT INTO ID VALUES tuple tuple_list SEMICOLON {
		CONTEXT->ssql->flag=SCF_INSERT;
		inserts_init(&CONTEXT->ssql->sstr.insertion, $3);
	}

tuple_list:
	/* empty */
	| COMMA tuple tuple_list
	{	/* do nothing here */	}

tuple: 
	LBRACE const_value value_list RBRACE {
		insert_value_append(&CONTEXT->ssql->sstr.insertion, $2);
		// tuple reduce: tuple_num ++
		(CONTEXT->ssql->sstr.insertion.tuple_num)++;
	}

value_list:
    /* empty */
    | COMMA const_value value_list  {
		insert_value_append(&CONTEXT->ssql->sstr.insertion, $2);
	}
    ;
const_value:
	SUB_OP NUMBER {
		$$ = (Value *)malloc(sizeof(Value));
		value_init_integer($$, -$2);
	}
	| SUB_OP FLOAT {
		$$ = (Value *)malloc(sizeof(Value));	
  		value_init_float($$, -$2);
	}
	| value { $$ = $1; }
	;
value:
    NUMBER{
		$$ = (Value *)malloc(sizeof(Value));	
  		value_init_integer($$, $1);
	}
    | FLOAT{
		$$ = (Value *)malloc(sizeof(Value));	
  		value_init_float($$, $1);
	}
    | SSS {
		$$ = (Value *)malloc(sizeof(Value));			
  		value_init_string($$, $1);
	}
	| DATE {
		int year = 0, month = 0, day = 0;
		if (sscanf($1, "%d-%d-%d", &year, &month, &day) != -1) {
			// check date
			if (!check_date(year, month, day)) {
				CONTEXT->ssql->sstr.errors = "invalid day num";
				yyerror(scanner, $1);
				YYERROR;
			}
			struct tm t;
			memset(&t, 0, sizeof(struct tm));
			t.tm_year = year - 1900, t.tm_mon = month - 1, t.tm_mday = day;
			t.tm_hour = 12;		// 防止0点有一天的换算偏差
			$$ = (Value *)malloc(sizeof(Value));			
			value_init_date($$, mktime(&t));
		}
	}
	| NULL_T {		
		$$ = (Value *)malloc(sizeof(Value));			
		value_init_null($$);
	}
    ;
    
delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON {
		CONTEXT->ssql->flag = SCF_DELETE;//"delete";
		deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
		deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, $4);
    }
    ;
update:			/*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ const_value where[wh] SEMICOLON {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		updates_init(&CONTEXT->ssql->sstr.update, $2, $4, $6, $wh);
	}
    ;
selects:				/*  select 语句的语法解析树*/
    select SEMICOLON {
		CONTEXT->ssql->flag = SCF_SELECT; //"select";
		CONTEXT->ssql->sstr.selection = std::move(*$1);
	}
select:
	SELECT select_expr[expr] select_expr_list[exprlist] FROM table_ref[ref] table_ref_list[reflist] where[wh] group[gp] order[od]
	{
		$$ = (Selects *)malloc(sizeof(Selects));
		// 1. append select_expr
		SelectExprList *expr_list = $exprlist;
		expr_list->push_front($expr);
		$$->exprs = expr_list;
		for (size_t i = 0;i < expr_list->size();i ++) {
			set_expr_parent(expr_list->at(i), $$);
		}

		// 2. append table_ref
		TableRefList *ref_list = $reflist;
		ref_list->push_front($ref);
		$$->references = ref_list;

		// 3. append condtion_list(可选项，可能为空)
		selects_append_conditions($$, $wh);

		// 4. append group_list(可选项，可能为空)
		selects_append_group($$, $gp);

		// 5. append order_list(可选项，可能为空)
		selects_append_order($$, $od);
		
		$$->relations = new RelationTable;
		$$->context = new SelectContext;

		$$->parent = nullptr;
		$$->id = CONTEXT->query_id ++;
	}
	;
/*************************** SELECT CLAUSE ****************************/
select_expr_list:
	/* empty */
	{
		$$ = new SelectExprList();
	}
	| COMMA select_expr select_expr_list {
		// append select_expr $2
		$$ = $3;
		$$->push_front($2);
	}
	;

select_expr: 
	select_arith_expr { $$ = $1; }
	| select_func { $$ = $1; }
	| STAR { 
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, NULL, "*");
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init($$, attr);
	}
	| ID DOT STAR {
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, $1, "*");
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init($$, attr);
	}
	;

/** 
 * 在语法层面上避免了：
 * 'T.*'和'*'出现在select输出列的运算中  
 */
select_arith_expr: 
	select_arith_expr ADD_OP select_arith_expr {
		/* expr "+" expr */
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr($$, $1, $3, ADD);
	}
	| select_arith_expr SUB_OP select_arith_expr {
		/* expr "-" expr */
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr($$, $1, $3, SUB);
	}
	| select_arith_expr STAR select_arith_expr {
		/* expr "*" expr */
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr($$, $1, $3, MUL);
	}
	| select_arith_expr DIV_OP select_arith_expr {
		/* expr "/" expr */
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr($$, $1, $3, DIV);
	}
	| col {
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init($$, $1);
	}
	| value { 
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_value_init($$, $1);	
	}
	| LBRACE select_arith_expr RBRACE {
		/* "(" expr ")" */
		$$ = $2;
		$$->has_brace = 1;
	}
	| SUB_OP select_arith_expr %prec UNARYMINUS {
		/* "-" expr */
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr($$, nullptr, $2, NEG);
	}
	;


select_func: 
	aggregate_func LBRACE col RBRACE {
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		FuncName func = static_cast<FuncName>($1);
		aggregate_function_init($$, func, $3);
	}
	| aggregate_func LBRACE STAR RBRACE {
		FuncName func = static_cast<FuncName>($1);
		if (func != COUNT_FUNC) {
			CONTEXT->ssql->sstr.errors = "Invalid args of aggregate function";
			YYERROR;
		}
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, NULL, "*");
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		aggregate_function_init($$, func, attr);
	}
	| aggregate_func LBRACE ID DOT STAR RBRACE {
		FuncName func = static_cast<FuncName>($1);
		if (func != COUNT_FUNC) {
			CONTEXT->ssql->sstr.errors = "Invalid args of aggregate function";
			YYERROR;
		}
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, $3, "*");
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		aggregate_function_init($$, func, attr);
	}
	;

aggregate_func:
	  MAX_F   { $$ = MAX_FUNC;   }
	| MIN_F   { $$ = MIN_FUNC;   }
	| COUNT_F { $$ = COUNT_FUNC; }
	| AVG_F   { $$ = AVG_FUNC;   }
	;

col:
	ID {
		$$ = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init($$, NULL, $1);
	}
	| ID DOT ID {
		$$ = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init($$, $1, $3);
	}
	;

/*************************** FROM CLAUSE ****************************/
table_ref_list:
    /* empty */
	{
		$$ = new TableRefList();
	}
    | COMMA table_ref[ref] table_ref_list[reflist] {	
		$$ = $reflist;
		$$->push_front($ref);
	}
    ;

table_ref: 
	ID { 
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 0, $1, nullptr, new ConditionList); 
		$$ = ref;
	} 
	| join_table { $$ = $1; }
	;

join_table: 
	table_ref INNER JOIN ID join_condition {
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 1, $4, $1, $5);
		$$ = ref;
	}
	;

join_condition:
	/* empty */
	{
		$$ = new ConditionList();
	}
	| ON condition condition_list {
		$$ = $3;
		$$->push_front($2);
	}
	;

/*************************** WHERE CLAUSE ****************************/
where:
    /* empty */ 
	{
		$$ = new ConditionList();
	}
    | WHERE condition condition_list {
		$$ = $3;
		$$->push_front($2);
	}
    ;

/*************************** CONDITION ****************************/
condition_list:
    /* empty */
	{
		$$ = new ConditionList();
	}
    | AND condition condition_list {
		$$ = $3;
		$$->push_front($2);
	}
    ;

condition:
	non_subquery comOp non_subquery {
		/* 非子查询 compareOp 非子查询 */
		CompOp op = static_cast<CompOp>($2);
		$$ = (Condition *)malloc(sizeof(Condition));
		non_subquery_cond_init($$, $1, $3, op);
	}
	| non_subquery comOp subquery {
		/* 非子查询 compareOp 子查询 */
		CompOp op = static_cast<CompOp>($2);
		$$ = (Condition *)malloc(sizeof(Condition));
		com_subquery_init($$, $1, $3, op);
	}
	| subquery comOp non_subquery {
		/* 子查询 compareOp 非子查询 */
		CompOp op = static_cast<CompOp>($2);
		$$ = (Condition *)malloc(sizeof(Condition));
		com_subquery_init($$, $3, $1, get_neg_comp_op(op));
	}
	| subquery comOp subquery {
		/* 子查询 compareOp 子查询 */
		CompOp op = static_cast<CompOp>($2);
		$$ = (Condition *)malloc(sizeof(Condition));
		com_subquery_init($$, $3, $1, op);
	}
	| non_subquery membershipOp subquery {
		/* 非子查询 IN/NOT IN 子查询 */
		CompOp op = static_cast<CompOp>($2);
		$$ = (Condition *)malloc(sizeof(Condition));
		membership_subquery_init($$, $1, $3, op);
	}
	| subquery membershipOp subquery {
		/* 子查询 IN/NOT IN 子查询 */
		CompOp op = static_cast<CompOp>($2);
		$$ = (Condition *)malloc(sizeof(Condition));
		membership_subquery_init($$, $1, $3, op);
	}
	;

membershipOp:
	IN { $$ = MEM_IN; }
	| NOT IN { $$ = MEM_NOT_IN; }

non_subquery: 
	non_subquery ADD_OP non_subquery {
		$$ = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr($$, $1, $3, ADD);
	}
	| non_subquery SUB_OP non_subquery {
		$$ = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr($$, $1, $3, SUB);
	}
	| non_subquery STAR non_subquery {
		$$ = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr($$, $1, $3, MUL);
	}
	| non_subquery DIV_OP non_subquery {
		$$ = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr($$, $1, $3, DIV);
	}
	| col {
		$$ = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_attr_init($$, $1);
	}
	| value {
		$$ = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_value_init($$, $1);	
	}
	| LBRACE non_subquery RBRACE {
		$$ = $2;
	}
	| SUB_OP non_subquery %prec UNARYMINUS {
		/* "-" expr  */
		$$ = (ConditionExpr *) malloc(sizeof(ConditionExpr));
		append_cond_expr($$, nullptr, $2, NEG);
	}
	;

comOp:
  	  EQ 		{ $$ = EQUAL_TO; }
    | LT 		{ $$ = LESS_THAN; }
    | GT 		{ $$ = GREAT_THAN; }
    | LE 		{ $$ = LESS_EQUAL; }
    | GE 		{ $$ = GREAT_EQUAL; }
    | NE 		{ $$ = NOT_EQUAL; }
	| IS 		{ $$ = OP_IS; }
	| IS NOT 	{ $$ = OP_IS_NOT; }
    ;

subquery:
	LBRACE select RBRACE {
		$$ = $2;
	}

/*************************** GROUP BY ****************************/
group: 
	/* empty */
	{
		$$ = new GroupByList();
	}
	| GROUP BY col[column] group_by_list[gplist] {
		$$ = $gplist;
		$$->push_front($column);
	}
	;

group_by_list:
	/* empty */
	{
		$$ = new GroupByList();
	}
	| COMMA col[column] group_by_list[gplist] {
		$$ = $gplist;
		$$->push_front($column);
	}
	;

/*************************** ORDER BY ****************************/
order:
	/* empty */
	{
		$$ = new OrderColList;
	}
	| ORDER BY order_col[ocol] order_col_list[ocolist] {
		$$ = $ocolist;
		$$->push_front($ocol);
	}
	;

order_col_list:
	/* empty */
	{
		$$ = new OrderColList;
	}
	| COMMA order_col[ocol] order_col_list[ocolist] {
		$$ = $ocolist;
		$$->push_front($ocol);
	}
	;

order_col:
	col {
		$$ = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init($$, $1, 1);
	}
	| col ASC {
		$$ = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init($$, $1, 1);
	}
	| col DESC {
		$$ = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init($$, $1, 0);
	}
	;

load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(ParserContext));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
