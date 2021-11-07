/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.hpp"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<cstdio>
#include<stdlib.h>
#include<cstring>

typedef struct QueryContext{
  Query *ssql;
  size_t value_length{};
  size_t condition_length{};
  Value values[MAX_NUM]{};
  Condition conditions[MAX_NUM]{};
} QueryContext;

typedef struct ParserContext {
  Query *ssql;
  QueryContext context_stack[MAX_NUM]{}; // 只允许嵌套深度不超过20
  int top{};							   // 栈顶指针
} ParserContext;

void init(Query *query, yyscan_t scanner) {
	ParserContext *global = (ParserContext *)yyget_extra(scanner);
	global->top = -1;
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


#line 159 "yacc_sql.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_MAX_F = 4,                      /* MAX_F  */
  YYSYMBOL_MIN_F = 5,                      /* MIN_F  */
  YYSYMBOL_COUNT_F = 6,                    /* COUNT_F  */
  YYSYMBOL_AVG_F = 7,                      /* AVG_F  */
  YYSYMBOL_INNER = 8,                      /* INNER  */
  YYSYMBOL_JOIN = 9,                       /* JOIN  */
  YYSYMBOL_CREATE = 10,                    /* CREATE  */
  YYSYMBOL_DROP = 11,                      /* DROP  */
  YYSYMBOL_TABLE = 12,                     /* TABLE  */
  YYSYMBOL_TABLES = 13,                    /* TABLES  */
  YYSYMBOL_INDEX = 14,                     /* INDEX  */
  YYSYMBOL_UNIQUE = 15,                    /* UNIQUE  */
  YYSYMBOL_SELECT = 16,                    /* SELECT  */
  YYSYMBOL_DESC = 17,                      /* DESC  */
  YYSYMBOL_SHOW = 18,                      /* SHOW  */
  YYSYMBOL_SYNC = 19,                      /* SYNC  */
  YYSYMBOL_INSERT = 20,                    /* INSERT  */
  YYSYMBOL_DELETE = 21,                    /* DELETE  */
  YYSYMBOL_UPDATE = 22,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 23,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 24,                    /* RBRACE  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 26,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 27,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 28,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 29,                     /* INT_T  */
  YYSYMBOL_STRING_T = 30,                  /* STRING_T  */
  YYSYMBOL_DATE_T = 31,                    /* DATE_T  */
  YYSYMBOL_FLOAT_T = 32,                   /* FLOAT_T  */
  YYSYMBOL_TEXT_T = 33,                    /* TEXT_T  */
  YYSYMBOL_HELP = 34,                      /* HELP  */
  YYSYMBOL_EXIT = 35,                      /* EXIT  */
  YYSYMBOL_IS = 36,                        /* IS  */
  YYSYMBOL_NOT = 37,                       /* NOT  */
  YYSYMBOL_NULL_T = 38,                    /* NULL_T  */
  YYSYMBOL_NULLABLE = 39,                  /* NULLABLE  */
  YYSYMBOL_DOT = 40,                       /* DOT  */
  YYSYMBOL_INTO = 41,                      /* INTO  */
  YYSYMBOL_VALUES = 42,                    /* VALUES  */
  YYSYMBOL_FROM = 43,                      /* FROM  */
  YYSYMBOL_WHERE = 44,                     /* WHERE  */
  YYSYMBOL_AND = 45,                       /* AND  */
  YYSYMBOL_SET = 46,                       /* SET  */
  YYSYMBOL_ON = 47,                        /* ON  */
  YYSYMBOL_LOAD = 48,                      /* LOAD  */
  YYSYMBOL_DATA = 49,                      /* DATA  */
  YYSYMBOL_INFILE = 50,                    /* INFILE  */
  YYSYMBOL_GROUP = 51,                     /* GROUP  */
  YYSYMBOL_ORDER = 52,                     /* ORDER  */
  YYSYMBOL_BY = 53,                        /* BY  */
  YYSYMBOL_ASC = 54,                       /* ASC  */
  YYSYMBOL_ADD_OP = 55,                    /* ADD_OP  */
  YYSYMBOL_SUB_OP = 56,                    /* SUB_OP  */
  YYSYMBOL_DIV_OP = 57,                    /* DIV_OP  */
  YYSYMBOL_EQ = 58,                        /* EQ  */
  YYSYMBOL_LT = 59,                        /* LT  */
  YYSYMBOL_GT = 60,                        /* GT  */
  YYSYMBOL_LE = 61,                        /* LE  */
  YYSYMBOL_GE = 62,                        /* GE  */
  YYSYMBOL_NE = 63,                        /* NE  */
  YYSYMBOL_IN = 64,                        /* IN  */
  YYSYMBOL_NUMBER = 65,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 66,                     /* FLOAT  */
  YYSYMBOL_ID = 67,                        /* ID  */
  YYSYMBOL_PATH = 68,                      /* PATH  */
  YYSYMBOL_SSS = 69,                       /* SSS  */
  YYSYMBOL_DATE = 70,                      /* DATE  */
  YYSYMBOL_STAR = 71,                      /* STAR  */
  YYSYMBOL_STRING_V = 72,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 73,                  /* $accept  */
  YYSYMBOL_commands = 74,                  /* commands  */
  YYSYMBOL_command = 75,                   /* command  */
  YYSYMBOL_exit = 76,                      /* exit  */
  YYSYMBOL_help = 77,                      /* help  */
  YYSYMBOL_sync = 78,                      /* sync  */
  YYSYMBOL_begin = 79,                     /* begin  */
  YYSYMBOL_commit = 80,                    /* commit  */
  YYSYMBOL_rollback = 81,                  /* rollback  */
  YYSYMBOL_drop_table = 82,                /* drop_table  */
  YYSYMBOL_show_tables = 83,               /* show_tables  */
  YYSYMBOL_desc_table = 84,                /* desc_table  */
  YYSYMBOL_create_index = 85,              /* create_index  */
  YYSYMBOL_attr_list = 86,                 /* attr_list  */
  YYSYMBOL_drop_index = 87,                /* drop_index  */
  YYSYMBOL_create_table = 88,              /* create_table  */
  YYSYMBOL_attr_def_list = 89,             /* attr_def_list  */
  YYSYMBOL_attr_def = 90,                  /* attr_def  */
  YYSYMBOL_number = 91,                    /* number  */
  YYSYMBOL_type = 92,                      /* type  */
  YYSYMBOL_is_nullable = 93,               /* is_nullable  */
  YYSYMBOL_insert = 94,                    /* insert  */
  YYSYMBOL_tuple_list = 95,                /* tuple_list  */
  YYSYMBOL_tuple = 96,                     /* tuple  */
  YYSYMBOL_value_list = 97,                /* value_list  */
  YYSYMBOL_value = 98,                     /* value  */
  YYSYMBOL_delete = 99,                    /* delete  */
  YYSYMBOL_update = 100,                   /* update  */
  YYSYMBOL_selects = 101,                  /* selects  */
  YYSYMBOL_select = 102,                   /* select  */
  YYSYMBOL_start_select = 103,             /* start_select  */
  YYSYMBOL_select_expr_list = 104,         /* select_expr_list  */
  YYSYMBOL_select_expr = 105,              /* select_expr  */
  YYSYMBOL_select_arith_expr = 106,        /* select_arith_expr  */
  YYSYMBOL_select_func = 107,              /* select_func  */
  YYSYMBOL_aggregate_func = 108,           /* aggregate_func  */
  YYSYMBOL_col = 109,                      /* col  */
  YYSYMBOL_table_ref_list = 110,           /* table_ref_list  */
  YYSYMBOL_table_ref = 111,                /* table_ref  */
  YYSYMBOL_join_table = 112,               /* join_table  */
  YYSYMBOL_join_condition = 113,           /* join_condition  */
  YYSYMBOL_where = 114,                    /* where  */
  YYSYMBOL_condition_list = 115,           /* condition_list  */
  YYSYMBOL_condition = 116,                /* condition  */
  YYSYMBOL_membershipOp = 117,             /* membershipOp  */
  YYSYMBOL_non_subquery = 118,             /* non_subquery  */
  YYSYMBOL_comOp = 119,                    /* comOp  */
  YYSYMBOL_subquery = 120,                 /* subquery  */
  YYSYMBOL_group = 121,                    /* group  */
  YYSYMBOL_group_list = 122,               /* group_list  */
  YYSYMBOL_order = 123,                    /* order  */
  YYSYMBOL_order_list = 124,               /* order_list  */
  YYSYMBOL_order_col = 125,                /* order_col  */
  YYSYMBOL_load_data = 126                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   271

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  130
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  258

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   327


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   209,   209,   211,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   235,   240,   245,   251,   257,   263,   269,   275,   281,
     288,   294,   302,   304,   309,   316,   321,   323,   327,   333,
     342,   346,   347,   348,   349,   350,   354,   355,   356,   360,
     365,   367,   371,   378,   380,   383,   386,   389,   392,   408,
     414,   424,   434,   438,   462,   469,   471,   478,   479,   480,
     486,   499,   503,   507,   511,   515,   519,   526,   533,   538,
     549,   563,   564,   565,   566,   570,   574,   581,   583,   589,
     594,   598,   607,   609,   613,   615,   619,   621,   625,   629,
     633,   640,   641,   644,   648,   652,   656,   660,   664,   671,
     677,   678,   679,   680,   681,   682,   683,   684,   688,   694,
     696,   701,   703,   709,   711,   716,   718,   724,   728,   732,
     739
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "MAX_F",
  "MIN_F", "COUNT_F", "AVG_F", "INNER", "JOIN", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "UNIQUE", "SELECT", "DESC", "SHOW", "SYNC", "INSERT",
  "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "DATE_T", "FLOAT_T",
  "TEXT_T", "HELP", "EXIT", "IS", "NOT", "NULL_T", "NULLABLE", "DOT",
  "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA",
  "INFILE", "GROUP", "ORDER", "BY", "ASC", "ADD_OP", "SUB_OP", "DIV_OP",
  "EQ", "LT", "GT", "LE", "GE", "NE", "IN", "NUMBER", "FLOAT", "ID",
  "PATH", "SSS", "DATE", "STAR", "STRING_V", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index", "attr_list",
  "drop_index", "create_table", "attr_def_list", "attr_def", "number",
  "type", "is_nullable", "insert", "tuple_list", "tuple", "value_list",
  "value", "delete", "update", "selects", "select", "start_select",
  "select_expr_list", "select_expr", "select_arith_expr", "select_func",
  "aggregate_func", "col", "table_ref_list", "table_ref", "join_table",
  "join_condition", "where", "condition_list", "condition", "membershipOp",
  "non_subquery", "comOp", "subquery", "group", "group_list", "order",
  "order_list", "order_col", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-191)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -191,    88,  -191,   123,    32,  -191,   -28,    12,    46,    11,
      23,     0,    69,    74,    80,    98,    99,    41,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,   100,  -191,    45,    50,   106,
      54,    58,     4,   110,   127,  -191,    59,    67,    94,  -191,
    -191,  -191,  -191,  -191,   102,  -191,   122,   107,    86,   145,
     152,  -191,  -191,  -191,  -191,    62,  -191,  -191,  -191,   119,
    -191,  -191,  -191,  -191,   138,   -43,  -191,   146,  -191,  -191,
    -191,   143,   142,   125,   118,   126,   128,   147,  -191,  -191,
     149,    87,   -45,     4,   160,    62,    62,    62,    62,    -3,
     167,    95,   202,   148,   166,   168,   183,   186,   150,   151,
    -191,  -191,  -191,   138,   153,   -52,   -52,  -191,  -191,   170,
     188,   189,    81,   190,    95,  -191,  -191,   169,   120,  -191,
      81,   204,  -191,  -191,  -191,  -191,  -191,    -5,   126,   195,
     154,   199,  -191,  -191,    -4,  -191,    15,  -191,  -191,   198,
     167,   221,   117,    95,  -191,   191,   161,    95,    95,    95,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,    95,   203,   101,
     142,   162,   165,   193,  -191,  -191,   183,   224,   207,   171,
     225,   153,   142,   209,    81,   211,   190,  -191,  -191,   169,
    -191,  -191,   -33,   -33,  -191,  -191,   220,  -191,    27,   -40,
    -191,   234,   236,  -191,   216,  -191,  -191,  -191,   174,   218,
     207,   176,    -4,   194,  -191,   198,  -191,  -191,  -191,   222,
    -191,  -191,    52,   207,   241,   223,   201,  -191,   196,   200,
    -191,  -191,  -191,  -191,  -191,   247,    95,  -191,   184,   205,
    -191,  -191,   169,   228,   184,  -191,   184,  -191,   -14,   229,
     228,  -191,  -191,   184,  -191,  -191,   229,  -191
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,     0,    18,     0,     0,     0,
       0,     0,     0,     0,     0,    23,     0,     0,     0,    24,
      25,    26,    22,    21,     0,    62,     0,     0,     0,     0,
       0,    81,    82,    83,    84,     0,    59,    55,    56,    85,
      57,    58,    69,    76,    65,    67,    68,     0,    75,    29,
      28,     0,    94,     0,     0,     0,     0,     0,    27,    34,
      85,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,     0,     0,     0,
      77,    86,    70,    65,     0,    71,    72,    74,    73,    85,
       0,     0,     0,    50,     0,   108,   107,    96,     0,    60,
       0,     0,    41,    42,    44,    43,    45,    46,     0,     0,
       0,     0,    66,    89,    87,    90,     0,    79,    78,    53,
       0,     0,     0,     0,    95,   116,     0,     0,     0,     0,
     110,   111,   112,   113,   114,   115,   101,     0,     0,     0,
      94,     0,     0,     0,    48,    39,    36,     0,    32,     0,
       0,     0,    94,     0,     0,     0,    50,    49,   109,    96,
     117,   102,   103,   104,   106,   105,     0,   100,     0,    98,
      99,     0,     0,    40,     0,    47,    37,    35,     0,     0,
      32,     0,    87,   119,    80,    53,    52,    51,    97,     0,
      61,   130,    46,    32,     0,     0,    92,    88,     0,   123,
      54,   118,    38,    33,    30,     0,     0,    91,     0,     0,
      63,    31,    96,   121,     0,    93,     0,   120,   127,   125,
     121,   129,   128,     0,   124,   122,   125,   126
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -190,  -191,  -191,    79,   121,  -191,  -191,
      34,  -191,    71,   111,    47,   -35,  -191,  -191,  -191,   259,
    -191,   155,   172,   -17,  -191,  -191,   -42,    51,    83,  -191,
    -191,  -141,  -183,  -152,  -191,  -122,  -191,    97,  -191,    17,
    -191,    13,    18,  -191
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   209,    29,    30,   139,   106,   204,   137,
     175,    31,   151,   123,   185,   125,    32,    33,    34,   219,
      42,    94,    74,    75,    76,    77,   126,   182,   144,   145,
     237,   102,   154,   127,   168,   128,   169,   197,   229,   247,
     240,   254,   249,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      78,   189,   152,   251,   180,    97,   218,    73,    61,    62,
      63,    64,    95,    96,    97,   157,   158,   159,   172,    98,
     225,   181,   111,    78,   159,    44,   112,    65,    98,   201,
      73,   167,   173,   233,   174,   192,   193,   194,   167,    43,
     252,   213,    66,     5,    40,   195,    41,   199,    91,    45,
     124,    78,    46,    78,    78,    78,    78,   121,    73,   245,
      73,    73,    73,    73,   119,    66,    47,    48,   120,    67,
      68,    69,    49,    70,    71,    72,   152,    50,   115,   116,
     117,   118,   111,    51,   242,    65,   183,   149,     2,   173,
      54,   174,    67,    68,    90,   170,    70,    71,     3,     4,
      66,    52,    53,    55,     5,     6,     7,     8,     9,    10,
      11,   110,    56,    79,    12,    13,    14,    57,   124,    66,
      58,    59,    15,    16,   198,    60,    81,    67,    68,    90,
      80,    70,    71,    66,    82,    37,    17,    38,    39,    66,
      83,   188,    95,    96,    97,    85,    67,    68,    88,   215,
      70,    71,    84,    87,    86,    89,   155,   156,    98,    92,
      67,    68,    90,    93,    70,    71,    67,    68,    90,    99,
      70,    71,   157,   158,   159,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   100,   101,   104,   167,   109,
     122,   167,   103,   105,   108,   107,   243,   132,   133,   134,
     135,   136,   248,   114,   250,   129,   130,   131,   138,   140,
     146,   248,   147,   148,   153,   150,   171,   141,   111,   177,
     143,   178,   179,   184,   187,   191,   196,   207,   190,   202,
     203,   205,   208,   214,   211,   216,     5,   220,   210,   221,
     222,   223,   224,   226,   234,   228,   231,   235,   236,   238,
     241,    90,   239,   246,   253,   206,   232,   217,   244,   176,
      35,   186,   230,   227,   212,   113,   200,   255,   142,   257,
       0,   256
};

static const yytype_int16 yycheck[] =
{
      42,   153,   124,    17,     8,    57,   189,    42,     4,     5,
       6,     7,    55,    56,    57,    55,    56,    57,    23,    71,
     210,    25,    67,    65,    57,    13,    71,    23,    71,   170,
      65,    71,    37,   223,    39,   157,   158,   159,    71,    67,
      54,   182,    38,    16,    12,   167,    14,   169,    65,     3,
      23,    93,    41,    95,    96,    97,    98,    99,    93,   242,
      95,    96,    97,    98,    67,    38,    43,    67,    71,    65,
      66,    67,     3,    69,    70,    71,   198,     3,    95,    96,
      97,    98,    67,     3,   236,    23,    71,   122,     0,    37,
      49,    39,    65,    66,    67,   130,    69,    70,    10,    11,
      38,     3,     3,     3,    16,    17,    18,    19,    20,    21,
      22,    24,    67,     3,    26,    27,    28,    67,    23,    38,
      14,    67,    34,    35,    23,    67,    67,    65,    66,    67,
       3,    69,    70,    38,    67,    12,    48,    14,    15,    38,
      46,    24,    55,    56,    57,    23,    65,    66,     3,   184,
      69,    70,    50,    67,    47,     3,    36,    37,    71,    40,
      65,    66,    67,    25,    69,    70,    65,    66,    67,    23,
      69,    70,    55,    56,    57,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    42,    44,    69,    71,    40,
      23,    71,    67,    67,    47,    67,   238,    29,    30,    31,
      32,    33,   244,    43,   246,     3,    58,    41,    25,    23,
      40,   253,    24,    24,    45,    25,    12,    67,    67,    24,
      67,    67,    23,    25,     3,    64,    23,     3,    37,    67,
      65,    38,    25,    24,     9,    24,    16,     3,    67,     3,
      24,    67,    24,    67,     3,    51,    24,    24,    47,    53,
       3,    67,    52,    25,    25,   176,   222,   186,    53,   138,
       1,   150,   215,   212,   181,    93,   169,   250,   113,   256,
      -1,   253
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    74,     0,    10,    11,    16,    17,    18,    19,    20,
      21,    22,    26,    27,    28,    34,    35,    48,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    87,
      88,    94,    99,   100,   101,   102,   126,    12,    14,    15,
      12,    14,   103,    67,    13,     3,    41,    43,    67,     3,
       3,     3,     3,     3,    49,     3,    67,    67,    14,    67,
      67,     4,     5,     6,     7,    23,    38,    65,    66,    67,
      69,    70,    71,    98,   105,   106,   107,   108,   109,     3,
       3,    67,    67,    46,    50,    23,    47,    67,     3,     3,
      67,   106,    40,    25,   104,    55,    56,    57,    71,    23,
      42,    44,   114,    67,    69,    67,    90,    67,    47,    40,
      24,    67,    71,   105,    43,   106,   106,   106,   106,    67,
      71,   109,    23,    96,    23,    98,   109,   116,   118,     3,
      58,    41,    29,    30,    31,    32,    33,    92,    25,    89,
      23,    67,   104,    67,   111,   112,    40,    24,    24,    98,
      25,    95,   118,    45,   115,    36,    37,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    71,   117,   119,
      98,    12,    23,    37,    39,    93,    90,    24,    67,    23,
       8,    25,   110,    71,    25,    97,    96,     3,    24,   116,
      37,    64,   118,   118,   118,   118,    23,   120,    23,   118,
     120,   114,    67,    65,    91,    38,    89,     3,    25,    86,
      67,     9,   111,   114,    24,    98,    24,    95,   115,   102,
       3,     3,    24,    67,    24,    86,    67,   110,    51,   121,
      97,    24,    93,    86,     3,    24,    47,   113,    53,    52,
     123,     3,   116,   109,    53,   115,    25,   122,   109,   125,
     109,    17,    54,    25,   124,   122,   125,   124
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    73,    74,    74,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    85,    86,    86,    87,    88,    89,    89,    90,    90,
      91,    92,    92,    92,    92,    92,    93,    93,    93,    94,
      95,    95,    96,    97,    97,    98,    98,    98,    98,    98,
      99,   100,   101,   102,   103,   104,   104,   105,   105,   105,
     105,   106,   106,   106,   106,   106,   106,   106,   107,   107,
     107,   108,   108,   108,   108,   109,   109,   110,   110,   111,
     111,   112,   113,   113,   114,   114,   115,   115,   116,   116,
     116,   117,   117,   118,   118,   118,   118,   118,   118,   118,
     119,   119,   119,   119,   119,   119,   119,   119,   120,   121,
     121,   122,   122,   123,   123,   124,   124,   125,   125,   125,
     126
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    11,     0,     3,     4,     8,     0,     3,     6,     3,
       1,     1,     1,     1,     1,     1,     0,     2,     1,     7,
       0,     3,     4,     0,     3,     1,     1,     1,     1,     1,
       5,     8,     2,    10,     0,     0,     3,     1,     1,     1,
       3,     3,     3,     3,     3,     1,     1,     3,     4,     4,
       6,     1,     1,     1,     1,     1,     3,     0,     3,     1,
       1,     5,     0,     3,     0,     3,     0,     3,     3,     3,
       3,     1,     2,     3,     3,     3,     3,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     0,
       4,     0,     3,     0,     4,     0,     3,     1,     2,     2,
       8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 21: /* exit: EXIT SEMICOLON  */
#line 235 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1471 "yacc_sql.tab.cpp"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 240 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1479 "yacc_sql.tab.cpp"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 245 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1487 "yacc_sql.tab.cpp"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 251 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1495 "yacc_sql.tab.cpp"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 257 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1503 "yacc_sql.tab.cpp"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 263 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1511 "yacc_sql.tab.cpp"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 269 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1520 "yacc_sql.tab.cpp"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 275 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1528 "yacc_sql.tab.cpp"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 281 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1537 "yacc_sql.tab.cpp"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID attr_list RBRACE SEMICOLON  */
#line 289 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
		}
#line 1547 "yacc_sql.tab.cpp"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID attr_list RBRACE SEMICOLON  */
#line 295 "yacc_sql.y"
                {	// 由于只用支持UNIQUE，采用最简单写法
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_unique_index";
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
		}
#line 1557 "yacc_sql.tab.cpp"
    break;

  case 33: /* attr_list: COMMA ID attr_list  */
#line 304 "yacc_sql.y"
                             {
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1565 "yacc_sql.tab.cpp"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 309 "yacc_sql.y"
                             {
		CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
		drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
	}
#line 1574 "yacc_sql.tab.cpp"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 316 "yacc_sql.y"
                                                                   {
		CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
		create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
	}
#line 1583 "yacc_sql.tab.cpp"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 323 "yacc_sql.y"
                                   {    }
#line 1589 "yacc_sql.tab.cpp"
    break;

  case 38: /* attr_def: ID type LBRACE number RBRACE is_nullable  */
#line 327 "yacc_sql.y"
                                            {
		AttrInfo attribute;
		AttrType type = static_cast<AttrType>((yyvsp[-4].number));
		attr_info_init(&attribute, (yyvsp[-5].string), type, (yyvsp[-2].number), (yyvsp[0].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
#line 1600 "yacc_sql.tab.cpp"
    break;

  case 39: /* attr_def: ID type is_nullable  */
#line 333 "yacc_sql.y"
                         {
		AttrInfo attribute;
		AttrType type = static_cast<AttrType>((yyvsp[-1].number));
		attr_info_init(&attribute, (yyvsp[-2].string), type, (type == DATES || type == ATTR_TEXT) ? 8 : 4, (yyvsp[0].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
#line 1611 "yacc_sql.tab.cpp"
    break;

  case 40: /* number: NUMBER  */
#line 342 "yacc_sql.y"
               {(yyval.number) = (yyvsp[0].number);}
#line 1617 "yacc_sql.tab.cpp"
    break;

  case 41: /* type: INT_T  */
#line 346 "yacc_sql.y"
                   { (yyval.number)=INTS; }
#line 1623 "yacc_sql.tab.cpp"
    break;

  case 42: /* type: STRING_T  */
#line 347 "yacc_sql.y"
                   { (yyval.number)=CHARS; }
#line 1629 "yacc_sql.tab.cpp"
    break;

  case 43: /* type: FLOAT_T  */
#line 348 "yacc_sql.y"
                   { (yyval.number)=FLOATS; }
#line 1635 "yacc_sql.tab.cpp"
    break;

  case 44: /* type: DATE_T  */
#line 349 "yacc_sql.y"
                   { (yyval.number)=DATES; }
#line 1641 "yacc_sql.tab.cpp"
    break;

  case 45: /* type: TEXT_T  */
#line 350 "yacc_sql.y"
             { (yyval.number)=ATTR_TEXT; }
#line 1647 "yacc_sql.tab.cpp"
    break;

  case 46: /* is_nullable: %empty  */
#line 354 "yacc_sql.y"
                    { (yyval.number) = 0; }
#line 1653 "yacc_sql.tab.cpp"
    break;

  case 47: /* is_nullable: NOT NULL_T  */
#line 355 "yacc_sql.y"
                    { (yyval.number) = 0; }
#line 1659 "yacc_sql.tab.cpp"
    break;

  case 48: /* is_nullable: NULLABLE  */
#line 356 "yacc_sql.y"
                    { (yyval.number) = 1; }
#line 1665 "yacc_sql.tab.cpp"
    break;

  case 49: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 360 "yacc_sql.y"
                                                         {
		CONTEXT->ssql->flag=SCF_INSERT;
		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
	}
#line 1674 "yacc_sql.tab.cpp"
    break;

  case 51: /* tuple_list: COMMA tuple tuple_list  */
#line 368 "yacc_sql.y"
        {	/* do nothing here */	}
#line 1680 "yacc_sql.tab.cpp"
    break;

  case 52: /* tuple: LBRACE value value_list RBRACE  */
#line 371 "yacc_sql.y"
                                       {
		// 由于tuple这种语法[形如(v1, v2, ..., vn)]只在insert中使用
		insert_tuple_init(&CONTEXT->ssql->sstr.insertion, TOP->values, TOP->value_length);
		// 清空CONTEXT临时变量
		TOP->value_length = 0;
	}
#line 1691 "yacc_sql.tab.cpp"
    break;

  case 54: /* value_list: COMMA value value_list  */
#line 380 "yacc_sql.y"
                              {}
#line 1697 "yacc_sql.tab.cpp"
    break;

  case 55: /* value: NUMBER  */
#line 383 "yacc_sql.y"
          {	
  		value_init_integer(&TOP->values[TOP->value_length++], (yyvsp[0].number));
	}
#line 1705 "yacc_sql.tab.cpp"
    break;

  case 56: /* value: FLOAT  */
#line 386 "yacc_sql.y"
           {
  		value_init_float(&TOP->values[TOP->value_length++], (yyvsp[0].floats));
	}
#line 1713 "yacc_sql.tab.cpp"
    break;

  case 57: /* value: SSS  */
#line 389 "yacc_sql.y"
          {
  		value_init_string(&TOP->values[TOP->value_length++], (yyvsp[0].string));
	}
#line 1721 "yacc_sql.tab.cpp"
    break;

  case 58: /* value: DATE  */
#line 392 "yacc_sql.y"
               {
		int year = 0, month = 0, day = 0;
		if (sscanf((yyvsp[0].string), "%d-%d-%d", &year, &month, &day) != -1) {
			// check date
			if (!check_date(year, month, day)) {
				CONTEXT->ssql->sstr.errors = "invalid day num";
				yyerror(scanner, (yyvsp[0].string));
				YYERROR;
			}
			struct tm t;
			memset(&t, 0, sizeof(struct tm));
			t.tm_year = year - 1900, t.tm_mon = month - 1, t.tm_mday = day;
			t.tm_hour = 12;		// 防止0点有一天的换算偏差
			value_init_date(&TOP->values[TOP->value_length++], mktime(&t));
		}
	}
#line 1742 "yacc_sql.tab.cpp"
    break;

  case 59: /* value: NULL_T  */
#line 408 "yacc_sql.y"
                 {
		value_init_null(&TOP->values[TOP->value_length++]);
	}
#line 1750 "yacc_sql.tab.cpp"
    break;

  case 60: /* delete: DELETE FROM ID where SEMICOLON  */
#line 414 "yacc_sql.y"
                                   {
		CONTEXT->ssql->flag = SCF_DELETE;//"delete";
		deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
		deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, TOP->conditions, TOP->condition_length);
		
		// CONTEXT临时变量清零
		TOP->condition_length = 0;	
    }
#line 1763 "yacc_sql.tab.cpp"
    break;

  case 61: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 424 "yacc_sql.y"
                                              {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		Value *value = &TOP->values[0];
		updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, TOP->conditions, TOP->condition_length);
		
		// CONTEXT临时变量清零
		TOP->condition_length = 0;
	}
#line 1776 "yacc_sql.tab.cpp"
    break;

  case 62: /* selects: select SEMICOLON  */
#line 434 "yacc_sql.y"
                     {
		CONTEXT->ssql->flag = SCF_SELECT; //"select";
	}
#line 1784 "yacc_sql.tab.cpp"
    break;

  case 63: /* select: SELECT start_select select_expr select_expr_list FROM table_ref table_ref_list where group order  */
#line 439 "yacc_sql.y"
        {
		// 1. append select_expr $3
		selects_append_expr(&TOP->ssql->sstr.selection, (yyvsp[-7].sexpr));

		// 2. append table_ref $6
		selects_append_relation(&TOP->ssql->sstr.selection, (yyvsp[-4].ref));

		// 3. append condtion_list(可选项，可能为空)
		selects_append_conditions(&TOP->ssql->sstr.selection, TOP->conditions, TOP->condition_length);

		// 4. append group_list(可选项，可能为空)

		// 5. append order_list(可选项，可能为空)
		
		TOP->ssql->sstr.selection.context = new RelationTable();
		//临时变量清零
		TOP->condition_length=0;
		TOP->value_length = 0;

		(yyval.select) = &TOP->ssql->sstr.selection;
	}
#line 1810 "yacc_sql.tab.cpp"
    break;

  case 64: /* start_select: %empty  */
#line 462 "yacc_sql.y"
              {
		PUSH;
		if (TOP->ssql == NULL) {
			TOP->ssql = (Query *)malloc(sizeof(Query));
		}
	}
#line 1821 "yacc_sql.tab.cpp"
    break;

  case 66: /* select_expr_list: COMMA select_expr select_expr_list  */
#line 471 "yacc_sql.y"
                                             {
		// append select_expr $2
		selects_append_expr(&TOP->ssql->sstr.selection, (yyvsp[-1].sexpr));
	}
#line 1830 "yacc_sql.tab.cpp"
    break;

  case 67: /* select_expr: select_arith_expr  */
#line 478 "yacc_sql.y"
                          { (yyval.sexpr) = (yyvsp[0].sexpr); }
#line 1836 "yacc_sql.tab.cpp"
    break;

  case 68: /* select_expr: select_func  */
#line 479 "yacc_sql.y"
                      { (yyval.sexpr) = (yyvsp[0].sexpr); }
#line 1842 "yacc_sql.tab.cpp"
    break;

  case 69: /* select_expr: STAR  */
#line 480 "yacc_sql.y"
               { 
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, NULL, "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), attr);
	}
#line 1853 "yacc_sql.tab.cpp"
    break;

  case 70: /* select_expr: ID DOT STAR  */
#line 486 "yacc_sql.y"
                      {
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, (yyvsp[-2].string), "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), attr);
	}
#line 1864 "yacc_sql.tab.cpp"
    break;

  case 71: /* select_arith_expr: select_arith_expr ADD_OP select_arith_expr  */
#line 499 "yacc_sql.y"
                                                   {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), ADD);
	}
#line 1873 "yacc_sql.tab.cpp"
    break;

  case 72: /* select_arith_expr: select_arith_expr SUB_OP select_arith_expr  */
#line 503 "yacc_sql.y"
                                                     {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), SUB);
	}
#line 1882 "yacc_sql.tab.cpp"
    break;

  case 73: /* select_arith_expr: select_arith_expr STAR select_arith_expr  */
#line 507 "yacc_sql.y"
                                                   {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), MUL);
	}
#line 1891 "yacc_sql.tab.cpp"
    break;

  case 74: /* select_arith_expr: select_arith_expr DIV_OP select_arith_expr  */
#line 511 "yacc_sql.y"
                                                     {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), DIV);
	}
#line 1900 "yacc_sql.tab.cpp"
    break;

  case 75: /* select_arith_expr: col  */
#line 515 "yacc_sql.y"
              {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), (yyvsp[0].attr));
	}
#line 1909 "yacc_sql.tab.cpp"
    break;

  case 76: /* select_arith_expr: value  */
#line 519 "yacc_sql.y"
                { 
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_value_init((yyval.sexpr), &TOP->values[TOP->value_length - 1]);	

		// 释放临时变量
		TOP->value_length --;
	}
#line 1921 "yacc_sql.tab.cpp"
    break;

  case 77: /* select_arith_expr: LBRACE select_arith_expr RBRACE  */
#line 526 "yacc_sql.y"
                                          {
		(yyval.sexpr) = (yyvsp[-1].sexpr);
	}
#line 1929 "yacc_sql.tab.cpp"
    break;

  case 78: /* select_func: aggregate_func LBRACE col RBRACE  */
#line 533 "yacc_sql.y"
                                         {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		FuncName func = static_cast<FuncName>((yyvsp[-3].number));
		aggregate_function_init((yyval.sexpr), func, (yyvsp[-1].attr));
	}
#line 1939 "yacc_sql.tab.cpp"
    break;

  case 79: /* select_func: aggregate_func LBRACE STAR RBRACE  */
#line 538 "yacc_sql.y"
                                            {
		FuncName func = static_cast<FuncName>((yyvsp[-3].number));
		if (func != COUNT_FUNC) {
			CONTEXT->ssql->sstr.errors = "Invalid args of aggregate function";
			YYERROR;
		}
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, NULL, "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		aggregate_function_init((yyval.sexpr), func, attr);
	}
#line 1955 "yacc_sql.tab.cpp"
    break;

  case 80: /* select_func: aggregate_func LBRACE ID DOT STAR RBRACE  */
#line 549 "yacc_sql.y"
                                                   {
		FuncName func = static_cast<FuncName>((yyvsp[-5].number));
		if (func != COUNT_FUNC) {
			CONTEXT->ssql->sstr.errors = "Invalid args of aggregate function";
			YYERROR;
		}
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, (yyvsp[-3].string), "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		aggregate_function_init((yyval.sexpr), func, attr);
	}
#line 1971 "yacc_sql.tab.cpp"
    break;

  case 81: /* aggregate_func: MAX_F  */
#line 563 "yacc_sql.y"
                  { (yyval.number) = MAX_FUNC;   }
#line 1977 "yacc_sql.tab.cpp"
    break;

  case 82: /* aggregate_func: MIN_F  */
#line 564 "yacc_sql.y"
                  { (yyval.number) = MIN_FUNC;   }
#line 1983 "yacc_sql.tab.cpp"
    break;

  case 83: /* aggregate_func: COUNT_F  */
#line 565 "yacc_sql.y"
                  { (yyval.number) = COUNT_FUNC; }
#line 1989 "yacc_sql.tab.cpp"
    break;

  case 84: /* aggregate_func: AVG_F  */
#line 566 "yacc_sql.y"
                  { (yyval.number) = AVG_FUNC;   }
#line 1995 "yacc_sql.tab.cpp"
    break;

  case 85: /* col: ID  */
#line 570 "yacc_sql.y"
           {
		(yyval.attr) = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init((yyval.attr), NULL, (yyvsp[0].string));
	}
#line 2004 "yacc_sql.tab.cpp"
    break;

  case 86: /* col: ID DOT ID  */
#line 574 "yacc_sql.y"
                    {
		(yyval.attr) = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init((yyval.attr), (yyvsp[-2].string), (yyvsp[0].string));
	}
#line 2013 "yacc_sql.tab.cpp"
    break;

  case 88: /* table_ref_list: COMMA table_ref table_ref_list  */
#line 583 "yacc_sql.y"
                                     {	
		selects_append_relation(&TOP->ssql->sstr.selection, (yyvsp[-1].ref));
	}
#line 2021 "yacc_sql.tab.cpp"
    break;

  case 89: /* table_ref: ID  */
#line 589 "yacc_sql.y"
           { 
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 0, (yyvsp[0].string), NULL, NULL, 0); 
		(yyval.ref) = ref;
	}
#line 2031 "yacc_sql.tab.cpp"
    break;

  case 90: /* table_ref: join_table  */
#line 594 "yacc_sql.y"
                     { (yyval.ref) = (yyvsp[0].ref); }
#line 2037 "yacc_sql.tab.cpp"
    break;

  case 91: /* join_table: table_ref INNER JOIN ID join_condition  */
#line 598 "yacc_sql.y"
                                               {
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 1, (yyvsp[-1].string), (yyvsp[-4].ref), TOP->conditions, TOP->condition_length);
		(yyval.ref) = ref;
		// 临时变量清零
		TOP->condition_length = 0;
	}
#line 2049 "yacc_sql.tab.cpp"
    break;

  case 93: /* join_condition: ON condition condition_list  */
#line 609 "yacc_sql.y"
                                      {}
#line 2055 "yacc_sql.tab.cpp"
    break;

  case 95: /* where: WHERE condition condition_list  */
#line 615 "yacc_sql.y"
                                     {}
#line 2061 "yacc_sql.tab.cpp"
    break;

  case 97: /* condition_list: AND condition condition_list  */
#line 621 "yacc_sql.y"
                                   {}
#line 2067 "yacc_sql.tab.cpp"
    break;

  case 98: /* condition: non_subquery comOp non_subquery  */
#line 625 "yacc_sql.y"
                                        {
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		non_subquery_cond_init(&TOP->conditions[TOP->condition_length++], (yyvsp[-2].cexpr), (yyvsp[0].cexpr), op);
	}
#line 2076 "yacc_sql.tab.cpp"
    break;

  case 99: /* condition: non_subquery comOp subquery  */
#line 629 "yacc_sql.y"
                                      {
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		com_subquery_init(&TOP->conditions[TOP->condition_length++], (yyvsp[-2].cexpr), (yyvsp[0].select), op);
	}
#line 2085 "yacc_sql.tab.cpp"
    break;

  case 100: /* condition: non_subquery membershipOp subquery  */
#line 633 "yacc_sql.y"
                                             {
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		membership_subquery_init(&TOP->conditions[TOP->condition_length++], (yyvsp[-2].cexpr), (yyvsp[0].select), op);
	}
#line 2094 "yacc_sql.tab.cpp"
    break;

  case 101: /* membershipOp: IN  */
#line 640 "yacc_sql.y"
           { (yyval.number) = MEM_IN; }
#line 2100 "yacc_sql.tab.cpp"
    break;

  case 102: /* membershipOp: NOT IN  */
#line 641 "yacc_sql.y"
                 { (yyval.number) = MEM_NOT_IN; }
#line 2106 "yacc_sql.tab.cpp"
    break;

  case 103: /* non_subquery: non_subquery ADD_OP non_subquery  */
#line 644 "yacc_sql.y"
                                         {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), ADD);
	}
#line 2115 "yacc_sql.tab.cpp"
    break;

  case 104: /* non_subquery: non_subquery SUB_OP non_subquery  */
#line 648 "yacc_sql.y"
                                           {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), SUB);
	}
#line 2124 "yacc_sql.tab.cpp"
    break;

  case 105: /* non_subquery: non_subquery STAR non_subquery  */
#line 652 "yacc_sql.y"
                                         {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), MUL);
	}
#line 2133 "yacc_sql.tab.cpp"
    break;

  case 106: /* non_subquery: non_subquery DIV_OP non_subquery  */
#line 656 "yacc_sql.y"
                                           {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), DIV);
	}
#line 2142 "yacc_sql.tab.cpp"
    break;

  case 107: /* non_subquery: col  */
#line 660 "yacc_sql.y"
              {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_attr_init((yyval.cexpr), (yyvsp[0].attr));
	}
#line 2151 "yacc_sql.tab.cpp"
    break;

  case 108: /* non_subquery: value  */
#line 664 "yacc_sql.y"
                {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_value_init((yyval.cexpr), &TOP->values[TOP->value_length - 1]);	

		// 释放临时变量
		TOP->value_length --;
	}
#line 2163 "yacc_sql.tab.cpp"
    break;

  case 109: /* non_subquery: LBRACE non_subquery RBRACE  */
#line 671 "yacc_sql.y"
                                     {
		(yyval.cexpr) = (yyvsp[-1].cexpr);
	}
#line 2171 "yacc_sql.tab.cpp"
    break;

  case 110: /* comOp: EQ  */
#line 677 "yacc_sql.y"
                        { (yyval.number) = EQUAL_TO; }
#line 2177 "yacc_sql.tab.cpp"
    break;

  case 111: /* comOp: LT  */
#line 678 "yacc_sql.y"
                        { (yyval.number) = LESS_THAN; }
#line 2183 "yacc_sql.tab.cpp"
    break;

  case 112: /* comOp: GT  */
#line 679 "yacc_sql.y"
                        { (yyval.number) = GREAT_THAN; }
#line 2189 "yacc_sql.tab.cpp"
    break;

  case 113: /* comOp: LE  */
#line 680 "yacc_sql.y"
                        { (yyval.number) = LESS_EQUAL; }
#line 2195 "yacc_sql.tab.cpp"
    break;

  case 114: /* comOp: GE  */
#line 681 "yacc_sql.y"
                        { (yyval.number) = GREAT_EQUAL; }
#line 2201 "yacc_sql.tab.cpp"
    break;

  case 115: /* comOp: NE  */
#line 682 "yacc_sql.y"
                        { (yyval.number) = NOT_EQUAL; }
#line 2207 "yacc_sql.tab.cpp"
    break;

  case 116: /* comOp: IS  */
#line 683 "yacc_sql.y"
                        { (yyval.number) = OP_IS; }
#line 2213 "yacc_sql.tab.cpp"
    break;

  case 117: /* comOp: IS NOT  */
#line 684 "yacc_sql.y"
                        { (yyval.number) = OP_IS_NOT; }
#line 2219 "yacc_sql.tab.cpp"
    break;

  case 118: /* subquery: LBRACE select RBRACE  */
#line 688 "yacc_sql.y"
                             {
		(yyval.select) = (yyvsp[-1].select);
		POP;
	}
#line 2228 "yacc_sql.tab.cpp"
    break;

  case 120: /* group: GROUP BY col group_list  */
#line 696 "yacc_sql.y"
                                  {
		selects_append_group(&TOP->ssql->sstr.selection, (yyvsp[-1].attr));
	}
#line 2236 "yacc_sql.tab.cpp"
    break;

  case 122: /* group_list: COMMA col group_list  */
#line 703 "yacc_sql.y"
                               {
		selects_append_group(&TOP->ssql->sstr.selection, (yyvsp[-1].attr));
	}
#line 2244 "yacc_sql.tab.cpp"
    break;

  case 124: /* order: ORDER BY order_col order_list  */
#line 711 "yacc_sql.y"
                                        {
		selects_append_order(&TOP->ssql->sstr.selection, (yyvsp[-1].ocol));
	}
#line 2252 "yacc_sql.tab.cpp"
    break;

  case 126: /* order_list: COMMA order_col order_list  */
#line 718 "yacc_sql.y"
                                     {
		selects_append_order(&TOP->ssql->sstr.selection, (yyvsp[-1].ocol));
	}
#line 2260 "yacc_sql.tab.cpp"
    break;

  case 127: /* order_col: col  */
#line 724 "yacc_sql.y"
            {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[0].attr), 1);
	}
#line 2269 "yacc_sql.tab.cpp"
    break;

  case 128: /* order_col: col ASC  */
#line 728 "yacc_sql.y"
                  {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[-1].attr), 1);
	}
#line 2278 "yacc_sql.tab.cpp"
    break;

  case 129: /* order_col: col DESC  */
#line 732 "yacc_sql.y"
                   {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[-1].attr), 0);
	}
#line 2287 "yacc_sql.tab.cpp"
    break;

  case 130: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 740 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2296 "yacc_sql.tab.cpp"
    break;


#line 2300 "yacc_sql.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 745 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	// memset(&context, 0, sizeof(ParserContext));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	INIT(sqls);
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
