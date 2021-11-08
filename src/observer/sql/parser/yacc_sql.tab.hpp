/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_TAB_HPP_INCLUDED
# define YY_YY_YACC_SQL_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    MAX_F = 259,                   /* MAX_F  */
    MIN_F = 260,                   /* MIN_F  */
    COUNT_F = 261,                 /* COUNT_F  */
    AVG_F = 262,                   /* AVG_F  */
    INNER = 263,                   /* INNER  */
    JOIN = 264,                    /* JOIN  */
    CREATE = 265,                  /* CREATE  */
    DROP = 266,                    /* DROP  */
    TABLE = 267,                   /* TABLE  */
    TABLES = 268,                  /* TABLES  */
    INDEX = 269,                   /* INDEX  */
    UNIQUE = 270,                  /* UNIQUE  */
    SELECT = 271,                  /* SELECT  */
    DESC = 272,                    /* DESC  */
    SHOW = 273,                    /* SHOW  */
    SYNC = 274,                    /* SYNC  */
    INSERT = 275,                  /* INSERT  */
    DELETE = 276,                  /* DELETE  */
    UPDATE = 277,                  /* UPDATE  */
    LBRACE = 278,                  /* LBRACE  */
    RBRACE = 279,                  /* RBRACE  */
    COMMA = 280,                   /* COMMA  */
    TRX_BEGIN = 281,               /* TRX_BEGIN  */
    TRX_COMMIT = 282,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 283,            /* TRX_ROLLBACK  */
    INT_T = 284,                   /* INT_T  */
    STRING_T = 285,                /* STRING_T  */
    DATE_T = 286,                  /* DATE_T  */
    FLOAT_T = 287,                 /* FLOAT_T  */
    TEXT_T = 288,                  /* TEXT_T  */
    HELP = 289,                    /* HELP  */
    EXIT = 290,                    /* EXIT  */
    IS = 291,                      /* IS  */
    NOT = 292,                     /* NOT  */
    NULL_T = 293,                  /* NULL_T  */
    NULLABLE = 294,                /* NULLABLE  */
    DOT = 295,                     /* DOT  */
    INTO = 296,                    /* INTO  */
    VALUES = 297,                  /* VALUES  */
    FROM = 298,                    /* FROM  */
    WHERE = 299,                   /* WHERE  */
    AND = 300,                     /* AND  */
    SET = 301,                     /* SET  */
    ON = 302,                      /* ON  */
    LOAD = 303,                    /* LOAD  */
    DATA = 304,                    /* DATA  */
    INFILE = 305,                  /* INFILE  */
    GROUP = 306,                   /* GROUP  */
    ORDER = 307,                   /* ORDER  */
    BY = 308,                      /* BY  */
    ASC = 309,                     /* ASC  */
    ADD_OP = 310,                  /* ADD_OP  */
    SUB_OP = 311,                  /* SUB_OP  */
    DIV_OP = 312,                  /* DIV_OP  */
    EQ = 313,                      /* EQ  */
    LT = 314,                      /* LT  */
    GT = 315,                      /* GT  */
    LE = 316,                      /* LE  */
    GE = 317,                      /* GE  */
    NE = 318,                      /* NE  */
    IN = 319,                      /* IN  */
    NUMBER = 320,                  /* NUMBER  */
    FLOAT = 321,                   /* FLOAT  */
    ID = 322,                      /* ID  */
    PATH = 323,                    /* PATH  */
    SSS = 324,                     /* SSS  */
    DATE = 325,                    /* DATE  */
    STAR = 326,                    /* STAR  */
    STRING_V = 327                 /* STRING_V  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 158 "yacc_sql.y"

  struct _Selects *select;
  struct _TableRef *ref;		// Table reference
  struct _SelectExpr *sexpr;	// select expr
  struct _ConditionExpr *cexpr; // condition expr
  struct _RelAttr *attr;
  struct _Value *val;
  struct _OrderCol *ocol; 		// order column
  char *string;
  int number;
  float floats;
  char *position;

#line 150 "yacc_sql.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (void *scanner);


#endif /* !YY_YY_YACC_SQL_TAB_HPP_INCLUDED  */
