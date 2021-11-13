/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_YACC_SQL_TAB_HPP_INCLUDED
# define YY_YY_YACC_SQL_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 36 "yacc_sql.y"

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

#line 65 "yacc_sql.tab.hpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    MAX_F = 259,
    MIN_F = 260,
    COUNT_F = 261,
    AVG_F = 262,
    INNER = 263,
    JOIN = 264,
    CREATE = 265,
    DROP = 266,
    TABLE = 267,
    TABLES = 268,
    INDEX = 269,
    UNIQUE = 270,
    SELECT = 271,
    DESC = 272,
    SHOW = 273,
    SYNC = 274,
    INSERT = 275,
    DELETE = 276,
    UPDATE = 277,
    LBRACE = 278,
    RBRACE = 279,
    COMMA = 280,
    TRX_BEGIN = 281,
    TRX_COMMIT = 282,
    TRX_ROLLBACK = 283,
    INT_T = 284,
    STRING_T = 285,
    DATE_T = 286,
    FLOAT_T = 287,
    TEXT_T = 288,
    HELP = 289,
    EXIT = 290,
    IS = 291,
    NOT = 292,
    NULL_T = 293,
    NULLABLE = 294,
    DOT = 295,
    INTO = 296,
    VALUES = 297,
    FROM = 298,
    WHERE = 299,
    AND = 300,
    SET = 301,
    ON = 302,
    LOAD = 303,
    DATA = 304,
    INFILE = 305,
    GROUP = 306,
    ORDER = 307,
    BY = 308,
    ASC = 309,
    ADD_OP = 310,
    SUB_OP = 311,
    DIV_OP = 312,
    EQ = 313,
    LT = 314,
    GT = 315,
    LE = 316,
    GE = 317,
    NE = 318,
    IN = 319,
    NUMBER = 320,
    FLOAT = 321,
    ID = 322,
    PATH = 323,
    SSS = 324,
    DATE = 325,
    STAR = 326,
    STRING_V = 327,
    UNARYMINUS = 328
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 121 "yacc_sql.y"

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

#line 171 "yacc_sql.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_HPP_INCLUDED  */
