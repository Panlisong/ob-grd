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


#line 160 "yacc_sql.tab.c"

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

#include "yacc_sql.tab.h"
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
  YYSYMBOL_SELECT = 15,                    /* SELECT  */
  YYSYMBOL_DESC = 16,                      /* DESC  */
  YYSYMBOL_SHOW = 17,                      /* SHOW  */
  YYSYMBOL_SYNC = 18,                      /* SYNC  */
  YYSYMBOL_INSERT = 19,                    /* INSERT  */
  YYSYMBOL_DELETE = 20,                    /* DELETE  */
  YYSYMBOL_UPDATE = 21,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 22,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 23,                    /* RBRACE  */
  YYSYMBOL_COMMA = 24,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 25,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 26,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 27,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 28,                     /* INT_T  */
  YYSYMBOL_STRING_T = 29,                  /* STRING_T  */
  YYSYMBOL_DATE_T = 30,                    /* DATE_T  */
  YYSYMBOL_FLOAT_T = 31,                   /* FLOAT_T  */
  YYSYMBOL_HELP = 32,                      /* HELP  */
  YYSYMBOL_EXIT = 33,                      /* EXIT  */
  YYSYMBOL_IS = 34,                        /* IS  */
  YYSYMBOL_NOT = 35,                       /* NOT  */
  YYSYMBOL_NULL_T = 36,                    /* NULL_T  */
  YYSYMBOL_NULLABLE = 37,                  /* NULLABLE  */
  YYSYMBOL_DOT = 38,                       /* DOT  */
  YYSYMBOL_INTO = 39,                      /* INTO  */
  YYSYMBOL_VALUES = 40,                    /* VALUES  */
  YYSYMBOL_FROM = 41,                      /* FROM  */
  YYSYMBOL_WHERE = 42,                     /* WHERE  */
  YYSYMBOL_AND = 43,                       /* AND  */
  YYSYMBOL_SET = 44,                       /* SET  */
  YYSYMBOL_ON = 45,                        /* ON  */
  YYSYMBOL_LOAD = 46,                      /* LOAD  */
  YYSYMBOL_DATA = 47,                      /* DATA  */
  YYSYMBOL_INFILE = 48,                    /* INFILE  */
  YYSYMBOL_GROUP = 49,                     /* GROUP  */
  YYSYMBOL_ORDER = 50,                     /* ORDER  */
  YYSYMBOL_BY = 51,                        /* BY  */
  YYSYMBOL_ASC = 52,                       /* ASC  */
  YYSYMBOL_ADD_OP = 53,                    /* ADD_OP  */
  YYSYMBOL_SUB_OP = 54,                    /* SUB_OP  */
  YYSYMBOL_MUL_OP = 55,                    /* MUL_OP  */
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
  YYSYMBOL_drop_index = 85,                /* drop_index  */
  YYSYMBOL_create_table = 86,              /* create_table  */
  YYSYMBOL_attr_def_list = 87,             /* attr_def_list  */
  YYSYMBOL_attr_def = 88,                  /* attr_def  */
  YYSYMBOL_number = 89,                    /* number  */
  YYSYMBOL_type = 90,                      /* type  */
  YYSYMBOL_is_nullable = 91,               /* is_nullable  */
  YYSYMBOL_insert = 92,                    /* insert  */
  YYSYMBOL_tuple_list = 93,                /* tuple_list  */
  YYSYMBOL_tuple = 94,                     /* tuple  */
  YYSYMBOL_value_list = 95,                /* value_list  */
  YYSYMBOL_value = 96,                     /* value  */
  YYSYMBOL_delete = 97,                    /* delete  */
  YYSYMBOL_update = 98,                    /* update  */
  YYSYMBOL_selects = 99,                   /* selects  */
  YYSYMBOL_select = 100,                   /* select  */
  YYSYMBOL_select_expr_list = 101,         /* select_expr_list  */
  YYSYMBOL_select_expr = 102,              /* select_expr  */
  YYSYMBOL_select_arith_expr = 103,        /* select_arith_expr  */
  YYSYMBOL_arithOp = 104,                  /* arithOp  */
  YYSYMBOL_select_func = 105,              /* select_func  */
  YYSYMBOL_aggregate_func = 106,           /* aggregate_func  */
  YYSYMBOL_col = 107,                      /* col  */
  YYSYMBOL_table_ref_list = 108,           /* table_ref_list  */
  YYSYMBOL_table_ref = 109,                /* table_ref  */
  YYSYMBOL_join_table = 110,               /* join_table  */
  YYSYMBOL_join_condition = 111,           /* join_condition  */
  YYSYMBOL_where = 112,                    /* where  */
  YYSYMBOL_condition_list = 113,           /* condition_list  */
  YYSYMBOL_condition = 114,                /* condition  */
  YYSYMBOL_membershipOp = 115,             /* membershipOp  */
  YYSYMBOL_non_subquery = 116,             /* non_subquery  */
  YYSYMBOL_comOp = 117,                    /* comOp  */
  YYSYMBOL_subquery = 118,                 /* subquery  */
  YYSYMBOL_subquery_start = 119,           /* subquery_start  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYLAST   218

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  228

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
       0,   205,   205,   207,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   231,   236,   241,   247,   253,   259,   265,   271,   277,
     284,   291,   298,   303,   305,   309,   314,   322,   326,   327,
     328,   329,   333,   334,   335,   339,   344,   346,   350,   357,
     359,   362,   365,   368,   371,   387,   393,   403,   413,   417,
     442,   444,   451,   452,   453,   459,   472,   476,   480,   490,
     491,   492,   493,   497,   501,   511,   524,   525,   526,   527,
     531,   535,   542,   544,   550,   555,   559,   568,   570,   574,
     576,   580,   582,   586,   589,   592,   598,   599,   602,   606,
     610,   620,   621,   622,   623,   624,   625,   626,   627,   631,
     636,   642,   644,   649,   651,   657,   659,   664,   666,   672,
     676,   680,   687
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
  "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE",
  "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "STRING_T", "DATE_T", "FLOAT_T", "HELP", "EXIT",
  "IS", "NOT", "NULL_T", "NULLABLE", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "GROUP", "ORDER",
  "BY", "ASC", "ADD_OP", "SUB_OP", "MUL_OP", "DIV_OP", "EQ", "LT", "GT",
  "LE", "GE", "NE", "IN", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "DATE",
  "STAR", "STRING_V", "$accept", "commands", "command", "exit", "help",
  "sync", "begin", "commit", "rollback", "drop_table", "show_tables",
  "desc_table", "create_index", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "is_nullable", "insert",
  "tuple_list", "tuple", "value_list", "value", "delete", "update",
  "selects", "select", "select_expr_list", "select_expr",
  "select_arith_expr", "arithOp", "select_func", "aggregate_func", "col",
  "table_ref_list", "table_ref", "join_table", "join_condition", "where",
  "condition_list", "condition", "membershipOp", "non_subquery", "comOp",
  "subquery", "subquery_start", "group", "group_list", "order",
  "order_list", "order_col", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-167)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -167,     7,  -167,     2,    45,    -1,   -35,     8,    41,    11,
      44,    10,    57,    78,    83,    92,   101,    58,  -167,  -167,
    -167,  -167,  -167,  -167,  -167,  -167,  -167,  -167,  -167,  -167,
    -167,  -167,  -167,  -167,  -167,   103,  -167,    42,    43,    46,
      47,  -167,  -167,  -167,  -167,  -167,  -167,  -167,    69,  -167,
    -167,  -167,  -167,    87,   -41,  -167,    93,  -167,   111,   114,
    -167,    52,    53,    76,  -167,  -167,  -167,  -167,  -167,    73,
    -167,   100,    79,   122,   123,   -29,    -1,    86,  -167,  -167,
    -167,  -167,   -17,   -28,  -167,  -167,    88,    89,    63,    62,
      66,    67,  -167,  -167,  -167,  -167,    87,    68,    97,   -41,
      98,   115,   116,   118,   -17,   134,    84,   104,    61,   120,
     124,  -167,  -167,    12,  -167,    81,    -4,  -167,  -167,    19,
     121,  -167,  -167,    99,    40,  -167,    19,   136,  -167,  -167,
    -167,  -167,    21,    66,   126,    85,   141,    68,    89,   129,
     130,   118,   150,   -17,  -167,   125,    94,  -167,  -167,  -167,
    -167,  -167,  -167,  -167,   -17,  -167,   -17,    89,    90,    91,
     127,  -167,  -167,   120,   155,   138,    96,    12,   110,  -167,
      19,   142,   121,  -167,    99,  -167,  -167,   -41,  -167,   144,
     -41,  -167,   161,   165,  -167,   146,  -167,  -167,  -167,   167,
     128,  -167,   131,   133,   130,  -167,  -167,  -167,   156,  -167,
    -167,    35,  -167,   -17,  -167,   106,   135,  -167,  -167,   151,
    -167,    99,   152,   106,  -167,  -167,   106,  -167,    -6,   153,
     152,  -167,  -167,   106,  -167,  -167,   153,  -167
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,     0,    18,     0,     0,     0,
       0,    76,    77,    78,    79,    55,    51,    52,    80,    53,
      54,    64,    68,    60,    62,    63,     0,    67,     0,     0,
      23,     0,     0,     0,    24,    25,    26,    22,    21,     0,
      58,     0,     0,     0,     0,     0,     0,     0,    69,    70,
      72,    71,     0,     0,    29,    28,     0,    89,     0,     0,
       0,     0,    27,    31,    81,    65,    60,     0,    80,    66,
      80,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,    61,    84,    82,    85,     0,     0,    74,    73,     0,
      46,   100,    99,    91,     0,    56,     0,     0,    38,    39,
      41,    40,    42,     0,     0,     0,     0,     0,    89,     0,
      49,     0,     0,     0,    90,   107,     0,   101,   102,   103,
     104,   105,   106,    96,     0,   110,   110,    89,     0,     0,
       0,    44,    36,    33,     0,     0,     0,    82,   111,    75,
       0,     0,    46,    45,    91,   108,    97,    98,    95,     0,
      93,    94,     0,     0,    37,     0,    43,    34,    32,     0,
      87,    83,     0,   115,    49,    48,    47,    92,     0,    57,
     122,    42,    30,     0,    86,     0,     0,    59,    50,     0,
      35,    91,   113,     0,   109,    88,     0,   112,   119,   117,
     113,   121,   120,     0,   116,   114,   117,   118
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -167,  -167,  -167,  -167,  -167,  -167,  -167,  -167,  -167,  -167,
    -167,  -167,  -167,  -167,  -167,    15,    48,  -167,  -167,   -26,
    -167,    13,    38,   -14,    -3,  -167,  -167,  -167,   -11,    95,
     108,   107,   -45,  -167,  -167,    -5,    23,    51,  -167,  -167,
    -127,  -166,  -142,  -167,   -74,  -167,    36,  -167,  -167,   -27,
    -167,   -32,   -25,  -167
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,   134,   109,   185,   132,   162,
      31,   142,   120,   171,   121,    32,    33,    34,    35,    77,
      53,    54,   154,    55,    56,   122,   138,   113,   114,   204,
     105,   144,   123,   155,   124,   156,   178,   179,   193,   217,
     207,   224,   219,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      57,   174,    52,    41,    42,    43,    44,     2,   197,    82,
     221,   168,    78,    79,    37,    80,    38,     3,     4,    45,
     136,    59,     5,     6,     7,     8,     9,    10,    11,    81,
     182,    58,    12,    13,    14,    45,   137,    94,   100,    15,
      16,    95,   101,   159,    60,   215,   222,    46,    47,    98,
      61,    49,    50,    17,    82,    45,   160,    39,   161,    40,
      64,   211,    94,    46,    47,    48,   139,    49,    50,    51,
     160,    57,   161,    52,   145,   146,    63,    57,   102,    52,
     177,    65,   180,    46,    47,    62,    66,    49,    50,   128,
     129,   130,   131,    78,    79,    67,    80,   147,   148,   149,
     150,   151,   152,   153,    68,    69,    70,    75,    71,    72,
      81,    76,    73,    74,    84,    83,   140,    85,    86,    87,
      88,    89,    90,   157,    91,    92,    93,    97,   103,   106,
     107,   104,   108,   110,   112,   115,   116,   125,   117,   118,
     119,   126,   143,   127,   133,   141,   135,    94,   158,   164,
     166,   165,   169,   173,   170,   184,   183,   176,   188,   192,
     175,   189,   190,   186,   199,   195,   198,   194,   200,   201,
     202,     5,    98,   203,   214,   210,   216,   223,   187,   172,
     208,   163,   205,   206,    96,   196,   213,   209,   167,    99,
     191,   111,   181,   225,   227,     0,     0,     0,   226,     0,
     212,     0,     0,     0,     0,     0,     0,     0,   218,     0,
       0,   220,     0,     0,     0,     0,     0,     0,   218
};

static const yytype_int16 yycheck[] =
{
       5,   143,     5,     4,     5,     6,     7,     0,   174,    54,
      16,   138,    53,    54,    12,    56,    14,    10,    11,    36,
       8,    13,    15,    16,    17,    18,    19,    20,    21,    70,
     157,    66,    25,    26,    27,    36,    24,    66,    66,    32,
      33,    70,    70,    22,     3,   211,    52,    64,    65,    66,
      39,    68,    69,    46,    99,    36,    35,    12,    37,    14,
       3,   203,    66,    64,    65,    66,    70,    68,    69,    70,
      35,    76,    37,    76,    34,    35,    66,    82,    83,    82,
     154,     3,   156,    64,    65,    41,     3,    68,    69,    28,
      29,    30,    31,    53,    54,     3,    56,    57,    58,    59,
      60,    61,    62,    63,     3,    47,     3,    38,    66,    66,
      70,    24,    66,    66,     3,    22,   119,     3,    66,    66,
      44,    48,    22,   126,    45,     3,     3,    41,    40,    66,
      68,    42,    66,    66,    66,    38,    38,     3,    23,    23,
      22,    57,    43,    39,    24,    24,    22,    66,    12,    23,
       9,    66,    23,     3,    24,    64,    66,    63,     3,    49,
      35,    23,    66,    36,     3,    23,    22,   170,     3,    23,
       3,    15,    66,    45,    23,   201,    24,    24,   163,   141,
     194,   133,    51,    50,    76,   172,    51,   198,   137,    82,
     167,    96,   156,   220,   226,    -1,    -1,    -1,   223,    -1,
     205,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   213,    -1,
      -1,   216,    -1,    -1,    -1,    -1,    -1,    -1,   223
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    73,     0,    10,    11,    15,    16,    17,    18,    19,
      20,    21,    25,    26,    27,    32,    33,    46,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    92,    97,    98,    99,   100,   125,    12,    14,    12,
      14,     4,     5,     6,     7,    36,    64,    65,    66,    68,
      69,    70,    96,   102,   103,   105,   106,   107,    66,    13,
       3,    39,    41,    66,     3,     3,     3,     3,     3,    47,
       3,    66,    66,    66,    66,    38,    24,   101,    53,    54,
      56,    70,   104,    22,     3,     3,    66,    66,    44,    48,
      22,    45,     3,     3,    66,    70,   102,    41,    66,   103,
      66,    70,   107,    40,    42,   112,    66,    68,    66,    88,
      66,   101,    66,   109,   110,    38,    38,    23,    23,    22,
      94,    96,   107,   114,   116,     3,    57,    39,    28,    29,
      30,    31,    90,    24,    87,    22,     8,    24,   108,    70,
      96,    24,    93,    43,   113,    34,    35,    57,    58,    59,
      60,    61,    62,    63,   104,   115,   117,    96,    12,    22,
      35,    37,    91,    88,    23,    66,     9,   109,   112,    23,
      24,    95,    94,     3,   114,    35,    63,   116,   118,   119,
     116,   118,   112,    66,    64,    89,    36,    87,     3,    23,
      66,   108,    49,   120,    96,    23,    93,   113,    22,     3,
       3,    23,     3,    45,   111,    51,    50,   122,    95,   100,
      91,   114,   107,    51,    23,   113,    24,   121,   107,   124,
     107,    16,    52,    24,   123,   121,   124,   123
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    72,    73,    73,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    87,    88,    88,    89,    90,    90,
      90,    90,    91,    91,    91,    92,    93,    93,    94,    95,
      95,    96,    96,    96,    96,    96,    97,    98,    99,   100,
     101,   101,   102,   102,   102,   102,   103,   103,   103,   104,
     104,   104,   104,   105,   105,   105,   106,   106,   106,   106,
     107,   107,   108,   108,   109,   109,   110,   111,   111,   112,
     112,   113,   113,   114,   114,   114,   115,   115,   116,   116,
     116,   117,   117,   117,   117,   117,   117,   117,   117,   118,
     119,   120,   120,   121,   121,   122,   122,   123,   123,   124,
     124,   124,   125
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       9,     4,     8,     0,     3,     6,     3,     1,     1,     1,
       1,     1,     0,     2,     1,     7,     0,     3,     4,     0,
       3,     1,     1,     1,     1,     1,     5,     8,     2,     9,
       0,     3,     1,     1,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     4,     4,     6,     1,     1,     1,     1,
       1,     3,     0,     3,     1,     1,     5,     0,     3,     0,
       3,     0,     3,     3,     3,     3,     1,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     4,
       0,     0,     4,     0,     3,     0,     4,     0,     3,     1,
       2,     2,     8
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
#line 231 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1447 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 236 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1455 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 241 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1463 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 247 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1471 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 253 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1479 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 259 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1487 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 265 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1496 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 271 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1504 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 277 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1513 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 284 "yacc_sql.y"
                                                     {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
	}
#line 1522 "yacc_sql.tab.c"
    break;

  case 31: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 291 "yacc_sql.y"
                             {
		CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
		drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
	}
#line 1531 "yacc_sql.tab.c"
    break;

  case 32: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 298 "yacc_sql.y"
                                                                   {
		CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
		create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
	}
#line 1540 "yacc_sql.tab.c"
    break;

  case 34: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 305 "yacc_sql.y"
                                   {    }
#line 1546 "yacc_sql.tab.c"
    break;

  case 35: /* attr_def: ID type LBRACE number RBRACE is_nullable  */
#line 309 "yacc_sql.y"
                                            {
		AttrInfo attribute;
		attr_info_init(&attribute, (yyvsp[-5].string), (yyvsp[-4].number), (yyvsp[-2].number), (yyvsp[0].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
#line 1556 "yacc_sql.tab.c"
    break;

  case 36: /* attr_def: ID type is_nullable  */
#line 314 "yacc_sql.y"
                         {
		AttrInfo attribute;
		attr_info_init(&attribute, (yyvsp[-2].string), (yyvsp[-1].number), (yyvsp[-1].number) == DATES ? 8 : 4, (yyvsp[0].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
#line 1566 "yacc_sql.tab.c"
    break;

  case 37: /* number: NUMBER  */
#line 322 "yacc_sql.y"
               {(yyval.number) = (yyvsp[0].number);}
#line 1572 "yacc_sql.tab.c"
    break;

  case 38: /* type: INT_T  */
#line 326 "yacc_sql.y"
                   { (yyval.number)=INTS; }
#line 1578 "yacc_sql.tab.c"
    break;

  case 39: /* type: STRING_T  */
#line 327 "yacc_sql.y"
                   { (yyval.number)=CHARS; }
#line 1584 "yacc_sql.tab.c"
    break;

  case 40: /* type: FLOAT_T  */
#line 328 "yacc_sql.y"
                   { (yyval.number)=FLOATS; }
#line 1590 "yacc_sql.tab.c"
    break;

  case 41: /* type: DATE_T  */
#line 329 "yacc_sql.y"
                   { (yyval.number)=DATES; }
#line 1596 "yacc_sql.tab.c"
    break;

  case 42: /* is_nullable: %empty  */
#line 333 "yacc_sql.y"
                    { (yyval.number) = 0; }
#line 1602 "yacc_sql.tab.c"
    break;

  case 43: /* is_nullable: NOT NULL_T  */
#line 334 "yacc_sql.y"
                    { (yyval.number) = 0; }
#line 1608 "yacc_sql.tab.c"
    break;

  case 44: /* is_nullable: NULLABLE  */
#line 335 "yacc_sql.y"
                    { (yyval.number) = 1; }
#line 1614 "yacc_sql.tab.c"
    break;

  case 45: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 339 "yacc_sql.y"
                                                         {
		CONTEXT->ssql->flag=SCF_INSERT;
		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
	}
#line 1623 "yacc_sql.tab.c"
    break;

  case 47: /* tuple_list: COMMA tuple tuple_list  */
#line 347 "yacc_sql.y"
        {	/* do nothing here */	}
#line 1629 "yacc_sql.tab.c"
    break;

  case 48: /* tuple: LBRACE value value_list RBRACE  */
#line 350 "yacc_sql.y"
                                       {
		// 由于tuple这种语法[形如(v1, v2, ..., vn)]只在insert中使用
		insert_tuple_init(&CONTEXT->ssql->sstr.insertion, TOP->values, TOP->value_length);
		// 清空CONTEXT临时变量
		TOP->value_length = 0;
	}
#line 1640 "yacc_sql.tab.c"
    break;

  case 50: /* value_list: COMMA value value_list  */
#line 359 "yacc_sql.y"
                              {}
#line 1646 "yacc_sql.tab.c"
    break;

  case 51: /* value: NUMBER  */
#line 362 "yacc_sql.y"
          {	
  		value_init_integer(&TOP->values[TOP->value_length++], (yyvsp[0].number));
	}
#line 1654 "yacc_sql.tab.c"
    break;

  case 52: /* value: FLOAT  */
#line 365 "yacc_sql.y"
           {
  		value_init_float(&TOP->values[TOP->value_length++], (yyvsp[0].floats));
	}
#line 1662 "yacc_sql.tab.c"
    break;

  case 53: /* value: SSS  */
#line 368 "yacc_sql.y"
          {
  		value_init_string(&TOP->values[TOP->value_length++], (yyvsp[0].string));
	}
#line 1670 "yacc_sql.tab.c"
    break;

  case 54: /* value: DATE  */
#line 371 "yacc_sql.y"
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
#line 1691 "yacc_sql.tab.c"
    break;

  case 55: /* value: NULL_T  */
#line 387 "yacc_sql.y"
                 {
		value_init_null(&TOP->values[TOP->value_length++]);
	}
#line 1699 "yacc_sql.tab.c"
    break;

  case 56: /* delete: DELETE FROM ID where SEMICOLON  */
#line 393 "yacc_sql.y"
                                   {
		CONTEXT->ssql->flag = SCF_DELETE;//"delete";
		deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
		deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, TOP->conditions, TOP->condition_length);
		
		// CONTEXT临时变量清零
		TOP->condition_length = 0;	
    }
#line 1712 "yacc_sql.tab.c"
    break;

  case 57: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 403 "yacc_sql.y"
                                              {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		Value *value = &TOP->values[0];
		updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, TOP->conditions, TOP->condition_length);
		
		// CONTEXT临时变量清零
		TOP->condition_length = 0;
	}
#line 1725 "yacc_sql.tab.c"
    break;

  case 58: /* selects: select SEMICOLON  */
#line 413 "yacc_sql.y"
                     {
		CONTEXT->ssql->flag = SCF_SELECT; //"select";
	}
#line 1733 "yacc_sql.tab.c"
    break;

  case 59: /* select: SELECT select_expr select_expr_list FROM table_ref table_ref_list where group order  */
#line 418 "yacc_sql.y"
        {
		// 1. append select_expr $2
		selects_append_expr(&TOP->ssql->sstr.selection, (yyvsp[-7].sexpr));

		// 2. append table_ref $5
		selects_append_relation(&TOP->ssql->sstr.selection, (yyvsp[-4].ref));

		// 3. append condtion_list(可选项，可能为空)
		selects_append_conditions(&TOP->ssql->sstr.selection, TOP->conditions, TOP->condition_length);

		// 4. append group_list(可选项，可能为空)

		// 5. append order_list(可选项，可能为空)
		

		//临时变量清零
		TOP->condition_length=0;
		TOP->value_length = 0;

		(yyval.select) = &TOP->ssql->sstr.selection;
	}
#line 1759 "yacc_sql.tab.c"
    break;

  case 61: /* select_expr_list: COMMA select_expr select_expr_list  */
#line 444 "yacc_sql.y"
                                             {
		// append select_expr $2
		selects_append_expr(&TOP->ssql->sstr.selection, (yyvsp[-1].sexpr));
	}
#line 1768 "yacc_sql.tab.c"
    break;

  case 62: /* select_expr: select_arith_expr  */
#line 451 "yacc_sql.y"
                          { (yyval.sexpr) = (yyvsp[0].sexpr); }
#line 1774 "yacc_sql.tab.c"
    break;

  case 63: /* select_expr: select_func  */
#line 452 "yacc_sql.y"
                      { (yyval.sexpr) = (yyvsp[0].sexpr); }
#line 1780 "yacc_sql.tab.c"
    break;

  case 64: /* select_expr: STAR  */
#line 453 "yacc_sql.y"
               { 
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, NULL, "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), attr);
	}
#line 1791 "yacc_sql.tab.c"
    break;

  case 65: /* select_expr: ID DOT STAR  */
#line 459 "yacc_sql.y"
                      {
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, (yyvsp[-2].string), "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), attr);
	}
#line 1802 "yacc_sql.tab.c"
    break;

  case 66: /* select_arith_expr: select_arith_expr arithOp select_arith_expr  */
#line 472 "yacc_sql.y"
                                                    {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), (yyvsp[-1].number));
	}
#line 1811 "yacc_sql.tab.c"
    break;

  case 67: /* select_arith_expr: col  */
#line 476 "yacc_sql.y"
              {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), (yyvsp[0].attr));
	}
#line 1820 "yacc_sql.tab.c"
    break;

  case 68: /* select_arith_expr: value  */
#line 480 "yacc_sql.y"
                { 
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_value_init((yyval.sexpr), &TOP->values[TOP->value_length - 1]);	

		// 释放临时变量
		TOP->value_length --;
	}
#line 1832 "yacc_sql.tab.c"
    break;

  case 69: /* arithOp: ADD_OP  */
#line 490 "yacc_sql.y"
                 { (yyval.number) = ADD; }
#line 1838 "yacc_sql.tab.c"
    break;

  case 70: /* arithOp: SUB_OP  */
#line 491 "yacc_sql.y"
                 { (yyval.number) = SUB; }
#line 1844 "yacc_sql.tab.c"
    break;

  case 71: /* arithOp: STAR  */
#line 492 "yacc_sql.y"
                 { (yyval.number) = MUL; }
#line 1850 "yacc_sql.tab.c"
    break;

  case 72: /* arithOp: DIV_OP  */
#line 493 "yacc_sql.y"
                 { (yyval.number) = DIV; }
#line 1856 "yacc_sql.tab.c"
    break;

  case 73: /* select_func: aggregate_func LBRACE col RBRACE  */
#line 497 "yacc_sql.y"
                                         {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		aggregate_function_init((yyval.sexpr), (yyvsp[-3].number), (yyvsp[-1].attr));
	}
#line 1865 "yacc_sql.tab.c"
    break;

  case 74: /* select_func: aggregate_func LBRACE STAR RBRACE  */
#line 501 "yacc_sql.y"
                                            {
		if ((yyvsp[-3].number) != COUNT_FUNC) {
			CONTEXT->ssql->sstr.errors = "Invalid args of aggregate function";
			YYERROR;
		}
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, NULL, "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		aggregate_function_init((yyval.sexpr), (yyvsp[-3].number), attr);
	}
#line 1880 "yacc_sql.tab.c"
    break;

  case 75: /* select_func: aggregate_func LBRACE ID DOT STAR RBRACE  */
#line 511 "yacc_sql.y"
                                                   {
		if ((yyvsp[-5].number) != COUNT_FUNC) {
			CONTEXT->ssql->sstr.errors = "Invalid args of aggregate function";
			YYERROR;
		}
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, (yyvsp[-3].string), "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		aggregate_function_init((yyval.sexpr), (yyvsp[-5].number), attr);
	}
#line 1895 "yacc_sql.tab.c"
    break;

  case 76: /* aggregate_func: MAX_F  */
#line 524 "yacc_sql.y"
                  { (yyval.number) = MAX_FUNC;   }
#line 1901 "yacc_sql.tab.c"
    break;

  case 77: /* aggregate_func: MIN_F  */
#line 525 "yacc_sql.y"
                  { (yyval.number) = MIN_FUNC;   }
#line 1907 "yacc_sql.tab.c"
    break;

  case 78: /* aggregate_func: COUNT_F  */
#line 526 "yacc_sql.y"
                  { (yyval.number) = COUNT_FUNC; }
#line 1913 "yacc_sql.tab.c"
    break;

  case 79: /* aggregate_func: AVG_F  */
#line 527 "yacc_sql.y"
                  { (yyval.number) = AVG_FUNC;   }
#line 1919 "yacc_sql.tab.c"
    break;

  case 80: /* col: ID  */
#line 531 "yacc_sql.y"
           {
		(yyval.attr) = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init((yyval.attr), NULL, (yyvsp[0].string));
	}
#line 1928 "yacc_sql.tab.c"
    break;

  case 81: /* col: ID DOT ID  */
#line 535 "yacc_sql.y"
                    {
		(yyval.attr) = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init((yyval.attr), (yyvsp[-2].string), (yyvsp[0].string));
	}
#line 1937 "yacc_sql.tab.c"
    break;

  case 83: /* table_ref_list: COMMA table_ref table_ref_list  */
#line 544 "yacc_sql.y"
                                     {	
		selects_append_relation(&TOP->ssql->sstr.selection, (yyvsp[-1].ref));
	}
#line 1945 "yacc_sql.tab.c"
    break;

  case 84: /* table_ref: ID  */
#line 550 "yacc_sql.y"
           { 
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 0, (yyvsp[0].string), NULL, NULL, 0); 
		(yyval.ref) = ref;
	}
#line 1955 "yacc_sql.tab.c"
    break;

  case 85: /* table_ref: join_table  */
#line 555 "yacc_sql.y"
                     { (yyval.ref) = (yyvsp[0].ref); }
#line 1961 "yacc_sql.tab.c"
    break;

  case 86: /* join_table: table_ref INNER JOIN ID join_condition  */
#line 559 "yacc_sql.y"
                                               {
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 1, (yyvsp[-1].string), (yyvsp[-4].ref), TOP->conditions, TOP->condition_length);
		(yyval.ref) = ref;
		// 临时变量清零
		TOP->condition_length = 0;
	}
#line 1973 "yacc_sql.tab.c"
    break;

  case 88: /* join_condition: ON condition condition_list  */
#line 570 "yacc_sql.y"
                                      {}
#line 1979 "yacc_sql.tab.c"
    break;

  case 90: /* where: WHERE condition condition_list  */
#line 576 "yacc_sql.y"
                                     {}
#line 1985 "yacc_sql.tab.c"
    break;

  case 92: /* condition_list: AND condition condition_list  */
#line 582 "yacc_sql.y"
                                   {}
#line 1991 "yacc_sql.tab.c"
    break;

  case 93: /* condition: non_subquery comOp non_subquery  */
#line 586 "yacc_sql.y"
                                        {
		non_subquery_cond_init(&TOP->conditions[TOP->condition_length++], (yyvsp[-2].cexpr), (yyvsp[0].cexpr), (yyvsp[-1].number));
	}
#line 1999 "yacc_sql.tab.c"
    break;

  case 94: /* condition: non_subquery comOp subquery  */
#line 589 "yacc_sql.y"
                                      {
		com_subquery_init(&TOP->conditions[TOP->condition_length++], (yyvsp[-2].cexpr), (yyvsp[0].select), (yyvsp[-1].number));
	}
#line 2007 "yacc_sql.tab.c"
    break;

  case 95: /* condition: non_subquery membershipOp subquery  */
#line 592 "yacc_sql.y"
                                             {
		membership_subquery_init(&TOP->conditions[TOP->condition_length++], (yyvsp[-2].cexpr), (yyvsp[0].select), (yyvsp[-1].number));
	}
#line 2015 "yacc_sql.tab.c"
    break;

  case 96: /* membershipOp: IN  */
#line 598 "yacc_sql.y"
           { (yyval.number) = MEM_IN; }
#line 2021 "yacc_sql.tab.c"
    break;

  case 97: /* membershipOp: NOT IN  */
#line 599 "yacc_sql.y"
                 { (yyval.number) = MEM_NOT_IN; }
#line 2027 "yacc_sql.tab.c"
    break;

  case 98: /* non_subquery: non_subquery arithOp non_subquery  */
#line 602 "yacc_sql.y"
                                          {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), (yyvsp[-1].number));
	}
#line 2036 "yacc_sql.tab.c"
    break;

  case 99: /* non_subquery: col  */
#line 606 "yacc_sql.y"
              {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_attr_init((yyval.cexpr), (yyvsp[0].attr));
	}
#line 2045 "yacc_sql.tab.c"
    break;

  case 100: /* non_subquery: value  */
#line 610 "yacc_sql.y"
                {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_value_init((yyval.cexpr), &TOP->values[TOP->value_length - 1]);	

		// 释放临时变量
		TOP->value_length --;
	}
#line 2057 "yacc_sql.tab.c"
    break;

  case 101: /* comOp: EQ  */
#line 620 "yacc_sql.y"
                        { (yyval.number) = EQUAL_TO; }
#line 2063 "yacc_sql.tab.c"
    break;

  case 102: /* comOp: LT  */
#line 621 "yacc_sql.y"
                        { (yyval.number) = LESS_THAN; }
#line 2069 "yacc_sql.tab.c"
    break;

  case 103: /* comOp: GT  */
#line 622 "yacc_sql.y"
                        { (yyval.number) = GREAT_THAN; }
#line 2075 "yacc_sql.tab.c"
    break;

  case 104: /* comOp: LE  */
#line 623 "yacc_sql.y"
                        { (yyval.number) = LESS_EQUAL; }
#line 2081 "yacc_sql.tab.c"
    break;

  case 105: /* comOp: GE  */
#line 624 "yacc_sql.y"
                        { (yyval.number) = GREAT_EQUAL; }
#line 2087 "yacc_sql.tab.c"
    break;

  case 106: /* comOp: NE  */
#line 625 "yacc_sql.y"
                        { (yyval.number) = NOT_EQUAL; }
#line 2093 "yacc_sql.tab.c"
    break;

  case 107: /* comOp: IS  */
#line 626 "yacc_sql.y"
                        { (yyval.number) = OP_IS; }
#line 2099 "yacc_sql.tab.c"
    break;

  case 108: /* comOp: IS NOT  */
#line 627 "yacc_sql.y"
                        { (yyval.number) = OP_IS_NOT; }
#line 2105 "yacc_sql.tab.c"
    break;

  case 109: /* subquery: subquery_start LBRACE select RBRACE  */
#line 631 "yacc_sql.y"
                                            {
		(yyval.select) = (yyvsp[-1].select);
		POP;
	}
#line 2114 "yacc_sql.tab.c"
    break;

  case 110: /* subquery_start: %empty  */
#line 636 "yacc_sql.y"
                {
	PUSH;
	TOP->ssql = (Query *)malloc(sizeof(Query));
}
#line 2123 "yacc_sql.tab.c"
    break;

  case 112: /* group: GROUP BY col group_list  */
#line 644 "yacc_sql.y"
                                  {
		selects_append_group(&TOP->ssql->sstr.selection, (yyvsp[-1].attr));
	}
#line 2131 "yacc_sql.tab.c"
    break;

  case 114: /* group_list: COMMA col group_list  */
#line 651 "yacc_sql.y"
                               {
		selects_append_group(&TOP->ssql->sstr.selection, (yyvsp[-1].attr));
	}
#line 2139 "yacc_sql.tab.c"
    break;

  case 116: /* order: ORDER BY order_col order_list  */
#line 659 "yacc_sql.y"
                                        {
		selects_append_order(&TOP->ssql->sstr.selection, (yyvsp[-1].ocol));
	}
#line 2147 "yacc_sql.tab.c"
    break;

  case 118: /* order_list: COMMA order_col order_list  */
#line 666 "yacc_sql.y"
                                     {
		selects_append_order(&TOP->ssql->sstr.selection, (yyvsp[-1].ocol));
	}
#line 2155 "yacc_sql.tab.c"
    break;

  case 119: /* order_col: col  */
#line 672 "yacc_sql.y"
            {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[0].attr), 1);
	}
#line 2164 "yacc_sql.tab.c"
    break;

  case 120: /* order_col: col ASC  */
#line 676 "yacc_sql.y"
                  {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[-1].attr), 1);
	}
#line 2173 "yacc_sql.tab.c"
    break;

  case 121: /* order_col: col DESC  */
#line 680 "yacc_sql.y"
                   {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[-1].attr), 0);
	}
#line 2182 "yacc_sql.tab.c"
    break;

  case 122: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 688 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2191 "yacc_sql.tab.c"
    break;


#line 2195 "yacc_sql.tab.c"

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

#line 693 "yacc_sql.y"

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
