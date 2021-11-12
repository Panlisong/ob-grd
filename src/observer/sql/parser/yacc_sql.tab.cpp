/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

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


#line 103 "yacc_sql.tab.cpp"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
#line 35 "yacc_sql.y"

#include <deque>
typedef struct _Selects Selects;
typedef struct _SelectExpr SelectExpr;
typedef struct _RelAttr RelAttr;
typedef struct _Value Value;
typedef struct _TableRef TableRef;
typedef struct _Condition Condition;
typedef struct _ConditionExpr ConditionExpr;
typedef struct _OrderCol OrderCol;
typedef std::deque<Condition> ConditionList;
typedef std::deque<SelectExpr *> SelectExprList;
typedef std::deque<TableRef *> TableRefList;
typedef std::deque<OrderCol *> OrderColList;
typedef std::deque<RelAttr *> GroupByList;

#line 163 "yacc_sql.tab.cpp"

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
#line 120 "yacc_sql.y"

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

#line 269 "yacc_sql.tab.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_HPP_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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

#define YYUNDEFTOK  2
#define YYMAXUTOK   328


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
     386,   390,   407,   414,   421,   427,   432,   462,   465,   473,
     474,   475,   481,   494,   499,   504,   509,   514,   518,   522,
     527,   536,   541,   552,   566,   567,   568,   569,   573,   577,
     586,   589,   596,   601,   605,   614,   617,   626,   629,   638,
     641,   648,   654,   660,   666,   672,   678,   687,   688,   691,
     695,   699,   703,   707,   711,   715,   718,   726,   727,   728,
     729,   730,   731,   732,   733,   737,   744,   747,   755,   758,
     767,   770,   778,   781,   788,   792,   796,   803
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "MAX_F", "MIN_F", "COUNT_F",
  "AVG_F", "INNER", "JOIN", "CREATE", "DROP", "TABLE", "TABLES", "INDEX",
  "UNIQUE", "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE",
  "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK",
  "INT_T", "STRING_T", "DATE_T", "FLOAT_T", "TEXT_T", "HELP", "EXIT", "IS",
  "NOT", "NULL_T", "NULLABLE", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "GROUP", "ORDER", "BY",
  "ASC", "ADD_OP", "SUB_OP", "DIV_OP", "EQ", "LT", "GT", "LE", "GE", "NE",
  "IN", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "DATE", "STAR", "STRING_V",
  "UNARYMINUS", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "attr_list", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "is_nullable", "insert",
  "tuple_list", "tuple", "value_list", "const_value", "value", "delete",
  "update", "selects", "select", "select_expr_list", "select_expr",
  "select_arith_expr", "select_func", "aggregate_func", "col",
  "table_ref_list", "table_ref", "join_table", "join_condition", "where",
  "condition_list", "condition", "membershipOp", "non_subquery", "comOp",
  "subquery", "group", "group_by_list", "order", "order_col_list",
  "order_col", "load_data", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328
};
# endif

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
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
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

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
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

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
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

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
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


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, void *scanner)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , scanner);
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 21:
#line 218 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1660 "yacc_sql.tab.cpp"
    break;

  case 22:
#line 223 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1668 "yacc_sql.tab.cpp"
    break;

  case 23:
#line 228 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1676 "yacc_sql.tab.cpp"
    break;

  case 24:
#line 234 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1684 "yacc_sql.tab.cpp"
    break;

  case 25:
#line 240 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1692 "yacc_sql.tab.cpp"
    break;

  case 26:
#line 246 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1700 "yacc_sql.tab.cpp"
    break;

  case 27:
#line 252 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1709 "yacc_sql.tab.cpp"
    break;

  case 28:
#line 258 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1717 "yacc_sql.tab.cpp"
    break;

  case 29:
#line 264 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1726 "yacc_sql.tab.cpp"
    break;

  case 30:
#line 272 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0);
		}
#line 1736 "yacc_sql.tab.cpp"
    break;

  case 31:
#line 278 "yacc_sql.y"
                {	// 由于只用支持UNIQUE，采用最简单写法
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_unique_index";
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1);
		}
#line 1746 "yacc_sql.tab.cpp"
    break;

  case 33:
#line 287 "yacc_sql.y"
                             {
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1754 "yacc_sql.tab.cpp"
    break;

  case 34:
#line 292 "yacc_sql.y"
                             {
		CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
		drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
	}
#line 1763 "yacc_sql.tab.cpp"
    break;

  case 35:
#line 299 "yacc_sql.y"
                                                                   {
		CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
		create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
	}
#line 1772 "yacc_sql.tab.cpp"
    break;

  case 37:
#line 306 "yacc_sql.y"
                                   {    }
#line 1778 "yacc_sql.tab.cpp"
    break;

  case 38:
#line 310 "yacc_sql.y"
                                            {
		AttrInfo attribute;
		AttrType type = static_cast<AttrType>((yyvsp[-4].number));
		attr_info_init(&attribute, (yyvsp[-5].string), type, (yyvsp[-2].number), (yyvsp[0].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
#line 1789 "yacc_sql.tab.cpp"
    break;

  case 39:
#line 316 "yacc_sql.y"
                         {
		AttrInfo attribute;
		AttrType type = static_cast<AttrType>((yyvsp[-1].number));
		attr_info_init(&attribute, (yyvsp[-2].string), type, (type == DATES || type == ATTR_TEXT) ? 8 : 4, (yyvsp[0].number));
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
	}
#line 1800 "yacc_sql.tab.cpp"
    break;

  case 40:
#line 325 "yacc_sql.y"
               {(yyval.number) = (yyvsp[0].number);}
#line 1806 "yacc_sql.tab.cpp"
    break;

  case 41:
#line 329 "yacc_sql.y"
                   { (yyval.number)=INTS; }
#line 1812 "yacc_sql.tab.cpp"
    break;

  case 42:
#line 330 "yacc_sql.y"
                   { (yyval.number)=CHARS; }
#line 1818 "yacc_sql.tab.cpp"
    break;

  case 43:
#line 331 "yacc_sql.y"
                   { (yyval.number)=FLOATS; }
#line 1824 "yacc_sql.tab.cpp"
    break;

  case 44:
#line 332 "yacc_sql.y"
                   { (yyval.number)=DATES; }
#line 1830 "yacc_sql.tab.cpp"
    break;

  case 45:
#line 333 "yacc_sql.y"
             { (yyval.number)=ATTR_TEXT; }
#line 1836 "yacc_sql.tab.cpp"
    break;

  case 46:
#line 337 "yacc_sql.y"
                    { (yyval.number) = 0; }
#line 1842 "yacc_sql.tab.cpp"
    break;

  case 47:
#line 338 "yacc_sql.y"
                    { (yyval.number) = 0; }
#line 1848 "yacc_sql.tab.cpp"
    break;

  case 48:
#line 339 "yacc_sql.y"
                    { (yyval.number) = 1; }
#line 1854 "yacc_sql.tab.cpp"
    break;

  case 49:
#line 343 "yacc_sql.y"
                                                         {
		CONTEXT->ssql->flag=SCF_INSERT;
		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string));
	}
#line 1863 "yacc_sql.tab.cpp"
    break;

  case 51:
#line 351 "yacc_sql.y"
        {	/* do nothing here */	}
#line 1869 "yacc_sql.tab.cpp"
    break;

  case 52:
#line 354 "yacc_sql.y"
                                             {
		insert_value_append(&CONTEXT->ssql->sstr.insertion, (yyvsp[-2].val));
		// tuple reduce: tuple_num ++
		(CONTEXT->ssql->sstr.insertion.tuple_num)++;
	}
#line 1879 "yacc_sql.tab.cpp"
    break;

  case 54:
#line 362 "yacc_sql.y"
                                    {
		insert_value_append(&CONTEXT->ssql->sstr.insertion, (yyvsp[-1].val));
	}
#line 1887 "yacc_sql.tab.cpp"
    break;

  case 55:
#line 367 "yacc_sql.y"
                      {
		(yyval.val) = (Value *)malloc(sizeof(Value));
		value_init_integer((yyval.val), -(yyvsp[0].number));
	}
#line 1896 "yacc_sql.tab.cpp"
    break;

  case 56:
#line 371 "yacc_sql.y"
                       {
		(yyval.val) = (Value *)malloc(sizeof(Value));	
  		value_init_float((yyval.val), -(yyvsp[0].floats));
	}
#line 1905 "yacc_sql.tab.cpp"
    break;

  case 57:
#line 375 "yacc_sql.y"
                { (yyval.val) = (yyvsp[0].val); }
#line 1911 "yacc_sql.tab.cpp"
    break;

  case 58:
#line 378 "yacc_sql.y"
          {
		(yyval.val) = (Value *)malloc(sizeof(Value));	
  		value_init_integer((yyval.val), (yyvsp[0].number));
	}
#line 1920 "yacc_sql.tab.cpp"
    break;

  case 59:
#line 382 "yacc_sql.y"
           {
		(yyval.val) = (Value *)malloc(sizeof(Value));	
  		value_init_float((yyval.val), (yyvsp[0].floats));
	}
#line 1929 "yacc_sql.tab.cpp"
    break;

  case 60:
#line 386 "yacc_sql.y"
          {
		(yyval.val) = (Value *)malloc(sizeof(Value));			
  		value_init_string((yyval.val), (yyvsp[0].string));
	}
#line 1938 "yacc_sql.tab.cpp"
    break;

  case 61:
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
#line 1960 "yacc_sql.tab.cpp"
    break;

  case 62:
#line 407 "yacc_sql.y"
                 {		
		(yyval.val) = (Value *)malloc(sizeof(Value));			
		value_init_null((yyval.val));
	}
#line 1969 "yacc_sql.tab.cpp"
    break;

  case 63:
#line 414 "yacc_sql.y"
                                   {
		CONTEXT->ssql->flag = SCF_DELETE;//"delete";
		deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
		deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, (yyvsp[-1].cond_list));
    }
#line 1979 "yacc_sql.tab.cpp"
    break;

  case 64:
#line 421 "yacc_sql.y"
                                                        {
		CONTEXT->ssql->flag = SCF_UPDATE;//"update";
		updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].val), (yyvsp[-1].cond_list));
	}
#line 1988 "yacc_sql.tab.cpp"
    break;

  case 65:
#line 427 "yacc_sql.y"
                     {
		CONTEXT->ssql->flag = SCF_SELECT; //"select";
		CONTEXT->ssql->sstr.selection = std::move(*(yyvsp[-1].select));
	}
#line 1997 "yacc_sql.tab.cpp"
    break;

  case 66:
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
		selects_append_group((yyval.select), (yyvsp[-1].group_list));

		// 5. append order_list(可选项，可能为空)
		selects_append_order((yyval.select), (yyvsp[0].ocol_list));
		
		(yyval.select)->context = new RelationTable();
	}
#line 2027 "yacc_sql.tab.cpp"
    break;

  case 67:
#line 462 "yacc_sql.y"
        {
		(yyval.sexpr_list) = new SelectExprList();
	}
#line 2035 "yacc_sql.tab.cpp"
    break;

  case 68:
#line 465 "yacc_sql.y"
                                             {
		// append select_expr $2
		(yyval.sexpr_list) = (yyvsp[0].sexpr_list);
		(yyval.sexpr_list)->push_front((yyvsp[-1].sexpr));
	}
#line 2045 "yacc_sql.tab.cpp"
    break;

  case 69:
#line 473 "yacc_sql.y"
                          { (yyval.sexpr) = (yyvsp[0].sexpr); }
#line 2051 "yacc_sql.tab.cpp"
    break;

  case 70:
#line 474 "yacc_sql.y"
                      { (yyval.sexpr) = (yyvsp[0].sexpr); }
#line 2057 "yacc_sql.tab.cpp"
    break;

  case 71:
#line 475 "yacc_sql.y"
               { 
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, NULL, "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), attr);
	}
#line 2068 "yacc_sql.tab.cpp"
    break;

  case 72:
#line 481 "yacc_sql.y"
                      {
		RelAttr *attr = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init(attr, (yyvsp[-2].string), "*");
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), attr);
	}
#line 2079 "yacc_sql.tab.cpp"
    break;

  case 73:
#line 494 "yacc_sql.y"
                                                   {
		/* expr "+" expr */
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), ADD);
	}
#line 2089 "yacc_sql.tab.cpp"
    break;

  case 74:
#line 499 "yacc_sql.y"
                                                     {
		/* expr "-" expr */
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), SUB);
	}
#line 2099 "yacc_sql.tab.cpp"
    break;

  case 75:
#line 504 "yacc_sql.y"
                                                   {
		/* expr "*" expr */
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), MUL);
	}
#line 2109 "yacc_sql.tab.cpp"
    break;

  case 76:
#line 509 "yacc_sql.y"
                                                     {
		/* expr "/" expr */
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), (yyvsp[-2].sexpr), (yyvsp[0].sexpr), DIV);
	}
#line 2119 "yacc_sql.tab.cpp"
    break;

  case 77:
#line 514 "yacc_sql.y"
              {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_attr_init((yyval.sexpr), (yyvsp[0].attr));
	}
#line 2128 "yacc_sql.tab.cpp"
    break;

  case 78:
#line 518 "yacc_sql.y"
                { 
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		select_value_init((yyval.sexpr), (yyvsp[0].val));	
	}
#line 2137 "yacc_sql.tab.cpp"
    break;

  case 79:
#line 522 "yacc_sql.y"
                                          {
		/* "(" expr ")" */
		(yyval.sexpr) = (yyvsp[-1].sexpr);
		(yyval.sexpr)->has_brace = 1;
	}
#line 2147 "yacc_sql.tab.cpp"
    break;

  case 80:
#line 527 "yacc_sql.y"
                                                    {
		/* "-" expr */
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		append_subexpr((yyval.sexpr), nullptr, (yyvsp[0].sexpr), NEG);
	}
#line 2157 "yacc_sql.tab.cpp"
    break;

  case 81:
#line 536 "yacc_sql.y"
                                         {
		(yyval.sexpr) = (SelectExpr *) malloc(sizeof(SelectExpr));
		FuncName func = static_cast<FuncName>((yyvsp[-3].number));
		aggregate_function_init((yyval.sexpr), func, (yyvsp[-1].attr));
	}
#line 2167 "yacc_sql.tab.cpp"
    break;

  case 82:
#line 541 "yacc_sql.y"
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
#line 2183 "yacc_sql.tab.cpp"
    break;

  case 83:
#line 552 "yacc_sql.y"
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
#line 2199 "yacc_sql.tab.cpp"
    break;

  case 84:
#line 566 "yacc_sql.y"
                  { (yyval.number) = MAX_FUNC;   }
#line 2205 "yacc_sql.tab.cpp"
    break;

  case 85:
#line 567 "yacc_sql.y"
                  { (yyval.number) = MIN_FUNC;   }
#line 2211 "yacc_sql.tab.cpp"
    break;

  case 86:
#line 568 "yacc_sql.y"
                  { (yyval.number) = COUNT_FUNC; }
#line 2217 "yacc_sql.tab.cpp"
    break;

  case 87:
#line 569 "yacc_sql.y"
                  { (yyval.number) = AVG_FUNC;   }
#line 2223 "yacc_sql.tab.cpp"
    break;

  case 88:
#line 573 "yacc_sql.y"
           {
		(yyval.attr) = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init((yyval.attr), NULL, (yyvsp[0].string));
	}
#line 2232 "yacc_sql.tab.cpp"
    break;

  case 89:
#line 577 "yacc_sql.y"
                    {
		(yyval.attr) = (RelAttr *)malloc(sizeof(RelAttr));
		attr_init((yyval.attr), (yyvsp[-2].string), (yyvsp[0].string));
	}
#line 2241 "yacc_sql.tab.cpp"
    break;

  case 90:
#line 586 "yacc_sql.y"
        {
		(yyval.ref_list) = new TableRefList();
	}
#line 2249 "yacc_sql.tab.cpp"
    break;

  case 91:
#line 589 "yacc_sql.y"
                                                   {	
		(yyval.ref_list) = (yyvsp[0].ref_list);
		(yyval.ref_list)->push_front((yyvsp[-1].ref));
	}
#line 2258 "yacc_sql.tab.cpp"
    break;

  case 92:
#line 596 "yacc_sql.y"
           { 
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 0, (yyvsp[0].string), nullptr, new ConditionList); 
		(yyval.ref) = ref;
	}
#line 2268 "yacc_sql.tab.cpp"
    break;

  case 93:
#line 601 "yacc_sql.y"
                     { (yyval.ref) = (yyvsp[0].ref); }
#line 2274 "yacc_sql.tab.cpp"
    break;

  case 94:
#line 605 "yacc_sql.y"
                                               {
		TableRef *ref = (TableRef *)malloc(sizeof(TableRef));
		table_ref_init(ref, 1, (yyvsp[-1].string), (yyvsp[-4].ref), (yyvsp[0].cond_list));
		(yyval.ref) = ref;
	}
#line 2284 "yacc_sql.tab.cpp"
    break;

  case 95:
#line 614 "yacc_sql.y"
        {
		(yyval.cond_list) = new ConditionList();
	}
#line 2292 "yacc_sql.tab.cpp"
    break;

  case 96:
#line 617 "yacc_sql.y"
                                      {
		(yyval.cond_list) = (yyvsp[0].cond_list);
		(yyval.cond_list)->push_front(*(yyvsp[-1].cond));
	}
#line 2301 "yacc_sql.tab.cpp"
    break;

  case 97:
#line 626 "yacc_sql.y"
        {
		(yyval.cond_list) = new ConditionList();
	}
#line 2309 "yacc_sql.tab.cpp"
    break;

  case 98:
#line 629 "yacc_sql.y"
                                     {
		(yyval.cond_list) = (yyvsp[0].cond_list);
		(yyval.cond_list)->push_front(*(yyvsp[-1].cond));
	}
#line 2318 "yacc_sql.tab.cpp"
    break;

  case 99:
#line 638 "yacc_sql.y"
        {
		(yyval.cond_list) = new ConditionList();
	}
#line 2326 "yacc_sql.tab.cpp"
    break;

  case 100:
#line 641 "yacc_sql.y"
                                   {
		(yyval.cond_list) = (yyvsp[0].cond_list);
		(yyval.cond_list)->push_front(*(yyvsp[-1].cond));
	}
#line 2335 "yacc_sql.tab.cpp"
    break;

  case 101:
#line 648 "yacc_sql.y"
                                        {
		/* 非子查询 compareOp 非子查询 */
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		non_subquery_cond_init((yyval.cond), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), op);
	}
#line 2346 "yacc_sql.tab.cpp"
    break;

  case 102:
#line 654 "yacc_sql.y"
                                      {
		/* 非子查询 compareOp 子查询 */
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		com_subquery_init((yyval.cond), (yyvsp[-2].cexpr), (yyvsp[0].select), op);
	}
#line 2357 "yacc_sql.tab.cpp"
    break;

  case 103:
#line 660 "yacc_sql.y"
                                      {
		/* 子查询 compareOp 非子查询 */
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		com_subquery_init((yyval.cond), (yyvsp[0].cexpr), (yyvsp[-2].select), get_neg_comp_op(op));
	}
#line 2368 "yacc_sql.tab.cpp"
    break;

  case 104:
#line 666 "yacc_sql.y"
                                  {
		/* 子查询 compareOp 子查询 */
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		com_subquery_init((yyval.cond), (yyvsp[0].select), (yyvsp[-2].select), op);
	}
#line 2379 "yacc_sql.tab.cpp"
    break;

  case 105:
#line 672 "yacc_sql.y"
                                             {
		/* 非子查询 IN/NOT IN 子查询 */
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		membership_subquery_init((yyval.cond), (yyvsp[-2].cexpr), (yyvsp[0].select), op);
	}
#line 2390 "yacc_sql.tab.cpp"
    break;

  case 106:
#line 678 "yacc_sql.y"
                                         {
		/* 子查询 IN/NOT IN 子查询 */
		CompOp op = static_cast<CompOp>((yyvsp[-1].number));
		(yyval.cond) = (Condition *)malloc(sizeof(Condition));
		membership_subquery_init((yyval.cond), (yyvsp[-2].select), (yyvsp[0].select), op);
	}
#line 2401 "yacc_sql.tab.cpp"
    break;

  case 107:
#line 687 "yacc_sql.y"
           { (yyval.number) = MEM_IN; }
#line 2407 "yacc_sql.tab.cpp"
    break;

  case 108:
#line 688 "yacc_sql.y"
                 { (yyval.number) = MEM_NOT_IN; }
#line 2413 "yacc_sql.tab.cpp"
    break;

  case 109:
#line 691 "yacc_sql.y"
                                         {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), ADD);
	}
#line 2422 "yacc_sql.tab.cpp"
    break;

  case 110:
#line 695 "yacc_sql.y"
                                           {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), SUB);
	}
#line 2431 "yacc_sql.tab.cpp"
    break;

  case 111:
#line 699 "yacc_sql.y"
                                         {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), MUL);
	}
#line 2440 "yacc_sql.tab.cpp"
    break;

  case 112:
#line 703 "yacc_sql.y"
                                           {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), (yyvsp[-2].cexpr), (yyvsp[0].cexpr), DIV);
	}
#line 2449 "yacc_sql.tab.cpp"
    break;

  case 113:
#line 707 "yacc_sql.y"
              {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_attr_init((yyval.cexpr), (yyvsp[0].attr));
	}
#line 2458 "yacc_sql.tab.cpp"
    break;

  case 114:
#line 711 "yacc_sql.y"
                {
		(yyval.cexpr) = (ConditionExpr *)malloc(sizeof(ConditionExpr));
		cond_value_init((yyval.cexpr), (yyvsp[0].val));	
	}
#line 2467 "yacc_sql.tab.cpp"
    break;

  case 115:
#line 715 "yacc_sql.y"
                                     {
		(yyval.cexpr) = (yyvsp[-1].cexpr);
	}
#line 2475 "yacc_sql.tab.cpp"
    break;

  case 116:
#line 718 "yacc_sql.y"
                                               {
		/* "-" expr  */
		(yyval.cexpr) = (ConditionExpr *) malloc(sizeof(ConditionExpr));
		append_cond_expr((yyval.cexpr), nullptr, (yyvsp[0].cexpr), NEG);
	}
#line 2485 "yacc_sql.tab.cpp"
    break;

  case 117:
#line 726 "yacc_sql.y"
                        { (yyval.number) = EQUAL_TO; }
#line 2491 "yacc_sql.tab.cpp"
    break;

  case 118:
#line 727 "yacc_sql.y"
                        { (yyval.number) = LESS_THAN; }
#line 2497 "yacc_sql.tab.cpp"
    break;

  case 119:
#line 728 "yacc_sql.y"
                        { (yyval.number) = GREAT_THAN; }
#line 2503 "yacc_sql.tab.cpp"
    break;

  case 120:
#line 729 "yacc_sql.y"
                        { (yyval.number) = LESS_EQUAL; }
#line 2509 "yacc_sql.tab.cpp"
    break;

  case 121:
#line 730 "yacc_sql.y"
                        { (yyval.number) = GREAT_EQUAL; }
#line 2515 "yacc_sql.tab.cpp"
    break;

  case 122:
#line 731 "yacc_sql.y"
                        { (yyval.number) = NOT_EQUAL; }
#line 2521 "yacc_sql.tab.cpp"
    break;

  case 123:
#line 732 "yacc_sql.y"
                        { (yyval.number) = OP_IS; }
#line 2527 "yacc_sql.tab.cpp"
    break;

  case 124:
#line 733 "yacc_sql.y"
                        { (yyval.number) = OP_IS_NOT; }
#line 2533 "yacc_sql.tab.cpp"
    break;

  case 125:
#line 737 "yacc_sql.y"
                             {
		(yyval.select) = (yyvsp[-1].select);
	}
#line 2541 "yacc_sql.tab.cpp"
    break;

  case 126:
#line 744 "yacc_sql.y"
        {
		(yyval.group_list) = new GroupByList();
	}
#line 2549 "yacc_sql.tab.cpp"
    break;

  case 127:
#line 747 "yacc_sql.y"
                                                     {
		(yyval.group_list) = (yyvsp[0].group_list);
		(yyval.group_list)->push_front((yyvsp[-1].attr));
	}
#line 2558 "yacc_sql.tab.cpp"
    break;

  case 128:
#line 755 "yacc_sql.y"
        {
		(yyval.group_list) = new GroupByList();
	}
#line 2566 "yacc_sql.tab.cpp"
    break;

  case 129:
#line 758 "yacc_sql.y"
                                                  {
		(yyval.group_list) = (yyvsp[0].group_list);
		(yyval.group_list)->push_front((yyvsp[-1].attr));
	}
#line 2575 "yacc_sql.tab.cpp"
    break;

  case 130:
#line 767 "yacc_sql.y"
        {
		(yyval.ocol_list) = new OrderColList;
	}
#line 2583 "yacc_sql.tab.cpp"
    break;

  case 131:
#line 770 "yacc_sql.y"
                                                           {
		(yyval.ocol_list) = (yyvsp[0].ocol_list);
		(yyval.ocol_list)->push_front((yyvsp[-1].ocol));
	}
#line 2592 "yacc_sql.tab.cpp"
    break;

  case 132:
#line 778 "yacc_sql.y"
        {
		(yyval.ocol_list) = new OrderColList;
	}
#line 2600 "yacc_sql.tab.cpp"
    break;

  case 133:
#line 781 "yacc_sql.y"
                                                        {
		(yyval.ocol_list) = (yyvsp[0].ocol_list);
		(yyval.ocol_list)->push_front((yyvsp[-1].ocol));
	}
#line 2609 "yacc_sql.tab.cpp"
    break;

  case 134:
#line 788 "yacc_sql.y"
            {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[0].attr), 1);
	}
#line 2618 "yacc_sql.tab.cpp"
    break;

  case 135:
#line 792 "yacc_sql.y"
                  {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[-1].attr), 1);
	}
#line 2627 "yacc_sql.tab.cpp"
    break;

  case 136:
#line 796 "yacc_sql.y"
                   {
		(yyval.ocol) = (OrderCol *)malloc(sizeof(OrderCol));
		order_col_init((yyval.ocol), (yyvsp[-1].attr), 0);
	}
#line 2636 "yacc_sql.tab.cpp"
    break;

  case 137:
#line 804 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2645 "yacc_sql.tab.cpp"
    break;


#line 2649 "yacc_sql.tab.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 809 "yacc_sql.y"

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
