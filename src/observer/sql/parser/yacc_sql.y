
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct QueryContext{
  Query *ssql;
  size_t value_length;
  size_t condition_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  char id[MAX_NUM];
} QueryContext;

typedef struct ParserContext {
  Query *ssql;
  QueryContext context_stack[MAX_NUM]; // 只允许嵌套深度不超过20
  int top;							   // 栈顶指针
} ParserContext;

void init(Query *query, yyscan_t scanner) {
	ParserContext *global = (ParserContext *)yyget_extra(scanner);
	global->top = 0;
	global->context_stack[0].ssql = query;
}

QueryContext *top(yyscan_t scanner) {
	ParserContext *global = (ParserContext *)yyget_extra(scanner);
	return &(global->context_stack[global->top]);
}

void pop(yyscan_t scanner) {
	ParserContext *global = (ParserContext *)yyget_extra(scanner);
	global->top --;
}

void push(yyscan_t scanner) {
	ParserContext *global = (ParserContext *)yyget_extra(scanner);
	global->top ++;
}

/////////////////////////////////////////////////
// 由于整个过程只有一个scanner，使用marco封装

/**
 * ParserContext初始化，将解析结果Q放入栈顶
 */
#define INIT(Q) init(Q, scanner)

/**
 * 返回指向Query Context Stack栈顶QueryContext结构的指针
 */
#define TOP top(scanner)

/**
 * 将Query Context Stack栈顶弹出
 */
#define POP pop(scanner)

/**
 * 栈顶指针上移
 * PS: 注意给Query *ssql分配空间
 */
 #define PUSH push(scanner)

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
		MUL_OP
		DIV_OP
        EQ
        LT
        GT
        LE
        GE
        NE
		IN

%union {
  struct _Selects *select;
  struct _TableRef *ref;		// Table reference
  struct _SelectExpr *sexpr;	// select expr
  struct _ConditionExpr *cexpr; // condition expr
  struct _RelAttr *attr;
  struct _OrderCol *ocol; 		// order column
  char *string;
  int number;
  float floats;
  char *position;
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

%type <number> arithOp
%type <number> membershipOp
%type <number> comOp

%type <ref>	table_ref
%type <ref>	join_table
%type <sexpr> select_expr
%type <sexpr> select_func
%type <sexpr> select_arith_expr
%type <attr> col
%type <ocol> order_col

%type <cexpr> non_subquery

%type <number> type
%type <number> is_nullable
%type <number> aggregate_func
%type <number> number

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
    CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
		create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5, $7);
	}
    ;

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
		attr_info_init(&attribute, $1, $2, $4, $6);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
    |ID type is_nullable {
		AttrInfo attribute;
		attr_info_init(&attribute, $1, $2, $2 == DATES ? 8 : 4, $3);
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
	LBRACE value value_list RBRACE {
		// 由于tuple这种语法[形如(v1, v2, ..., vn)]只在insert中使用
		insert_tuple_init(&CONTEXT->ssql->sstr.insertion, TOP->values, TOP->value_length);
		// 清空CONTEXT临时变量
		TOP->value_length = 0;
	}

value_list:
    /* empty */
    | COMMA value value_list  {}
    ;
value:
    NUMBER{	
  		value_init_integer(&TOP->values[TOP->value_length++], $1);
	}
    | FLOAT{
  		value_init_float(&TOP->values[TOP->value_length++], $1);
	}
    | SSS {
  		value_init_string(&TOP->values[TOP->value_length++], $1);
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
			value_init_date(&TOP->values[TOP->value_length++], mktime(&t));
		}
	}
	| NULL_T {
		value_init_null(&TOP->values[TOP->value_length++]);
	}
    ;
    
delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON {
		CONTEXT->ssql->flag = SCF_DELETE;//"delete";
		deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
		deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, TOP->conditions, TOP->condition_length);
		
		// CONTEXT临时变量清零
		TOP->condition_length = 0;	
    }
    ;
update:			/*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where SEMICOLON {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		Value *value = &TOP->values[0];
		updates_init(&CONTEXT->ssql->sstr.update, $2, $4, value, TOP->conditions, TOP->condition_length);
		
		// CONTEXT临时变量清零
		TOP->condition_length = 0;
	}
    ;
selects:				/*  select 语句的语法解析树*/
    select SEMICOLON {
		CONTEXT->ssql->flag = SCF_SELECT; //"select";
	}
select:
	SELECT select_expr select_expr_list FROM table_ref table_ref_list where group order
	{
		// 1. append select_expr $2
		selects_append_expr(&TOP->ssql->sstr.selection, $2);

		// 2. append table_ref $5
		selects_append_relation(&TOP->ssql->sstr.selection, $5);

		// 3. append condtion_list(可选项，可能为空)
		selects_append_conditions(&TOP->ssql->sstr.selection, TOP->conditions, TOP->condition_length);

		// 4. append group_list(可选项，可能为空)

		// 5. append order_list(可选项，可能为空)
		

		//临时变量清零
		TOP->condition_length=0;
		TOP->value_length = 0;

		$$ = &TOP->ssql->sstr.selection;
	}
	;

/*************************** SELECT CLAUSE ****************************/
select_expr_list:
	/* empty */
	| COMMA select_expr select_expr_list {
		// append select_expr $2
		selects_append_expr(&TOP->ssql->sstr.selection, $2);
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
	select_arith_expr arithOp select_arith_expr {
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr($$, $1, $3, $2);
	}
	| col {
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init($$, $1);
	}
	| value { 
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_value_init($$, &TOP->values[TOP->value_length - 1]);	

		// 释放临时变量
		TOP->value_length --;
	}
	;

arithOp:
	  ADD_OP { $$ = ADD; }
	| SUB_OP { $$ = SUB; }
	| STAR   { $$ = MUL; }
	| DIV_OP { $$ = DIV; }
	;

select_func: 
	aggregate_func LBRACE col RBRACE {
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		aggregate_function_init($$, $1, $3);
	}
	| aggregate_func LBRACE STAR RBRACE {
		if ($1 != COUNT_FUNC) {
			CONTEXT->ssql->sstr.errors = "Invalid args of aggregate function";
			YYERROR;
		}
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, NULL, "*");
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		aggregate_function_init($$, $1, attr);
	}
	| aggregate_func LBRACE ID DOT STAR RBRACE {
		if ($1 != COUNT_FUNC) {
			CONTEXT->ssql->sstr.errors = "Invalid args of aggregate function";
			YYERROR;
		}
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, $3, "*");
		$$ = (SelectExpr *) malloc(sizeof(SelectExpr));
		aggregate_function_init($$, $1, attr);
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
    | COMMA table_ref table_ref_list {	
		selects_append_relation(&TOP->ssql->sstr.selection, $2);
	}
    ;

table_ref: 
	ID { 
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 0, $1, NULL, NULL, 0); 
		$$ = ref;
	} 
	| join_table { $$ = $1; }
	;

join_table: 
	table_ref INNER JOIN ID join_condition {
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 1, $4, $1, TOP->conditions, TOP->condition_length);
		$$ = ref;
		// 临时变量清零
		TOP->condition_length = 0;
	}
	;

join_condition:
	/* empty */
	| ON condition condition_list {}
	;

/*************************** WHERE CLAUSE ****************************/
where:
    /* empty */ 
    | WHERE condition condition_list {}
    ;

/*************************** CONDITION ****************************/
condition_list:
    /* empty */
    | AND condition condition_list {}
    ;

condition:
	non_subquery comOp non_subquery {
		non_subquery_cond_init(&TOP->conditions[TOP->condition_length++], $1, $3, $2);
	}
	| non_subquery comOp subquery {
		com_subquery_init(&TOP->conditions[TOP->condition_length++], $1, $3, $2);
	}
	| non_subquery membershipOp subquery {
		membership_subquery_init(&TOP->conditions[TOP->condition_length++], $1, $3, $2);
	}
	;

membershipOp:
	IN { $$ = MEM_IN; }
	| NOT IN { $$ = MEM_NOT_IN; }

non_subquery: 
	non_subquery arithOp non_subquery {
		$$ = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr($$, $1, $3, $2);
	}
	| col {
		$$ = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_attr_init($$, $1);
	}
	| value {
		$$ = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_value_init($$, &TOP->values[TOP->value_length - 1]);	

		// 释放临时变量
		TOP->value_length --;
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
	subquery_start LBRACE select RBRACE {
		$$ = $3;
		POP;
	}

subquery_start: {
	PUSH;
	TOP->ssql = (Query *)malloc(sizeof(Query));
}

/*************************** GROUP BY ****************************/
group: 
	/* empty */
	| GROUP BY col group_list {
		selects_append_group(&TOP->ssql->sstr.selection, $3);
	}
	;

group_list:
	/* empty */
	| COMMA col group_list {
		selects_append_group(&TOP->ssql->sstr.selection, $2);
	}
	;

/*************************** ORDER BY ****************************/
order:
	/* empty */
	| ORDER BY order_col order_list {
		selects_append_order(&TOP->ssql->sstr.selection, $3);
	}
	;

order_list:
	/* empty */
	| COMMA order_col order_list {
		selects_append_order(&TOP->ssql->sstr.selection, $2);
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
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	INIT(sqls);
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
