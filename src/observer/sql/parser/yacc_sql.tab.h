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

#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
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
    CREATE = 263,                  /* CREATE  */
    DROP = 264,                    /* DROP  */
    TABLE = 265,                   /* TABLE  */
    TABLES = 266,                  /* TABLES  */
    INDEX = 267,                   /* INDEX  */
    SELECT = 268,                  /* SELECT  */
    DESC = 269,                    /* DESC  */
    SHOW = 270,                    /* SHOW  */
    SYNC = 271,                    /* SYNC  */
    INSERT = 272,                  /* INSERT  */
    DELETE = 273,                  /* DELETE  */
    UPDATE = 274,                  /* UPDATE  */
    LBRACE = 275,                  /* LBRACE  */
    RBRACE = 276,                  /* RBRACE  */
    COMMA = 277,                   /* COMMA  */
    TRX_BEGIN = 278,               /* TRX_BEGIN  */
    TRX_COMMIT = 279,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 280,            /* TRX_ROLLBACK  */
    INT_T = 281,                   /* INT_T  */
    STRING_T = 282,                /* STRING_T  */
    DATE_T = 283,                  /* DATE_T  */
    FLOAT_T = 284,                 /* FLOAT_T  */
    HELP = 285,                    /* HELP  */
    EXIT = 286,                    /* EXIT  */
    IS = 287,                      /* IS  */
    NOT = 288,                     /* NOT  */
    NULL_T = 289,                  /* NULL_T  */
    NULLABLE = 290,                /* NULLABLE  */
    DOT = 291,                     /* DOT  */
    INTO = 292,                    /* INTO  */
    VALUES = 293,                  /* VALUES  */
    FROM = 294,                    /* FROM  */
    WHERE = 295,                   /* WHERE  */
    AND = 296,                     /* AND  */
    SET = 297,                     /* SET  */
    ON = 298,                      /* ON  */
    LOAD = 299,                    /* LOAD  */
    DATA = 300,                    /* DATA  */
    INFILE = 301,                  /* INFILE  */
    EQ = 302,                      /* EQ  */
    LT = 303,                      /* LT  */
    GT = 304,                      /* GT  */
    LE = 305,                      /* LE  */
    GE = 306,                      /* GE  */
    NE = 307,                      /* NE  */
    NUMBER = 308,                  /* NUMBER  */
    FLOAT = 309,                   /* FLOAT  */
    ID = 310,                      /* ID  */
    PATH = 311,                    /* PATH  */
    SSS = 312,                     /* SSS  */
    DATE = 313,                    /* DATE  */
    STAR = 314,                    /* STAR  */
    STRING_V = 315                 /* STRING_V  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 115 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;

#line 134 "yacc_sql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (void *scanner);


#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
