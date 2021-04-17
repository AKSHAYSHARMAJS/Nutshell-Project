/* A Bison parser, made by GNU Bison 3.7.6.  */

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
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"


#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include <string>
#include <unistd.h>
#include <stddef.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <pwd.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <readline/readline.h>
#include <readline/history.h>
#include <time.h>



int yylex();

int yyparse();

void yyerror(char *s){
	fprintf(stderr, "error: %s\n",s);
}

int cmd_number = -1;
char* varTbl[128][100];
char* wildcard[100];
char* users[1000];
int wild = 0;
int row = 0;
int col = 0;
char* temp_string = "temp";
char* temp_string2 = "temp";
char* io = "";
LL *list;
int filedesc;

char* alias_expand(char* name)
{
	return command_expand(list, name);
}

bool match(char *first, char * second)
{
    if (*first == '\0' && *second == '\0')
        return true;

    if (*first == '*' && *(first+1) != '\0' && *second == '\0')
        return false;

    if (*first == '?' || *first == *second)
        return match(first+1, second+1);

    if (*first == '*')
        return match(first+1, second) || match(first, second+1);
    return false;
}


#line 139 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BYE = 3,                        /* BYE  */
  YYSYMBOL_ENDF = 4,                       /* ENDF  */
  YYSYMBOL_CD = 5,                         /* CD  */
  YYSYMBOL_ALIAS = 6,                      /* ALIAS  */
  YYSYMBOL_QUOTE = 7,                      /* QUOTE  */
  YYSYMBOL_UNALIAS = 8,                    /* UNALIAS  */
  YYSYMBOL_SETENV = 9,                     /* SETENV  */
  YYSYMBOL_PRINTENV = 10,                  /* PRINTENV  */
  YYSYMBOL_UNSETENV = 11,                  /* UNSETENV  */
  YYSYMBOL_LESS = 12,                      /* LESS  */
  YYSYMBOL_GREATER = 13,                   /* GREATER  */
  YYSYMBOL_STAR = 14,                      /* STAR  */
  YYSYMBOL_AND = 15,                       /* AND  */
  YYSYMBOL_QUESTION = 16,                  /* QUESTION  */
  YYSYMBOL_DOLLAR = 17,                    /* DOLLAR  */
  YYSYMBOL_OCURL = 18,                     /* OCURL  */
  YYSYMBOL_CCURL = 19,                     /* CCURL  */
  YYSYMBOL_LS = 20,                        /* LS  */
  YYSYMBOL_PRINT = 21,                     /* PRINT  */
  YYSYMBOL_PWD = 22,                       /* PWD  */
  YYSYMBOL_TILDE = 23,                     /* TILDE  */
  YYSYMBOL_TOUCH = 24,                     /* TOUCH  */
  YYSYMBOL_HEAD = 25,                      /* HEAD  */
  YYSYMBOL_TAIL = 26,                      /* TAIL  */
  YYSYMBOL_CAT = 27,                       /* CAT  */
  YYSYMBOL_WC = 28,                        /* WC  */
  YYSYMBOL_ESC = 29,                       /* ESC  */
  YYSYMBOL_MKDIR = 30,                     /* MKDIR  */
  YYSYMBOL_RM = 31,                        /* RM  */
  YYSYMBOL_DATE = 32,                      /* DATE  */
  YYSYMBOL_WORD = 33,                      /* WORD  */
  YYSYMBOL_ARG = 34,                       /* ARG  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_cmdline = 36,                   /* cmdline  */
  YYSYMBOL_cmd = 37,                       /* cmd  */
  YYSYMBOL_envexpand = 38,                 /* envexpand  */
  YYSYMBOL_params = 39,                    /* params  */
  YYSYMBOL_bye = 40,                       /* bye  */
  YYSYMBOL_redirectIO = 41,                /* redirectIO  */
  YYSYMBOL_cd = 42,                        /* cd  */
  YYSYMBOL_date = 43,                      /* date  */
  YYSYMBOL_alias = 44,                     /* alias  */
  YYSYMBOL_unalias = 45,                   /* unalias  */
  YYSYMBOL_setenv = 46,                    /* setenv  */
  YYSYMBOL_unsetenv = 47,                  /* unsetenv  */
  YYSYMBOL_printenv = 48,                  /* printenv  */
  YYSYMBOL_ls = 49,                        /* ls  */
  YYSYMBOL_touch = 50,                     /* touch  */
  YYSYMBOL_head = 51,                      /* head  */
  YYSYMBOL_tail = 52,                      /* tail  */
  YYSYMBOL_echo = 53,                      /* echo  */
  YYSYMBOL_pwd = 54,                       /* pwd  */
  YYSYMBOL_cat = 55,                       /* cat  */
  YYSYMBOL_mkdir = 56,                     /* mkdir  */
  YYSYMBOL_rm = 57,                        /* rm  */
  YYSYMBOL_wc = 58,                        /* wc  */
  YYSYMBOL_word = 59                       /* word  */
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
#define YYLAST   166

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    83,    83,    84,    86,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    91,    97,   100,   103,
     106,   109,   112,   115,   123,   126,   129,   137,   144,   179,
     211,   232,   257,   258,   261,   264,   267,   271,   278,   281,
     288,   291,   307,   314,   325,   385,   393,   403,   408,   414,
     418,   426,   437,   448,   461,   480,   489,   499,   513,   516,
     528,   531,   538,   549,   560,   572,   578,   587,   593,   603,
     613,   619,   630,   633,   636,   642,   650,   665,   682,   695,
     701,   729
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
  "\"end of file\"", "error", "\"invalid token\"", "BYE", "ENDF", "CD",
  "ALIAS", "QUOTE", "UNALIAS", "SETENV", "PRINTENV", "UNSETENV", "LESS",
  "GREATER", "STAR", "AND", "QUESTION", "DOLLAR", "OCURL", "CCURL", "LS",
  "PRINT", "PWD", "TILDE", "TOUCH", "HEAD", "TAIL", "CAT", "WC", "ESC",
  "MKDIR", "RM", "DATE", "WORD", "ARG", "$accept", "cmdline", "cmd",
  "envexpand", "params", "bye", "redirectIO", "cd", "date", "alias",
  "unalias", "setenv", "unsetenv", "printenv", "ls", "touch", "head",
  "tail", "echo", "pwd", "cat", "mkdir", "rm", "wc", "word", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289
};
#endif

#define YYPACT_NINF (-30)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-36)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -30,     3,   -30,   -30,   -30,    90,   -29,   -16,   -15,     9,
      13,    27,    51,    74,    60,    12,   -30,    25,    30,    81,
      50,    54,    83,    84,   -30,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   116,
     -30,   -30,   -30,   -30,    87,    62,   -30,    89,    63,   133,
      33,   110,   -30,    98,   -30,    76,   -30,   -30,    96,   -30,
     133,   -30,    -7,   -30,    99,   -30,     9,   100,   -30,   101,
     102,   -30,   -30,   -30,   -30,    42,   -30,   -30,   115,   -30,
     114,   130,   -30,   -30,   116,    22,   118,   116,   126,   133,
     -30,   -30,   134,   -30,   145,   147,   148,   -30,   -30,   -30,
     149,   -30,   -30,   -30,   124,    45,   139,    69,   -30,   -30,
     -30,   -30,   -30,   -30,   -30,   141,   -30,   -30,   -30,   -30
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,    43,    42,    48,    58,     0,     0,    68,
       0,    45,    44,     0,    70,     0,    85,     0,     0,     0,
       0,     0,     0,     0,    55,    91,     3,    18,     5,    12,
       6,    23,     7,     8,     9,    11,    10,    13,    19,    20,
      21,    14,    15,    24,    16,    17,    22,    25,    27,     0,
      28,    29,    31,    30,     0,    32,    34,    50,    35,    49,
       0,     0,    59,     0,    69,    65,    47,    46,     0,    74,
      71,    72,     0,    82,     0,    75,    77,     0,    80,     0,
       0,    86,    90,    88,    89,     0,    38,    33,    51,    39,
      41,     0,    36,    53,     0,    56,     0,     0,    61,     0,
      66,    67,     0,    73,     0,     0,     0,    78,    79,    81,
       0,    52,    54,    40,     0,     0,     0,     0,    63,    64,
      26,    83,    84,    76,    87,     0,    57,    60,    62,    37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -30,   -30,   -30,    91,   -12,   -30,    -9,   -30,   -30,   -30,
     -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,   -30,   -30,   -30
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    26,    27,    59,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,    61,    70,     2,    60,    71,     3,     4,     5,     6,
      13,     7,     8,     9,    10,    11,    12,    62,    63,    72,
      13,    11,    12,    14,    15,    16,   104,    17,    18,    19,
      20,    21,    74,    22,    23,    24,    25,    85,    48,    91,
      94,    50,    51,    52,    53,    73,    65,    54,    95,   111,
      93,    99,   126,    55,    56,    92,   101,    80,    75,    91,
      66,   103,    91,    76,    77,    48,    58,   107,    50,    51,
      52,    53,    11,    12,    54,    92,   128,    89,    92,    90,
      55,    56,   115,    81,    67,   117,    91,    82,    11,    12,
     119,   100,    68,    58,    69,    48,    87,    49,    50,    51,
      52,    53,    92,    48,    54,    97,    50,    51,    52,    53,
      55,    56,    54,    57,    78,    79,    83,    84,    55,    56,
      86,    48,    88,    58,    50,    51,    52,    53,    96,   102,
      54,    98,   106,   108,   109,   110,    55,    56,   -35,   -35,
      89,   118,    90,   -35,   112,    11,    12,   113,   114,    58,
      91,   116,   121,   120,   122,   123,   124,   125,   127,   -35,
     129,     0,     0,   105,     0,     0,    92
};

static const yytype_int8 yycheck[] =
{
       9,    17,    14,     0,    33,    14,     3,     4,     5,     6,
      17,     8,     9,    10,    11,    12,    13,    33,    33,     7,
      17,    12,    13,    20,    21,    22,    33,    24,    25,    26,
      27,    28,     7,    30,    31,    32,    33,    49,     5,    17,
       7,     8,     9,    10,    11,    33,    33,    14,    60,     7,
      59,    63,     7,    20,    21,    33,    65,     7,    33,    17,
      33,    70,    17,    33,    34,     5,    33,    76,     8,     9,
      10,    11,    12,    13,    14,    33,     7,    14,    33,    16,
      20,    21,    94,    33,    33,    97,    17,    33,    12,    13,
      99,    15,    18,    33,    34,     5,    34,     7,     8,     9,
      10,    11,    33,     5,    14,     7,     8,     9,    10,    11,
      20,    21,    14,    23,    33,    34,    33,    33,    20,    21,
      33,     5,    33,    33,     8,     9,    10,    11,    18,    33,
      14,    33,    33,    33,    33,    33,    20,    21,    12,    13,
      14,    15,    16,    17,    29,    12,    13,    33,    18,    33,
      17,    33,     7,    19,     7,     7,     7,    33,    19,    33,
      19,    -1,    -1,    72,    -1,    -1,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    36,     0,     3,     4,     5,     6,     8,     9,    10,
      11,    12,    13,    17,    20,    21,    22,    24,    25,    26,
      27,    28,    30,    31,    32,    33,    37,    38,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,     5,     7,
       8,     9,    10,    11,    14,    20,    21,    23,    33,    39,
      33,    17,    33,    33,    41,    33,    33,    33,    18,    34,
      39,    41,     7,    33,     7,    33,    33,    34,    33,    34,
       7,    33,    33,    33,    33,    39,    33,    34,    33,    14,
      16,    17,    33,    41,     7,    39,    18,     7,    33,    39,
      15,    41,    33,    41,    33,    38,    33,    41,    33,    33,
      33,     7,    29,    33,    18,    39,    33,    39,    15,    41,
      19,     7,     7,     7,     7,    33,     7,    19,     7,    19
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    36,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    38,    39,    39,    39,
      39,    39,    39,    39,    39,    39,    39,    39,    39,    39,
      39,    39,    40,    40,    41,    41,    41,    41,    42,    42,
      42,    42,    42,    42,    42,    43,    44,    44,    44,    45,
      45,    46,    46,    46,    46,    47,    47,    47,    48,    48,
      49,    49,    49,    49,    49,    50,    50,    51,    51,    51,
      52,    52,    53,    53,    53,    54,    55,    55,    56,    57,
      58,    59
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     2,     5,     2,     2,
       3,     2,     1,     1,     1,     1,     2,     2,     1,     2,
       2,     3,     4,     3,     4,     1,     3,     5,     1,     2,
       5,     3,     5,     4,     4,     2,     3,     3,     1,     2,
       1,     2,     2,     3,     2,     2,     4,     2,     3,     3,
       2,     3,     2,     4,     4,     1,     2,     4,     2,     2,
       2,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
      yychar = yylex ();
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
  case 26: /* envexpand: DOLLAR OCURL WORD CCURL  */
#line 91 "parser.y"
                                        {
			 	printf("%s\n",getenv((yyvsp[-1].string)));
			}
#line 1291 "parser.tab.c"
    break;

  case 27: /* params: CD  */
#line 97 "parser.y"
                   {
			temp_string = "cd";
		}
#line 1299 "parser.tab.c"
    break;

  case 28: /* params: UNALIAS  */
#line 100 "parser.y"
                          {
			temp_string = "unalias";
		}
#line 1307 "parser.tab.c"
    break;

  case 29: /* params: SETENV  */
#line 103 "parser.y"
                               {
			temp_string = "setenv";
		}
#line 1315 "parser.tab.c"
    break;

  case 30: /* params: UNSETENV  */
#line 106 "parser.y"
                           {
			temp_string = "unsetenv";
		}
#line 1323 "parser.tab.c"
    break;

  case 31: /* params: PRINTENV  */
#line 109 "parser.y"
                           {
			temp_string = "printenv";
		}
#line 1331 "parser.tab.c"
    break;

  case 32: /* params: LS  */
#line 112 "parser.y"
                     {
			temp_string = "ls";
		}
#line 1339 "parser.tab.c"
    break;

  case 33: /* params: LS ARG  */
#line 115 "parser.y"
                        {
			temp_string = "ls";
			char buffer[100];
			strcpy(buffer, temp_string);
			strcat(buffer, " ");
			strcat(buffer, (yyvsp[0].string));
			temp_string = buffer;
		}
#line 1352 "parser.tab.c"
    break;

  case 34: /* params: PRINT  */
#line 123 "parser.y"
                        {
			temp_string = "echo";
		}
#line 1360 "parser.tab.c"
    break;

  case 35: /* params: WORD  */
#line 126 "parser.y"
                       {
			temp_string = (yyvsp[0].string);
		}
#line 1368 "parser.tab.c"
    break;

  case 36: /* params: params WORD  */
#line 129 "parser.y"
                              {
			char buffer[100];
			strcpy(buffer, temp_string);
			strcat(buffer, " ");
			strcat(buffer, (yyvsp[0].string));
			temp_string = buffer;
		}
#line 1380 "parser.tab.c"
    break;

  case 37: /* params: params DOLLAR OCURL WORD CCURL  */
#line 137 "parser.y"
                                                  {
			char buffer[100];
			strcpy(buffer, temp_string);
			strcat(buffer, " ");
			strcat(buffer, getenv((yyvsp[-1].string)));
			temp_string = buffer;
		}
#line 1392 "parser.tab.c"
    break;

  case 38: /* params: STAR WORD  */
#line 144 "parser.y"
                            {
			wild = 0;
			struct dirent *dir;
			DIR *d;
			d = opendir(".");
			int matching, length = strlen((yyvsp[0].string));
			char *stringin = (yyvsp[0].string), *stringout;
			if(d)
			{
				while ((dir = readdir(d)) != NULL)
				{
					matching = 1;
					stringout = dir->d_name;
					int outlength = strlen(stringout) -1;
					int k;
					for (k = length - 1; k >= 0; k--)
					 {
						if (stringout[outlength] != stringin[k])
						{
							matching = 0;
							break;
						}
						outlength--;
					}
					if (matching == 1)
					{
						temp_string = stringout;
						wildcard[wild] = temp_string;
						wild++;

					}
				}
			closedir(d);
			}
		}
#line 1432 "parser.tab.c"
    break;

  case 39: /* params: WORD STAR  */
#line 179 "parser.y"
                            {
			wild = 0;
			struct dirent *dir;
			DIR *d;
			d = opendir(".");
			int matching, length = strlen((yyvsp[-1].string));
			char *stringin = (yyvsp[-1].string), *stringout;
			if(d)
			{
				while ((dir = readdir(d)) != NULL)
				{
					matching = 1;
					stringout = dir->d_name;
					int k;
					for (k = 0; k < length; k++)
					{
						if (stringout[k] != stringin[k])
						{
							matching = 0;
							break;
						}
					}
					if (matching == 1)
					{
						temp_string = stringout;
						wildcard[wild] = temp_string;
						wild++;
					}
				}
			closedir(d);
			}
		}
#line 1469 "parser.tab.c"
    break;

  case 40: /* params: WORD QUESTION WORD  */
#line 211 "parser.y"
                                     {
			wild = 0;
			DIR *d;
			struct dirent *dir;
			d = opendir(".");
			char *stringin = (yyvsp[-2].string), *stringinright = (yyvsp[0].string);
			strcat(stringin,"?");
			strcat(stringin, stringinright);
			if(d)
			{
				while ((dir = readdir(d)) != NULL)
				{
					if (match(stringin, dir->d_name))
					{
						wildcard[wild] = dir->d_name;
						wild++;
					}
				}
			closedir(d);
			}
		}
#line 1495 "parser.tab.c"
    break;

  case 41: /* params: WORD QUESTION  */
#line 232 "parser.y"
                                {
			printf("%s", (yyvsp[-1].string));
			wild = 0;
			DIR *d;
			struct dirent *dir;
			d = opendir(".");
			char *stringin = (yyvsp[-1].string);
			strcat(stringin,"?");
			if(d)
			{
				while ((dir = readdir(d)) != NULL)
				{
					if (match(stringin, dir->d_name))
					{
						printf("%s", dir->d_name);
						wildcard[wild] = dir->d_name;
						wild++;
					}
				}
			closedir(d);
			}
		}
#line 1522 "parser.tab.c"
    break;

  case 42: /* bye: ENDF  */
#line 257 "parser.y"
       { exit(0);}
#line 1528 "parser.tab.c"
    break;

  case 43: /* bye: BYE  */
#line 258 "parser.y"
        { cmd_number = 1;}
#line 1534 "parser.tab.c"
    break;

  case 44: /* redirectIO: GREATER  */
#line 261 "parser.y"
                        {
			io = "greater";
		}
#line 1542 "parser.tab.c"
    break;

  case 45: /* redirectIO: LESS  */
#line 264 "parser.y"
                       {
			io = "less";
		}
#line 1550 "parser.tab.c"
    break;

  case 46: /* redirectIO: GREATER WORD  */
#line 267 "parser.y"
                                     {
			temp_string2 = (yyvsp[0].string);
			io = "greater";
		}
#line 1559 "parser.tab.c"
    break;

  case 47: /* redirectIO: LESS WORD  */
#line 271 "parser.y"
                                  {
				temp_string2 = (yyvsp[0].string);
				io = "less";
			}
#line 1568 "parser.tab.c"
    break;

  case 48: /* cd: CD  */
#line 278 "parser.y"
           {
			cmd_number = 2;
		}
#line 1576 "parser.tab.c"
    break;

  case 49: /* cd: CD params  */
#line 281 "parser.y"
                    {
			cmd_number = 3;
			col = 0;
			varTbl[row][col] = temp_string;
			col++;
			row++;
	}
#line 1588 "parser.tab.c"
    break;

  case 50: /* cd: CD TILDE  */
#line 288 "parser.y"
                   {
		cmd_number = 2;
	}
#line 1596 "parser.tab.c"
    break;

  case 51: /* cd: CD TILDE WORD  */
#line 291 "parser.y"
                       {
		struct passwd *pw;
		if((pw = getpwnam((yyvsp[0].string))) == NULL)
    {
          fprintf(stderr, "unknown user %s\n", (yyvsp[0].string));
    }
		else
		{
			cmd_number = 3;
			col = 0;
			varTbl[row][col] = pw->pw_dir;
			col++;
			row++;
		}

	}
#line 1617 "parser.tab.c"
    break;

  case 52: /* cd: CD QUOTE params QUOTE  */
#line 307 "parser.y"
                               {
		cmd_number = 3;
		col = 0;
		varTbl[row][col] = temp_string;
		col++;
		row++;
	}
#line 1629 "parser.tab.c"
    break;

  case 53: /* cd: CD params redirectIO  */
#line 314 "parser.y"
                               {
		cmd_number = 3;
		col= 0;
		varTbl[row][col] = temp_string;
		col++;
		varTbl[row][col] = io;
		col++;
		varTbl[row][col] = temp_string2;
		col++;
		row++;
	}
#line 1645 "parser.tab.c"
    break;

  case 54: /* cd: CD TILDE WORD ESC  */
#line 325 "parser.y"
                           {

		/*while (true) {
		 errno = 0; // so we can distinguish errors from no more entries
		 passwd* entry = getpwent();
		 if (!entry) {
				 if (errno) {
						 std::cerr << "Error reading password database\n";
						 return EXIT_FAILURE;
				 }
				 break;
		 }
		 std::cout << entry->pw_name << '\n';
 }
 endpwent();*/

			struct dirent *dir;
			DIR *d;
			char path[100] = "";
			strcat(path, getenv("HOME"));
			printf("%s early", path);
			strcat(path,"/..");
			d = opendir(path);
			int matching, length = strlen((yyvsp[-1].string));
			char *stringin = (yyvsp[-1].string), *stringout;
			if(d)
			{
				while ((dir = readdir(d)) != NULL)
				{
					matching = 1;
					stringout = dir->d_name;
					int k;
					for (k = 0; k < length; k++)
					{
						if (stringout[k] != stringin[k])
						{
							matching = 0;
							break;
						}
					}
					if (matching == 1)
					{
						temp_string = stringout;
						break;
					}
				}
			closedir(d);
			}
			strcat(path,"/");
			strcat(path,temp_string);
			cmd_number = 3;
			col = 0;
			varTbl[row][col] = path;
			col++;
			row++;

	}
#line 1707 "parser.tab.c"
    break;

  case 55: /* date: DATE  */
#line 385 "parser.y"
             {
		time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	}
#line 1717 "parser.tab.c"
    break;

  case 56: /* alias: ALIAS WORD params  */
#line 393 "parser.y"
                                   {
			cmd_number = 4;
			char *name = (yyvsp[-1].string);
			char *value = temp_string;
			varTbl[row][col] = name;
			col++;
			varTbl[row][col] = value;
			col++;
			row++;
		}
#line 1732 "parser.tab.c"
    break;

  case 57: /* alias: ALIAS WORD QUOTE params QUOTE  */
#line 403 "parser.y"
                                                {
			char *name = (yyvsp[-3].string);
			char *value = temp_string;
			push_LL(list, name, value);
		}
#line 1742 "parser.tab.c"
    break;

  case 58: /* alias: ALIAS  */
#line 408 "parser.y"
                        {
			print_LL(list);
		}
#line 1750 "parser.tab.c"
    break;

  case 59: /* unalias: UNALIAS WORD  */
#line 414 "parser.y"
                                    {
			char *name = (yyvsp[0].string);
			remove_node(list, name);
		}
#line 1759 "parser.tab.c"
    break;

  case 60: /* unalias: UNALIAS DOLLAR OCURL WORD CCURL  */
#line 418 "parser.y"
                                                          {
				char *name = getenv((yyvsp[-1].string));
				remove_node(list, name);
			}
#line 1768 "parser.tab.c"
    break;

  case 61: /* setenv: SETENV WORD WORD  */
#line 426 "parser.y"
                                 {
			cmd_number = 5;
			col = 0;
			char* name = (yyvsp[-1].string);
			char* value = (yyvsp[0].string);
			varTbl[row][col] = name;
			col++;
			varTbl[row][col] = value;
			col++;
			row++;
		}
#line 1784 "parser.tab.c"
    break;

  case 62: /* setenv: SETENV WORD QUOTE params QUOTE  */
#line 437 "parser.y"
                                                 {
			cmd_number = 5;
			col = 0;
			char* name = (yyvsp[-3].string);
			char* value = temp_string;
			varTbl[row][col] = name;
			col++;
			varTbl[row][col] = value;
			col++;
			row++;
		}
#line 1800 "parser.tab.c"
    break;

  case 63: /* setenv: SETENV WORD WORD AND  */
#line 448 "parser.y"
                               {
		cmd_number = 5;
		col = 0;
		char* name = (yyvsp[-2].string);
		char* value = (yyvsp[-1].string);
		varTbl[row][col] = name;
		col++;
		varTbl[row][col] = value;
		col++;
		varTbl[row][col] = "&";
		col++;
		row++;
	}
#line 1818 "parser.tab.c"
    break;

  case 64: /* setenv: SETENV WORD params redirectIO  */
#line 461 "parser.y"
                                        {
		cmd_number = 5;
		col = 0;
		char* name = (yyvsp[-2].string);
		char* value = temp_string;
		char* file = temp_string2;
		varTbl[row][col] = name;
		col++;
		varTbl[row][col] = value;
		col++;
		varTbl[row][col] = io;
		col++;
		varTbl[row][col] = file;
		col++;
		row++;
	}
#line 1839 "parser.tab.c"
    break;

  case 65: /* unsetenv: UNSETENV WORD  */
#line 480 "parser.y"
                                      {
				cmd_number = 6;
				col = 0;
				char* name = (yyvsp[0].string);
				varTbl[row][col] = name;
				col++;
				row++;
			}
#line 1852 "parser.tab.c"
    break;

  case 66: /* unsetenv: UNSETENV WORD AND  */
#line 489 "parser.y"
                                            {
				cmd_number = 6;
				col = 0;
				char* name = (yyvsp[-1].string);
				varTbl[row][col] = name;
				col++;
				varTbl[row][col] = "&";
				col++;
				row++;
			}
#line 1867 "parser.tab.c"
    break;

  case 67: /* unsetenv: UNSETENV WORD redirectIO  */
#line 499 "parser.y"
                                                   {
				cmd_number = 6;
				col = 0;
				varTbl[row][col] = (yyvsp[-1].string);
				col++;
				varTbl[row][col] = io;
				col++;
				varTbl[row][col] = temp_string2;
				col++;
				row++;
			}
#line 1883 "parser.tab.c"
    break;

  case 68: /* printenv: PRINTENV  */
#line 513 "parser.y"
                                         {
					cmd_number = 7;
				}
#line 1891 "parser.tab.c"
    break;

  case 69: /* printenv: PRINTENV redirectIO  */
#line 516 "parser.y"
                                                      {
					cmd_number = 7;
					col = 0;
					varTbl[row][col] = io;
					col++;
					varTbl[row][col] = temp_string2;
					col++;
					row++;
				}
#line 1905 "parser.tab.c"
    break;

  case 70: /* ls: LS  */
#line 528 "parser.y"
                   {
				cmd_number = 9;
			}
#line 1913 "parser.tab.c"
    break;

  case 71: /* ls: LS params  */
#line 531 "parser.y"
                                   {
				col = 0;
				cmd_number = 10;
				varTbl[row][col] = temp_string;
				col++;
				row++;
			}
#line 1925 "parser.tab.c"
    break;

  case 72: /* ls: LS redirectIO  */
#line 538 "parser.y"
                                        {
				col = 0;
				cmd_number = 9;
				varTbl[row][col] = temp_string;
				col++;
				varTbl[row][col] = io;
				col++;
				varTbl[row][col] = temp_string2;
				col++;
				row++;
			}
#line 1941 "parser.tab.c"
    break;

  case 73: /* ls: LS params redirectIO  */
#line 549 "parser.y"
                                               {
				col = 0;
				cmd_number = 10;
				varTbl[row][col] = temp_string;
				col++;
				varTbl[row][col] = io;
				col++;
				varTbl[row][col] = temp_string2;
				col++;
				row++;
			}
#line 1957 "parser.tab.c"
    break;

  case 74: /* ls: LS ARG  */
#line 560 "parser.y"
                                {
				col = 0;
				cmd_number = 11;
				varTbl[row][col] = temp_string;
				col++;
				varTbl[row][col] = (yyvsp[0].string);
				col++;
				row++;
			}
#line 1971 "parser.tab.c"
    break;

  case 75: /* touch: TOUCH WORD  */
#line 572 "parser.y"
                          {
			cmd_number = 12;
			varTbl[row][col] = (yyvsp[0].string);
			row++;
			col++;
		}
#line 1982 "parser.tab.c"
    break;

  case 76: /* touch: TOUCH QUOTE WORD QUOTE  */
#line 579 "parser.y"
                {
			cmd_number = 12;
			varTbl[row][col] = (yyvsp[-1].string);
			row++;
			col++;
		}
#line 1993 "parser.tab.c"
    break;

  case 77: /* head: HEAD WORD  */
#line 587 "parser.y"
                         {
				varTbl[row][col] = (yyvsp[0].string);
				row++;
				col++;
				cmd_number = 13;
		}
#line 2004 "parser.tab.c"
    break;

  case 78: /* head: HEAD WORD redirectIO  */
#line 593 "parser.y"
                                       {
			varTbl[row][col] = (yyvsp[-1].string);
			col++;
			varTbl[row][col] = io;
			col++;
			varTbl[row][col] = temp_string2;
			row++;
			col++;
			cmd_number = 13;
		}
#line 2019 "parser.tab.c"
    break;

  case 79: /* head: HEAD ARG WORD  */
#line 603 "parser.y"
                               {
			varTbl[row][col] = (yyvsp[-1].string);
			col++;
			varTbl[row][col] = (yyvsp[0].string);
			row++;
			col++;
			cmd_number = 14;
		}
#line 2032 "parser.tab.c"
    break;

  case 80: /* tail: TAIL WORD  */
#line 613 "parser.y"
                                 {
				varTbl[row][col] = (yyvsp[0].string);
				row++;
				col++;
				cmd_number = 15;
		}
#line 2043 "parser.tab.c"
    break;

  case 81: /* tail: TAIL ARG WORD  */
#line 619 "parser.y"
                               {
			varTbl[row][col] = (yyvsp[-1].string);
			col++;
			varTbl[row][col] = (yyvsp[0].string);
			row++;
			col++;
			cmd_number = 16;
		}
#line 2056 "parser.tab.c"
    break;

  case 82: /* echo: PRINT WORD  */
#line 630 "parser.y"
                           {
			printf("%s", (yyvsp[0].string));
		}
#line 2064 "parser.tab.c"
    break;

  case 83: /* echo: PRINT QUOTE WORD QUOTE  */
#line 633 "parser.y"
                                        {
			printf("%s", (yyvsp[-1].string));
		}
#line 2072 "parser.tab.c"
    break;

  case 84: /* echo: PRINT QUOTE envexpand QUOTE  */
#line 636 "parser.y"
                                              {

		}
#line 2080 "parser.tab.c"
    break;

  case 85: /* pwd: PWD  */
#line 642 "parser.y"
           {
		char cwd[PATH_MAX];
		getcwd(cwd, sizeof(cwd));
		printf("%s\n",cwd);
	}
#line 2090 "parser.tab.c"
    break;

  case 86: /* cat: CAT WORD  */
#line 650 "parser.y"
                 {
		int fd, ch;
		fd = open((yyvsp[0].string),O_RDONLY);            /*open the file in READONLY mode*/

		if(fd < 0) {
			printf("error opening file or file doesn't exist\n");

		}
		else
		{
			while(read(fd,&ch,1))                   /*Read one byte at a time*/
				write(STDOUT_FILENO,&ch,1);
		}

	}
#line 2110 "parser.tab.c"
    break;

  case 87: /* cat: CAT QUOTE WORD QUOTE  */
#line 665 "parser.y"
                               {
		int fd, ch;
		fd = open((yyvsp[-1].string) ,O_RDONLY);            /*open the file in READONLY mode*/

		if(fd < 0) {
			printf("error opening file or file doesn't exist\n");

		}
		else
		{
			while(read(fd,&ch,1))                   /*Read one byte at a time*/
				write(STDOUT_FILENO,&ch,1);
		}
	}
#line 2129 "parser.tab.c"
    break;

  case 88: /* mkdir: MKDIR WORD  */
#line 682 "parser.y"
                          {
			int check = mkdir((yyvsp[0].string),0777);

    // check if directory is created or not
	    if (!check)
	        printf("Directory created\n");
	    else {
	        printf("Unable to create directory\n");
    }
		}
#line 2144 "parser.tab.c"
    break;

  case 89: /* rm: RM WORD  */
#line 695 "parser.y"
               {
		remove((yyvsp[0].string));
	}
#line 2152 "parser.tab.c"
    break;

  case 90: /* wc: WC WORD  */
#line 701 "parser.y"
                {
			std::string line;
	    std::fstream file;
			file.open((yyvsp[0].string));
			if(file != NULL)
			{
				int numlines=0, numwords = 0;
				while(getline(file, line))
				{
				    ++numlines;
				    std::stringstream lineStream(line);
				    while(getline(lineStream, line, ' '))
				    {
				        ++numwords;
				    }
				}

				printf("%d %d %d %s\n",numlines, numwords, (int)file.tellg(), (yyvsp[0].string));
			}
			else
			{
				printf("error opening file or file doesn't exist\n");
			}
			file.close();

	}
#line 2183 "parser.tab.c"
    break;

  case 91: /* word: WORD  */
#line 729 "parser.y"
             {

		char *expand = command_expand(list, (yyvsp[0].string));
		cmd_number = 20;
		struct stat sb;
  	if(stat((yyvsp[0].string), &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			pid_t p;
			int mutex, wpid;
			p = fork();
			if (p < 0)
			{
				printf("fork failed");
			}
			else if (p == 0)
			{
				char *symlinkpath = (yyvsp[0].string);
				char actualpath [PATH_MAX+1];
				char *ptr;
				ptr = realpath(symlinkpath, actualpath);
				execl(ptr, "cmdvalue.txt", 0);
			}
			else
			{
				while ((wpid = wait(&mutex)) > 0)
				{
					//parent process waits until child exits
				}
			}
		}
		else if(strcmp("Command not found", expand) == 0)
		{
			printf("%s : command not found", (yyvsp[0].string));
		}
		else
		{

			int pipe1[2]; //pipe with two ends, read and write
			pid_t p;
			int mutex, wpid;
			pipe(pipe1); //creates pipe
			p = fork();
			if (p < 0)
			{
				printf("fork failed");
			}
			else if (p == 0)
			{
				FILE *f;
				f = fopen("cmdvalue.txt", "w");
				fprintf(f, "%s\n", expand);
				fclose(f);
				f = fopen("cmdvalue.txt", "r");
				int filedesc = fileno(f);
				dup2(filedesc, fileno(stdin));
				fclose(f);
				char dest[100];
				strcpy(dest, getenv("PWD"));
				strcat(dest, "/");
				strcat(dest, "cmdvalue.txt");
				execl(dest, "cmdvalue.txt", 0);
			}
			else
			{
				while ((wpid = wait(&mutex)) > 0)
				{
					//parent process waits until child exits
				}
			}
		}
		printf("\n");
}
#line 2260 "parser.tab.c"
    break;


#line 2264 "parser.tab.c"

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
      yyerror (YY_("syntax error"));
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 802 "parser.y"

