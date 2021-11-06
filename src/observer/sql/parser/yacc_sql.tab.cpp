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
  YYSYMBOL_HELP = 33,                      /* HELP  */
  YYSYMBOL_EXIT = 34,                      /* EXIT  */
  YYSYMBOL_IS = 35,                        /* IS  */
  YYSYMBOL_NOT = 36,                       /* NOT  */
  YYSYMBOL_NULL_T = 37,                    /* NULL_T  */
  YYSYMBOL_NULLABLE = 38,                  /* NULLABLE  */
  YYSYMBOL_DOT = 39,                       /* DOT  */
  YYSYMBOL_INTO = 40,                      /* INTO  */
  YYSYMBOL_VALUES = 41,                    /* VALUES  */
  YYSYMBOL_FROM = 42,                      /* FROM  */
  YYSYMBOL_WHERE = 43,                     /* WHERE  */
  YYSYMBOL_AND = 44,                       /* AND  */
  YYSYMBOL_SET = 45,                       /* SET  */
  YYSYMBOL_ON = 46,                        /* ON  */
  YYSYMBOL_LOAD = 47,                      /* LOAD  */
  YYSYMBOL_DATA = 48,                      /* DATA  */
  YYSYMBOL_INFILE = 49,                    /* INFILE  */
  YYSYMBOL_GROUP = 50,                     /* GROUP  */
  YYSYMBOL_ORDER = 51,                     /* ORDER  */
  YYSYMBOL_BY = 52,                        /* BY  */
  YYSYMBOL_ASC = 53,                       /* ASC  */
  YYSYMBOL_ADD_OP = 54,                    /* ADD_OP  */
  YYSYMBOL_SUB_OP = 55,                    /* SUB_OP  */
  YYSYMBOL_DIV_OP = 56,                    /* DIV_OP  */
  YYSYMBOL_EQ = 57,                        /* EQ  */
  YYSYMBOL_LT = 58,                        /* LT  */
  YYSYMBOL_GT = 59,                        /* GT  */
  YYSYMBOL_LE = 60,                        /* LE  */
  YYSYMBOL_GE = 61,                        /* GE  */
  YYSYMBOL_NE = 62,                        /* NE  */
  YYSYMBOL_IN = 63,                        /* IN  */
  YYSYMBOL_NUMBER = 64,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 65,                     /* FLOAT  */
  YYSYMBOL_ID = 66,                        /* ID  */
  YYSYMBOL_PATH = 67,                      /* PATH  */
  YYSYMBOL_SSS = 68,                       /* SSS  */
  YYSYMBOL_DATE = 69,                      /* DATE  */
  YYSYMBOL_STAR = 70,                      /* STAR  */
  YYSYMBOL_STRING_V = 71,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 72,                  /* $accept  */
  YYSYMBOL_commands = 73,                  /* commands  */
  YYSYMBOL_command = 74,                   /* command  */
  YYSYMBOL_exit = 75,                      /* exit  */
  YYSYMBOL_help = 76,                      /* help  */
  YYSYMBOL_sync = 77,                      /* sync  */
  YYSYMBOL_begin = 78,                     /* begin  */
  YYSYMBOL_commit = 79,                    /* commit  */
  YYSYMBOL_rollback = 80,                  /* rollback  */
  YYSYMBOL_drop_table = 81,                /* drop_table  */
  YYSYMBOL_show_tables = 82,               /* show_tables  */
  YYSYMBOL_desc_table = 83,                /* desc_table  */
  YYSYMBOL_create_index = 84,              /* create_index  */
  YYSYMBOL_attr_list = 85,                 /* attr_list  */
  YYSYMBOL_drop_index = 86,                /* drop_index  */
  YYSYMBOL_create_table = 87,              /* create_table  */
  YYSYMBOL_attr_def_list = 88,             /* attr_def_list  */
  YYSYMBOL_attr_def = 89,                  /* attr_def  */
  YYSYMBOL_number = 90,                    /* number  */
  YYSYMBOL_type = 91,                      /* type  */
  YYSYMBOL_is_nullable = 92,               /* is_nullable  */
  YYSYMBOL_insert = 93,                    /* insert  */
  YYSYMBOL_tuple_list = 94,                /* tuple_list  */
  YYSYMBOL_tuple = 95,                     /* tuple  */
  YYSYMBOL_value_list = 96,                /* value_list  */
  YYSYMBOL_value = 97,                     /* value  */
  YYSYMBOL_delete = 98,                    /* delete  */
  YYSYMBOL_update = 99,                    /* update  */
  YYSYMBOL_selects = 100,                  /* selects  */
  YYSYMBOL_select = 101,                   /* select  */
  YYSYMBOL_start_select = 102,             /* start_select  */
  YYSYMBOL_select_expr_list = 103,         /* select_expr_list  */
  YYSYMBOL_select_expr = 104,              /* select_expr  */
  YYSYMBOL_select_arith_expr = 105,        /* select_arith_expr  */
  YYSYMBOL_select_func = 106,              /* select_func  */
  YYSYMBOL_aggregate_func = 107,           /* aggregate_func  */
  YYSYMBOL_col = 108,                      /* col  */
  YYSYMBOL_table_ref_list = 109,           /* table_ref_list  */
  YYSYMBOL_table_ref = 110,                /* table_ref  */
  YYSYMBOL_join_table = 111,               /* join_table  */
  YYSYMBOL_join_condition = 112,           /* join_condition  */
  YYSYMBOL_where = 113,                    /* where  */
  YYSYMBOL_condition_list = 114,           /* condition_list  */
  YYSYMBOL_condition = 115,                /* condition  */
  YYSYMBOL_membershipOp = 116,             /* membershipOp  */
  YYSYMBOL_non_subquery = 117,             /* non_subquery  */
  YYSYMBOL_comOp = 118,                    /* comOp  */
  YYSYMBOL_subquery = 119,                 /* subquery  */
  YYSYMBOL_group = 120,                    /* group  */
  YYSYMBOL_group_list = 121,               /* group_list  */
  YYSYMBOL_order = 122,                    /* order  */
  YYSYMBOL_order_list = 123,               /* order_list  */
  YYSYMBOL_order_col = 124,                /* order_col  */
  YYSYMBOL_load_data = 125                 /* load_data  */
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
#define YYLAST   269

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  257

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   326


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
      65,    66,    67,    68,    69,    70,    71
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   208,   208,   210,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   234,   239,   244,   250,   256,   262,   268,   274,   280,
     287,   293,   301,   303,   308,   315,   320,   322,   326,   332,
     341,   345,   346,   347,   348,   352,   353,   354,   358,   363,
     365,   369,   376,   378,   381,   384,   387,   390,   406,   412,
     422,   432,   436,   460,   467,   469,   476,   477,   478,   484,
     497,   501,   505,   509,   513,   517,   524,   531,   536,   547,
     561,   562,   563,   564,   568,   572,   579,   581,   587,   592,
     596,   605,   607,   611,   613,   617,   619,   623,   627,   631,
     638,   639,   642,   646,   650,   654,   658,   662,   669,   675,
     676,   677,   678,   679,   680,   681,   682,   686,   692,   694,
     699,   701,   707,   709,   714,   716,   722,   726,   730,   737
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
  "HELP", "EXIT", "IS", "NOT", "NULL_T", "NULLABLE", "DOT", "INTO",
  "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE",
  "GROUP", "ORDER", "BY", "ASC", "ADD_OP", "SUB_OP", "DIV_OP", "EQ", "LT",
  "GT", "LE", "GE", "NE", "IN", "NUMBER", "FLOAT", "ID", "PATH", "SSS",
  "DATE", "STAR", "STRING_V", "$accept", "commands", "command", "exit",
  "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "desc_table", "create_index", "attr_list", "drop_index",
  "create_table", "attr_def_list", "attr_def", "number", "type",
  "is_nullable", "insert", "tuple_list", "tuple", "value_list", "value",
  "delete", "update", "selects", "select", "start_select",
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

#define YYPACT_NINF (-178)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -178,   103,  -178,    90,    74,  -178,   -49,     9,    28,     3,
      10,     5,    79,    80,    91,    93,   107,    58,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,   113,  -178,    51,    62,   119,
      68,    69,     4,   135,   136,  -178,    83,    85,   100,  -178,
    -178,  -178,  -178,  -178,   116,  -178,   117,   106,    96,   163,
     164,  -178,  -178,  -178,  -178,    78,  -178,  -178,  -178,   132,
    -178,  -178,  -178,  -178,   166,   -41,  -178,   165,  -178,  -178,
    -178,   148,   149,   127,   126,   130,   131,   152,  -178,  -178,
     160,    -6,   -33,     4,   158,    78,    78,    78,    78,   -28,
     179,    95,   201,   150,   168,   155,   180,   183,   143,   145,
    -178,  -178,  -178,   166,   146,   -51,   -51,  -178,  -178,   174,
     190,   191,    89,   192,    95,  -178,  -178,   172,   120,  -178,
      89,   206,  -178,  -178,  -178,  -178,    53,   130,   195,   154,
     198,  -178,  -178,    -4,  -178,    15,  -178,  -178,   197,   179,
     220,    23,    95,  -178,   188,   162,    95,    95,    95,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,    95,   203,   104,   149,
     161,   167,   193,  -178,  -178,   180,   225,   204,   169,   223,
     146,   149,   209,    89,   210,   192,  -178,  -178,   172,  -178,
    -178,   -50,   -50,  -178,  -178,   221,  -178,    43,   -30,  -178,
     233,   235,  -178,   215,  -178,  -178,  -178,   175,   216,   204,
     176,    -4,   194,  -178,   197,  -178,  -178,  -178,   219,  -178,
    -178,    54,   204,   242,   222,   202,  -178,   199,   196,  -178,
    -178,  -178,  -178,  -178,   246,    95,  -178,   184,   200,  -178,
    -178,   172,   228,   184,  -178,   184,  -178,   -14,   229,   228,
    -178,  -178,   184,  -178,  -178,   229,  -178
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,     0,    18,     0,     0,     0,
       0,     0,     0,     0,     0,    23,     0,     0,     0,    24,
      25,    26,    22,    21,     0,    61,     0,     0,     0,     0,
       0,    80,    81,    82,    83,     0,    58,    54,    55,    84,
      56,    57,    68,    75,    64,    66,    67,     0,    74,    29,
      28,     0,    93,     0,     0,     0,     0,     0,    27,    34,
      84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,     0,     0,     0,
      76,    85,    69,    64,     0,    70,    71,    73,    72,    84,
       0,     0,     0,    49,     0,   107,   106,    95,     0,    59,
       0,     0,    41,    42,    44,    43,    45,     0,     0,     0,
       0,    65,    88,    86,    89,     0,    78,    77,    52,     0,
       0,     0,     0,    94,   115,     0,     0,     0,     0,   109,
     110,   111,   112,   113,   114,   100,     0,     0,     0,    93,
       0,     0,     0,    47,    39,    36,     0,    32,     0,     0,
       0,    93,     0,     0,     0,    49,    48,   108,    95,   116,
     101,   102,   103,   105,   104,     0,    99,     0,    97,    98,
       0,     0,    40,     0,    46,    37,    35,     0,     0,    32,
       0,    86,   118,    79,    52,    51,    50,    96,     0,    60,
     129,    45,    32,     0,     0,    91,    87,     0,   122,    53,
     117,    38,    33,    30,     0,     0,    90,     0,     0,    62,
      31,    95,   120,     0,    92,     0,   119,   126,   124,   120,
     128,   127,     0,   123,   121,   124,   125
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -177,  -178,  -178,    81,   118,  -178,  -178,
      36,  -178,    73,   110,    46,   -35,  -178,  -178,  -178,   260,
    -178,   151,   170,     2,  -178,  -178,   -42,    55,    82,  -178,
    -178,  -153,  -176,  -151,  -178,  -122,  -178,    97,  -178,    18,
    -178,    13,    17,  -178
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   208,    29,    30,   138,   106,   203,   136,
     174,    31,   150,   123,   184,   125,    32,    33,    34,   218,
      42,    94,    74,    75,    76,    77,   126,   181,   143,   144,
     236,   102,   153,   127,   167,   128,   168,   196,   228,   246,
     239,   253,   248,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      78,   188,   151,   250,   179,    97,   158,    73,    61,    62,
      63,    64,   217,    95,    96,    97,   200,    43,   110,    98,
     166,   180,    44,    78,   156,   157,   158,    65,   212,    98,
      73,    45,   224,   111,   191,   192,   193,   112,   119,   251,
     166,    66,   120,    46,   194,   232,   198,   187,    95,    96,
      97,    78,    47,    78,    78,    78,    78,   121,    73,     5,
      73,    73,    73,    73,    98,   244,   124,    91,    67,    68,
      69,    48,    70,    71,    72,   151,   171,   156,   157,   158,
      66,   111,    49,    50,   241,   182,    40,   148,    41,   172,
     172,   173,   173,   166,    51,   169,    52,   115,   116,   117,
     118,    65,    37,     2,    38,    39,    54,    67,    68,    90,
      53,    70,    71,     3,     4,    66,    55,    56,   124,     5,
       6,     7,     8,     9,    10,    11,    66,   197,    57,    12,
      13,    14,    66,    58,    59,    60,    15,    16,    79,    80,
      85,    66,    67,    68,    90,    83,    70,    71,   214,    81,
      17,    82,    86,    67,    68,   154,   155,    70,    71,    67,
      68,    90,    87,    70,    71,    84,    88,    89,    67,    68,
      90,    92,    70,    71,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   132,   133,   134,   135,    99,   100,
     166,    93,   101,   103,   104,   242,   105,   107,   108,   109,
     114,   247,   122,   249,   129,   137,   139,   130,   131,   140,
     247,   111,   142,   145,   146,   147,   152,   149,   170,   176,
     177,   178,   183,   186,   189,   190,   195,   201,   206,   207,
     204,   202,   210,   213,   215,   209,   219,     5,   220,   221,
     223,   222,   225,   230,   227,   233,   234,   238,   235,   240,
      90,   237,   243,   245,   252,   175,   205,   231,   216,   185,
     229,    35,   211,   113,   141,   199,   226,   254,   256,   255
};

static const yytype_uint8 yycheck[] =
{
      42,   152,   124,    17,     8,    56,    56,    42,     4,     5,
       6,     7,   188,    54,    55,    56,   169,    66,    24,    70,
      70,    25,    13,    65,    54,    55,    56,    23,   181,    70,
      65,     3,   209,    66,   156,   157,   158,    70,    66,    53,
      70,    37,    70,    40,   166,   222,   168,    24,    54,    55,
      56,    93,    42,    95,    96,    97,    98,    99,    93,    16,
      95,    96,    97,    98,    70,   241,    23,    65,    64,    65,
      66,    66,    68,    69,    70,   197,    23,    54,    55,    56,
      37,    66,     3,     3,   235,    70,    12,   122,    14,    36,
      36,    38,    38,    70,     3,   130,     3,    95,    96,    97,
      98,    23,    12,     0,    14,    15,    48,    64,    65,    66,
       3,    68,    69,    10,    11,    37,     3,    66,    23,    16,
      17,    18,    19,    20,    21,    22,    37,    23,    66,    26,
      27,    28,    37,    14,    66,    66,    33,    34,     3,     3,
      23,    37,    64,    65,    66,    45,    68,    69,   183,    66,
      47,    66,    46,    64,    65,    35,    36,    68,    69,    64,
      65,    66,    66,    68,    69,    49,     3,     3,    64,    65,
      66,    39,    68,    69,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    29,    30,    31,    32,    23,    41,
      70,    25,    43,    66,    68,   237,    66,    66,    46,    39,
      42,   243,    23,   245,     3,    25,    23,    57,    40,    66,
     252,    66,    66,    39,    24,    24,    44,    25,    12,    24,
      66,    23,    25,     3,    36,    63,    23,    66,     3,    25,
      37,    64,     9,    24,    24,    66,     3,    16,     3,    24,
      24,    66,    66,    24,    50,     3,    24,    51,    46,     3,
      66,    52,    52,    25,    25,   137,   175,   221,   185,   149,
     214,     1,   180,    93,   113,   168,   211,   249,   255,   252
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    73,     0,    10,    11,    16,    17,    18,    19,    20,
      21,    22,    26,    27,    28,    33,    34,    47,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    86,
      87,    93,    98,    99,   100,   101,   125,    12,    14,    15,
      12,    14,   102,    66,    13,     3,    40,    42,    66,     3,
       3,     3,     3,     3,    48,     3,    66,    66,    14,    66,
      66,     4,     5,     6,     7,    23,    37,    64,    65,    66,
      68,    69,    70,    97,   104,   105,   106,   107,   108,     3,
       3,    66,    66,    45,    49,    23,    46,    66,     3,     3,
      66,   105,    39,    25,   103,    54,    55,    56,    70,    23,
      41,    43,   113,    66,    68,    66,    89,    66,    46,    39,
      24,    66,    70,   104,    42,   105,   105,   105,   105,    66,
      70,   108,    23,    95,    23,    97,   108,   115,   117,     3,
      57,    40,    29,    30,    31,    32,    91,    25,    88,    23,
      66,   103,    66,   110,   111,    39,    24,    24,    97,    25,
      94,   117,    44,   114,    35,    36,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    70,   116,   118,    97,
      12,    23,    36,    38,    92,    89,    24,    66,    23,     8,
      25,   109,    70,    25,    96,    95,     3,    24,   115,    36,
      63,   117,   117,   117,   117,    23,   119,    23,   117,   119,
     113,    66,    64,    90,    37,    88,     3,    25,    85,    66,
       9,   110,   113,    24,    97,    24,    94,   114,   101,     3,
       3,    24,    66,    24,    85,    66,   109,    50,   120,    96,
      24,    92,    85,     3,    24,    46,   112,    52,    51,   122,
       3,   115,   108,    52,   114,    25,   121,   108,   124,   108,
      17,    53,    25,   123,   121,   124,   123
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    72,    73,    73,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    84,    85,    85,    86,    87,    88,    88,    89,    89,
      90,    91,    91,    91,    91,    92,    92,    92,    93,    94,
      94,    95,    96,    96,    97,    97,    97,    97,    97,    98,
      99,   100,   101,   102,   103,   103,   104,   104,   104,   104,
     105,   105,   105,   105,   105,   105,   105,   106,   106,   106,
     107,   107,   107,   107,   108,   108,   109,   109,   110,   110,
     111,   112,   112,   113,   113,   114,   114,   115,   115,   115,
     116,   116,   117,   117,   117,   117,   117,   117,   117,   118,
     118,   118,   118,   118,   118,   118,   118,   119,   120,   120,
     121,   121,   122,   122,   123,   123,   124,   124,   124,   125
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    11,     0,     3,     4,     8,     0,     3,     6,     3,
       1,     1,     1,     1,     1,     0,     2,     1,     7,     0,
       3,     4,     0,     3,     1,     1,     1,     1,     1,     5,
       8,     2,    10,     0,     0,     3,     1,     1,     1,     3,
       3,     3,     3,     3,     1,     1,     3,     4,     4,     6,
       1,     1,     1,     1,     1,     3,     0,     3,     1,     1,
       5,     0,     3,     0,     3,     0,     3,     3,     3,     3,
       1,     2,     3,     3,     3,     3,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     0,     4,
       0,     3,     0,     4,     0,     3,     1,     2,     2,     8
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
#line 234 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1465 "yacc_sql.tab.cpp"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 239 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1473 "yacc_sql.tab.cpp"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 244 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1481 "yacc_sql.tab.cpp"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 250 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1489 "yacc_sql.tab.cpp"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 256 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1497 "yacc_sql.tab.cpp"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 262 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1505 "yacc_sql.tab.cpp"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 268 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1514 "yacc_sql.tab.cpp"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 274 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1522 "yacc_sql.tab.cpp"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 280 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1531 "yacc_sql.tab.cpp"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID attr_list RBRACE SEMICOLON  */
#line 288 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
		}
#line 1541 "yacc_sql.tab.cpp"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID attr_list RBRACE SEMICOLON  */
#line 294 "yacc_sql.y"
                {	// 由于只用支持UNIQUE，采用最简单写法
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_unique_index";
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
		}
#line 1551 "yacc_sql.tab.cpp"
    break;

  case 33: /* attr_list: COMMA ID attr_list  */
#line 303 "yacc_sql.y"
                             {
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1559 "yacc_sql.tab.cpp"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 308 "yacc_sql.y"
                             {
		CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
		drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
	}
#line 1568 "yacc_sql.tab.cpp"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 315 "yacc_sql.y"
                                                                   {
		CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
		create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
	}
#line 1577 "yacc_sql.tab.cpp"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 322 "yacc_sql.y"
                                   {    }
#line 1583 "yacc_sql.tab.cpp"
    break;

  case 38: /* attr_def: ID type LBRACE number RBRACE is_nullable  */
#line 326 "yacc_sql.y"
                                            {
		AttrInfo attribute;
		AttrType type = static_cast<AttrType>((yyvsp[-4].number));
		attr_info_init(&attribute, (yyvsp[-5].string), type, (yyvsp[-2].number), (yyvsp[0].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
#line 1594 "yacc_sql.tab.cpp"
    break;

  case 39: /* attr_def: ID type is_nullable  */
#line 332 "yacc_sql.y"
                         {
		AttrInfo attribute;
		AttrType type = static_cast<AttrType>((yyvsp[-1].number));
		attr_info_init(&attribute, (yyvsp[-2].string), type, type == DATES ? 8 : 4, (yyvsp[0].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
#line 1605 "yacc_sql.tab.cpp"
    break;

  case 40: /* number: NUMBER  */
#line 341 "yacc_sql.y"
               {(yyval.number) = (yyvsp[0].number);}
#line 1611 "yacc_sql.tab.cpp"
    break;

  case 41: /* type: INT_T  */
#line 345 "yacc_sql.y"
                   { (yyval.number)=INTS; }
#line 1617 "yacc_sql.tab.cpp"
    break;

  case 42: /* type: STRING_T  */
#line 346 "yacc_sql.y"
                   { (yyval.number)=CHARS; }
#line 1623 "yacc_sql.tab.cpp"
    break;

  case 43: /* type: FLOAT_T  */
#line 347 "yacc_sql.y"
                   { (yyval.number)=FLOATS; }
#line 1629 "yacc_sql.tab.cpp"
    break;

  case 44: /* type: DATE_T  */
#line 348 "yacc_sql.y"
                   { (yyval.number)=DATES; }
#line 1635 "yacc_sql.tab.cpp"
    break;

  case 45: /* is_nullable: %empty  */
#line 352 "yacc_sql.y"
                    { (yyval.number) = 0; }
#line 1641 "yacc_sql.tab.cpp"
    break;

  case 46: /* is_nullable: NOT NULL_T  */
#line 353 "yacc_sql.y"
                    { (yyval.number) = 0; }
#line 1647 "yacc_sql.tab.cpp"
    break;

  case 47: /* is_nullable: NULLABLE  */
#line 354 "yacc_sql.y"
                    { (yyval.number) = 1; }
#line 1653 "yacc_sql.tab.cpp"
    break;

  case 48: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 358 "yacc_sql.y"
                                                         {
		CONTEXT->ssql->flag=SCF_INSERT;
		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
	}
#line 1662 "yacc_sql.tab.cpp"
    break;

  case 50: /* tuple_list: COMMA tuple tuple_list  */
#line 366 "yacc_sql.y"
        {	/* do nothing here */	}
#line 1668 "yacc_sql.tab.cpp"
    break;

  case 51: /* tuple: LBRACE value value_list RBRACE  */
#line 369 "yacc_sql.y"
                                       {
		// 由于tuple这种语法[形如(v1, v2, ..., vn)]只在insert中使用
		insert_tuple_init(&CONTEXT->ssql->sstr.insertion, TOP->values, TOP->value_length);
		// 清空CONTEXT临时变量
		TOP->value_length = 0;
	}
#line 1679 "yacc_sql.tab.cpp"
    break;

  case 53: /* value_list: COMMA value value_list  */
#line 378 "yacc_sql.y"
                              {}
#line 1685 "yacc_sql.tab.cpp"
    break;

  case 54: /* value: NUMBER  */
#line 381 "yacc_sql.y"
          {	
  		value_init_integer(&TOP->values[TOP->value_length++], (yyvsp[0].number));
	}
#line 1693 "yacc_sql.tab.cpp"
    break;

  case 55: /* value: FLOAT  */
#line 384 "yacc_sql.y"
           {
  		value_init_float(&TOP->values[TOP->value_length++], (yyvsp[0].floats));
	}
#line 1701 "yacc_sql.tab.cpp"
    break;

  case 56: /* value: SSS  */
#line 387 "yacc_sql.y"
          {
  		value_init_string(&TOP->values[TOP->value_length++], (yyvsp[0].string));
	}
#line 1709 "yacc_sql.tab.cpp"
    break;

  case 57: /* value: DATE  */
#line 390 "yacc_sql.y"
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
#line 1730 "yacc_sql.tab.cpp"
    break;

  case 58: /* value: NULL_T  */
#line 406 "yacc_sql.y"
                 {
		value_init_null(&TOP->values[TOP->value_length++]);
	}
#line 1738 "yacc_sql.tab.cpp"
    break;

  case 59: /* delete: DELETE FROM ID where SEMICOLON  */
#line 412 "yacc_sql.y"
                                   {
		CONTEXT->ssql->flag = SCF_DELETE;//"delete";
		deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
		deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, TOP->conditions, TOP->condition_length);
		
		// CONTEXT临时变量清零
		TOP->condition_length = 0;	
    }
#line 1751 "yacc_sql.tab.cpp"
    break;

  case 60: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 422 "yacc_sql.y"
                                              {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		Value *value = &TOP->values[0];
		updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, TOP->conditions, TOP->condition_length);
		
		// CONTEXT临时变量清零
		TOP->condition_length = 0;
	}
#line 1764 "yacc_sql.tab.cpp"
    break;

  case 61: /* selects: select SEMICOLON  */
#line 432 "yacc_sql.y"
                     {
		CONTEXT->ssql->flag = SCF_SELECT; //"select";
	}
#line 1772 "yacc_sql.tab.cpp"
    break;

  case 62: /* select: SELECT start_select select_expr select_expr_list FROM table_ref table_ref_list where group order  */
#line 437 "yacc_sql.y"
        {
		// 1. append select_expr $2
		selects_append_expr(&TOP->ssql->sstr.selection, (yyvsp[-7].sexpr));

		// 2. append table_ref $5
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
#line 1798 "yacc_sql.tab.cpp"
    break;

  case 63: /* start_select: %empty  */
#line 460 "yacc_sql.y"
              {
		PUSH;
		if (TOP->ssql == NULL) {
			TOP->ssql = (Query *)malloc(sizeof(Query));
		}
	}
#line 1809 "yacc_sql.tab.cpp"
    break;

  case 65: /* select_expr_list: COMMA select_expr select_expr_list  */
#line 469 "yacc_sql.y"
                                             {
		// append select_expr $2
		selects_append_expr(&TOP->ssql->sstr.selection, (yyvsp[-1].sexpr));
	}
#line 1818 "yacc_sql.tab.cpp"
    break;

  case 66: /* select_expr: select_arith_expr  */
#line 476 "yacc_sql.y"
                          { (yyval.sexpr) = (yyvsp[0].sexpr); }
#line 1824 "yacc_sql.tab.cpp"
    break;

  case 67: /* select_expr: select_func  */
#line 477 "yacc_sql.y"
                      { (yyval.sexpr) = (yyvsp[0].sexpr); }
#line 1830 "yacc_sql.tab.cpp"
    break;

  case 68: /* select_expr: STAR  */
#line 478 "yacc_sql.y"
               { 
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, NULL, "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), attr);
	}
#line 1841 "yacc_sql.tab.cpp"
    break;

  case 69: /* select_expr: ID DOT STAR  */
#line 484 "yacc_sql.y"
                      {
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, (yyvsp[-2].string), "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), attr);
	}
#line 1852 "yacc_sql.tab.cpp"
    break;

  case 70: /* select_arith_expr: select_arith_expr ADD_OP select_arith_expr  */
#line 497 "yacc_sql.y"
                                                   {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), ADD);
	}
#line 1861 "yacc_sql.tab.cpp"
    break;

  case 71: /* select_arith_expr: select_arith_expr SUB_OP select_arith_expr  */
#line 501 "yacc_sql.y"
                                                     {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), SUB);
	}
#line 1870 "yacc_sql.tab.cpp"
    break;

  case 72: /* select_arith_expr: select_arith_expr STAR select_arith_expr  */
#line 505 "yacc_sql.y"
                                                   {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), MUL);
	}
#line 1879 "yacc_sql.tab.cpp"
    break;

  case 73: /* select_arith_expr: select_arith_expr DIV_OP select_arith_expr  */
#line 509 "yacc_sql.y"
                                                     {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), DIV);
	}
#line 1888 "yacc_sql.tab.cpp"
    break;

  case 74: /* select_arith_expr: col  */
#line 513 "yacc_sql.y"
              {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), (yyvsp[0].attr));
	}
#line 1897 "yacc_sql.tab.cpp"
    break;

  case 75: /* select_arith_expr: value  */
#line 517 "yacc_sql.y"
                { 
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_value_init((yyval.sexpr), &TOP->values[TOP->value_length - 1]);	

		// 释放临时变量
		TOP->value_length --;
	}
#line 1909 "yacc_sql.tab.cpp"
    break;

  case 76: /* select_arith_expr: LBRACE select_arith_expr RBRACE  */
#line 524 "yacc_sql.y"
                                          {
		(yyval.sexpr) = (yyvsp[-1].sexpr);
	}
#line 1917 "yacc_sql.tab.cpp"
    break;

  case 77: /* select_func: aggregate_func LBRACE col RBRACE  */
#line 531 "yacc_sql.y"
                                         {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		FuncName func = static_cast<FuncName>((yyvsp[-3].number));
		aggregate_function_init((yyval.sexpr), func, (yyvsp[-1].attr));
	}
#line 1927 "yacc_sql.tab.cpp"
    break;

  case 78: /* select_func: aggregate_func LBRACE STAR RBRACE  */
#line 536 "yacc_sql.y"
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
#line 1943 "yacc_sql.tab.cpp"
    break;

  case 79: /* select_func: aggregate_func LBRACE ID DOT STAR RBRACE  */
#line 547 "yacc_sql.y"
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
#line 1959 "yacc_sql.tab.cpp"
    break;

  case 80: /* aggregate_func: MAX_F  */
#line 561 "yacc_sql.y"
                  { (yyval.number) = MAX_FUNC;   }
#line 1965 "yacc_sql.tab.cpp"
    break;

  case 81: /* aggregate_func: MIN_F  */
#line 562 "yacc_sql.y"
                  { (yyval.number) = MIN_FUNC;   }
#line 1971 "yacc_sql.tab.cpp"
    break;

  case 82: /* aggregate_func: COUNT_F  */
#line 563 "yacc_sql.y"
                  { (yyval.number) = COUNT_FUNC; }
#line 1977 "yacc_sql.tab.cpp"
    break;

  case 83: /* aggregate_func: AVG_F  */
#line 564 "yacc_sql.y"
                  { (yyval.number) = AVG_FUNC;   }
#line 1983 "yacc_sql.tab.cpp"
    break;

  case 84: /* col: ID  */
#line 568 "yacc_sql.y"
           {
		(yyval.attr) = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init((yyval.attr), NULL, (yyvsp[0].string));
	}
#line 1992 "yacc_sql.tab.cpp"
    break;

  case 85: /* col: ID DOT ID  */
#line 572 "yacc_sql.y"
                    {
		(yyval.attr) = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init((yyval.attr), (yyvsp[-2].string), (yyvsp[0].string));
	}
#line 2001 "yacc_sql.tab.cpp"
    break;

  case 87: /* table_ref_list: COMMA table_ref table_ref_list  */
#line 581 "yacc_sql.y"
                                     {	
		selects_append_relation(&TOP->ssql->sstr.selection, (yyvsp[-1].ref));
	}
#line 2009 "yacc_sql.tab.cpp"
    break;

  case 88: /* table_ref: ID  */
#line 587 "yacc_sql.y"
           { 
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 0, (yyvsp[0].string), NULL, NULL, 0); 
		(yyval.ref) = ref;
	}
#line 2019 "yacc_sql.tab.cpp"
    break;

  case 89: /* table_ref: join_table  */
#line 592 "yacc_sql.y"
                     { (yyval.ref) = (yyvsp[0].ref); }
#line 2025 "yacc_sql.tab.cpp"
    break;

  case 90: /* join_table: table_ref INNER JOIN ID join_condition  */
#line 596 "yacc_sql.y"
                                               {
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 1, (yyvsp[-1].string), (yyvsp[-4].ref), TOP->conditions, TOP->condition_length);
		(yyval.ref) = ref;
		// 临时变量清零
		TOP->condition_length = 0;
	}
#line 2037 "yacc_sql.tab.cpp"
    break;

  case 92: /* join_condition: ON condition condition_list  */
#line 607 "yacc_sql.y"
                                      {}
#line 2043 "yacc_sql.tab.cpp"
    break;

  case 94: /* where: WHERE condition condition_list  */
#line 613 "yacc_sql.y"
                                     {}
#line 2049 "yacc_sql.tab.cpp"
    break;

  case 96: /* condition_list: AND condition condition_list  */
#line 619 "yacc_sql.y"
                                   {}
#line 2055 "yacc_sql.tab.cpp"
    break;

  case 97: /* condition: non_subquery comOp non_subquery  */
#line 623 "yacc_sql.y"
                                        {
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		non_subquery_cond_init(&TOP->conditions[TOP->condition_length++], (yyvsp[-2].cexpr), (yyvsp[0].cexpr), op);
	}
#line 2064 "yacc_sql.tab.cpp"
    break;

  case 98: /* condition: non_subquery comOp subquery  */
#line 627 "yacc_sql.y"
                                      {
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		com_subquery_init(&TOP->conditions[TOP->condition_length++], (yyvsp[-2].cexpr), (yyvsp[0].select), op);
	}
#line 2073 "yacc_sql.tab.cpp"
    break;

  case 99: /* condition: non_subquery membershipOp subquery  */
#line 631 "yacc_sql.y"
                                             {
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		membership_subquery_init(&TOP->conditions[TOP->condition_length++], (yyvsp[-2].cexpr), (yyvsp[0].select), op);
	}
#line 2082 "yacc_sql.tab.cpp"
    break;

  case 100: /* membershipOp: IN  */
#line 638 "yacc_sql.y"
           { (yyval.number) = MEM_IN; }
#line 2088 "yacc_sql.tab.cpp"
    break;

  case 101: /* membershipOp: NOT IN  */
#line 639 "yacc_sql.y"
                 { (yyval.number) = MEM_NOT_IN; }
#line 2094 "yacc_sql.tab.cpp"
    break;

  case 102: /* non_subquery: non_subquery ADD_OP non_subquery  */
#line 642 "yacc_sql.y"
                                         {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), ADD);
	}
#line 2103 "yacc_sql.tab.cpp"
    break;

  case 103: /* non_subquery: non_subquery SUB_OP non_subquery  */
#line 646 "yacc_sql.y"
                                           {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), SUB);
	}
#line 2112 "yacc_sql.tab.cpp"
    break;

  case 104: /* non_subquery: non_subquery STAR non_subquery  */
#line 650 "yacc_sql.y"
                                         {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), MUL);
	}
#line 2121 "yacc_sql.tab.cpp"
    break;

  case 105: /* non_subquery: non_subquery DIV_OP non_subquery  */
#line 654 "yacc_sql.y"
                                           {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), DIV);
	}
#line 2130 "yacc_sql.tab.cpp"
    break;

  case 106: /* non_subquery: col  */
#line 658 "yacc_sql.y"
              {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_attr_init((yyval.cexpr), (yyvsp[0].attr));
	}
#line 2139 "yacc_sql.tab.cpp"
    break;

  case 107: /* non_subquery: value  */
#line 662 "yacc_sql.y"
                {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_value_init((yyval.cexpr), &TOP->values[TOP->value_length - 1]);	

		// 释放临时变量
		TOP->value_length --;
	}
#line 2151 "yacc_sql.tab.cpp"
    break;

  case 108: /* non_subquery: LBRACE non_subquery RBRACE  */
#line 669 "yacc_sql.y"
                                     {
		(yyval.cexpr) = (yyvsp[-1].cexpr);
	}
#line 2159 "yacc_sql.tab.cpp"
    break;

  case 109: /* comOp: EQ  */
#line 675 "yacc_sql.y"
                        { (yyval.number) = EQUAL_TO; }
#line 2165 "yacc_sql.tab.cpp"
    break;

  case 110: /* comOp: LT  */
#line 676 "yacc_sql.y"
                        { (yyval.number) = LESS_THAN; }
#line 2171 "yacc_sql.tab.cpp"
    break;

  case 111: /* comOp: GT  */
#line 677 "yacc_sql.y"
                        { (yyval.number) = GREAT_THAN; }
#line 2177 "yacc_sql.tab.cpp"
    break;

  case 112: /* comOp: LE  */
#line 678 "yacc_sql.y"
                        { (yyval.number) = LESS_EQUAL; }
#line 2183 "yacc_sql.tab.cpp"
    break;

  case 113: /* comOp: GE  */
#line 679 "yacc_sql.y"
                        { (yyval.number) = GREAT_EQUAL; }
#line 2189 "yacc_sql.tab.cpp"
    break;

  case 114: /* comOp: NE  */
#line 680 "yacc_sql.y"
                        { (yyval.number) = NOT_EQUAL; }
#line 2195 "yacc_sql.tab.cpp"
    break;

  case 115: /* comOp: IS  */
#line 681 "yacc_sql.y"
                        { (yyval.number) = OP_IS; }
#line 2201 "yacc_sql.tab.cpp"
    break;

  case 116: /* comOp: IS NOT  */
#line 682 "yacc_sql.y"
                        { (yyval.number) = OP_IS_NOT; }
#line 2207 "yacc_sql.tab.cpp"
    break;

  case 117: /* subquery: LBRACE select RBRACE  */
#line 686 "yacc_sql.y"
                             {
		(yyval.select) = (yyvsp[-1].select);
		POP;
	}
#line 2216 "yacc_sql.tab.cpp"
    break;

  case 119: /* group: GROUP BY col group_list  */
#line 694 "yacc_sql.y"
                                  {
		selects_append_group(&TOP->ssql->sstr.selection, (yyvsp[-1].attr));
	}
#line 2224 "yacc_sql.tab.cpp"
    break;

  case 121: /* group_list: COMMA col group_list  */
#line 701 "yacc_sql.y"
                               {
		selects_append_group(&TOP->ssql->sstr.selection, (yyvsp[-1].attr));
	}
#line 2232 "yacc_sql.tab.cpp"
    break;

  case 123: /* order: ORDER BY order_col order_list  */
#line 709 "yacc_sql.y"
                                        {
		selects_append_order(&TOP->ssql->sstr.selection, (yyvsp[-1].ocol));
	}
#line 2240 "yacc_sql.tab.cpp"
    break;

  case 125: /* order_list: COMMA order_col order_list  */
#line 716 "yacc_sql.y"
                                     {
		selects_append_order(&TOP->ssql->sstr.selection, (yyvsp[-1].ocol));
	}
#line 2248 "yacc_sql.tab.cpp"
    break;

  case 126: /* order_col: col  */
#line 722 "yacc_sql.y"
            {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[0].attr), 1);
	}
#line 2257 "yacc_sql.tab.cpp"
    break;

  case 127: /* order_col: col ASC  */
#line 726 "yacc_sql.y"
                  {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[-1].attr), 1);
	}
#line 2266 "yacc_sql.tab.cpp"
    break;

  case 128: /* order_col: col DESC  */
#line 730 "yacc_sql.y"
                   {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[-1].attr), 0);
	}
#line 2275 "yacc_sql.tab.cpp"
    break;

  case 129: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 738 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2284 "yacc_sql.tab.cpp"
    break;


#line 2288 "yacc_sql.tab.cpp"

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

#line 743 "yacc_sql.y"

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
