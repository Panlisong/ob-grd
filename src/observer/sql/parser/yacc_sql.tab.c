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
  YYSYMBOL_MUL_OP = 56,                    /* MUL_OP  */
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
  YYSYMBOL_select_expr_list = 103,         /* select_expr_list  */
  YYSYMBOL_select_expr = 104,              /* select_expr  */
  YYSYMBOL_select_arith_expr = 105,        /* select_arith_expr  */
  YYSYMBOL_arithOp = 106,                  /* arithOp  */
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
  YYSYMBOL_subquery_start = 121,           /* subquery_start  */
  YYSYMBOL_group = 122,                    /* group  */
  YYSYMBOL_group_list = 123,               /* group_list  */
  YYSYMBOL_order = 124,                    /* order  */
  YYSYMBOL_order_list = 125,               /* order_list  */
  YYSYMBOL_order_col = 126,                /* order_col  */
  YYSYMBOL_load_data = 127                 /* load_data  */
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
#define YYLAST   232

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  242

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
       0,   206,   206,   208,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   232,   237,   242,   248,   254,   260,   266,   272,   278,
     285,   291,   299,   301,   306,   313,   318,   320,   324,   329,
     337,   341,   342,   343,   344,   348,   349,   350,   354,   359,
     361,   365,   372,   374,   377,   380,   383,   386,   402,   408,
     418,   428,   432,   457,   459,   466,   467,   468,   474,   487,
     491,   495,   505,   506,   507,   508,   512,   516,   526,   539,
     540,   541,   542,   546,   550,   557,   559,   565,   570,   574,
     583,   585,   589,   591,   595,   597,   601,   604,   607,   613,
     614,   617,   621,   625,   635,   636,   637,   638,   639,   640,
     641,   642,   646,   651,   657,   659,   664,   666,   672,   674,
     679,   681,   687,   691,   695,   702
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
  "GROUP", "ORDER", "BY", "ASC", "ADD_OP", "SUB_OP", "MUL_OP", "DIV_OP",
  "EQ", "LT", "GT", "LE", "GE", "NE", "IN", "NUMBER", "FLOAT", "ID",
  "PATH", "SSS", "DATE", "STAR", "STRING_V", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index", "attr_list",
  "drop_index", "create_table", "attr_def_list", "attr_def", "number",
  "type", "is_nullable", "insert", "tuple_list", "tuple", "value_list",
  "value", "delete", "update", "selects", "select", "select_expr_list",
  "select_expr", "select_arith_expr", "arithOp", "select_func",
  "aggregate_func", "col", "table_ref_list", "table_ref", "join_table",
  "join_condition", "where", "condition_list", "condition", "membershipOp",
  "non_subquery", "comOp", "subquery", "subquery_start", "group",
  "group_list", "order", "order_list", "order_col", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-172)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -172,     1,  -172,    47,    30,    -1,   -52,    13,    48,    18,
      15,    -4,    64,    68,    71,    82,    87,    43,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,    91,  -172,    11,    49,    83,
      50,    51,  -172,  -172,  -172,  -172,  -172,  -172,  -172,    76,
    -172,  -172,  -172,  -172,    85,   -24,  -172,    96,  -172,   111,
     118,  -172,    55,    56,    79,  -172,  -172,  -172,  -172,  -172,
      80,  -172,   102,    84,    59,   125,   128,   -28,    -1,    90,
    -172,  -172,  -172,  -172,    17,   -22,  -172,  -172,    92,    93,
      67,    66,    70,    72,    94,  -172,  -172,  -172,  -172,    85,
      74,    99,   -24,   103,   119,   120,   122,    17,   143,    89,
     108,    77,   124,   127,    86,  -172,  -172,    16,  -172,    88,
     -15,  -172,  -172,    23,   126,  -172,  -172,   110,    41,  -172,
      23,   140,  -172,  -172,  -172,  -172,     2,    70,   132,    95,
     134,   149,    74,    93,   135,   136,   122,   157,    17,  -172,
     129,   100,  -172,  -172,  -172,  -172,  -172,  -172,  -172,    17,
    -172,    17,    93,   101,    98,   130,  -172,  -172,   124,   163,
     144,   104,   105,    16,   131,  -172,    23,   146,   126,  -172,
     110,  -172,  -172,   -24,  -172,   151,   -24,  -172,   172,   173,
    -172,   153,  -172,  -172,  -172,   112,   154,   144,   137,  -172,
     133,   138,   136,  -172,  -172,  -172,   164,  -172,  -172,    75,
     144,   179,   160,    17,  -172,   121,   139,  -172,  -172,   162,
    -172,  -172,  -172,   184,   110,   165,   121,  -172,  -172,  -172,
     121,  -172,    -7,   167,   165,  -172,  -172,   121,  -172,  -172,
     167,  -172
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
       0,     0,    79,    80,    81,    82,    58,    54,    55,    83,
      56,    57,    67,    71,    63,    65,    66,     0,    70,     0,
       0,    23,     0,     0,     0,    24,    25,    26,    22,    21,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
      72,    73,    75,    74,     0,     0,    29,    28,     0,    92,
       0,     0,     0,     0,     0,    27,    34,    84,    68,    63,
       0,    83,    69,    83,     0,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,    64,    87,    85,    88,     0,
       0,    77,    76,     0,    49,   103,   102,    94,     0,    59,
       0,     0,    41,    42,    44,    43,    45,     0,     0,     0,
       0,     0,     0,    92,     0,    52,     0,     0,     0,    93,
     110,     0,   104,   105,   106,   107,   108,   109,    99,     0,
     113,   113,    92,     0,     0,     0,    47,    39,    36,     0,
      32,     0,     0,    85,   114,    78,     0,     0,    49,    48,
      94,   111,   100,   101,    98,     0,    96,    97,     0,     0,
      40,     0,    46,    37,    35,     0,     0,    32,    90,    86,
       0,   118,    52,    51,    50,    95,     0,    60,   125,    45,
      32,     0,     0,     0,    89,     0,     0,    62,    53,     0,
      38,    33,    30,     0,    94,   116,     0,   112,    31,    91,
       0,   115,   122,   120,   116,   124,   123,     0,   119,   117,
     120,   121
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -160,  -172,  -172,    25,    57,  -172,  -172,
     -14,  -172,    19,    52,    -6,    -3,  -172,  -172,  -172,    -2,
     106,   123,   115,   -47,  -172,  -172,    -5,    27,    60,  -172,
    -172,  -130,  -171,  -141,  -172,  -145,  -172,    42,  -172,  -172,
     -27,  -172,   -34,   -29,  -172
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   196,    29,    30,   138,   112,   191,   136,
     167,    31,   147,   124,   177,   125,    32,    33,    34,    35,
      79,    54,    55,   159,    56,    57,   126,   143,   117,   118,
     214,   108,   149,   127,   160,   128,   161,   184,   185,   201,
     231,   217,   238,   233,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      58,     2,    53,    42,    43,    44,    45,   180,    84,   205,
     235,     3,     4,   174,   183,    59,   186,     5,     6,     7,
       8,     9,    10,    11,   141,   164,    60,    12,    13,    14,
      80,    81,   188,    82,    15,    16,    46,   212,   165,    97,
     166,   142,    40,    98,    41,   103,   236,    83,    17,   104,
     221,    61,    97,   229,    46,    84,   144,    63,    62,    37,
      46,    38,    39,    64,    47,    48,    49,    65,    50,    51,
      52,    66,   224,    58,    67,    53,   150,   151,    72,    58,
     105,    53,    47,    48,   101,    68,    50,    51,    47,    48,
      69,    70,    50,    51,    71,    80,    81,    74,    82,   152,
     153,   154,   155,   156,   157,   158,   132,   133,   134,   135,
      78,   165,    83,   166,    86,    77,    73,    75,    76,    85,
     145,    87,    88,    89,    90,    92,    94,   162,    95,    91,
      93,    96,   100,   106,   109,   110,   107,   111,   119,   113,
     114,   116,   120,   121,   122,   123,   129,   130,   131,   137,
     139,   146,   163,   140,   148,    97,   169,   171,   172,   175,
     179,   176,   170,   190,   182,   181,   194,   192,   189,   195,
     203,   197,   198,   202,   206,   207,   208,   209,   211,   210,
       5,   200,   222,   213,   223,   215,   227,   228,   101,   216,
     230,   226,   237,   193,   168,   220,   218,   204,   178,   102,
     199,    99,   173,   187,   219,   115,   241,   239,   240,     0,
     225,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   232,     0,     0,     0,   234,     0,     0,     0,     0,
       0,     0,   232
};

static const yytype_int16 yycheck[] =
{
       5,     0,     5,     4,     5,     6,     7,   148,    55,   180,
      17,    10,    11,   143,   159,    67,   161,    16,    17,    18,
      19,    20,    21,    22,     8,    23,    13,    26,    27,    28,
      54,    55,   162,    57,    33,    34,    37,   197,    36,    67,
      38,    25,    12,    71,    14,    67,    53,    71,    47,    71,
     210,     3,    67,   224,    37,   102,    71,    42,    40,    12,
      37,    14,    15,    67,    65,    66,    67,     3,    69,    70,
      71,     3,   213,    78,     3,    78,    35,    36,    67,    84,
      85,    84,    65,    66,    67,     3,    69,    70,    65,    66,
       3,    48,    69,    70,     3,    54,    55,    14,    57,    58,
      59,    60,    61,    62,    63,    64,    29,    30,    31,    32,
      25,    36,    71,    38,     3,    39,    67,    67,    67,    23,
     123,     3,    67,    67,    45,    23,    67,   130,     3,    49,
      46,     3,    42,    41,    67,    69,    43,    67,    39,    67,
      46,    67,    39,    24,    24,    23,     3,    58,    40,    25,
      23,    25,    12,    67,    44,    67,    24,    23,     9,    24,
       3,    25,    67,    65,    64,    36,     3,    37,    67,    25,
      24,    67,    67,   176,    23,     3,     3,    24,    24,    67,
      16,    50,     3,    46,    24,    52,    24,     3,    67,    51,
      25,    52,    25,   168,   137,   209,   202,   178,   146,    84,
     173,    78,   142,   161,   206,    99,   240,   234,   237,    -1,
     215,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   226,    -1,    -1,    -1,   230,    -1,    -1,    -1,    -1,
      -1,    -1,   237
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    74,     0,    10,    11,    16,    17,    18,    19,    20,
      21,    22,    26,    27,    28,    33,    34,    47,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    87,
      88,    94,    99,   100,   101,   102,   127,    12,    14,    15,
      12,    14,     4,     5,     6,     7,    37,    65,    66,    67,
      69,    70,    71,    98,   104,   105,   107,   108,   109,    67,
      13,     3,    40,    42,    67,     3,     3,     3,     3,     3,
      48,     3,    67,    67,    14,    67,    67,    39,    25,   103,
      54,    55,    57,    71,   106,    23,     3,     3,    67,    67,
      45,    49,    23,    46,    67,     3,     3,    67,    71,   104,
      42,    67,   105,    67,    71,   109,    41,    43,   114,    67,
      69,    67,    90,    67,    46,   103,    67,   111,   112,    39,
      39,    24,    24,    23,    96,    98,   109,   116,   118,     3,
      58,    40,    29,    30,    31,    32,    92,    25,    89,    23,
      67,     8,    25,   110,    71,    98,    25,    95,    44,   115,
      35,    36,    58,    59,    60,    61,    62,    63,    64,   106,
     117,   119,    98,    12,    23,    36,    38,    93,    90,    24,
      67,    23,     9,   111,   114,    24,    25,    97,    96,     3,
     116,    36,    64,   118,   120,   121,   118,   120,   114,    67,
      65,    91,    37,    89,     3,    25,    86,    67,    67,   110,
      50,   122,    98,    24,    95,   115,    23,     3,     3,    24,
      67,    24,    86,    46,   113,    52,    51,   124,    97,   102,
      93,    86,     3,    24,   116,   109,    52,    24,     3,   115,
      25,   123,   109,   126,   109,    17,    53,    25,   125,   123,
     126,   125
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    73,    74,    74,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    85,    86,    86,    87,    88,    89,    89,    90,    90,
      91,    92,    92,    92,    92,    93,    93,    93,    94,    95,
      95,    96,    97,    97,    98,    98,    98,    98,    98,    99,
     100,   101,   102,   103,   103,   104,   104,   104,   104,   105,
     105,   105,   106,   106,   106,   106,   107,   107,   107,   108,
     108,   108,   108,   109,   109,   110,   110,   111,   111,   112,
     113,   113,   114,   114,   115,   115,   116,   116,   116,   117,
     117,   118,   118,   118,   119,   119,   119,   119,   119,   119,
     119,   119,   120,   121,   122,   122,   123,   123,   124,   124,
     125,   125,   126,   126,   126,   127
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
       8,     2,     9,     0,     3,     1,     1,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     4,     4,     6,     1,
       1,     1,     1,     1,     3,     0,     3,     1,     1,     5,
       0,     3,     0,     3,     0,     3,     3,     3,     3,     1,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     4,     0,     0,     4,     0,     3,     0,     4,
       0,     3,     1,     2,     2,     8
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
#line 232 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1459 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 237 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1467 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 242 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1475 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 248 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1483 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 254 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1491 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 260 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1499 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 266 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1508 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 272 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1516 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 278 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1525 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID attr_list RBRACE SEMICOLON  */
#line 286 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
		}
#line 1535 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID attr_list RBRACE SEMICOLON  */
#line 292 "yacc_sql.y"
                {	// 由于只用支持UNIQUE，采用最简单写法
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_unique_index";
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
		}
#line 1545 "yacc_sql.tab.c"
    break;

  case 33: /* attr_list: COMMA ID attr_list  */
#line 301 "yacc_sql.y"
                             {
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1553 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 306 "yacc_sql.y"
                             {
		CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
		drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
	}
#line 1562 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 313 "yacc_sql.y"
                                                                   {
		CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
		create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
	}
#line 1571 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 320 "yacc_sql.y"
                                   {    }
#line 1577 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID type LBRACE number RBRACE is_nullable  */
#line 324 "yacc_sql.y"
                                            {
		AttrInfo attribute;
		attr_info_init(&attribute, (yyvsp[-5].string), (yyvsp[-4].number), (yyvsp[-2].number), (yyvsp[0].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
#line 1587 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID type is_nullable  */
#line 329 "yacc_sql.y"
                         {
		AttrInfo attribute;
		attr_info_init(&attribute, (yyvsp[-2].string), (yyvsp[-1].number), (yyvsp[-1].number) == DATES ? 8 : 4, (yyvsp[0].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
#line 1597 "yacc_sql.tab.c"
    break;

  case 40: /* number: NUMBER  */
#line 337 "yacc_sql.y"
               {(yyval.number) = (yyvsp[0].number);}
#line 1603 "yacc_sql.tab.c"
    break;

  case 41: /* type: INT_T  */
#line 341 "yacc_sql.y"
                   { (yyval.number)=INTS; }
#line 1609 "yacc_sql.tab.c"
    break;

  case 42: /* type: STRING_T  */
#line 342 "yacc_sql.y"
                   { (yyval.number)=CHARS; }
#line 1615 "yacc_sql.tab.c"
    break;

  case 43: /* type: FLOAT_T  */
#line 343 "yacc_sql.y"
                   { (yyval.number)=FLOATS; }
#line 1621 "yacc_sql.tab.c"
    break;

  case 44: /* type: DATE_T  */
#line 344 "yacc_sql.y"
                   { (yyval.number)=DATES; }
#line 1627 "yacc_sql.tab.c"
    break;

  case 45: /* is_nullable: %empty  */
#line 348 "yacc_sql.y"
                    { (yyval.number) = 0; }
#line 1633 "yacc_sql.tab.c"
    break;

  case 46: /* is_nullable: NOT NULL_T  */
#line 349 "yacc_sql.y"
                    { (yyval.number) = 0; }
#line 1639 "yacc_sql.tab.c"
    break;

  case 47: /* is_nullable: NULLABLE  */
#line 350 "yacc_sql.y"
                    { (yyval.number) = 1; }
#line 1645 "yacc_sql.tab.c"
    break;

  case 48: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 354 "yacc_sql.y"
                                                         {
		CONTEXT->ssql->flag=SCF_INSERT;
		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
	}
#line 1654 "yacc_sql.tab.c"
    break;

  case 50: /* tuple_list: COMMA tuple tuple_list  */
#line 362 "yacc_sql.y"
        {	/* do nothing here */	}
#line 1660 "yacc_sql.tab.c"
    break;

  case 51: /* tuple: LBRACE value value_list RBRACE  */
#line 365 "yacc_sql.y"
                                       {
		// 由于tuple这种语法[形如(v1, v2, ..., vn)]只在insert中使用
		insert_tuple_init(&CONTEXT->ssql->sstr.insertion, TOP->values, TOP->value_length);
		// 清空CONTEXT临时变量
		TOP->value_length = 0;
	}
#line 1671 "yacc_sql.tab.c"
    break;

  case 53: /* value_list: COMMA value value_list  */
#line 374 "yacc_sql.y"
                              {}
#line 1677 "yacc_sql.tab.c"
    break;

  case 54: /* value: NUMBER  */
#line 377 "yacc_sql.y"
          {	
  		value_init_integer(&TOP->values[TOP->value_length++], (yyvsp[0].number));
	}
#line 1685 "yacc_sql.tab.c"
    break;

  case 55: /* value: FLOAT  */
#line 380 "yacc_sql.y"
           {
  		value_init_float(&TOP->values[TOP->value_length++], (yyvsp[0].floats));
	}
#line 1693 "yacc_sql.tab.c"
    break;

  case 56: /* value: SSS  */
#line 383 "yacc_sql.y"
          {
  		value_init_string(&TOP->values[TOP->value_length++], (yyvsp[0].string));
	}
#line 1701 "yacc_sql.tab.c"
    break;

  case 57: /* value: DATE  */
#line 386 "yacc_sql.y"
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
#line 1722 "yacc_sql.tab.c"
    break;

  case 58: /* value: NULL_T  */
#line 402 "yacc_sql.y"
                 {
		value_init_null(&TOP->values[TOP->value_length++]);
	}
#line 1730 "yacc_sql.tab.c"
    break;

  case 59: /* delete: DELETE FROM ID where SEMICOLON  */
#line 408 "yacc_sql.y"
                                   {
		CONTEXT->ssql->flag = SCF_DELETE;//"delete";
		deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
		deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, TOP->conditions, TOP->condition_length);
		
		// CONTEXT临时变量清零
		TOP->condition_length = 0;	
    }
#line 1743 "yacc_sql.tab.c"
    break;

  case 60: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 418 "yacc_sql.y"
                                              {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		Value *value = &TOP->values[0];
		updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, TOP->conditions, TOP->condition_length);
		
		// CONTEXT临时变量清零
		TOP->condition_length = 0;
	}
#line 1756 "yacc_sql.tab.c"
    break;

  case 61: /* selects: select SEMICOLON  */
#line 428 "yacc_sql.y"
                     {
		CONTEXT->ssql->flag = SCF_SELECT; //"select";
	}
#line 1764 "yacc_sql.tab.c"
    break;

  case 62: /* select: SELECT select_expr select_expr_list FROM table_ref table_ref_list where group order  */
#line 433 "yacc_sql.y"
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
#line 1790 "yacc_sql.tab.c"
    break;

  case 64: /* select_expr_list: COMMA select_expr select_expr_list  */
#line 459 "yacc_sql.y"
                                             {
		// append select_expr $2
		selects_append_expr(&TOP->ssql->sstr.selection, (yyvsp[-1].sexpr));
	}
#line 1799 "yacc_sql.tab.c"
    break;

  case 65: /* select_expr: select_arith_expr  */
#line 466 "yacc_sql.y"
                          { (yyval.sexpr) = (yyvsp[0].sexpr); }
#line 1805 "yacc_sql.tab.c"
    break;

  case 66: /* select_expr: select_func  */
#line 467 "yacc_sql.y"
                      { (yyval.sexpr) = (yyvsp[0].sexpr); }
#line 1811 "yacc_sql.tab.c"
    break;

  case 67: /* select_expr: STAR  */
#line 468 "yacc_sql.y"
               { 
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, NULL, "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), attr);
	}
#line 1822 "yacc_sql.tab.c"
    break;

  case 68: /* select_expr: ID DOT STAR  */
#line 474 "yacc_sql.y"
                      {
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, (yyvsp[-2].string), "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), attr);
	}
#line 1833 "yacc_sql.tab.c"
    break;

  case 69: /* select_arith_expr: select_arith_expr arithOp select_arith_expr  */
#line 487 "yacc_sql.y"
                                                    {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), (yyvsp[-1].number));
	}
#line 1842 "yacc_sql.tab.c"
    break;

  case 70: /* select_arith_expr: col  */
#line 491 "yacc_sql.y"
              {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), (yyvsp[0].attr));
	}
#line 1851 "yacc_sql.tab.c"
    break;

  case 71: /* select_arith_expr: value  */
#line 495 "yacc_sql.y"
                { 
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_value_init((yyval.sexpr), &TOP->values[TOP->value_length - 1]);	

		// 释放临时变量
		TOP->value_length --;
	}
#line 1863 "yacc_sql.tab.c"
    break;

  case 72: /* arithOp: ADD_OP  */
#line 505 "yacc_sql.y"
                 { (yyval.number) = ADD; }
#line 1869 "yacc_sql.tab.c"
    break;

  case 73: /* arithOp: SUB_OP  */
#line 506 "yacc_sql.y"
                 { (yyval.number) = SUB; }
#line 1875 "yacc_sql.tab.c"
    break;

  case 74: /* arithOp: STAR  */
#line 507 "yacc_sql.y"
                 { (yyval.number) = MUL; }
#line 1881 "yacc_sql.tab.c"
    break;

  case 75: /* arithOp: DIV_OP  */
#line 508 "yacc_sql.y"
                 { (yyval.number) = DIV; }
#line 1887 "yacc_sql.tab.c"
    break;

  case 76: /* select_func: aggregate_func LBRACE col RBRACE  */
#line 512 "yacc_sql.y"
                                         {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		aggregate_function_init((yyval.sexpr), (yyvsp[-3].number), (yyvsp[-1].attr));
	}
#line 1896 "yacc_sql.tab.c"
    break;

  case 77: /* select_func: aggregate_func LBRACE STAR RBRACE  */
#line 516 "yacc_sql.y"
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
#line 1911 "yacc_sql.tab.c"
    break;

  case 78: /* select_func: aggregate_func LBRACE ID DOT STAR RBRACE  */
#line 526 "yacc_sql.y"
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
#line 1926 "yacc_sql.tab.c"
    break;

  case 79: /* aggregate_func: MAX_F  */
#line 539 "yacc_sql.y"
                  { (yyval.number) = MAX_FUNC;   }
#line 1932 "yacc_sql.tab.c"
    break;

  case 80: /* aggregate_func: MIN_F  */
#line 540 "yacc_sql.y"
                  { (yyval.number) = MIN_FUNC;   }
#line 1938 "yacc_sql.tab.c"
    break;

  case 81: /* aggregate_func: COUNT_F  */
#line 541 "yacc_sql.y"
                  { (yyval.number) = COUNT_FUNC; }
#line 1944 "yacc_sql.tab.c"
    break;

  case 82: /* aggregate_func: AVG_F  */
#line 542 "yacc_sql.y"
                  { (yyval.number) = AVG_FUNC;   }
#line 1950 "yacc_sql.tab.c"
    break;

  case 83: /* col: ID  */
#line 546 "yacc_sql.y"
           {
		(yyval.attr) = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init((yyval.attr), NULL, (yyvsp[0].string));
	}
#line 1959 "yacc_sql.tab.c"
    break;

  case 84: /* col: ID DOT ID  */
#line 550 "yacc_sql.y"
                    {
		(yyval.attr) = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init((yyval.attr), (yyvsp[-2].string), (yyvsp[0].string));
	}
#line 1968 "yacc_sql.tab.c"
    break;

  case 86: /* table_ref_list: COMMA table_ref table_ref_list  */
#line 559 "yacc_sql.y"
                                     {	
		selects_append_relation(&TOP->ssql->sstr.selection, (yyvsp[-1].ref));
	}
#line 1976 "yacc_sql.tab.c"
    break;

  case 87: /* table_ref: ID  */
#line 565 "yacc_sql.y"
           { 
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 0, (yyvsp[0].string), NULL, NULL, 0); 
		(yyval.ref) = ref;
	}
#line 1986 "yacc_sql.tab.c"
    break;

  case 88: /* table_ref: join_table  */
#line 570 "yacc_sql.y"
                     { (yyval.ref) = (yyvsp[0].ref); }
#line 1992 "yacc_sql.tab.c"
    break;

  case 89: /* join_table: table_ref INNER JOIN ID join_condition  */
#line 574 "yacc_sql.y"
                                               {
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 1, (yyvsp[-1].string), (yyvsp[-4].ref), TOP->conditions, TOP->condition_length);
		(yyval.ref) = ref;
		// 临时变量清零
		TOP->condition_length = 0;
	}
#line 2004 "yacc_sql.tab.c"
    break;

  case 91: /* join_condition: ON condition condition_list  */
#line 585 "yacc_sql.y"
                                      {}
#line 2010 "yacc_sql.tab.c"
    break;

  case 93: /* where: WHERE condition condition_list  */
#line 591 "yacc_sql.y"
                                     {}
#line 2016 "yacc_sql.tab.c"
    break;

  case 95: /* condition_list: AND condition condition_list  */
#line 597 "yacc_sql.y"
                                   {}
#line 2022 "yacc_sql.tab.c"
    break;

  case 96: /* condition: non_subquery comOp non_subquery  */
#line 601 "yacc_sql.y"
                                        {
		non_subquery_cond_init(&TOP->conditions[TOP->condition_length++], (yyvsp[-2].cexpr), (yyvsp[0].cexpr), (yyvsp[-1].number));
	}
#line 2030 "yacc_sql.tab.c"
    break;

  case 97: /* condition: non_subquery comOp subquery  */
#line 604 "yacc_sql.y"
                                      {
		com_subquery_init(&TOP->conditions[TOP->condition_length++], (yyvsp[-2].cexpr), (yyvsp[0].select), (yyvsp[-1].number));
	}
#line 2038 "yacc_sql.tab.c"
    break;

  case 98: /* condition: non_subquery membershipOp subquery  */
#line 607 "yacc_sql.y"
                                             {
		membership_subquery_init(&TOP->conditions[TOP->condition_length++], (yyvsp[-2].cexpr), (yyvsp[0].select), (yyvsp[-1].number));
	}
#line 2046 "yacc_sql.tab.c"
    break;

  case 99: /* membershipOp: IN  */
#line 613 "yacc_sql.y"
           { (yyval.number) = MEM_IN; }
#line 2052 "yacc_sql.tab.c"
    break;

  case 100: /* membershipOp: NOT IN  */
#line 614 "yacc_sql.y"
                 { (yyval.number) = MEM_NOT_IN; }
#line 2058 "yacc_sql.tab.c"
    break;

  case 101: /* non_subquery: non_subquery arithOp non_subquery  */
#line 617 "yacc_sql.y"
                                          {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), (yyvsp[-1].number));
	}
#line 2067 "yacc_sql.tab.c"
    break;

  case 102: /* non_subquery: col  */
#line 621 "yacc_sql.y"
              {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_attr_init((yyval.cexpr), (yyvsp[0].attr));
	}
#line 2076 "yacc_sql.tab.c"
    break;

  case 103: /* non_subquery: value  */
#line 625 "yacc_sql.y"
                {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_value_init((yyval.cexpr), &TOP->values[TOP->value_length - 1]);	

		// 释放临时变量
		TOP->value_length --;
	}
#line 2088 "yacc_sql.tab.c"
    break;

  case 104: /* comOp: EQ  */
#line 635 "yacc_sql.y"
                        { (yyval.number) = EQUAL_TO; }
#line 2094 "yacc_sql.tab.c"
    break;

  case 105: /* comOp: LT  */
#line 636 "yacc_sql.y"
                        { (yyval.number) = LESS_THAN; }
#line 2100 "yacc_sql.tab.c"
    break;

  case 106: /* comOp: GT  */
#line 637 "yacc_sql.y"
                        { (yyval.number) = GREAT_THAN; }
#line 2106 "yacc_sql.tab.c"
    break;

  case 107: /* comOp: LE  */
#line 638 "yacc_sql.y"
                        { (yyval.number) = LESS_EQUAL; }
#line 2112 "yacc_sql.tab.c"
    break;

  case 108: /* comOp: GE  */
#line 639 "yacc_sql.y"
                        { (yyval.number) = GREAT_EQUAL; }
#line 2118 "yacc_sql.tab.c"
    break;

  case 109: /* comOp: NE  */
#line 640 "yacc_sql.y"
                        { (yyval.number) = NOT_EQUAL; }
#line 2124 "yacc_sql.tab.c"
    break;

  case 110: /* comOp: IS  */
#line 641 "yacc_sql.y"
                        { (yyval.number) = OP_IS; }
#line 2130 "yacc_sql.tab.c"
    break;

  case 111: /* comOp: IS NOT  */
#line 642 "yacc_sql.y"
                        { (yyval.number) = OP_IS_NOT; }
#line 2136 "yacc_sql.tab.c"
    break;

  case 112: /* subquery: subquery_start LBRACE select RBRACE  */
#line 646 "yacc_sql.y"
                                            {
		(yyval.select) = (yyvsp[-1].select);
		POP;
	}
#line 2145 "yacc_sql.tab.c"
    break;

  case 113: /* subquery_start: %empty  */
#line 651 "yacc_sql.y"
                {
	PUSH;
	TOP->ssql = (Query *)malloc(sizeof(Query));
}
#line 2154 "yacc_sql.tab.c"
    break;

  case 115: /* group: GROUP BY col group_list  */
#line 659 "yacc_sql.y"
                                  {
		selects_append_group(&TOP->ssql->sstr.selection, (yyvsp[-1].attr));
	}
#line 2162 "yacc_sql.tab.c"
    break;

  case 117: /* group_list: COMMA col group_list  */
#line 666 "yacc_sql.y"
                               {
		selects_append_group(&TOP->ssql->sstr.selection, (yyvsp[-1].attr));
	}
#line 2170 "yacc_sql.tab.c"
    break;

  case 119: /* order: ORDER BY order_col order_list  */
#line 674 "yacc_sql.y"
                                        {
		selects_append_order(&TOP->ssql->sstr.selection, (yyvsp[-1].ocol));
	}
#line 2178 "yacc_sql.tab.c"
    break;

  case 121: /* order_list: COMMA order_col order_list  */
#line 681 "yacc_sql.y"
                                     {
		selects_append_order(&TOP->ssql->sstr.selection, (yyvsp[-1].ocol));
	}
#line 2186 "yacc_sql.tab.c"
    break;

  case 122: /* order_col: col  */
#line 687 "yacc_sql.y"
            {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[0].attr), 1);
	}
#line 2195 "yacc_sql.tab.c"
    break;

  case 123: /* order_col: col ASC  */
#line 691 "yacc_sql.y"
                  {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[-1].attr), 1);
	}
#line 2204 "yacc_sql.tab.c"
    break;

  case 124: /* order_col: col DESC  */
#line 695 "yacc_sql.y"
                   {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[-1].attr), 0);
	}
#line 2213 "yacc_sql.tab.c"
    break;

  case 125: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 703 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2222 "yacc_sql.tab.c"
    break;


#line 2226 "yacc_sql.tab.c"

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

#line 708 "yacc_sql.y"

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
