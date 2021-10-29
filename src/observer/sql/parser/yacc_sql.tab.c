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

typedef struct ParserContext {
  Query * ssql;
  size_t condition_length;
  size_t value_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  char id[MAX_NUM];
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.tuple_num = 0;
  printf("parse sql failed. error=%s\n", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 124 "yacc_sql.tab.c"

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
  YYSYMBOL_EQ = 49,                        /* EQ  */
  YYSYMBOL_LT = 50,                        /* LT  */
  YYSYMBOL_GT = 51,                        /* GT  */
  YYSYMBOL_LE = 52,                        /* LE  */
  YYSYMBOL_GE = 53,                        /* GE  */
  YYSYMBOL_NE = 54,                        /* NE  */
  YYSYMBOL_NUMBER = 55,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 56,                     /* FLOAT  */
  YYSYMBOL_ID = 57,                        /* ID  */
  YYSYMBOL_PATH = 58,                      /* PATH  */
  YYSYMBOL_SSS = 59,                       /* SSS  */
  YYSYMBOL_DATE = 60,                      /* DATE  */
  YYSYMBOL_STAR = 61,                      /* STAR  */
  YYSYMBOL_STRING_V = 62,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 63,                  /* $accept  */
  YYSYMBOL_commands = 64,                  /* commands  */
  YYSYMBOL_command = 65,                   /* command  */
  YYSYMBOL_exit = 66,                      /* exit  */
  YYSYMBOL_help = 67,                      /* help  */
  YYSYMBOL_sync = 68,                      /* sync  */
  YYSYMBOL_begin = 69,                     /* begin  */
  YYSYMBOL_commit = 70,                    /* commit  */
  YYSYMBOL_rollback = 71,                  /* rollback  */
  YYSYMBOL_drop_table = 72,                /* drop_table  */
  YYSYMBOL_show_tables = 73,               /* show_tables  */
  YYSYMBOL_desc_table = 74,                /* desc_table  */
  YYSYMBOL_create_index = 75,              /* create_index  */
  YYSYMBOL_drop_index = 76,                /* drop_index  */
  YYSYMBOL_create_table = 77,              /* create_table  */
  YYSYMBOL_attr_def_list = 78,             /* attr_def_list  */
  YYSYMBOL_attr_def = 79,                  /* attr_def  */
  YYSYMBOL_number = 80,                    /* number  */
  YYSYMBOL_type = 81,                      /* type  */
  YYSYMBOL_ID_get = 82,                    /* ID_get  */
  YYSYMBOL_is_nullable = 83,               /* is_nullable  */
  YYSYMBOL_insert = 84,                    /* insert  */
  YYSYMBOL_tuple_list = 85,                /* tuple_list  */
  YYSYMBOL_tuple = 86,                     /* tuple  */
  YYSYMBOL_value_list = 87,                /* value_list  */
  YYSYMBOL_value = 88,                     /* value  */
  YYSYMBOL_delete = 89,                    /* delete  */
  YYSYMBOL_update = 90,                    /* update  */
  YYSYMBOL_select = 91,                    /* select  */
  YYSYMBOL_select_attr = 92,               /* select_attr  */
  YYSYMBOL_select_expr = 93,               /* select_expr  */
  YYSYMBOL_aggregate_func = 94,            /* aggregate_func  */
  YYSYMBOL_table_ref_list = 95,            /* table_ref_list  */
  YYSYMBOL_table_ref = 96,                 /* table_ref  */
  YYSYMBOL_join_table = 97,                /* join_table  */
  YYSYMBOL_join_condition = 98,            /* join_condition  */
  YYSYMBOL_where = 99,                     /* where  */
  YYSYMBOL_condition_list = 100,           /* condition_list  */
  YYSYMBOL_condition = 101,                /* condition  */
  YYSYMBOL_comOp = 102,                    /* comOp  */
  YYSYMBOL_load_data = 103                 /* load_data  */
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
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  224

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   317


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
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   140,   140,   142,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   166,   171,   176,   182,   188,   194,   200,   206,   212,
     219,   227,   234,   240,   242,   246,   252,   260,   263,   264,
     265,   266,   269,   276,   277,   278,   282,   288,   290,   294,
     302,   304,   307,   310,   313,   317,   333,   339,   349,   359,
     372,   377,   382,   387,   392,   401,   406,   415,   421,   423,
     428,   433,   438,   447,   452,   461,   469,   470,   471,   472,
     474,   476,   482,   487,   491,   500,   502,   505,   507,   509,
     511,   514,   525,   534,   545,   555,   565,   576,   590,   591,
     592,   593,   594,   595,   596,   597,   601
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
  "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT",
  "LE", "GE", "NE", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "DATE", "STAR",
  "STRING_V", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "drop_index", "create_table", "attr_def_list",
  "attr_def", "number", "type", "ID_get", "is_nullable", "insert",
  "tuple_list", "tuple", "value_list", "value", "delete", "update",
  "select", "select_attr", "select_expr", "aggregate_func",
  "table_ref_list", "table_ref", "join_table", "join_condition", "where",
  "condition_list", "condition", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-174)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -174,    85,  -174,    10,    50,     2,   -32,    20,    44,    26,
       7,    12,    80,    87,    88,    89,    95,    52,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,    57,    59,    62,    63,
    -174,  -174,  -174,  -174,    -4,  -174,    66,    99,   105,   120,
    -174,    73,    83,   100,  -174,  -174,  -174,  -174,  -174,   110,
     121,   106,   156,   157,     9,   -34,  -174,   104,    -8,  -174,
    -174,   122,   123,   107,   108,   109,   111,  -174,  -174,     5,
     141,   145,   145,  -174,    11,  -174,    -2,   147,   149,   -18,
     169,   124,   135,  -174,   151,   119,   154,    -1,  -174,     0,
    -174,  -174,   168,   104,   123,   145,    13,   145,    86,   155,
    -174,  -174,  -174,    75,  -174,  -174,   103,   137,  -174,    86,
     166,   109,   158,  -174,  -174,  -174,  -174,    -5,   125,   145,
     145,     8,   160,   127,    11,   182,  -174,   163,   164,  -174,
     165,   149,   185,   159,   133,  -174,  -174,  -174,  -174,  -174,
    -174,    16,    22,   -18,  -174,   123,   134,   151,   189,   138,
     161,  -174,  -174,   172,  -174,  -174,   145,    23,   145,   153,
    -174,  -174,   145,   145,    86,   173,   155,  -174,  -174,   103,
    -174,  -174,   162,  -174,   137,   196,   198,  -174,  -174,  -174,
     179,  -174,   200,  -174,   181,   183,  -174,   -18,  -174,  -174,
    -174,   165,  -174,  -174,    79,   148,  -174,  -174,  -174,    51,
    -174,   145,   145,   137,  -174,   170,  -174,  -174,  -174,  -174,
    -174,  -174,   150,  -174
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
      76,    77,    78,    79,    68,    60,     0,     0,     0,     0,
      23,     0,     0,     0,    24,    25,    26,    22,    21,     0,
       0,     0,     0,     0,     0,     0,    61,     0,     0,    29,
      28,     0,    87,     0,     0,     0,     0,    27,    31,    68,
       0,    68,    68,    82,    80,    83,     0,     0,     0,     0,
       0,     0,     0,    42,    33,     0,     0,     0,    69,     0,
      63,    62,     0,     0,    87,    68,     0,    68,     0,    47,
      56,    52,    53,     0,    54,    55,     0,    89,    57,     0,
       0,     0,     0,    38,    39,    41,    40,    45,     0,    68,
      68,     0,     0,     0,    80,     0,    65,     0,     0,    64,
      50,     0,     0,   104,     0,    98,    99,   100,   101,   102,
     103,     0,     0,     0,    88,    87,     0,    33,     0,     0,
       0,    44,    36,     0,    71,    70,    68,     0,    68,    85,
      81,    59,    68,    68,     0,     0,    47,    46,   105,     0,
      93,    91,    94,    92,    89,     0,     0,    34,    32,    37,
       0,    43,     0,    73,     0,     0,    72,     0,    84,    67,
      66,    50,    49,    48,     0,     0,    90,    58,   106,    45,
      30,    68,    68,    89,    51,     0,    95,    96,    35,    75,
      74,    86,     0,    97
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,  -174,  -174,    53,    90,  -174,  -174,  -174,
       3,  -174,    33,    72,    14,  -107,  -174,  -174,  -174,  -174,
     -79,   152,    84,   114,  -174,  -174,  -100,  -173,  -143,  -111,
    -174
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,   122,    94,   190,   127,    95,
     162,    31,   142,   109,   175,   116,    32,    33,    34,    46,
      66,    47,   104,    84,    85,   198,    90,   154,   117,   151,
      35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      98,   140,   100,   101,   135,   152,    40,    41,    42,    43,
     184,   206,   155,    40,    41,    42,    43,   159,   110,   102,
      64,   105,    36,    81,    37,    48,   136,    82,   139,    64,
     160,   166,   161,    49,    65,   103,   106,   111,   112,   113,
     221,   114,   115,    97,   181,   183,   167,    50,    52,    86,
     164,   165,   110,    87,   213,   185,   129,   131,   110,    44,
     130,   132,    38,    45,    39,    51,    79,   201,   204,    53,
     137,   111,   112,   180,   138,   114,   115,   111,   112,   182,
     194,   114,   115,    54,   195,     2,   160,   193,   161,   196,
      55,    56,    57,   199,   200,     3,     4,   216,    58,    59,
       5,     6,     7,     8,     9,    10,    11,    67,    69,   143,
      12,    13,    14,   144,    60,   110,    61,    15,    16,    62,
      63,    68,   110,    70,   145,   146,   147,   148,   149,   150,
      71,    17,   219,   220,   111,   112,   215,   143,   114,   115,
      72,   111,   112,    75,    73,   114,   115,   123,   124,   125,
     126,    76,   145,   146,   147,   148,   149,   150,    74,    77,
      78,    83,    88,    99,    91,    89,    93,    92,    96,    64,
     107,   108,   118,   119,   120,   121,   128,   133,   156,   141,
     153,   158,   163,   168,   169,   171,   172,   173,   177,   174,
     179,   186,   188,   189,   178,   192,   202,   191,   197,   207,
     205,   208,   209,   210,   211,   217,   212,   223,   222,   203,
     187,   157,   218,   176,     0,   214,    80,   134,   170
};

static const yytype_int16 yycheck[] =
{
      79,   108,    81,    82,   104,   116,     4,     5,     6,     7,
     153,   184,   119,     4,     5,     6,     7,    22,    36,     8,
      24,    23,    12,    57,    14,    57,   105,    61,   107,    24,
      35,    23,    37,    13,    38,    24,    38,    55,    56,    57,
     213,    59,    60,    38,   151,   152,    38,     3,    41,    57,
     129,   130,    36,    61,   197,   155,    57,    57,    36,    57,
      61,    61,    12,    61,    14,    39,    57,   174,   179,    57,
      57,    55,    56,    57,    61,    59,    60,    55,    56,    57,
      57,    59,    60,     3,    61,     0,    35,   166,    37,   168,
       3,     3,     3,   172,   173,    10,    11,   204,     3,    47,
      15,    16,    17,    18,    19,    20,    21,    41,     3,    34,
      25,    26,    27,    38,    57,    36,    57,    32,    33,    57,
      57,    22,    36,     3,    49,    50,    51,    52,    53,    54,
      57,    46,   211,   212,    55,    56,    57,    34,    59,    60,
      57,    55,    56,    22,    44,    59,    60,    28,    29,    30,
      31,    45,    49,    50,    51,    52,    53,    54,    48,     3,
       3,    57,    40,    22,    57,    42,    57,    59,    57,    24,
      23,    22,     3,    49,    39,    24,    22,     9,    12,    24,
      43,    23,    57,    23,    57,     3,    23,    23,     3,    24,
      57,    57,     3,    55,    35,    23,    23,    36,    45,     3,
      38,     3,    23,     3,    23,    57,    23,    57,    38,   176,
     157,   121,   209,   141,    -1,   201,    64,   103,   134
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    64,     0,    10,    11,    15,    16,    17,    18,    19,
      20,    21,    25,    26,    27,    32,    33,    46,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    84,    89,    90,    91,   103,    12,    14,    12,    14,
       4,     5,     6,     7,    57,    61,    92,    94,    57,    13,
       3,    39,    41,    57,     3,     3,     3,     3,     3,    47,
      57,    57,    57,    57,    24,    38,    93,    41,    22,     3,
       3,    57,    57,    44,    48,    22,    45,     3,     3,    57,
      94,    57,    61,    57,    96,    97,    57,    61,    40,    42,
      99,    57,    59,    57,    79,    82,    57,    38,    93,    22,
      93,    93,     8,    24,    95,    23,    38,    23,    22,    86,
      36,    55,    56,    57,    59,    60,    88,   101,     3,    49,
      39,    24,    78,    28,    29,    30,    31,    81,    22,    57,
      61,    57,    61,     9,    96,    99,    93,    57,    61,    93,
      88,    24,    85,    34,    38,    49,    50,    51,    52,    53,
      54,   102,   102,    43,   100,    88,    12,    79,    23,    22,
      35,    37,    83,    57,    93,    93,    23,    38,    23,    57,
      95,     3,    23,    23,    24,    87,    86,     3,    35,    57,
      57,    88,    57,    88,   101,    99,    57,    78,     3,    55,
      80,    36,    23,    93,    57,    61,    93,    45,    98,    93,
      93,    88,    23,    85,   102,    38,   100,     3,     3,    23,
       3,    23,    23,   101,    87,    57,    88,    57,    83,    93,
      93,   100,    38,    57
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    64,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    78,    79,    79,    80,    81,    81,
      81,    81,    82,    83,    83,    83,    84,    85,    85,    86,
      87,    87,    88,    88,    88,    88,    88,    89,    90,    91,
      92,    92,    92,    92,    92,    92,    92,    92,    93,    93,
      93,    93,    93,    93,    93,    93,    94,    94,    94,    94,
      95,    95,    96,    96,    97,    98,    98,    99,    99,   100,
     100,   101,   101,   101,   101,   101,   101,   101,   102,   102,
     102,   102,   102,   102,   102,   102,   103
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       9,     4,     8,     0,     3,     6,     3,     1,     1,     1,
       1,     1,     1,     2,     1,     0,     7,     0,     3,     4,
       0,     3,     1,     1,     1,     1,     1,     5,     8,     7,
       1,     2,     4,     4,     5,     5,     7,     7,     0,     3,
       5,     5,     6,     6,     8,     8,     1,     1,     1,     1,
       0,     3,     1,     1,     5,     0,     3,     0,     3,     0,
       3,     3,     3,     3,     3,     5,     5,     7,     1,     1,
       1,     1,     1,     1,     1,     2,     8
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
#line 166 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1376 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 171 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1384 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 176 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1392 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 182 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1400 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 188 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1408 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 194 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1416 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 200 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1425 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 206 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1433 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 212 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1442 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 220 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1451 "yacc_sql.tab.c"
    break;

  case 31: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 228 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1460 "yacc_sql.tab.c"
    break;

  case 32: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 235 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
		}
#line 1469 "yacc_sql.tab.c"
    break;

  case 34: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 242 "yacc_sql.y"
                                   {    }
#line 1475 "yacc_sql.tab.c"
    break;

  case 35: /* attr_def: ID_get type LBRACE number RBRACE is_nullable  */
#line 247 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number), (yyvsp[0].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
#line 1485 "yacc_sql.tab.c"
    break;

  case 36: /* attr_def: ID_get type is_nullable  */
#line 253 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), (yyvsp[-1].number) == DATES ? 8 : 4, (yyvsp[0].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		}
#line 1495 "yacc_sql.tab.c"
    break;

  case 37: /* number: NUMBER  */
#line 260 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1501 "yacc_sql.tab.c"
    break;

  case 38: /* type: INT_T  */
#line 263 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1507 "yacc_sql.tab.c"
    break;

  case 39: /* type: STRING_T  */
#line 264 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1513 "yacc_sql.tab.c"
    break;

  case 40: /* type: FLOAT_T  */
#line 265 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1519 "yacc_sql.tab.c"
    break;

  case 41: /* type: DATE_T  */
#line 266 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1525 "yacc_sql.tab.c"
    break;

  case 42: /* ID_get: ID  */
#line 270 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1534 "yacc_sql.tab.c"
    break;

  case 43: /* is_nullable: NOT NULL_T  */
#line 276 "yacc_sql.y"
            { (yyval.number) = 0; }
#line 1540 "yacc_sql.tab.c"
    break;

  case 44: /* is_nullable: NULLABLE  */
#line 277 "yacc_sql.y"
          { (yyval.number) = 1; }
#line 1546 "yacc_sql.tab.c"
    break;

  case 45: /* is_nullable: %empty  */
#line 278 "yacc_sql.y"
  {(yyval.number) = 0; }
#line 1552 "yacc_sql.tab.c"
    break;

  case 46: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 283 "yacc_sql.y"
        {
		CONTEXT->ssql->flag=SCF_INSERT;
		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
	}
#line 1561 "yacc_sql.tab.c"
    break;

  case 48: /* tuple_list: COMMA tuple tuple_list  */
#line 291 "yacc_sql.y"
        {	/* do nothing here */	}
#line 1567 "yacc_sql.tab.c"
    break;

  case 49: /* tuple: LBRACE value value_list RBRACE  */
#line 295 "yacc_sql.y"
        {
		// 由于tuple这种语法[形如(v1, v2, ..., vn)]只在insert中使用
		insert_tuple_init(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
		// 清空CONTEXT临时变量
		CONTEXT->value_length = 0;
	}
#line 1578 "yacc_sql.tab.c"
    break;

  case 51: /* value_list: COMMA value value_list  */
#line 304 "yacc_sql.y"
                              {}
#line 1584 "yacc_sql.tab.c"
    break;

  case 52: /* value: NUMBER  */
#line 307 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1592 "yacc_sql.tab.c"
    break;

  case 53: /* value: FLOAT  */
#line 310 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1600 "yacc_sql.tab.c"
    break;

  case 54: /* value: SSS  */
#line 313 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1609 "yacc_sql.tab.c"
    break;

  case 55: /* value: DATE  */
#line 317 "yacc_sql.y"
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
			value_init_date(&CONTEXT->values[CONTEXT->value_length++], mktime(&t));
		}
	}
#line 1630 "yacc_sql.tab.c"
    break;

  case 56: /* value: NULL_T  */
#line 333 "yacc_sql.y"
                {
			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1638 "yacc_sql.tab.c"
    break;

  case 57: /* delete: DELETE FROM ID where SEMICOLON  */
#line 340 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1650 "yacc_sql.tab.c"
    break;

  case 58: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 350 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1662 "yacc_sql.tab.c"
    break;

  case 59: /* select: SELECT select_attr FROM table_ref table_ref_list where SEMICOLON  */
#line 360 "yacc_sql.y"
                {
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].ref));
			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->value_length = 0;
	}
#line 1676 "yacc_sql.tab.c"
    break;

  case 60: /* select_attr: STAR  */
#line 372 "yacc_sql.y"
        {  
			RelAttr attr;
			relation_attr_init(&attr, COLUMN, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1686 "yacc_sql.tab.c"
    break;

  case 61: /* select_attr: ID select_expr  */
#line 377 "yacc_sql.y"
                     {
			RelAttr attr;
			relation_attr_init(&attr, COLUMN, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1696 "yacc_sql.tab.c"
    break;

  case 62: /* select_attr: ID DOT STAR select_expr  */
#line 382 "yacc_sql.y"
                                  {
		  	RelAttr attr;
			relation_attr_init(&attr, COLUMN, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	   }
#line 1706 "yacc_sql.tab.c"
    break;

  case 63: /* select_attr: ID DOT ID select_expr  */
#line 387 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, COLUMN, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1716 "yacc_sql.tab.c"
    break;

  case 64: /* select_attr: aggregate_func LBRACE STAR RBRACE select_expr  */
#line 392 "yacc_sql.y"
                                                       {
			RelAttr attr;
			if ((yyvsp[-4].number) != COUNT_FUNC) {
				CONTEXT->ssql->sstr.errors = "invalid arg of aggregate function";
				YYERROR;
			}
			relation_attr_init(&attr, COUNT_FUNC, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1730 "yacc_sql.tab.c"
    break;

  case 65: /* select_attr: aggregate_func LBRACE ID RBRACE select_expr  */
#line 401 "yacc_sql.y"
                                                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].number), NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1740 "yacc_sql.tab.c"
    break;

  case 66: /* select_attr: aggregate_func LBRACE ID DOT STAR RBRACE select_expr  */
#line 406 "yacc_sql.y"
                                                              {
			RelAttr attr;
			if ((yyvsp[-6].number) != COUNT_FUNC) {
				CONTEXT->ssql->sstr.errors = "invalid arg of aggregate function";
				YYERROR;
			}
			relation_attr_init(&attr, (yyvsp[-6].number), (yyvsp[-4].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1754 "yacc_sql.tab.c"
    break;

  case 67: /* select_attr: aggregate_func LBRACE ID DOT ID RBRACE select_expr  */
#line 415 "yacc_sql.y"
                                                            {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-6].number), (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1764 "yacc_sql.tab.c"
    break;

  case 69: /* select_expr: COMMA ID select_expr  */
#line 423 "yacc_sql.y"
                           {
			RelAttr attr;
			relation_attr_init(&attr, COLUMN, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
      }
#line 1774 "yacc_sql.tab.c"
    break;

  case 70: /* select_expr: COMMA ID DOT STAR select_expr  */
#line 428 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, COLUMN, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	  }
#line 1784 "yacc_sql.tab.c"
    break;

  case 71: /* select_expr: COMMA ID DOT ID select_expr  */
#line 433 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, COLUMN, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
  	  }
#line 1794 "yacc_sql.tab.c"
    break;

  case 72: /* select_expr: COMMA aggregate_func LBRACE STAR RBRACE select_expr  */
#line 438 "yacc_sql.y"
                                                             {
			RelAttr attr;
			if ((yyvsp[-4].number) != COUNT_FUNC) {
				CONTEXT->ssql->sstr.errors = "invalid arg of aggregate function";
				YYERROR;
			}
			relation_attr_init(&attr, (yyvsp[-4].number), NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1808 "yacc_sql.tab.c"
    break;

  case 73: /* select_expr: COMMA aggregate_func LBRACE ID RBRACE select_expr  */
#line 447 "yacc_sql.y"
                                                           {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].number), NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	  }
#line 1818 "yacc_sql.tab.c"
    break;

  case 74: /* select_expr: COMMA aggregate_func LBRACE ID DOT STAR RBRACE select_expr  */
#line 452 "yacc_sql.y"
                                                                    {
			RelAttr attr;
			if ((yyvsp[-6].number) != COUNT_FUNC) {
				CONTEXT->ssql->sstr.errors = "invalid arg of aggregate function";
				YYERROR;
			}
			relation_attr_init(&attr, (yyvsp[-6].number), (yyvsp[-4].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
      }
#line 1832 "yacc_sql.tab.c"
    break;

  case 75: /* select_expr: COMMA aggregate_func LBRACE ID DOT ID RBRACE select_expr  */
#line 461 "yacc_sql.y"
                                                                  {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-6].number), (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
      }
#line 1842 "yacc_sql.tab.c"
    break;

  case 76: /* aggregate_func: MAX_F  */
#line 469 "yacc_sql.y"
                  { (yyval.number) = MAX_FUNC;   }
#line 1848 "yacc_sql.tab.c"
    break;

  case 77: /* aggregate_func: MIN_F  */
#line 470 "yacc_sql.y"
                  { (yyval.number) = MIN_FUNC;   }
#line 1854 "yacc_sql.tab.c"
    break;

  case 78: /* aggregate_func: COUNT_F  */
#line 471 "yacc_sql.y"
                  { (yyval.number) = COUNT_FUNC; }
#line 1860 "yacc_sql.tab.c"
    break;

  case 79: /* aggregate_func: AVG_F  */
#line 472 "yacc_sql.y"
                  { (yyval.number) = AVG_FUNC;   }
#line 1866 "yacc_sql.tab.c"
    break;

  case 81: /* table_ref_list: COMMA table_ref table_ref_list  */
#line 476 "yacc_sql.y"
                                     {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].ref));
		  }
#line 1874 "yacc_sql.tab.c"
    break;

  case 82: /* table_ref: ID  */
#line 482 "yacc_sql.y"
           { 
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 0, (yyvsp[0].string), NULL, NULL, 0); 
		(yyval.ref) = ref;
	}
#line 1884 "yacc_sql.tab.c"
    break;

  case 83: /* table_ref: join_table  */
#line 487 "yacc_sql.y"
                     { (yyval.ref) = (yyvsp[0].ref); }
#line 1890 "yacc_sql.tab.c"
    break;

  case 84: /* join_table: table_ref INNER JOIN ID join_condition  */
#line 491 "yacc_sql.y"
                                               {
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 1, (yyvsp[-1].string), (yyvsp[-4].ref), CONTEXT->conditions, CONTEXT->condition_length);
		(yyval.ref) = ref;
		// 临时变量清零
		CONTEXT->condition_length = 0;
	}
#line 1902 "yacc_sql.tab.c"
    break;

  case 86: /* join_condition: ON condition condition_list  */
#line 502 "yacc_sql.y"
                                      {}
#line 1908 "yacc_sql.tab.c"
    break;

  case 88: /* where: WHERE condition condition_list  */
#line 507 "yacc_sql.y"
                                     {}
#line 1914 "yacc_sql.tab.c"
    break;

  case 90: /* condition_list: AND condition condition_list  */
#line 511 "yacc_sql.y"
                                   {}
#line 1920 "yacc_sql.tab.c"
    break;

  case 91: /* condition: ID comOp value  */
#line 515 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, COLUMN, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 1935 "yacc_sql.tab.c"
    break;

  case 92: /* condition: value comOp value  */
#line 526 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 1948 "yacc_sql.tab.c"
    break;

  case 93: /* condition: ID comOp ID  */
#line 535 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, COLUMN, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, COLUMN, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		}
#line 1963 "yacc_sql.tab.c"
    break;

  case 94: /* condition: value comOp ID  */
#line 546 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, COLUMN, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;		
		}
#line 1977 "yacc_sql.tab.c"
    break;

  case 95: /* condition: ID DOT ID comOp value  */
#line 556 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, COLUMN, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;		
    }
#line 1991 "yacc_sql.tab.c"
    break;

  case 96: /* condition: value comOp ID DOT ID  */
#line 566 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, COLUMN, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2006 "yacc_sql.tab.c"
    break;

  case 97: /* condition: ID DOT ID comOp ID DOT ID  */
#line 577 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, COLUMN, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, COLUMN, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2021 "yacc_sql.tab.c"
    break;

  case 98: /* comOp: EQ  */
#line 590 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2027 "yacc_sql.tab.c"
    break;

  case 99: /* comOp: LT  */
#line 591 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2033 "yacc_sql.tab.c"
    break;

  case 100: /* comOp: GT  */
#line 592 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2039 "yacc_sql.tab.c"
    break;

  case 101: /* comOp: LE  */
#line 593 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2045 "yacc_sql.tab.c"
    break;

  case 102: /* comOp: GE  */
#line 594 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2051 "yacc_sql.tab.c"
    break;

  case 103: /* comOp: NE  */
#line 595 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2057 "yacc_sql.tab.c"
    break;

  case 104: /* comOp: IS  */
#line 596 "yacc_sql.y"
                     { CONTEXT->comp = OP_IS; }
#line 2063 "yacc_sql.tab.c"
    break;

  case 105: /* comOp: IS NOT  */
#line 597 "yacc_sql.y"
                         { CONTEXT->comp = OP_IS_NOT; }
#line 2069 "yacc_sql.tab.c"
    break;

  case 106: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 602 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2078 "yacc_sql.tab.c"
    break;


#line 2082 "yacc_sql.tab.c"

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

#line 607 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
