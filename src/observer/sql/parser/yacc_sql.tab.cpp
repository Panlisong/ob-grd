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

typedef struct ParserContext {
  Query *ssql;
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


#line 104 "yacc_sql.tab.cpp"

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
  YYSYMBOL_group_by_list = 121,            /* group_by_list  */
  YYSYMBOL_order = 122,                    /* order  */
  YYSYMBOL_order_col_list = 123,           /* order_col_list  */
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
#define YYLAST   271

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  257

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
       0,   190,   190,   192,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   216,   221,   226,   232,   238,   244,   250,   256,   262,
     269,   275,   283,   285,   290,   297,   302,   304,   308,   314,
     323,   327,   328,   329,   330,   331,   335,   336,   337,   341,
     346,   348,   352,   358,   360,   365,   369,   373,   377,   394,
     401,   408,   414,   419,   447,   450,   458,   459,   460,   466,
     479,   483,   487,   491,   495,   499,   503,   510,   515,   526,
     540,   541,   542,   543,   547,   551,   560,   563,   570,   575,
     579,   588,   591,   600,   603,   612,   615,   622,   627,   632,
     640,   641,   644,   648,   652,   656,   660,   664,   668,   674,
     675,   676,   677,   678,   679,   680,   681,   685,   692,   695,
     703,   706,   715,   718,   726,   729,   736,   740,   744,   751
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
  "value", "delete", "update", "selects", "select", "select_expr_list",
  "select_expr", "select_arith_expr", "select_func", "aggregate_func",
  "col", "table_ref_list", "table_ref", "join_table", "join_condition",
  "where", "condition_list", "condition", "membershipOp", "non_subquery",
  "comOp", "subquery", "group", "group_by_list", "order", "order_col_list",
  "order_col", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-200)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -200,    84,  -200,    11,   101,    -1,   -51,    59,    74,    49,
      48,    30,    95,   104,   114,   118,   130,    82,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,   131,  -200,    77,    83,   140,
      97,    98,  -200,  -200,  -200,  -200,   -14,  -200,  -200,  -200,
     122,  -200,  -200,  -200,  -200,   141,   -36,  -200,   145,  -200,
     166,   167,  -200,   105,   106,   125,  -200,  -200,  -200,  -200,
    -200,   134,  -200,   162,   139,   120,   185,   188,   152,    92,
      -4,    -1,   150,   -14,   -14,   -14,   -14,     4,  -200,  -200,
     153,   154,   127,   132,   129,   133,   155,  -200,  -200,   136,
    -200,  -200,  -200,   141,   137,   -40,   -40,  -200,  -200,   157,
     175,   181,   183,    70,   204,   151,   169,   128,   186,   189,
     146,  -200,  -200,     3,  -200,    25,  -200,  -200,   -20,   190,
      70,  -200,  -200,   163,   119,  -200,   -20,   202,  -200,  -200,
    -200,  -200,  -200,    86,   129,   192,   156,   194,   209,   137,
     154,   195,   196,   183,   217,    96,    70,  -200,   187,   158,
      70,    70,    70,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
      70,   205,    76,   154,   160,   164,   193,  -200,  -200,   186,
     222,   207,   168,   171,     3,   179,  -200,   -20,   210,   190,
    -200,  -200,   163,  -200,  -200,   -28,   -28,  -200,  -200,   220,
    -200,    -8,   -17,  -200,   230,   236,  -200,   218,  -200,  -200,
    -200,   174,   219,   207,   197,  -200,   198,   200,   196,  -200,
    -200,  -200,   221,  -200,  -200,    85,   207,   243,   224,    70,
    -200,   182,   201,  -200,  -200,  -200,  -200,  -200,  -200,   247,
     163,   228,   182,  -200,  -200,   182,  -200,    -7,   231,   228,
    -200,  -200,   182,  -200,  -200,   231,  -200
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,     0,    18,     0,     0,     0,
       0,     0,    80,    81,    82,    83,     0,    59,    55,    56,
      84,    57,    58,    68,    75,    64,    66,    67,     0,    74,
       0,     0,    23,     0,     0,     0,    24,    25,    26,    22,
      21,     0,    62,     0,     0,     0,     0,     0,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,    28,
       0,    93,     0,     0,     0,     0,     0,    27,    34,     0,
      76,    85,    69,    64,     0,    70,    71,    73,    72,    84,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,    65,    88,    86,    89,     0,    78,    77,     0,    50,
       0,   107,   106,    95,     0,    60,     0,     0,    41,    42,
      44,    43,    45,    46,     0,     0,     0,     0,     0,     0,
      93,     0,    53,     0,     0,     0,     0,    94,   115,     0,
       0,     0,     0,   109,   110,   111,   112,   113,   114,   100,
       0,     0,     0,    93,     0,     0,     0,    48,    39,    36,
       0,    32,     0,     0,    86,   118,    79,     0,     0,    50,
      49,   108,    95,   116,   101,   102,   103,   105,   104,     0,
      99,     0,    97,    98,     0,     0,    40,     0,    47,    37,
      35,     0,     0,    32,    91,    87,     0,   122,    53,    52,
      51,    96,     0,    61,   129,    46,    32,     0,     0,     0,
      90,     0,     0,    63,    54,   117,    38,    33,    30,     0,
      95,   120,     0,    31,    92,     0,   119,   126,   124,   120,
     128,   127,     0,   123,   121,   124,   125
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -199,  -200,  -200,    78,   111,  -200,  -200,
      33,  -200,    71,   108,    41,     2,  -200,  -200,  -200,   261,
     161,   184,    43,  -200,  -200,    -5,    79,   117,  -200,  -200,
    -137,  -180,  -155,  -200,  -128,  -200,    99,  -200,    18,  -200,
      13,    17,  -200
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   212,    29,    30,   145,   118,   207,   143,
     178,    31,   154,   129,   188,   131,    32,    33,    34,   222,
      82,    55,    56,    57,    58,   132,   150,   123,   124,   230,
     114,   157,   133,   171,   134,   172,   200,   217,   246,   233,
     253,   248,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      59,   192,   155,    42,    43,    44,    45,    54,     5,    46,
     250,   148,   221,   185,   228,   130,    60,    85,    47,    83,
      84,    85,    46,    37,    47,    38,    39,   237,   149,   162,
      47,    86,   195,   196,   197,    86,   204,    47,   160,   161,
     162,    59,   198,   170,   202,    48,    49,   251,    54,    51,
      52,    48,    49,    78,   170,    51,    52,    48,    49,    78,
     244,    51,    52,   101,    48,    49,    50,   102,    51,    52,
      53,   109,    61,   155,   240,   110,    59,    62,    59,    59,
      59,    59,   111,    54,     2,    54,    54,    54,    54,    79,
      63,    64,   101,   130,     3,     4,   151,    65,    66,   201,
       5,     6,     7,     8,     9,    10,    11,    67,    47,   175,
      12,    13,    14,    40,    47,    41,   100,    68,    15,    16,
     191,    69,   176,   176,   177,   177,   105,   106,   107,   108,
     152,    71,    17,    70,    72,    48,    49,    78,   173,    51,
      52,    48,    49,    78,    73,    51,    52,    83,    84,    85,
      74,   160,   161,   162,    75,   158,   159,   138,   139,   140,
     141,   142,    80,    86,    76,    77,    81,   170,    87,    88,
      89,    92,    90,    91,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,    93,    94,    95,    96,    97,   218,
     170,    98,    99,   104,   115,   112,   117,   125,   113,   126,
     119,   116,   120,   101,   122,   127,   128,   135,   156,   136,
     137,   144,   146,   147,   174,   153,   180,   182,   183,   186,
     190,   187,   194,   181,   193,   210,   241,   205,   199,   206,
     216,   208,   211,   223,   219,   213,     5,   247,   214,   224,
     249,   226,   225,   227,   229,   235,   238,   247,   239,    78,
     243,   231,   232,   245,   242,   179,   252,   209,   236,   234,
     220,   189,    35,   215,   121,   103,   184,   254,   256,   255,
       0,   203
};

static const yytype_int16 yycheck[] =
{
       5,   156,   130,     4,     5,     6,     7,     5,    16,    23,
      17,     8,   192,   150,   213,    23,    67,    57,    38,    55,
      56,    57,    23,    12,    38,    14,    15,   226,    25,    57,
      38,    71,   160,   161,   162,    71,   173,    38,    55,    56,
      57,    46,   170,    71,   172,    65,    66,    54,    46,    69,
      70,    65,    66,    67,    71,    69,    70,    65,    66,    67,
     240,    69,    70,    67,    65,    66,    67,    71,    69,    70,
      71,    67,    13,   201,   229,    71,    81,     3,    83,    84,
      85,    86,    87,    81,     0,    83,    84,    85,    86,    46,
      41,    43,    67,    23,    10,    11,    71,    67,     3,    23,
      16,    17,    18,    19,    20,    21,    22,     3,    38,    23,
      26,    27,    28,    12,    38,    14,    24,     3,    34,    35,
      24,     3,    37,    37,    39,    39,    83,    84,    85,    86,
     128,    49,    48,     3,     3,    65,    66,    67,   136,    69,
      70,    65,    66,    67,    67,    69,    70,    55,    56,    57,
      67,    55,    56,    57,    14,    36,    37,    29,    30,    31,
      32,    33,    40,    71,    67,    67,    25,    71,    23,     3,
       3,    46,    67,    67,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    50,    23,    47,    67,     3,   187,
      71,     3,    40,    43,    67,    42,    67,    40,    44,    24,
      67,    69,    47,    67,    67,    24,    23,     3,    45,    58,
      41,    25,    23,    67,    12,    25,    24,    23,     9,    24,
       3,    25,    64,    67,    37,     3,   231,    67,    23,    65,
      51,    38,    25,     3,    24,    67,    16,   242,    67,     3,
     245,    67,    24,    24,    47,    24,     3,   252,    24,    67,
       3,    53,    52,    25,    53,   144,    25,   179,   225,   218,
     189,   153,     1,   184,   103,    81,   149,   249,   255,   252,
      -1,   172
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    74,     0,    10,    11,    16,    17,    18,    19,    20,
      21,    22,    26,    27,    28,    34,    35,    48,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    87,
      88,    94,    99,   100,   101,   102,   125,    12,    14,    15,
      12,    14,     4,     5,     6,     7,    23,    38,    65,    66,
      67,    69,    70,    71,    98,   104,   105,   106,   107,   108,
      67,    13,     3,    41,    43,    67,     3,     3,     3,     3,
       3,    49,     3,    67,    67,    14,    67,    67,    67,   105,
      40,    25,   103,    55,    56,    57,    71,    23,     3,     3,
      67,    67,    46,    50,    23,    47,    67,     3,     3,    40,
      24,    67,    71,   104,    43,   105,   105,   105,   105,    67,
      71,   108,    42,    44,   113,    67,    69,    67,    90,    67,
      47,   103,    67,   110,   111,    40,    24,    24,    23,    96,
      23,    98,   108,   115,   117,     3,    58,    41,    29,    30,
      31,    32,    33,    92,    25,    89,    23,    67,     8,    25,
     109,    71,    98,    25,    95,   117,    45,   114,    36,    37,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      71,   116,   118,    98,    12,    23,    37,    39,    93,    90,
      24,    67,    23,     9,   110,   113,    24,    25,    97,    96,
       3,    24,   115,    37,    64,   117,   117,   117,   117,    23,
     119,    23,   117,   119,   113,    67,    65,    91,    38,    89,
       3,    25,    86,    67,    67,   109,    51,   120,    98,    24,
      95,   114,   102,     3,     3,    24,    67,    24,    86,    47,
     112,    53,    52,   122,    97,    24,    93,    86,     3,    24,
     115,   108,    53,     3,   114,    25,   121,   108,   124,   108,
      17,    54,    25,   123,   121,   124,   123
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
       1,     1,     1,     1,     1,     1,     0,     2,     1,     7,
       0,     3,     4,     0,     3,     1,     1,     1,     1,     1,
       5,     8,     2,     9,     0,     3,     1,     1,     1,     3,
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
#line 216 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1412 "yacc_sql.tab.cpp"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 221 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1420 "yacc_sql.tab.cpp"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 226 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1428 "yacc_sql.tab.cpp"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 232 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1436 "yacc_sql.tab.cpp"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 238 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1444 "yacc_sql.tab.cpp"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 244 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1452 "yacc_sql.tab.cpp"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 250 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1461 "yacc_sql.tab.cpp"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 256 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1469 "yacc_sql.tab.cpp"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 262 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1478 "yacc_sql.tab.cpp"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID attr_list RBRACE SEMICOLON  */
#line 270 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
		}
#line 1488 "yacc_sql.tab.cpp"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID attr_list RBRACE SEMICOLON  */
#line 276 "yacc_sql.y"
                {	// 由于只用支持UNIQUE，采用最简单写法
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_unique_index";
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
		}
#line 1498 "yacc_sql.tab.cpp"
    break;

  case 33: /* attr_list: COMMA ID attr_list  */
#line 285 "yacc_sql.y"
                             {
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1506 "yacc_sql.tab.cpp"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 290 "yacc_sql.y"
                             {
		CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
		drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
	}
#line 1515 "yacc_sql.tab.cpp"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 297 "yacc_sql.y"
                                                                   {
		CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
		create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
	}
#line 1524 "yacc_sql.tab.cpp"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 304 "yacc_sql.y"
                                   {    }
#line 1530 "yacc_sql.tab.cpp"
    break;

  case 38: /* attr_def: ID type LBRACE number RBRACE is_nullable  */
#line 308 "yacc_sql.y"
                                            {
		AttrInfo attribute;
		AttrType type = static_cast<AttrType>((yyvsp[-4].number));
		attr_info_init(&attribute, (yyvsp[-5].string), type, (yyvsp[-2].number), (yyvsp[0].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
#line 1541 "yacc_sql.tab.cpp"
    break;

  case 39: /* attr_def: ID type is_nullable  */
#line 314 "yacc_sql.y"
                         {
		AttrInfo attribute;
		AttrType type = static_cast<AttrType>((yyvsp[-1].number));
		attr_info_init(&attribute, (yyvsp[-2].string), type, (type == DATES || type == ATTR_TEXT) ? 8 : 4, (yyvsp[0].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
#line 1552 "yacc_sql.tab.cpp"
    break;

  case 40: /* number: NUMBER  */
#line 323 "yacc_sql.y"
               {(yyval.number) = (yyvsp[0].number);}
#line 1558 "yacc_sql.tab.cpp"
    break;

  case 41: /* type: INT_T  */
#line 327 "yacc_sql.y"
                   { (yyval.number)=INTS; }
#line 1564 "yacc_sql.tab.cpp"
    break;

  case 42: /* type: STRING_T  */
#line 328 "yacc_sql.y"
                   { (yyval.number)=CHARS; }
#line 1570 "yacc_sql.tab.cpp"
    break;

  case 43: /* type: FLOAT_T  */
#line 329 "yacc_sql.y"
                   { (yyval.number)=FLOATS; }
#line 1576 "yacc_sql.tab.cpp"
    break;

  case 44: /* type: DATE_T  */
#line 330 "yacc_sql.y"
                   { (yyval.number)=DATES; }
#line 1582 "yacc_sql.tab.cpp"
    break;

  case 45: /* type: TEXT_T  */
#line 331 "yacc_sql.y"
             { (yyval.number)=ATTR_TEXT; }
#line 1588 "yacc_sql.tab.cpp"
    break;

  case 46: /* is_nullable: %empty  */
#line 335 "yacc_sql.y"
                    { (yyval.number) = 0; }
#line 1594 "yacc_sql.tab.cpp"
    break;

  case 47: /* is_nullable: NOT NULL_T  */
#line 336 "yacc_sql.y"
                    { (yyval.number) = 0; }
#line 1600 "yacc_sql.tab.cpp"
    break;

  case 48: /* is_nullable: NULLABLE  */
#line 337 "yacc_sql.y"
                    { (yyval.number) = 1; }
#line 1606 "yacc_sql.tab.cpp"
    break;

  case 49: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 341 "yacc_sql.y"
                                                         {
		CONTEXT->ssql->flag=SCF_INSERT;
		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
	}
#line 1615 "yacc_sql.tab.cpp"
    break;

  case 51: /* tuple_list: COMMA tuple tuple_list  */
#line 349 "yacc_sql.y"
        {	/* do nothing here */	}
#line 1621 "yacc_sql.tab.cpp"
    break;

  case 52: /* tuple: LBRACE value value_list RBRACE  */
#line 352 "yacc_sql.y"
                                       {
		insert_value_append(&CONTEXT->ssql->sstr.insertion, (yyvsp[-2].val));
		// tuple reduce: tuple_num ++
		(CONTEXT->ssql->sstr.insertion.tuple_num)++;
	}
#line 1631 "yacc_sql.tab.cpp"
    break;

  case 54: /* value_list: COMMA value value_list  */
#line 360 "yacc_sql.y"
                              {
		insert_value_append(&CONTEXT->ssql->sstr.insertion, (yyvsp[-1].val));
	}
#line 1639 "yacc_sql.tab.cpp"
    break;

  case 55: /* value: NUMBER  */
#line 365 "yacc_sql.y"
          {
		(yyval.val) = (Value *)malloc(sizeof(Value));	
  		value_init_integer((yyval.val), (yyvsp[0].number));
	}
#line 1648 "yacc_sql.tab.cpp"
    break;

  case 56: /* value: FLOAT  */
#line 369 "yacc_sql.y"
           {
		(yyval.val) = (Value *)malloc(sizeof(Value));	
  		value_init_float((yyval.val), (yyvsp[0].floats));
	}
#line 1657 "yacc_sql.tab.cpp"
    break;

  case 57: /* value: SSS  */
#line 373 "yacc_sql.y"
          {
		(yyval.val) = (Value *)malloc(sizeof(Value));			
  		value_init_string((yyval.val), (yyvsp[0].string));
	}
#line 1666 "yacc_sql.tab.cpp"
    break;

  case 58: /* value: DATE  */
#line 377 "yacc_sql.y"
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
			(yyval.val) = (Value *)malloc(sizeof(Value));			
			value_init_date((yyval.val), mktime(&t));
		}
	}
#line 1688 "yacc_sql.tab.cpp"
    break;

  case 59: /* value: NULL_T  */
#line 394 "yacc_sql.y"
                 {		
		(yyval.val) = (Value *)malloc(sizeof(Value));			
		value_init_null((yyval.val));
	}
#line 1697 "yacc_sql.tab.cpp"
    break;

  case 60: /* delete: DELETE FROM ID where SEMICOLON  */
#line 401 "yacc_sql.y"
                                   {
		CONTEXT->ssql->flag = SCF_DELETE;//"delete";
		deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
		deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, (yyvsp[-1].cond_list));
    }
#line 1707 "yacc_sql.tab.cpp"
    break;

  case 61: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 408 "yacc_sql.y"
                                                  {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].val), (yyvsp[-1].cond_list));
	}
#line 1716 "yacc_sql.tab.cpp"
    break;

  case 62: /* selects: select SEMICOLON  */
#line 414 "yacc_sql.y"
                     {
		CONTEXT->ssql->flag = SCF_SELECT; //"select";
		CONTEXT->ssql->sstr.selection = std::move(*(yyvsp[-1].select));
	}
#line 1725 "yacc_sql.tab.cpp"
    break;

  case 63: /* select: SELECT select_expr select_expr_list FROM table_ref table_ref_list where group order  */
#line 420 "yacc_sql.y"
        {
		(yyval.select) = (Selects *)malloc(sizeof(Selects));
		// 1. append select_expr
		SelectExprList *expr_list = (yyvsp[-6].sexpr_list);
		expr_list->push_front((yyvsp[-7].sexpr));
		(yyval.select)->exprs = expr_list;
		(yyval.select)->expr_num = expr_list->size();

		// 2. append table_ref
		TableRefList *ref_list = (yyvsp[-3].ref_list);
		ref_list->push_front((yyvsp[-4].ref));
		(yyval.select)->references = ref_list;
		(yyval.select)->ref_num = ref_list->size();

		// 3. append condtion_list(可选项，可能为空)
		selects_append_conditions((yyval.select), (yyvsp[-2].cond_list));

		// 4. append group_list(可选项，可能为空)

		// 5. append order_list(可选项，可能为空)
		
		(yyval.select)->context = new RelationTable();
	}
#line 1753 "yacc_sql.tab.cpp"
    break;

  case 64: /* select_expr_list: %empty  */
#line 447 "yacc_sql.y"
        {
		(yyval.sexpr_list) = new SelectExprList();
	}
#line 1761 "yacc_sql.tab.cpp"
    break;

  case 65: /* select_expr_list: COMMA select_expr select_expr_list  */
#line 450 "yacc_sql.y"
                                             {
		// append select_expr $2
		(yyval.sexpr_list) = (yyvsp[0].sexpr_list);
		(yyval.sexpr_list)->push_front((yyvsp[-1].sexpr));
	}
#line 1771 "yacc_sql.tab.cpp"
    break;

  case 66: /* select_expr: select_arith_expr  */
#line 458 "yacc_sql.y"
                          { (yyval.sexpr) = (yyvsp[0].sexpr); }
#line 1777 "yacc_sql.tab.cpp"
    break;

  case 67: /* select_expr: select_func  */
#line 459 "yacc_sql.y"
                      { (yyval.sexpr) = (yyvsp[0].sexpr); }
#line 1783 "yacc_sql.tab.cpp"
    break;

  case 68: /* select_expr: STAR  */
#line 460 "yacc_sql.y"
               { 
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, NULL, "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), attr);
	}
#line 1794 "yacc_sql.tab.cpp"
    break;

  case 69: /* select_expr: ID DOT STAR  */
#line 466 "yacc_sql.y"
                      {
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, (yyvsp[-2].string), "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), attr);
	}
#line 1805 "yacc_sql.tab.cpp"
    break;

  case 70: /* select_arith_expr: select_arith_expr ADD_OP select_arith_expr  */
#line 479 "yacc_sql.y"
                                                   {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), ADD);
	}
#line 1814 "yacc_sql.tab.cpp"
    break;

  case 71: /* select_arith_expr: select_arith_expr SUB_OP select_arith_expr  */
#line 483 "yacc_sql.y"
                                                     {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), SUB);
	}
#line 1823 "yacc_sql.tab.cpp"
    break;

  case 72: /* select_arith_expr: select_arith_expr STAR select_arith_expr  */
#line 487 "yacc_sql.y"
                                                   {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), MUL);
	}
#line 1832 "yacc_sql.tab.cpp"
    break;

  case 73: /* select_arith_expr: select_arith_expr DIV_OP select_arith_expr  */
#line 491 "yacc_sql.y"
                                                     {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), DIV);
	}
#line 1841 "yacc_sql.tab.cpp"
    break;

  case 74: /* select_arith_expr: col  */
#line 495 "yacc_sql.y"
              {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), (yyvsp[0].attr));
	}
#line 1850 "yacc_sql.tab.cpp"
    break;

  case 75: /* select_arith_expr: value  */
#line 499 "yacc_sql.y"
                { 
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_value_init((yyval.sexpr), (yyvsp[0].val));	
	}
#line 1859 "yacc_sql.tab.cpp"
    break;

  case 76: /* select_arith_expr: LBRACE select_arith_expr RBRACE  */
#line 503 "yacc_sql.y"
                                          {
		(yyval.sexpr) = (yyvsp[-1].sexpr);
	}
#line 1867 "yacc_sql.tab.cpp"
    break;

  case 77: /* select_func: aggregate_func LBRACE col RBRACE  */
#line 510 "yacc_sql.y"
                                         {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		FuncName func = static_cast<FuncName>((yyvsp[-3].number));
		aggregate_function_init((yyval.sexpr), func, (yyvsp[-1].attr));
	}
#line 1877 "yacc_sql.tab.cpp"
    break;

  case 78: /* select_func: aggregate_func LBRACE STAR RBRACE  */
#line 515 "yacc_sql.y"
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
#line 1893 "yacc_sql.tab.cpp"
    break;

  case 79: /* select_func: aggregate_func LBRACE ID DOT STAR RBRACE  */
#line 526 "yacc_sql.y"
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
#line 1909 "yacc_sql.tab.cpp"
    break;

  case 80: /* aggregate_func: MAX_F  */
#line 540 "yacc_sql.y"
                  { (yyval.number) = MAX_FUNC;   }
#line 1915 "yacc_sql.tab.cpp"
    break;

  case 81: /* aggregate_func: MIN_F  */
#line 541 "yacc_sql.y"
                  { (yyval.number) = MIN_FUNC;   }
#line 1921 "yacc_sql.tab.cpp"
    break;

  case 82: /* aggregate_func: COUNT_F  */
#line 542 "yacc_sql.y"
                  { (yyval.number) = COUNT_FUNC; }
#line 1927 "yacc_sql.tab.cpp"
    break;

  case 83: /* aggregate_func: AVG_F  */
#line 543 "yacc_sql.y"
                  { (yyval.number) = AVG_FUNC;   }
#line 1933 "yacc_sql.tab.cpp"
    break;

  case 84: /* col: ID  */
#line 547 "yacc_sql.y"
           {
		(yyval.attr) = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init((yyval.attr), NULL, (yyvsp[0].string));
	}
#line 1942 "yacc_sql.tab.cpp"
    break;

  case 85: /* col: ID DOT ID  */
#line 551 "yacc_sql.y"
                    {
		(yyval.attr) = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init((yyval.attr), (yyvsp[-2].string), (yyvsp[0].string));
	}
#line 1951 "yacc_sql.tab.cpp"
    break;

  case 86: /* table_ref_list: %empty  */
#line 560 "yacc_sql.y"
        {
		(yyval.ref_list) = new TableRefList();
	}
#line 1959 "yacc_sql.tab.cpp"
    break;

  case 87: /* table_ref_list: COMMA table_ref table_ref_list  */
#line 563 "yacc_sql.y"
                                                   {	
		(yyval.ref_list) = (yyvsp[0].ref_list);
		(yyval.ref_list)->push_front((yyvsp[-1].ref));
	}
#line 1968 "yacc_sql.tab.cpp"
    break;

  case 88: /* table_ref: ID  */
#line 570 "yacc_sql.y"
           { 
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 0, (yyvsp[0].string), nullptr, new ConditionList); 
		(yyval.ref) = ref;
	}
#line 1978 "yacc_sql.tab.cpp"
    break;

  case 89: /* table_ref: join_table  */
#line 575 "yacc_sql.y"
                     { (yyval.ref) = (yyvsp[0].ref); }
#line 1984 "yacc_sql.tab.cpp"
    break;

  case 90: /* join_table: table_ref INNER JOIN ID join_condition  */
#line 579 "yacc_sql.y"
                                               {
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 1, (yyvsp[-1].string), (yyvsp[-4].ref), (yyvsp[0].cond_list));
		(yyval.ref) = ref;
	}
#line 1994 "yacc_sql.tab.cpp"
    break;

  case 91: /* join_condition: %empty  */
#line 588 "yacc_sql.y"
        {
		(yyval.cond_list) = new ConditionList();
	}
#line 2002 "yacc_sql.tab.cpp"
    break;

  case 92: /* join_condition: ON condition condition_list  */
#line 591 "yacc_sql.y"
                                      {
		(yyval.cond_list) = (yyvsp[0].cond_list);
		(yyval.cond_list)->push_front(*(yyvsp[-1].cond));
	}
#line 2011 "yacc_sql.tab.cpp"
    break;

  case 93: /* where: %empty  */
#line 600 "yacc_sql.y"
        {
		(yyval.cond_list) = new ConditionList();
	}
#line 2019 "yacc_sql.tab.cpp"
    break;

  case 94: /* where: WHERE condition condition_list  */
#line 603 "yacc_sql.y"
                                     {
		(yyval.cond_list) = (yyvsp[0].cond_list);
		(yyval.cond_list)->push_front(*(yyvsp[-1].cond));
	}
#line 2028 "yacc_sql.tab.cpp"
    break;

  case 95: /* condition_list: %empty  */
#line 612 "yacc_sql.y"
        {
		(yyval.cond_list) = new ConditionList();
	}
#line 2036 "yacc_sql.tab.cpp"
    break;

  case 96: /* condition_list: AND condition condition_list  */
#line 615 "yacc_sql.y"
                                   {
		(yyval.cond_list) = (yyvsp[0].cond_list);
		(yyval.cond_list)->push_front(*(yyvsp[-1].cond));
	}
#line 2045 "yacc_sql.tab.cpp"
    break;

  case 97: /* condition: non_subquery comOp non_subquery  */
#line 622 "yacc_sql.y"
                                        {
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		non_subquery_cond_init((yyval.cond), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), op);
	}
#line 2055 "yacc_sql.tab.cpp"
    break;

  case 98: /* condition: non_subquery comOp subquery  */
#line 627 "yacc_sql.y"
                                      {
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		com_subquery_init((yyval.cond), (yyvsp[-2].cexpr), (yyvsp[0].select), op);
	}
#line 2065 "yacc_sql.tab.cpp"
    break;

  case 99: /* condition: non_subquery membershipOp subquery  */
#line 632 "yacc_sql.y"
                                             {
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		membership_subquery_init((yyval.cond), (yyvsp[-2].cexpr), (yyvsp[0].select), op);
	}
#line 2075 "yacc_sql.tab.cpp"
    break;

  case 100: /* membershipOp: IN  */
#line 640 "yacc_sql.y"
           { (yyval.number) = MEM_IN; }
#line 2081 "yacc_sql.tab.cpp"
    break;

  case 101: /* membershipOp: NOT IN  */
#line 641 "yacc_sql.y"
                 { (yyval.number) = MEM_NOT_IN; }
#line 2087 "yacc_sql.tab.cpp"
    break;

  case 102: /* non_subquery: non_subquery ADD_OP non_subquery  */
#line 644 "yacc_sql.y"
                                         {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), ADD);
	}
#line 2096 "yacc_sql.tab.cpp"
    break;

  case 103: /* non_subquery: non_subquery SUB_OP non_subquery  */
#line 648 "yacc_sql.y"
                                           {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), SUB);
	}
#line 2105 "yacc_sql.tab.cpp"
    break;

  case 104: /* non_subquery: non_subquery STAR non_subquery  */
#line 652 "yacc_sql.y"
                                         {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), MUL);
	}
#line 2114 "yacc_sql.tab.cpp"
    break;

  case 105: /* non_subquery: non_subquery DIV_OP non_subquery  */
#line 656 "yacc_sql.y"
                                           {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), DIV);
	}
#line 2123 "yacc_sql.tab.cpp"
    break;

  case 106: /* non_subquery: col  */
#line 660 "yacc_sql.y"
              {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_attr_init((yyval.cexpr), (yyvsp[0].attr));
	}
#line 2132 "yacc_sql.tab.cpp"
    break;

  case 107: /* non_subquery: value  */
#line 664 "yacc_sql.y"
                {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_value_init((yyval.cexpr), (yyvsp[0].val));	
	}
#line 2141 "yacc_sql.tab.cpp"
    break;

  case 108: /* non_subquery: LBRACE non_subquery RBRACE  */
#line 668 "yacc_sql.y"
                                     {
		(yyval.cexpr) = (yyvsp[-1].cexpr);
	}
#line 2149 "yacc_sql.tab.cpp"
    break;

  case 109: /* comOp: EQ  */
#line 674 "yacc_sql.y"
                        { (yyval.number) = EQUAL_TO; }
#line 2155 "yacc_sql.tab.cpp"
    break;

  case 110: /* comOp: LT  */
#line 675 "yacc_sql.y"
                        { (yyval.number) = LESS_THAN; }
#line 2161 "yacc_sql.tab.cpp"
    break;

  case 111: /* comOp: GT  */
#line 676 "yacc_sql.y"
                        { (yyval.number) = GREAT_THAN; }
#line 2167 "yacc_sql.tab.cpp"
    break;

  case 112: /* comOp: LE  */
#line 677 "yacc_sql.y"
                        { (yyval.number) = LESS_EQUAL; }
#line 2173 "yacc_sql.tab.cpp"
    break;

  case 113: /* comOp: GE  */
#line 678 "yacc_sql.y"
                        { (yyval.number) = GREAT_EQUAL; }
#line 2179 "yacc_sql.tab.cpp"
    break;

  case 114: /* comOp: NE  */
#line 679 "yacc_sql.y"
                        { (yyval.number) = NOT_EQUAL; }
#line 2185 "yacc_sql.tab.cpp"
    break;

  case 115: /* comOp: IS  */
#line 680 "yacc_sql.y"
                        { (yyval.number) = OP_IS; }
#line 2191 "yacc_sql.tab.cpp"
    break;

  case 116: /* comOp: IS NOT  */
#line 681 "yacc_sql.y"
                        { (yyval.number) = OP_IS_NOT; }
#line 2197 "yacc_sql.tab.cpp"
    break;

  case 117: /* subquery: LBRACE select RBRACE  */
#line 685 "yacc_sql.y"
                             {
		(yyval.select) = (yyvsp[-1].select);
	}
#line 2205 "yacc_sql.tab.cpp"
    break;

  case 118: /* group: %empty  */
#line 692 "yacc_sql.y"
        {
		(yyval.group_list) = new GroupByList();
	}
#line 2213 "yacc_sql.tab.cpp"
    break;

  case 119: /* group: GROUP BY col group_by_list  */
#line 695 "yacc_sql.y"
                                                     {
		(yyval.group_list) = (yyvsp[0].group_list);
		(yyval.group_list)->push_front((yyvsp[-1].attr));
	}
#line 2222 "yacc_sql.tab.cpp"
    break;

  case 120: /* group_by_list: %empty  */
#line 703 "yacc_sql.y"
        {
		(yyval.group_list) = new GroupByList();
	}
#line 2230 "yacc_sql.tab.cpp"
    break;

  case 121: /* group_by_list: COMMA col group_by_list  */
#line 706 "yacc_sql.y"
                                                  {
		(yyval.group_list) = (yyvsp[0].group_list);
		(yyval.group_list)->push_front((yyvsp[-1].attr));
	}
#line 2239 "yacc_sql.tab.cpp"
    break;

  case 122: /* order: %empty  */
#line 715 "yacc_sql.y"
        {
		(yyval.ocol_list) = new OrderColList;
	}
#line 2247 "yacc_sql.tab.cpp"
    break;

  case 123: /* order: ORDER BY order_col order_col_list  */
#line 718 "yacc_sql.y"
                                                           {
		(yyval.ocol_list) = (yyvsp[0].ocol_list);
		(yyval.ocol_list)->push_front((yyvsp[-1].ocol));
	}
#line 2256 "yacc_sql.tab.cpp"
    break;

  case 124: /* order_col_list: %empty  */
#line 726 "yacc_sql.y"
        {
		(yyval.ocol_list) = new OrderColList;
	}
#line 2264 "yacc_sql.tab.cpp"
    break;

  case 125: /* order_col_list: COMMA order_col order_col_list  */
#line 729 "yacc_sql.y"
                                                        {
		(yyval.ocol_list) = (yyvsp[0].ocol_list);
		(yyval.ocol_list)->push_front((yyvsp[-1].ocol));
	}
#line 2273 "yacc_sql.tab.cpp"
    break;

  case 126: /* order_col: col  */
#line 736 "yacc_sql.y"
            {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[0].attr), 1);
	}
#line 2282 "yacc_sql.tab.cpp"
    break;

  case 127: /* order_col: col ASC  */
#line 740 "yacc_sql.y"
                  {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[-1].attr), 1);
	}
#line 2291 "yacc_sql.tab.cpp"
    break;

  case 128: /* order_col: col DESC  */
#line 744 "yacc_sql.y"
                   {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[-1].attr), 0);
	}
#line 2300 "yacc_sql.tab.cpp"
    break;

  case 129: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 752 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2309 "yacc_sql.tab.cpp"
    break;


#line 2313 "yacc_sql.tab.cpp"

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

#line 757 "yacc_sql.y"

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
