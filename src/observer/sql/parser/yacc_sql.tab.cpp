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
  YYSYMBOL_UNARYMINUS = 73,                /* UNARYMINUS  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_commands = 75,                  /* commands  */
  YYSYMBOL_command = 76,                   /* command  */
  YYSYMBOL_exit = 77,                      /* exit  */
  YYSYMBOL_help = 78,                      /* help  */
  YYSYMBOL_sync = 79,                      /* sync  */
  YYSYMBOL_begin = 80,                     /* begin  */
  YYSYMBOL_commit = 81,                    /* commit  */
  YYSYMBOL_rollback = 82,                  /* rollback  */
  YYSYMBOL_drop_table = 83,                /* drop_table  */
  YYSYMBOL_show_tables = 84,               /* show_tables  */
  YYSYMBOL_desc_table = 85,                /* desc_table  */
  YYSYMBOL_create_index = 86,              /* create_index  */
  YYSYMBOL_attr_list = 87,                 /* attr_list  */
  YYSYMBOL_drop_index = 88,                /* drop_index  */
  YYSYMBOL_create_table = 89,              /* create_table  */
  YYSYMBOL_attr_def_list = 90,             /* attr_def_list  */
  YYSYMBOL_attr_def = 91,                  /* attr_def  */
  YYSYMBOL_number = 92,                    /* number  */
  YYSYMBOL_type = 93,                      /* type  */
  YYSYMBOL_is_nullable = 94,               /* is_nullable  */
  YYSYMBOL_insert = 95,                    /* insert  */
  YYSYMBOL_tuple_list = 96,                /* tuple_list  */
  YYSYMBOL_tuple = 97,                     /* tuple  */
  YYSYMBOL_value_list = 98,                /* value_list  */
  YYSYMBOL_const_value = 99,               /* const_value  */
  YYSYMBOL_value = 100,                    /* value  */
  YYSYMBOL_delete = 101,                   /* delete  */
  YYSYMBOL_update = 102,                   /* update  */
  YYSYMBOL_selects = 103,                  /* selects  */
  YYSYMBOL_select = 104,                   /* select  */
  YYSYMBOL_select_expr_list = 105,         /* select_expr_list  */
  YYSYMBOL_select_expr = 106,              /* select_expr  */
  YYSYMBOL_select_arith_expr = 107,        /* select_arith_expr  */
  YYSYMBOL_select_func = 108,              /* select_func  */
  YYSYMBOL_aggregate_func = 109,           /* aggregate_func  */
  YYSYMBOL_col = 110,                      /* col  */
  YYSYMBOL_table_ref_list = 111,           /* table_ref_list  */
  YYSYMBOL_table_ref = 112,                /* table_ref  */
  YYSYMBOL_join_table = 113,               /* join_table  */
  YYSYMBOL_join_condition = 114,           /* join_condition  */
  YYSYMBOL_where = 115,                    /* where  */
  YYSYMBOL_condition_list = 116,           /* condition_list  */
  YYSYMBOL_condition = 117,                /* condition  */
  YYSYMBOL_membershipOp = 118,             /* membershipOp  */
  YYSYMBOL_non_subquery = 119,             /* non_subquery  */
  YYSYMBOL_comOp = 120,                    /* comOp  */
  YYSYMBOL_subquery = 121,                 /* subquery  */
  YYSYMBOL_group = 122,                    /* group  */
  YYSYMBOL_group_by_list = 123,            /* group_by_list  */
  YYSYMBOL_order = 124,                    /* order  */
  YYSYMBOL_order_col_list = 125,           /* order_col_list  */
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
#define YYLAST   303

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  137
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  271

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328


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
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   192,   192,   194,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   218,   223,   228,   234,   240,   246,   252,   258,   264,
     271,   277,   285,   287,   292,   299,   304,   306,   310,   316,
     325,   329,   330,   331,   332,   333,   337,   338,   339,   343,
     348,   350,   354,   360,   362,   367,   371,   375,   378,   382,
     386,   390,   407,   414,   421,   427,   432,   460,   463,   471,
     472,   473,   479,   492,   497,   502,   507,   512,   516,   520,
     525,   534,   539,   550,   564,   565,   566,   567,   571,   575,
     584,   587,   594,   599,   603,   612,   615,   624,   627,   636,
     639,   646,   652,   658,   664,   670,   676,   685,   686,   689,
     693,   697,   701,   705,   709,   713,   716,   724,   725,   726,
     727,   728,   729,   730,   731,   735,   742,   745,   753,   756,
     765,   768,   776,   779,   786,   790,   794,   801
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
  "PATH", "SSS", "DATE", "STAR", "STRING_V", "UNARYMINUS", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "create_index",
  "attr_list", "drop_index", "create_table", "attr_def_list", "attr_def",
  "number", "type", "is_nullable", "insert", "tuple_list", "tuple",
  "value_list", "const_value", "value", "delete", "update", "selects",
  "select", "select_expr_list", "select_expr", "select_arith_expr",
  "select_func", "aggregate_func", "col", "table_ref_list", "table_ref",
  "join_table", "join_condition", "where", "condition_list", "condition",
  "membershipOp", "non_subquery", "comOp", "subquery", "group",
  "group_by_list", "order", "order_col_list", "order_col", "load_data", YY_NULLPTR
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
    -200,   117,  -200,   191,    40,    -3,   -48,    13,    24,    -8,
      18,   -23,    46,    68,    74,    83,    92,    61,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -200,  -200,   110,  -200,    57,    63,   101,
      82,    86,  -200,  -200,  -200,  -200,    56,  -200,    56,  -200,
    -200,   114,  -200,  -200,  -200,  -200,   125,   -39,  -200,   132,
    -200,   156,   159,  -200,    96,   109,   137,  -200,  -200,  -200,
    -200,  -200,   134,  -200,   175,   152,   140,   201,   205,   171,
      48,  -200,   -20,    -3,   169,    56,    56,    56,    56,    25,
    -200,  -200,   173,   172,   150,   157,   158,   161,   180,  -200,
    -200,   162,  -200,  -200,  -200,   125,   163,   -46,   -46,  -200,
    -200,   192,   207,   209,   211,    91,   232,   178,   196,   139,
     213,   216,   176,  -200,  -200,     6,  -200,    26,  -200,  -200,
     144,   215,   -10,   108,  -200,  -200,   197,   130,   160,  -200,
     144,   233,  -200,  -200,  -200,  -200,  -200,     1,   158,   220,
     179,   224,   239,   163,   172,   225,    75,   227,  -200,   211,
     247,   108,   229,   124,  -200,    91,  -200,   218,   193,   108,
     108,   108,  -200,  -200,  -200,  -200,  -200,  -200,  -200,   108,
     235,    91,   235,    91,   172,   189,   194,   222,  -200,  -200,
     213,   259,   238,   198,   199,     6,   217,  -200,  -200,  -200,
     144,   240,   215,  -200,  -200,  -200,   197,  -200,  -200,   -42,
     -42,  -200,  -200,   251,  -200,   -34,  -200,  -200,   -34,  -200,
     266,   267,  -200,   248,  -200,  -200,  -200,   204,   249,   238,
     228,  -200,   221,   226,   227,  -200,  -200,  -200,  -200,  -200,
      72,   238,   273,   253,    91,  -200,   212,   230,  -200,  -200,
    -200,  -200,  -200,   277,   197,   256,   212,  -200,  -200,   212,
    -200,    -9,   257,   256,  -200,  -200,   212,  -200,  -200,   257,
    -200
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
       0,     0,    84,    85,    86,    87,     0,    62,     0,    58,
      59,    88,    60,    61,    71,    78,    67,    69,    70,     0,
      77,     0,     0,    23,     0,     0,     0,    24,    25,    26,
      22,    21,     0,    65,     0,     0,     0,     0,     0,    88,
       0,    80,     0,     0,     0,     0,     0,     0,     0,     0,
      29,    28,     0,    97,     0,     0,     0,     0,     0,    27,
      34,     0,    79,    89,    72,    67,     0,    73,    74,    76,
      75,    88,     0,     0,     0,     0,     0,     0,     0,     0,
      36,     0,     0,    68,    92,    90,    93,     0,    82,    81,
       0,    50,     0,     0,   114,   113,    99,     0,     0,    63,
       0,     0,    41,    42,    44,    43,    45,    46,     0,     0,
       0,     0,     0,     0,    97,     0,     0,    53,    57,     0,
       0,     0,     0,     0,   116,     0,    98,   123,     0,     0,
       0,     0,   117,   118,   119,   120,   121,   122,   107,     0,
       0,     0,     0,     0,    97,     0,     0,     0,    48,    39,
      36,     0,    32,     0,     0,    90,   126,    83,    55,    56,
       0,     0,    50,    49,   125,   115,    99,   124,   108,   109,
     110,   112,   111,     0,   105,   101,   102,   106,   103,   104,
       0,     0,    40,     0,    47,    37,    35,     0,     0,    32,
      95,    91,     0,   130,    53,    52,    51,   100,    64,   137,
      46,    32,     0,     0,     0,    94,     0,     0,    66,    54,
      38,    33,    30,     0,    99,   128,     0,    31,    96,     0,
     127,   134,   132,   128,   136,   135,     0,   131,   129,   132,
     133
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,  -200,
    -200,  -200,  -200,  -199,  -200,  -200,    94,   138,  -200,  -200,
      45,  -200,    85,   129,    55,  -135,     2,  -200,  -200,  -200,
     289,   186,   210,   -12,  -200,  -200,    -5,    97,   141,  -200,
    -200,  -145,  -196,  -153,   164,   -63,   165,   -81,  -200,    32,
    -200,    27,    31,  -200
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   228,    29,    30,   149,   120,   223,   147,
     189,    31,   160,   131,   201,   157,   134,    32,    33,    34,
     162,    84,    56,    57,    58,    59,   135,   154,   125,   126,
     245,   116,   166,   136,   180,   137,   181,   138,   233,   260,
     248,   267,   262,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      60,    42,    43,    44,    45,   184,     5,    55,   264,   196,
     237,    87,   206,   161,   152,   171,    85,    86,    87,    61,
      46,   169,   170,   171,   186,    88,    62,    63,    47,   179,
     243,   153,    88,    64,    80,    47,    81,   179,   187,   220,
     188,    60,   251,    60,    66,   265,   133,   103,    55,    67,
      55,   104,    40,    48,    41,    49,    50,    79,   258,    52,
      53,    65,    49,    50,    51,   234,    52,    53,    54,   163,
     164,    68,   102,   107,   108,   109,   110,    69,    60,    46,
      60,    60,    60,    60,   113,    55,    70,    55,    55,    55,
      55,   254,   111,   103,    47,    71,   112,   155,   163,   214,
     216,   217,   219,    85,    86,    87,   209,   210,   211,   187,
      72,   188,    48,    73,   132,    76,   212,     2,   215,    88,
     218,    49,    50,    79,    74,    52,    53,     3,     4,    47,
      75,   161,   158,     5,     6,     7,     8,     9,    10,    11,
     198,   199,   158,    12,    13,    14,    47,   133,   205,    77,
      83,    15,    16,    78,    82,    89,    49,    50,    79,    90,
      52,    53,    91,    92,   133,    17,   167,   168,   142,   143,
     144,   145,   146,    49,    50,    79,    93,    52,    53,   169,
     170,   171,    47,    94,    95,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   167,   168,    96,    97,
     156,   179,   158,    37,    99,    38,    39,    98,   100,    49,
      50,   101,   106,    52,    53,   114,   115,   117,   172,   173,
     174,   175,   176,   177,   178,   119,   118,   122,   121,   103,
     124,   128,   127,   129,   130,   139,   140,   141,   148,   150,
     159,   255,   165,   151,   191,   185,   192,   193,   194,   197,
     203,   261,   200,   204,   263,   207,   221,   208,   213,   222,
     224,   261,   226,   227,   235,   229,   230,     5,   232,   238,
     239,   241,   240,   242,   246,   244,   252,   253,   247,    79,
     257,   259,   266,   256,   225,   250,   190,   236,   202,   249,
      35,   123,   231,   105,   195,   268,   270,   269,     0,     0,
       0,     0,   182,   183
};

static const yytype_int16 yycheck[] =
{
       5,     4,     5,     6,     7,   140,    16,     5,    17,   154,
     206,    57,   165,    23,     8,    57,    55,    56,    57,    67,
      23,    55,    56,    57,    23,    71,    13,     3,    38,    71,
     229,    25,    71,    41,    46,    38,    48,    71,    37,   184,
      39,    46,   241,    48,    67,    54,    56,    67,    46,     3,
      48,    71,    12,    56,    14,    65,    66,    67,   254,    69,
      70,    43,    65,    66,    67,   200,    69,    70,    71,   132,
     133,     3,    24,    85,    86,    87,    88,     3,    83,    23,
      85,    86,    87,    88,    89,    83,     3,    85,    86,    87,
      88,   244,    67,    67,    38,     3,    71,    71,   161,   180,
     181,   182,   183,    55,    56,    57,   169,   170,   171,    37,
      49,    39,    56,     3,    23,    14,   179,     0,   181,    71,
     183,    65,    66,    67,    67,    69,    70,    10,    11,    38,
      67,    23,   130,    16,    17,    18,    19,    20,    21,    22,
      65,    66,   140,    26,    27,    28,    38,    56,    24,    67,
      25,    34,    35,    67,    40,    23,    65,    66,    67,     3,
      69,    70,     3,    67,    56,    48,    36,    37,    29,    30,
      31,    32,    33,    65,    66,    67,    67,    69,    70,    55,
      56,    57,    38,    46,    50,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    71,    36,    37,    23,    47,
      56,    71,   200,    12,     3,    14,    15,    67,     3,    65,
      66,    40,    43,    69,    70,    42,    44,    67,    58,    59,
      60,    61,    62,    63,    64,    67,    69,    47,    67,    67,
      67,    24,    40,    24,    23,     3,    58,    41,    25,    23,
      25,   246,    45,    67,    24,    12,    67,    23,     9,    24,
       3,   256,    25,    24,   259,    37,    67,    64,    23,    65,
      38,   266,     3,    25,    24,    67,    67,    16,    51,     3,
       3,    67,    24,    24,    53,    47,     3,    24,    52,    67,
       3,    25,    25,    53,   190,   240,   148,   202,   159,   234,
       1,   105,   195,    83,   153,   263,   269,   266,    -1,    -1,
      -1,    -1,   138,   138
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    75,     0,    10,    11,    16,    17,    18,    19,    20,
      21,    22,    26,    27,    28,    34,    35,    48,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    88,
      89,    95,   101,   102,   103,   104,   127,    12,    14,    15,
      12,    14,     4,     5,     6,     7,    23,    38,    56,    65,
      66,    67,    69,    70,    71,   100,   106,   107,   108,   109,
     110,    67,    13,     3,    41,    43,    67,     3,     3,     3,
       3,     3,    49,     3,    67,    67,    14,    67,    67,    67,
     107,   107,    40,    25,   105,    55,    56,    57,    71,    23,
       3,     3,    67,    67,    46,    50,    23,    47,    67,     3,
       3,    40,    24,    67,    71,   106,    43,   107,   107,   107,
     107,    67,    71,   110,    42,    44,   115,    67,    69,    67,
      91,    67,    47,   105,    67,   112,   113,    40,    24,    24,
      23,    97,    23,    56,   100,   110,   117,   119,   121,     3,
      58,    41,    29,    30,    31,    32,    33,    93,    25,    90,
      23,    67,     8,    25,   111,    71,    56,    99,   100,    25,
      96,    23,   104,   119,   119,    45,   116,    36,    37,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    71,
     118,   120,   118,   120,    99,    12,    23,    37,    39,    94,
      91,    24,    67,    23,     9,   112,   115,    24,    65,    66,
      25,    98,    97,     3,    24,    24,   117,    37,    64,   119,
     119,   119,   119,    23,   121,   119,   121,   121,   119,   121,
     115,    67,    65,    92,    38,    90,     3,    25,    87,    67,
      67,   111,    51,   122,    99,    24,    96,   116,     3,     3,
      24,    67,    24,    87,    47,   114,    53,    52,   124,    98,
      94,    87,     3,    24,   117,   110,    53,     3,   116,    25,
     123,   110,   126,   110,    17,    54,    25,   125,   123,   126,
     125
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    74,    75,    75,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    86,    87,    87,    88,    89,    90,    90,    91,    91,
      92,    93,    93,    93,    93,    93,    94,    94,    94,    95,
      96,    96,    97,    98,    98,    99,    99,    99,   100,   100,
     100,   100,   100,   101,   102,   103,   104,   105,   105,   106,
     106,   106,   106,   107,   107,   107,   107,   107,   107,   107,
     107,   108,   108,   108,   109,   109,   109,   109,   110,   110,
     111,   111,   112,   112,   113,   114,   114,   115,   115,   116,
     116,   117,   117,   117,   117,   117,   117,   118,   118,   119,
     119,   119,   119,   119,   119,   119,   119,   120,   120,   120,
     120,   120,   120,   120,   120,   121,   122,   122,   123,   123,
     124,   124,   125,   125,   126,   126,   126,   127
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    11,     0,     3,     4,     8,     0,     3,     6,     3,
       1,     1,     1,     1,     1,     1,     0,     2,     1,     7,
       0,     3,     4,     0,     3,     2,     2,     1,     1,     1,
       1,     1,     1,     5,     8,     2,     9,     0,     3,     1,
       1,     1,     3,     3,     3,     3,     3,     1,     1,     3,
       2,     4,     4,     6,     1,     1,     1,     1,     1,     3,
       0,     3,     1,     1,     5,     0,     3,     0,     3,     0,
       3,     3,     3,     3,     3,     3,     3,     1,     2,     3,
       3,     3,     3,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     0,     4,     0,     3,
       0,     4,     0,     3,     1,     2,     2,     8
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
#line 218 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1429 "yacc_sql.tab.cpp"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 223 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1437 "yacc_sql.tab.cpp"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 228 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1445 "yacc_sql.tab.cpp"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 234 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1453 "yacc_sql.tab.cpp"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 240 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1461 "yacc_sql.tab.cpp"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 246 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1469 "yacc_sql.tab.cpp"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 252 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1478 "yacc_sql.tab.cpp"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 258 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1486 "yacc_sql.tab.cpp"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 264 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1495 "yacc_sql.tab.cpp"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID attr_list RBRACE SEMICOLON  */
#line 272 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
		}
#line 1505 "yacc_sql.tab.cpp"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID attr_list RBRACE SEMICOLON  */
#line 278 "yacc_sql.y"
                {	// 由于只用支持UNIQUE，采用最简单写法
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_unique_index";
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
		}
#line 1515 "yacc_sql.tab.cpp"
    break;

  case 33: /* attr_list: COMMA ID attr_list  */
#line 287 "yacc_sql.y"
                             {
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1523 "yacc_sql.tab.cpp"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 292 "yacc_sql.y"
                             {
		CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
		drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
	}
#line 1532 "yacc_sql.tab.cpp"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 299 "yacc_sql.y"
                                                                   {
		CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
		create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
	}
#line 1541 "yacc_sql.tab.cpp"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 306 "yacc_sql.y"
                                   {    }
#line 1547 "yacc_sql.tab.cpp"
    break;

  case 38: /* attr_def: ID type LBRACE number RBRACE is_nullable  */
#line 310 "yacc_sql.y"
                                            {
		AttrInfo attribute;
		AttrType type = static_cast<AttrType>((yyvsp[-4].number));
		attr_info_init(&attribute, (yyvsp[-5].string), type, (yyvsp[-2].number), (yyvsp[0].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
#line 1558 "yacc_sql.tab.cpp"
    break;

  case 39: /* attr_def: ID type is_nullable  */
#line 316 "yacc_sql.y"
                         {
		AttrInfo attribute;
		AttrType type = static_cast<AttrType>((yyvsp[-1].number));
		attr_info_init(&attribute, (yyvsp[-2].string), type, (type == DATES || type == ATTR_TEXT) ? 8 : 4, (yyvsp[0].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
#line 1569 "yacc_sql.tab.cpp"
    break;

  case 40: /* number: NUMBER  */
#line 325 "yacc_sql.y"
               {(yyval.number) = (yyvsp[0].number);}
#line 1575 "yacc_sql.tab.cpp"
    break;

  case 41: /* type: INT_T  */
#line 329 "yacc_sql.y"
                   { (yyval.number)=INTS; }
#line 1581 "yacc_sql.tab.cpp"
    break;

  case 42: /* type: STRING_T  */
#line 330 "yacc_sql.y"
                   { (yyval.number)=CHARS; }
#line 1587 "yacc_sql.tab.cpp"
    break;

  case 43: /* type: FLOAT_T  */
#line 331 "yacc_sql.y"
                   { (yyval.number)=FLOATS; }
#line 1593 "yacc_sql.tab.cpp"
    break;

  case 44: /* type: DATE_T  */
#line 332 "yacc_sql.y"
                   { (yyval.number)=DATES; }
#line 1599 "yacc_sql.tab.cpp"
    break;

  case 45: /* type: TEXT_T  */
#line 333 "yacc_sql.y"
             { (yyval.number)=ATTR_TEXT; }
#line 1605 "yacc_sql.tab.cpp"
    break;

  case 46: /* is_nullable: %empty  */
#line 337 "yacc_sql.y"
                    { (yyval.number) = 0; }
#line 1611 "yacc_sql.tab.cpp"
    break;

  case 47: /* is_nullable: NOT NULL_T  */
#line 338 "yacc_sql.y"
                    { (yyval.number) = 0; }
#line 1617 "yacc_sql.tab.cpp"
    break;

  case 48: /* is_nullable: NULLABLE  */
#line 339 "yacc_sql.y"
                    { (yyval.number) = 1; }
#line 1623 "yacc_sql.tab.cpp"
    break;

  case 49: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 343 "yacc_sql.y"
                                                         {
		CONTEXT->ssql->flag=SCF_INSERT;
		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
	}
#line 1632 "yacc_sql.tab.cpp"
    break;

  case 51: /* tuple_list: COMMA tuple tuple_list  */
#line 351 "yacc_sql.y"
        {	/* do nothing here */	}
#line 1638 "yacc_sql.tab.cpp"
    break;

  case 52: /* tuple: LBRACE const_value value_list RBRACE  */
#line 354 "yacc_sql.y"
                                             {
		insert_value_append(&CONTEXT->ssql->sstr.insertion, (yyvsp[-2].val));
		// tuple reduce: tuple_num ++
		(CONTEXT->ssql->sstr.insertion.tuple_num)++;
	}
#line 1648 "yacc_sql.tab.cpp"
    break;

  case 54: /* value_list: COMMA const_value value_list  */
#line 362 "yacc_sql.y"
                                    {
		insert_value_append(&CONTEXT->ssql->sstr.insertion, (yyvsp[-1].val));
	}
#line 1656 "yacc_sql.tab.cpp"
    break;

  case 55: /* const_value: SUB_OP NUMBER  */
#line 367 "yacc_sql.y"
                      {
		(yyval.val) = (Value *)malloc(sizeof(Value));
		value_init_integer((yyval.val), -(yyvsp[0].number));
	}
#line 1665 "yacc_sql.tab.cpp"
    break;

  case 56: /* const_value: SUB_OP FLOAT  */
#line 371 "yacc_sql.y"
                       {
		(yyval.val) = (Value *)malloc(sizeof(Value));	
  		value_init_float((yyval.val), -(yyvsp[0].floats));
	}
#line 1674 "yacc_sql.tab.cpp"
    break;

  case 57: /* const_value: value  */
#line 375 "yacc_sql.y"
                { (yyval.val) = (yyvsp[0].val); }
#line 1680 "yacc_sql.tab.cpp"
    break;

  case 58: /* value: NUMBER  */
#line 378 "yacc_sql.y"
          {
		(yyval.val) = (Value *)malloc(sizeof(Value));	
  		value_init_integer((yyval.val), (yyvsp[0].number));
	}
#line 1689 "yacc_sql.tab.cpp"
    break;

  case 59: /* value: FLOAT  */
#line 382 "yacc_sql.y"
           {
		(yyval.val) = (Value *)malloc(sizeof(Value));	
  		value_init_float((yyval.val), (yyvsp[0].floats));
	}
#line 1698 "yacc_sql.tab.cpp"
    break;

  case 60: /* value: SSS  */
#line 386 "yacc_sql.y"
          {
		(yyval.val) = (Value *)malloc(sizeof(Value));			
  		value_init_string((yyval.val), (yyvsp[0].string));
	}
#line 1707 "yacc_sql.tab.cpp"
    break;

  case 61: /* value: DATE  */
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
			(yyval.val) = (Value *)malloc(sizeof(Value));			
			value_init_date((yyval.val), mktime(&t));
		}
	}
#line 1729 "yacc_sql.tab.cpp"
    break;

  case 62: /* value: NULL_T  */
#line 407 "yacc_sql.y"
                 {		
		(yyval.val) = (Value *)malloc(sizeof(Value));			
		value_init_null((yyval.val));
	}
#line 1738 "yacc_sql.tab.cpp"
    break;

  case 63: /* delete: DELETE FROM ID where SEMICOLON  */
#line 414 "yacc_sql.y"
                                   {
		CONTEXT->ssql->flag = SCF_DELETE;//"delete";
		deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
		deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, (yyvsp[-1].cond_list));
    }
#line 1748 "yacc_sql.tab.cpp"
    break;

  case 64: /* update: UPDATE ID SET ID EQ const_value where SEMICOLON  */
#line 421 "yacc_sql.y"
                                                        {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].val), (yyvsp[-1].cond_list));
	}
#line 1757 "yacc_sql.tab.cpp"
    break;

  case 65: /* selects: select SEMICOLON  */
#line 427 "yacc_sql.y"
                     {
		CONTEXT->ssql->flag = SCF_SELECT; //"select";
		CONTEXT->ssql->sstr.selection = std::move(*(yyvsp[-1].select));
	}
#line 1766 "yacc_sql.tab.cpp"
    break;

  case 66: /* select: SELECT select_expr select_expr_list FROM table_ref table_ref_list where group order  */
#line 433 "yacc_sql.y"
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
#line 1794 "yacc_sql.tab.cpp"
    break;

  case 67: /* select_expr_list: %empty  */
#line 460 "yacc_sql.y"
        {
		(yyval.sexpr_list) = new SelectExprList();
	}
#line 1802 "yacc_sql.tab.cpp"
    break;

  case 68: /* select_expr_list: COMMA select_expr select_expr_list  */
#line 463 "yacc_sql.y"
                                             {
		// append select_expr $2
		(yyval.sexpr_list) = (yyvsp[0].sexpr_list);
		(yyval.sexpr_list)->push_front((yyvsp[-1].sexpr));
	}
#line 1812 "yacc_sql.tab.cpp"
    break;

  case 69: /* select_expr: select_arith_expr  */
#line 471 "yacc_sql.y"
                          { (yyval.sexpr) = (yyvsp[0].sexpr); }
#line 1818 "yacc_sql.tab.cpp"
    break;

  case 70: /* select_expr: select_func  */
#line 472 "yacc_sql.y"
                      { (yyval.sexpr) = (yyvsp[0].sexpr); }
#line 1824 "yacc_sql.tab.cpp"
    break;

  case 71: /* select_expr: STAR  */
#line 473 "yacc_sql.y"
               { 
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, NULL, "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), attr);
	}
#line 1835 "yacc_sql.tab.cpp"
    break;

  case 72: /* select_expr: ID DOT STAR  */
#line 479 "yacc_sql.y"
                      {
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, (yyvsp[-2].string), "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), attr);
	}
#line 1846 "yacc_sql.tab.cpp"
    break;

  case 73: /* select_arith_expr: select_arith_expr ADD_OP select_arith_expr  */
#line 492 "yacc_sql.y"
                                                   {
		/* expr "+" expr */
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), ADD);
	}
#line 1856 "yacc_sql.tab.cpp"
    break;

  case 74: /* select_arith_expr: select_arith_expr SUB_OP select_arith_expr  */
#line 497 "yacc_sql.y"
                                                     {
		/* expr "-" expr */
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), SUB);
	}
#line 1866 "yacc_sql.tab.cpp"
    break;

  case 75: /* select_arith_expr: select_arith_expr STAR select_arith_expr  */
#line 502 "yacc_sql.y"
                                                   {
		/* expr "*" expr */
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), MUL);
	}
#line 1876 "yacc_sql.tab.cpp"
    break;

  case 76: /* select_arith_expr: select_arith_expr DIV_OP select_arith_expr  */
#line 507 "yacc_sql.y"
                                                     {
		/* expr "/" expr */
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), DIV);
	}
#line 1886 "yacc_sql.tab.cpp"
    break;

  case 77: /* select_arith_expr: col  */
#line 512 "yacc_sql.y"
              {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), (yyvsp[0].attr));
	}
#line 1895 "yacc_sql.tab.cpp"
    break;

  case 78: /* select_arith_expr: value  */
#line 516 "yacc_sql.y"
                { 
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_value_init((yyval.sexpr), (yyvsp[0].val));	
	}
#line 1904 "yacc_sql.tab.cpp"
    break;

  case 79: /* select_arith_expr: LBRACE select_arith_expr RBRACE  */
#line 520 "yacc_sql.y"
                                          {
		/* "(" expr ")" */
		(yyval.sexpr) = (yyvsp[-1].sexpr);
		(yyval.sexpr)->has_brace = 1;
	}
#line 1914 "yacc_sql.tab.cpp"
    break;

  case 80: /* select_arith_expr: SUB_OP select_arith_expr  */
#line 525 "yacc_sql.y"
                                                    {
		/* "-" expr */
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), nullptr, (yyvsp[0].sexpr), NEG);
	}
#line 1924 "yacc_sql.tab.cpp"
    break;

  case 81: /* select_func: aggregate_func LBRACE col RBRACE  */
#line 534 "yacc_sql.y"
                                         {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		FuncName func = static_cast<FuncName>((yyvsp[-3].number));
		aggregate_function_init((yyval.sexpr), func, (yyvsp[-1].attr));
	}
#line 1934 "yacc_sql.tab.cpp"
    break;

  case 82: /* select_func: aggregate_func LBRACE STAR RBRACE  */
#line 539 "yacc_sql.y"
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
#line 1950 "yacc_sql.tab.cpp"
    break;

  case 83: /* select_func: aggregate_func LBRACE ID DOT STAR RBRACE  */
#line 550 "yacc_sql.y"
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
#line 1966 "yacc_sql.tab.cpp"
    break;

  case 84: /* aggregate_func: MAX_F  */
#line 564 "yacc_sql.y"
                  { (yyval.number) = MAX_FUNC;   }
#line 1972 "yacc_sql.tab.cpp"
    break;

  case 85: /* aggregate_func: MIN_F  */
#line 565 "yacc_sql.y"
                  { (yyval.number) = MIN_FUNC;   }
#line 1978 "yacc_sql.tab.cpp"
    break;

  case 86: /* aggregate_func: COUNT_F  */
#line 566 "yacc_sql.y"
                  { (yyval.number) = COUNT_FUNC; }
#line 1984 "yacc_sql.tab.cpp"
    break;

  case 87: /* aggregate_func: AVG_F  */
#line 567 "yacc_sql.y"
                  { (yyval.number) = AVG_FUNC;   }
#line 1990 "yacc_sql.tab.cpp"
    break;

  case 88: /* col: ID  */
#line 571 "yacc_sql.y"
           {
		(yyval.attr) = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init((yyval.attr), NULL, (yyvsp[0].string));
	}
#line 1999 "yacc_sql.tab.cpp"
    break;

  case 89: /* col: ID DOT ID  */
#line 575 "yacc_sql.y"
                    {
		(yyval.attr) = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init((yyval.attr), (yyvsp[-2].string), (yyvsp[0].string));
	}
#line 2008 "yacc_sql.tab.cpp"
    break;

  case 90: /* table_ref_list: %empty  */
#line 584 "yacc_sql.y"
        {
		(yyval.ref_list) = new TableRefList();
	}
#line 2016 "yacc_sql.tab.cpp"
    break;

  case 91: /* table_ref_list: COMMA table_ref table_ref_list  */
#line 587 "yacc_sql.y"
                                                   {	
		(yyval.ref_list) = (yyvsp[0].ref_list);
		(yyval.ref_list)->push_front((yyvsp[-1].ref));
	}
#line 2025 "yacc_sql.tab.cpp"
    break;

  case 92: /* table_ref: ID  */
#line 594 "yacc_sql.y"
           { 
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 0, (yyvsp[0].string), nullptr, new ConditionList); 
		(yyval.ref) = ref;
	}
#line 2035 "yacc_sql.tab.cpp"
    break;

  case 93: /* table_ref: join_table  */
#line 599 "yacc_sql.y"
                     { (yyval.ref) = (yyvsp[0].ref); }
#line 2041 "yacc_sql.tab.cpp"
    break;

  case 94: /* join_table: table_ref INNER JOIN ID join_condition  */
#line 603 "yacc_sql.y"
                                               {
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 1, (yyvsp[-1].string), (yyvsp[-4].ref), (yyvsp[0].cond_list));
		(yyval.ref) = ref;
	}
#line 2051 "yacc_sql.tab.cpp"
    break;

  case 95: /* join_condition: %empty  */
#line 612 "yacc_sql.y"
        {
		(yyval.cond_list) = new ConditionList();
	}
#line 2059 "yacc_sql.tab.cpp"
    break;

  case 96: /* join_condition: ON condition condition_list  */
#line 615 "yacc_sql.y"
                                      {
		(yyval.cond_list) = (yyvsp[0].cond_list);
		(yyval.cond_list)->push_front(*(yyvsp[-1].cond));
	}
#line 2068 "yacc_sql.tab.cpp"
    break;

  case 97: /* where: %empty  */
#line 624 "yacc_sql.y"
        {
		(yyval.cond_list) = new ConditionList();
	}
#line 2076 "yacc_sql.tab.cpp"
    break;

  case 98: /* where: WHERE condition condition_list  */
#line 627 "yacc_sql.y"
                                     {
		(yyval.cond_list) = (yyvsp[0].cond_list);
		(yyval.cond_list)->push_front(*(yyvsp[-1].cond));
	}
#line 2085 "yacc_sql.tab.cpp"
    break;

  case 99: /* condition_list: %empty  */
#line 636 "yacc_sql.y"
        {
		(yyval.cond_list) = new ConditionList();
	}
#line 2093 "yacc_sql.tab.cpp"
    break;

  case 100: /* condition_list: AND condition condition_list  */
#line 639 "yacc_sql.y"
                                   {
		(yyval.cond_list) = (yyvsp[0].cond_list);
		(yyval.cond_list)->push_front(*(yyvsp[-1].cond));
	}
#line 2102 "yacc_sql.tab.cpp"
    break;

  case 101: /* condition: non_subquery comOp non_subquery  */
#line 646 "yacc_sql.y"
                                        {
		/* 非子查询 compareOp 非子查询 */
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		non_subquery_cond_init((yyval.cond), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), op);
	}
#line 2113 "yacc_sql.tab.cpp"
    break;

  case 102: /* condition: non_subquery comOp subquery  */
#line 652 "yacc_sql.y"
                                      {
		/* 非子查询 compareOp 子查询 */
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		com_subquery_init((yyval.cond), (yyvsp[-2].cexpr), (yyvsp[0].select), op);
	}
#line 2124 "yacc_sql.tab.cpp"
    break;

  case 103: /* condition: subquery comOp non_subquery  */
#line 658 "yacc_sql.y"
                                      {
		/* 子查询 compareOp 非子查询 */
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		com_subquery_init((yyval.cond), (yyvsp[0].cexpr), (yyvsp[-2].select), get_neg_comp_op(op));
	}
#line 2135 "yacc_sql.tab.cpp"
    break;

  case 104: /* condition: subquery comOp subquery  */
#line 664 "yacc_sql.y"
                                  {
		/* 子查询 compareOp 子查询 */
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		com_subquery_init((yyval.cond), (yyvsp[0].select), (yyvsp[-2].select), op);
	}
#line 2146 "yacc_sql.tab.cpp"
    break;

  case 105: /* condition: non_subquery membershipOp subquery  */
#line 670 "yacc_sql.y"
                                             {
		/* 非子查询 IN/NOT IN 子查询 */
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		membership_subquery_init((yyval.cond), (yyvsp[-2].cexpr), (yyvsp[0].select), op);
	}
#line 2157 "yacc_sql.tab.cpp"
    break;

  case 106: /* condition: subquery membershipOp subquery  */
#line 676 "yacc_sql.y"
                                         {
		/* 子查询 IN/NOT IN 子查询 */
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		membership_subquery_init((yyval.cond), (yyvsp[-2].select), (yyvsp[0].select), op);
	}
#line 2168 "yacc_sql.tab.cpp"
    break;

  case 107: /* membershipOp: IN  */
#line 685 "yacc_sql.y"
           { (yyval.number) = MEM_IN; }
#line 2174 "yacc_sql.tab.cpp"
    break;

  case 108: /* membershipOp: NOT IN  */
#line 686 "yacc_sql.y"
                 { (yyval.number) = MEM_NOT_IN; }
#line 2180 "yacc_sql.tab.cpp"
    break;

  case 109: /* non_subquery: non_subquery ADD_OP non_subquery  */
#line 689 "yacc_sql.y"
                                         {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), ADD);
	}
#line 2189 "yacc_sql.tab.cpp"
    break;

  case 110: /* non_subquery: non_subquery SUB_OP non_subquery  */
#line 693 "yacc_sql.y"
                                           {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), SUB);
	}
#line 2198 "yacc_sql.tab.cpp"
    break;

  case 111: /* non_subquery: non_subquery STAR non_subquery  */
#line 697 "yacc_sql.y"
                                         {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), MUL);
	}
#line 2207 "yacc_sql.tab.cpp"
    break;

  case 112: /* non_subquery: non_subquery DIV_OP non_subquery  */
#line 701 "yacc_sql.y"
                                           {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), DIV);
	}
#line 2216 "yacc_sql.tab.cpp"
    break;

  case 113: /* non_subquery: col  */
#line 705 "yacc_sql.y"
              {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_attr_init((yyval.cexpr), (yyvsp[0].attr));
	}
#line 2225 "yacc_sql.tab.cpp"
    break;

  case 114: /* non_subquery: value  */
#line 709 "yacc_sql.y"
                {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_value_init((yyval.cexpr), (yyvsp[0].val));	
	}
#line 2234 "yacc_sql.tab.cpp"
    break;

  case 115: /* non_subquery: LBRACE non_subquery RBRACE  */
#line 713 "yacc_sql.y"
                                     {
		(yyval.cexpr) = (yyvsp[-1].cexpr);
	}
#line 2242 "yacc_sql.tab.cpp"
    break;

  case 116: /* non_subquery: SUB_OP non_subquery  */
#line 716 "yacc_sql.y"
                                               {
		/* "-" expr  */
		(yyval.cexpr) = (ConditionExpr *) malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), nullptr, (yyvsp[0].cexpr), NEG);
	}
#line 2252 "yacc_sql.tab.cpp"
    break;

  case 117: /* comOp: EQ  */
#line 724 "yacc_sql.y"
                        { (yyval.number) = EQUAL_TO; }
#line 2258 "yacc_sql.tab.cpp"
    break;

  case 118: /* comOp: LT  */
#line 725 "yacc_sql.y"
                        { (yyval.number) = LESS_THAN; }
#line 2264 "yacc_sql.tab.cpp"
    break;

  case 119: /* comOp: GT  */
#line 726 "yacc_sql.y"
                        { (yyval.number) = GREAT_THAN; }
#line 2270 "yacc_sql.tab.cpp"
    break;

  case 120: /* comOp: LE  */
#line 727 "yacc_sql.y"
                        { (yyval.number) = LESS_EQUAL; }
#line 2276 "yacc_sql.tab.cpp"
    break;

  case 121: /* comOp: GE  */
#line 728 "yacc_sql.y"
                        { (yyval.number) = GREAT_EQUAL; }
#line 2282 "yacc_sql.tab.cpp"
    break;

  case 122: /* comOp: NE  */
#line 729 "yacc_sql.y"
                        { (yyval.number) = NOT_EQUAL; }
#line 2288 "yacc_sql.tab.cpp"
    break;

  case 123: /* comOp: IS  */
#line 730 "yacc_sql.y"
                        { (yyval.number) = OP_IS; }
#line 2294 "yacc_sql.tab.cpp"
    break;

  case 124: /* comOp: IS NOT  */
#line 731 "yacc_sql.y"
                        { (yyval.number) = OP_IS_NOT; }
#line 2300 "yacc_sql.tab.cpp"
    break;

  case 125: /* subquery: LBRACE select RBRACE  */
#line 735 "yacc_sql.y"
                             {
		(yyval.select) = (yyvsp[-1].select);
	}
#line 2308 "yacc_sql.tab.cpp"
    break;

  case 126: /* group: %empty  */
#line 742 "yacc_sql.y"
        {
		(yyval.group_list) = new GroupByList();
	}
#line 2316 "yacc_sql.tab.cpp"
    break;

  case 127: /* group: GROUP BY col group_by_list  */
#line 745 "yacc_sql.y"
                                                     {
		(yyval.group_list) = (yyvsp[0].group_list);
		(yyval.group_list)->push_front((yyvsp[-1].attr));
	}
#line 2325 "yacc_sql.tab.cpp"
    break;

  case 128: /* group_by_list: %empty  */
#line 753 "yacc_sql.y"
        {
		(yyval.group_list) = new GroupByList();
	}
#line 2333 "yacc_sql.tab.cpp"
    break;

  case 129: /* group_by_list: COMMA col group_by_list  */
#line 756 "yacc_sql.y"
                                                  {
		(yyval.group_list) = (yyvsp[0].group_list);
		(yyval.group_list)->push_front((yyvsp[-1].attr));
	}
#line 2342 "yacc_sql.tab.cpp"
    break;

  case 130: /* order: %empty  */
#line 765 "yacc_sql.y"
        {
		(yyval.ocol_list) = new OrderColList;
	}
#line 2350 "yacc_sql.tab.cpp"
    break;

  case 131: /* order: ORDER BY order_col order_col_list  */
#line 768 "yacc_sql.y"
                                                           {
		(yyval.ocol_list) = (yyvsp[0].ocol_list);
		(yyval.ocol_list)->push_front((yyvsp[-1].ocol));
	}
#line 2359 "yacc_sql.tab.cpp"
    break;

  case 132: /* order_col_list: %empty  */
#line 776 "yacc_sql.y"
        {
		(yyval.ocol_list) = new OrderColList;
	}
#line 2367 "yacc_sql.tab.cpp"
    break;

  case 133: /* order_col_list: COMMA order_col order_col_list  */
#line 779 "yacc_sql.y"
                                                        {
		(yyval.ocol_list) = (yyvsp[0].ocol_list);
		(yyval.ocol_list)->push_front((yyvsp[-1].ocol));
	}
#line 2376 "yacc_sql.tab.cpp"
    break;

  case 134: /* order_col: col  */
#line 786 "yacc_sql.y"
            {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[0].attr), 1);
	}
#line 2385 "yacc_sql.tab.cpp"
    break;

  case 135: /* order_col: col ASC  */
#line 790 "yacc_sql.y"
                  {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[-1].attr), 1);
	}
#line 2394 "yacc_sql.tab.cpp"
    break;

  case 136: /* order_col: col DESC  */
#line 794 "yacc_sql.y"
                   {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[-1].attr), 0);
	}
#line 2403 "yacc_sql.tab.cpp"
    break;

  case 137: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 802 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2412 "yacc_sql.tab.cpp"
    break;


#line 2416 "yacc_sql.tab.cpp"

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

#line 807 "yacc_sql.y"

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
