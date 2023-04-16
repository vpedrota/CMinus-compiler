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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "bison/bison.y"


// Importação das bibliotecas 
#define YYSTYPE TreeNode*
#include "globals.h"
#include "arvore.h"

int yyerror(char *s);
static TreeNode *root;

static int savedLineNo;
static char* savedName;


#line 85 "bison.tab.c"

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
#ifndef YY_YY_BISON_TAB_H_INCLUDED
# define YY_YY_BISON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ELSE = 258,
    IF = 259,
    INT = 260,
    RETURN = 261,
    VOID = 262,
    WHILE = 263,
    PLUS = 264,
    SUB = 265,
    MULT = 266,
    DIV = 267,
    LT = 268,
    LET = 269,
    GT = 270,
    GET = 271,
    COMP = 272,
    DIF = 273,
    ASSIGN = 274,
    PV = 275,
    VIR = 276,
    LPAR = 277,
    RPAR = 278,
    LCOL = 279,
    RCOL = 280,
    LCHA = 281,
    RCHA = 282,
    ID = 283,
    NUM = 284,
    ERR = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_TAB_H_INCLUDED  */



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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   138

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  117

#define YYUNDEFTOK  2
#define YYMAXUTOK   285


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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    36,    36,    38,    47,    49,    50,    52,    61,    73,
      79,    84,    89,    95,   106,   117,   118,   124,   133,   134,
     142,   152,   161,   165,   169,   172,   181,   183,   192,   195,
     196,   197,   198,   199,   200,   200,   201,   206,   213,   219,
     221,   226,   231,   233,   233,   240,   244,   246,   251,   257,
     262,   267,   272,   278,   282,   284,   288,   293,   297,   299,
     302,   307,   308,   309,   310,   312,   318,   318,   319,   328
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ELSE", "IF", "INT", "RETURN", "VOID",
  "WHILE", "PLUS", "SUB", "MULT", "DIV", "LT", "LET", "GT", "GET", "COMP",
  "DIF", "ASSIGN", "PV", "VIR", "LPAR", "RPAR", "LCOL", "RCOL", "LCHA",
  "RCHA", "ID", "NUM", "ERR", "$accept", "programa", "declaracao-lista",
  "declaracao", "var-declaracao", "num", "id", "tipo-especificador",
  "fun-declaracao", "params", "param-lista", "param", "composto-decl",
  "local-declaracoes", "statement-lista", "statement", "expressao-decl",
  "selecao-decl", "iteracao-decl", "retorno-decl", "expressao", "var",
  "simples-expressao", "relacional", "soma-expressao", "soma", "termo",
  "mult", "fator", "ativacao", "args", "arg-lista", YY_NULLPTR
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
     285
};
# endif

#define YYPACT_NINF (-51)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-17)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      32,    -2,    -2,    41,    32,   -51,   -51,   -51,   -51,    -1,
     -15,   -51,   -51,   -51,    35,    27,    35,   -51,     9,    -2,
      57,    43,   -51,   -51,    61,    70,    67,    72,    66,    79,
      72,    75,     7,   -51,   -51,   -51,   -51,   -51,   -51,    80,
      -2,   -12,    82,   -51,    25,   -51,    84,   -51,   -51,    83,
     -51,    40,    55,   -51,   -51,   -51,   -51,   -51,    86,    73,
     -51,   102,    38,   -51,   -51,    25,    -6,   -51,    93,    25,
      91,    25,    25,   -51,   -51,    68,   -51,   -51,   -51,    25,
     -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,    25,    25,
     -51,   -51,    25,    98,   -51,    99,   -51,   100,   -51,   101,
     105,   -51,   -51,   -51,    69,    38,   -51,    81,    81,   -51,
     -51,    25,   120,   -51,   -51,    81,   -51
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     2,     4,     5,     6,    10,     0,
       0,     1,     3,     7,     0,     0,     0,    11,    12,     0,
       0,    15,    18,     9,     0,     0,    19,     0,     0,     0,
       0,     0,     0,    13,    12,    17,     8,    14,    20,     0,
       0,     0,     0,    35,     0,    24,    10,    26,    64,    43,
      30,     0,     0,    28,    29,    31,    32,    33,     0,    62,
      42,    46,    54,    58,    63,     0,     0,    39,     0,     0,
       0,     0,    67,    22,    25,     0,    23,    27,    34,     0,
      55,    56,    48,    47,    49,    50,    51,    52,     0,     0,
      59,    60,     0,     0,    40,     0,    61,     0,    69,     0,
      66,    21,    41,    62,    45,    53,    57,     0,     0,    44,
      65,     0,    36,    38,    68,     0,    37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -51,   -51,   -51,   123,   -31,   113,     3,   -51,   -51,   114,
     -51,   103,   -21,   -51,    78,   -50,   -51,   -51,   -51,   -51,
     -41,   -37,   -51,   -51,    44,   -51,    45,   -51,    46,   -51,
     -51,   -51
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    48,    49,    19,     7,    20,
      21,    22,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    88,    61,    89,    62,    92,    63,    64,
      99,   100
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      68,    47,    77,    70,     9,    10,    33,    16,    67,    37,
      44,    39,    40,    41,    13,    42,    46,    23,    15,    13,
      74,    14,    26,    15,    93,    77,     8,    43,    95,    44,
      97,    98,   -16,    32,    45,    46,    23,     1,   102,     2,
      17,    11,    18,    66,    39,    40,    41,    44,    42,    90,
      91,   103,   103,    46,    23,   103,    23,   112,   113,    39,
      43,    41,    44,    42,    28,   116,    32,    73,    46,    23,
     114,    17,    39,    34,    41,    43,    42,    44,    80,    81,
      27,    32,    76,    46,    23,    39,    29,    41,    43,    42,
      44,    31,    79,    30,    32,   101,    46,    23,    32,    36,
      38,    43,    65,    44,    69,    72,    78,    32,    71,    46,
      23,    80,    81,    94,    96,    82,    83,    84,    85,    86,
      87,   107,   108,   115,   110,   109,   111,    12,    24,    75,
      25,    35,   104,     0,   105,     0,     0,     0,   106
};

static const yytype_int8 yycheck[] =
{
      41,    32,    52,    44,     1,     2,    27,    22,    20,    30,
      22,     4,     5,     6,    20,     8,    28,    29,    24,    20,
      51,    22,    19,    24,    65,    75,    28,    20,    69,    22,
      71,    72,    23,    26,    27,    28,    29,     5,    79,     7,
       5,     0,     7,    40,     4,     5,     6,    22,     8,    11,
      12,    88,    89,    28,    29,    92,    29,   107,   108,     4,
      20,     6,    22,     8,    21,   115,    26,    27,    28,    29,
     111,     5,     4,     7,     6,    20,     8,    22,     9,    10,
      23,    26,    27,    28,    29,     4,    25,     6,    20,     8,
      22,    24,    19,    23,    26,    27,    28,    29,    26,    20,
      25,    20,    22,    22,    22,    22,    20,    26,    24,    28,
      29,     9,    10,    20,    23,    13,    14,    15,    16,    17,
      18,    23,    23,     3,    23,    25,    21,     4,    15,    51,
      16,    28,    88,    -1,    89,    -1,    -1,    -1,    92
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,     7,    32,    33,    34,    35,    39,    28,    37,
      37,     0,    34,    20,    22,    24,    22,     5,     7,    38,
      40,    41,    42,    29,    36,    40,    37,    23,    21,    25,
      23,    24,    26,    43,     7,    42,    20,    43,    25,     4,
       5,     6,     8,    20,    22,    27,    28,    35,    36,    37,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    55,    57,    59,    60,    22,    37,    20,    51,    22,
      51,    24,    22,    27,    35,    45,    27,    46,    20,    19,
       9,    10,    13,    14,    15,    16,    17,    18,    54,    56,
      11,    12,    58,    51,    20,    51,    23,    51,    51,    61,
      62,    27,    51,    52,    55,    57,    59,    23,    23,    25,
      23,    21,    46,    46,    51,     3,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    35,    35,    36,
      37,    38,    38,    39,    39,    40,    40,    41,    41,    42,
      42,    43,    43,    43,    43,    44,    44,    45,    45,    46,
      46,    46,    46,    46,    47,    47,    48,    48,    49,    50,
      50,    51,    51,    52,    52,    53,    53,    54,    54,    54,
      54,    54,    54,    55,    55,    56,    56,    57,    57,    58,
      58,    59,    59,    59,    59,    60,    61,    61,    62,    62
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     1,     1,     6,     6,     1,     1,     3,     1,     2,
       4,     4,     3,     3,     2,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     2,     1,     5,     7,     5,     2,
       3,     3,     1,     1,     4,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     4,     1,     0,     3,     1
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
        yyerror (YY_("syntax error: cannot back up")); \
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
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
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
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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
      yychar = yylex ();
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
  case 2:
#line 36 "bison/bison.y"
                               { root =  yyvsp[0]; }
#line 1422 "bison.tab.c"
    break;

  case 3:
#line 38 "bison/bison.y"
                                                  {
                    TreeNode* t = yyvsp[-1];
                    if(t != NULL){
                        while(t->sibling != NULL) { t = t->sibling;}
                        t->sibling = yyvsp[0];
                        yyval = yyvsp[-1];
                    } else{
                        yyval = yyvsp[0];
                    }
                    }
#line 1437 "bison.tab.c"
    break;

  case 4:
#line 47 "bison/bison.y"
                                   { yyval = yyvsp[0]; }
#line 1443 "bison.tab.c"
    break;

  case 5:
#line 49 "bison/bison.y"
                               {yyval = yyvsp[0];}
#line 1449 "bison.tab.c"
    break;

  case 6:
#line 50 "bison/bison.y"
                                 {yyval = yyvsp[0];}
#line 1455 "bison.tab.c"
    break;

  case 7:
#line 52 "bison/bison.y"
                              {
                        yyval = newExpNode(TypeK);
                        yyval->type = IntegerK;
                        yyval->attr.name = "inteiro";
                        yyval->child[0] = yyvsp[-1];
                        yyvsp[-1]->nodekind = StmtK;
                        yyvsp[-1]->kind.stmt = VarK;
                        yyvsp[-1]->type = IntegerK;
                    }
#line 1469 "bison.tab.c"
    break;

  case 8:
#line 61 "bison/bison.y"
                                              {
                        yyval = newExpNode(TypeK);
                        yyval->type = IntegerK;
                        yyval->attr.name = "inteiro";
                        yyval->child[0] = yyvsp[-4];
                        yyvsp[-4]->nodekind = StmtK;
                        yyvsp[-4]->kind.stmt = VarK;
                        yyvsp[-4]->type = IntegerK; 
                        yyvsp[-4]->attr.len = yyvsp[-2]->attr.val;
                    }
#line 1484 "bison.tab.c"
    break;

  case 9:
#line 73 "bison/bison.y"
             {
        yyval = newExpNode(ConstK);
        yyval->attr.val = atoi(yytext);
        yyval->type = IntegerK;
    }
#line 1494 "bison.tab.c"
    break;

  case 10:
#line 79 "bison/bison.y"
           { 
      yyval = newExpNode(IdK);
      yyval->attr.name = copyString(yytext);
    }
#line 1503 "bison.tab.c"
    break;

  case 11:
#line 84 "bison/bison.y"
                            {
                            yyval = newExpNode(TypeK);
                            yyval->attr.name = "inteiro";
                            yyval->type = IntegerK;
                        }
#line 1513 "bison.tab.c"
    break;

  case 12:
#line 89 "bison/bison.y"
                               {
                            yyval = newExpNode(TypeK);
                            yyval->attr.name = "void";
                            yyval->type = VoidK;
                        }
#line 1523 "bison.tab.c"
    break;

  case 13:
#line 95 "bison/bison.y"
                                                         {
        yyval = newExpNode(TypeK);
        yyval->type = IntegerK;
        yyval->attr.name = "inteiro";
        yyval->child[0] = yyvsp[-4];
        yyvsp[-4]->child[0] = yyvsp[-2];
        yyvsp[-4]->child[1] = yyvsp[0];
        yyvsp[-4]->nodekind = StmtK;
        yyvsp[-4]->kind.stmt = FunK;
        yyvsp[-4]->type = IntegerK;
        yyvsp[-2]->type = IntegerK;
    }
#line 1540 "bison.tab.c"
    break;

  case 14:
#line 106 "bison/bison.y"
                                              {
        yyval = newExpNode(TypeK);
        yyval->type = VoidK;
        yyval->attr.name = "void";
        yyval->child[0] = yyvsp[-4];
        yyvsp[-4]->child[0] = yyvsp[-2];
        yyvsp[-4]->child[1] = yyvsp[0];
        yyvsp[-4]->nodekind = StmtK;
        yyvsp[-4]->kind.stmt = FunK;
    }
#line 1555 "bison.tab.c"
    break;

  case 15:
#line 117 "bison/bison.y"
                        {yyval = yyvsp[0];}
#line 1561 "bison.tab.c"
    break;

  case 16:
#line 118 "bison/bison.y"
           {
        yyval = newExpNode(TypeK);
        yyval->attr.name = "void";
        yyval->child[0] = NULL; 
    }
#line 1571 "bison.tab.c"
    break;

  case 17:
#line 124 "bison/bison.y"
                                       {
        TreeNode* t = yyvsp[-2];
        if(t != NULL){
            while(t->sibling != NULL) { t = t->sibling;}
            t->sibling = yyvsp[0];
            yyval = yyvsp[-2];
        } else{
            yyval = yyvsp[0];
        }
    }
#line 1586 "bison.tab.c"
    break;

  case 18:
#line 133 "bison/bison.y"
              {yyval = yyvsp[0];}
#line 1592 "bison.tab.c"
    break;

  case 19:
#line 134 "bison/bison.y"
                                 {
        yyval = newExpNode(TypeK);
        yyval->child[0]= yyvsp[0];
        yyval->type = yyvsp[-1]->type;
        yyval->attr.name = yyvsp[-1]->attr.name;
        yyvsp[0]->nodekind = StmtK;
        yyvsp[0]->kind.stmt = VarK;
        yyvsp[0]->type = yyvsp[-1]->type;
    }
#line 1606 "bison.tab.c"
    break;

  case 20:
#line 142 "bison/bison.y"
                                        {
        yyval= newExpNode(TypeK);
        yyval->child[0]= yyvsp[-2];
        yyval->type = yyvsp[-3]->type;
        yyval->attr.name = yyvsp[-3]->attr.name;
        yyvsp[-2]->nodekind = StmtK;
        yyvsp[-2]->type = yyvsp[-3]->type;
        yyvsp[-2]->kind.stmt = VetK;
    }
#line 1620 "bison.tab.c"
    break;

  case 21:
#line 152 "bison/bison.y"
                                                              {
        TreeNode* t = yyvsp[-2];
        if(t != NULL){
            while(t->sibling != NULL)
            t = t->sibling;
            t->sibling = yyvsp[-1];
            yyval = yyvsp[-2];
        } 
        else yyval = yyvsp[-1];
    }
#line 1635 "bison.tab.c"
    break;

  case 22:
#line 162 "bison/bison.y"
              {
                yyval = yyvsp[-1];
              }
#line 1643 "bison.tab.c"
    break;

  case 23:
#line 166 "bison/bison.y"
              {
                yyval = yyvsp[-1];
              }
#line 1651 "bison.tab.c"
    break;

  case 24:
#line 169 "bison/bison.y"
                          {}
#line 1657 "bison.tab.c"
    break;

  case 25:
#line 172 "bison/bison.y"
                                                        {
        TreeNode* t = yyvsp[-1];
        if(t != NULL){
            while(t->sibling != NULL) { t = t->sibling;}
            t->sibling = yyvsp[0];
            yyval = yyvsp[-1];
        } else{
            yyval = yyvsp[0];
        }
    }
#line 1672 "bison.tab.c"
    break;

  case 26:
#line 181 "bison/bison.y"
                        {yyval = yyvsp[0];}
#line 1678 "bison.tab.c"
    break;

  case 27:
#line 183 "bison/bison.y"
                                               {
        TreeNode* t = yyvsp[-1];
        if(t != NULL){
            while(t->sibling != NULL) { t = t->sibling;}
            t->sibling = yyvsp[0];
            yyval = yyvsp[-1];
        } else{
            yyval = yyvsp[0];
        }
    }
#line 1693 "bison.tab.c"
    break;

  case 28:
#line 192 "bison/bison.y"
                  {yyval = yyvsp[0];}
#line 1699 "bison.tab.c"
    break;

  case 29:
#line 195 "bison/bison.y"
                       {yyval = yyvsp[0];}
#line 1705 "bison.tab.c"
    break;

  case 30:
#line 196 "bison/bison.y"
                        {yyval = yyvsp[0];}
#line 1711 "bison.tab.c"
    break;

  case 31:
#line 197 "bison/bison.y"
                       {yyval = yyvsp[0];}
#line 1717 "bison.tab.c"
    break;

  case 32:
#line 198 "bison/bison.y"
                        {yyval = yyvsp[0];}
#line 1723 "bison.tab.c"
    break;

  case 33:
#line 199 "bison/bison.y"
                       {yyval = yyvsp[0];}
#line 1729 "bison.tab.c"
    break;

  case 34:
#line 200 "bison/bison.y"
                                 { yyval = yyvsp[-1]; }
#line 1735 "bison.tab.c"
    break;

  case 36:
#line 201 "bison/bison.y"
                                                   {
        yyval = newStmtNode(IfK);
        yyval->child[0] = yyvsp[-2];
        yyval->child[1] = yyvsp[0];
    }
#line 1745 "bison.tab.c"
    break;

  case 37:
#line 206 "bison/bison.y"
                                                      {
        yyval = newStmtNode(IfK);
        yyval->child[0] = yyvsp[-4];
        yyval->child[1] = yyvsp[-2];
        yyval->child[2] = yyvsp[0];
    }
#line 1756 "bison.tab.c"
    break;

  case 38:
#line 213 "bison/bison.y"
                                                       {
        yyval = newStmtNode(WhileK);
        yyval->child[0] = yyvsp[-2];
        yyval->child[1] = yyvsp[0];
    }
#line 1766 "bison.tab.c"
    break;

  case 39:
#line 219 "bison/bison.y"
                            {
        yyval = newStmtNode(ReturnK);
    }
#line 1774 "bison.tab.c"
    break;

  case 40:
#line 221 "bison/bison.y"
                            {
        yyval = newStmtNode(ReturnK);
        yyval->child[0] = yyvsp[-1];
    }
#line 1783 "bison.tab.c"
    break;

  case 41:
#line 226 "bison/bison.y"
                                    {
        yyval = newStmtNode(AssignK);
        yyval->attr.name = yyvsp[-2]->attr.name;
        yyval->child[0] = yyvsp[-2];
        yyval->child[1] = yyvsp[0];
    }
#line 1794 "bison.tab.c"
    break;

  case 42:
#line 231 "bison/bison.y"
                          { yyval = yyvsp[0];}
#line 1800 "bison.tab.c"
    break;

  case 43:
#line 233 "bison/bison.y"
            { yyval = yyvsp[0];}
#line 1806 "bison.tab.c"
    break;

  case 44:
#line 233 "bison/bison.y"
                                                 {
        yyval = yyvsp[-3];
        yyval->child[0] = yyvsp[-1];
        yyval->kind.exp = VetK;
        yyval->type = IntegerK;
    }
#line 1817 "bison.tab.c"
    break;

  case 45:
#line 240 "bison/bison.y"
                                                                {
        yyval = yyvsp[-1];
        yyval->child[0] = yyvsp[-2];
        yyval->child[1] = yyvsp[0];
    }
#line 1827 "bison.tab.c"
    break;

  case 46:
#line 244 "bison/bison.y"
                      { yyval = yyvsp[0]; }
#line 1833 "bison.tab.c"
    break;

  case 47:
#line 246 "bison/bison.y"
                    { 
        yyval = newExpNode(OpK);
        yyval->attr.op = LET;                            
		yyval->type = BooleanK;
    }
#line 1843 "bison.tab.c"
    break;

  case 48:
#line 251 "bison/bison.y"
          {
        yyval = newExpNode(OpK);
        yyval->attr.op = LT;                            
		yyval->type = BooleanK;
     
    }
#line 1854 "bison.tab.c"
    break;

  case 49:
#line 257 "bison/bison.y"
          {
        yyval = newExpNode(OpK);
        yyval->attr.op = GT;                            
		yyval->type = BooleanK; 
    }
#line 1864 "bison.tab.c"
    break;

  case 50:
#line 262 "bison/bison.y"
          {
        yyval = newExpNode(OpK);
        yyval->attr.op = GET;                            
		yyval->type = BooleanK; 
    }
#line 1874 "bison.tab.c"
    break;

  case 51:
#line 267 "bison/bison.y"
           {
        yyval = newExpNode(OpK);
        yyval->attr.op = COMP;                            
		yyval->type = BooleanK; 
    }
#line 1884 "bison.tab.c"
    break;

  case 52:
#line 272 "bison/bison.y"
          {
        yyval = newExpNode(OpK);
        yyval->attr.op = DIF;                            
		yyval->type = BooleanK;
    }
#line 1894 "bison.tab.c"
    break;

  case 53:
#line 278 "bison/bison.y"
                                              {
        yyval = yyvsp[-1];
        yyval->child[0] = yyvsp[-2];
        yyval->child[1] = yyvsp[0];
    }
#line 1904 "bison.tab.c"
    break;

  case 54:
#line 282 "bison/bison.y"
              { yyval = yyvsp[0]; }
#line 1910 "bison.tab.c"
    break;

  case 55:
#line 284 "bison/bison.y"
               {
        yyval = newExpNode(OpK);
        yyval->attr.op = PLUS;  
    }
#line 1919 "bison.tab.c"
    break;

  case 56:
#line 288 "bison/bison.y"
          {
        yyval = newExpNode(OpK);
        yyval->attr.op = SUB;  
    }
#line 1928 "bison.tab.c"
    break;

  case 57:
#line 293 "bison/bison.y"
                            {
        yyval = yyvsp[-1];
        yyval->child[0] = yyvsp[-2];
        yyval->child[1] = yyvsp[0];
    }
#line 1938 "bison.tab.c"
    break;

  case 58:
#line 297 "bison/bison.y"
              { yyval = yyvsp[0];}
#line 1944 "bison.tab.c"
    break;

  case 59:
#line 299 "bison/bison.y"
               {
        yyval = newExpNode(OpK);
        yyval->attr.op = MULT; 
    }
#line 1953 "bison.tab.c"
    break;

  case 60:
#line 302 "bison/bison.y"
            {
        yyval = newExpNode(OpK);
        yyval->attr.op = DIV; 
    }
#line 1962 "bison.tab.c"
    break;

  case 61:
#line 307 "bison/bison.y"
                               { yyval = yyvsp[-1]; }
#line 1968 "bison.tab.c"
    break;

  case 62:
#line 308 "bison/bison.y"
          {  yyval = yyvsp[0]; }
#line 1974 "bison.tab.c"
    break;

  case 63:
#line 309 "bison/bison.y"
               { yyval = yyvsp[0]; }
#line 1980 "bison.tab.c"
    break;

  case 64:
#line 310 "bison/bison.y"
          {yyval = yyvsp[0];}
#line 1986 "bison.tab.c"
    break;

  case 65:
#line 312 "bison/bison.y"
                                {
        yyval = yyvsp[-3];
        yyval->child[0] = yyvsp[-1];
        yyval->nodekind = StmtK;
        yyval->kind.stmt = CallK;
    }
#line 1997 "bison.tab.c"
    break;

  case 66:
#line 318 "bison/bison.y"
                    { yyval = yyvsp[0]; }
#line 2003 "bison.tab.c"
    break;

  case 67:
#line 318 "bison/bison.y"
                                   { yyval = NULL; }
#line 2009 "bison.tab.c"
    break;

  case 68:
#line 319 "bison/bison.y"
                                       {
        TreeNode* t = yyvsp[-2];
        if(t != NULL){
            while(t->sibling != NULL) { t = t->sibling;}
            t->sibling = yyvsp[0];
            yyval = yyvsp[-2];
        } else{
            yyval = yyvsp[0] ;
        }
    }
#line 2024 "bison.tab.c"
    break;

  case 69:
#line 328 "bison/bison.y"
                  { yyval = yyvsp[0]; }
#line 2030 "bison.tab.c"
    break;


#line 2034 "bison.tab.c"

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
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
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
                      yytoken, &yylval);
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
                  yystos[yystate], yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
#line 330 "bison/bison.y"


int yyerror(char *msg){
    printf("ERRO SINTÁTICO: %s LINHA: %d\n", yytext, lineno);
}


TreeNode* parse(){
    yyparse();
    printTree(root);
    return root;
}

