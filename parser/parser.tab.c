/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 21 "parser.y"

#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void yyerror(const char *);

Node *ast_root;
Node* new_node(const char *s){
    Node *n = malloc(sizeof(Node));
    n->name    = strdup(s);
    n->kids    = NULL;
    n->kid_cnt = 0;
    return n;
}
void add_child(Node *p, Node *c){
    p->kids = realloc(p->kids,
                     sizeof(Node*) * (p->kid_cnt + 1));
    p->kids[p->kid_cnt++] = c;
}
void print_tree(Node *n,int d){
    for(int i=0;i<d;i++) printf("   ");
    if(d>0) printf("|-- ");
    if(n->kid_cnt==0) printf("%s\n",n->name);
    else{
        printf("<%s>\n",n->name);
        for(int i=0;i<n->kid_cnt;i++)
            print_tree(n->kids[i],d+1);
    }
}
void free_tree(Node *n){
    for(int i=0;i<n->kid_cnt;i++) free_tree(n->kids[i]);
    free(n->kids);
    free(n->name);
    free(n);
}
extern int yylex(void);
void yyerror(const char *s){
    fprintf(stderr,"Parse error: %s\n",s);
    exit(1);
}

/* Line 371 of yacc.c  */
#line 111 "parser.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
/* Line 387 of yacc.c  */
#line 17 "parser.y"

#include "ast.h"


/* Line 387 of yacc.c  */
#line 148 "parser.tab.c"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MINUS = 258,
     PLUS = 259,
     MOD = 260,
     DIV = 261,
     MUL = 262,
     LOR = 263,
     LAND = 264,
     NE = 265,
     EQ = 266,
     GE = 267,
     GT = 268,
     LE = 269,
     LT = 270,
     UMINUS = 271,
     LOWER_THAN_ELSE = 272,
     ELSE = 273,
     ID = 274,
     NUMBER = 275,
     CHAR_CONST = 276,
     STRING = 277,
     VOID = 278,
     INT = 279,
     FLOAT = 280,
     CONST = 281,
     IF = 282,
     WHILE = 283,
     RETURN = 284,
     BREAK = 285,
     CONTINUE = 286,
     PRINT = 287,
     ASSIGN = 288,
     NOT = 289,
     LP = 290,
     RP = 291,
     LBRACE = 292,
     RBRACE = 293,
     LBRACK = 294,
     RBRACK = 295,
     SEMI = 296,
     COMMA = 297,
     OPERATOR = 298
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 68 "parser.y"

    char *string;
    Node *node;


/* Line 387 of yacc.c  */
#line 212 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 240 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   215

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNRULES -- Number of states.  */
#define YYNSTATES  174

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    21,
      23,    27,    32,    34,    38,    40,    44,    48,    50,    54,
      57,    62,    64,    67,    71,    73,    77,    83,    90,    93,
      98,   104,   106,   110,   112,   116,   118,   120,   122,   126,
     127,   130,   132,   134,   135,   139,   144,   148,   153,   154,
     159,   162,   167,   173,   178,   182,   188,   196,   202,   204,
     207,   210,   212,   214,   216,   220,   222,   226,   228,   232,
     236,   238,   242,   246,   250,   254,   256,   260,   264,   266,
     270,   274,   278,   280,   283,   286,   289,   291,   295,   299,
     304,   306,   308,   310
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    46,    -1,    45,    46,    -1,    58,    -1,
      47,    -1,    48,    -1,    53,    -1,    26,    62,    49,    41,
      -1,    50,    -1,    49,    42,    50,    -1,    19,    66,    33,
      51,    -1,    71,    -1,    37,    52,    38,    -1,    51,    -1,
      52,    42,    51,    -1,    62,    54,    41,    -1,    55,    -1,
      54,    42,    55,    -1,    19,    66,    -1,    19,    66,    33,
      56,    -1,    71,    -1,    37,    38,    -1,    37,    57,    38,
      -1,    56,    -1,    57,    42,    56,    -1,    62,    19,    35,
      36,    63,    -1,    62,    19,    35,    60,    36,    63,    -1,
      62,    19,    -1,    62,    19,    39,    40,    -1,    62,    19,
      39,    40,    67,    -1,    59,    -1,    60,    42,    59,    -1,
      71,    -1,    61,    42,    71,    -1,    23,    -1,    24,    -1,
      25,    -1,    37,    64,    38,    -1,    -1,    64,    65,    -1,
      53,    -1,    70,    -1,    -1,    39,    76,    40,    -1,    66,
      39,    76,    40,    -1,    39,    20,    40,    -1,    67,    39,
      20,    40,    -1,    -1,    68,    39,    71,    40,    -1,    19,
      68,    -1,    19,    35,    36,    41,    -1,    19,    35,    61,
      36,    41,    -1,    69,    33,    71,    41,    -1,    29,    71,
      41,    -1,    27,    35,    79,    36,    70,    -1,    27,    35,
      79,    36,    70,    18,    70,    -1,    28,    35,    79,    36,
      70,    -1,    63,    -1,    30,    41,    -1,    31,    41,    -1,
      41,    -1,    72,    -1,    73,    -1,    72,     8,    73,    -1,
      74,    -1,    73,     9,    74,    -1,    75,    -1,    74,    11,
      75,    -1,    74,    10,    75,    -1,    76,    -1,    75,    15,
      76,    -1,    75,    14,    76,    -1,    75,    13,    76,    -1,
      75,    12,    76,    -1,    77,    -1,    76,     4,    77,    -1,
      76,     3,    77,    -1,    78,    -1,    77,     7,    78,    -1,
      77,     6,    78,    -1,    77,     5,    78,    -1,    80,    -1,
       4,    78,    -1,     3,    78,    -1,    34,    78,    -1,    72,
      -1,    35,    71,    36,    -1,    19,    35,    36,    -1,    19,
      35,    61,    36,    -1,    69,    -1,    20,    -1,    22,    -1,
      21,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   107,   112,   113,   118,   119,   123,   134,
     135,   139,   150,   152,   162,   163,   167,   177,   182,   191,
     202,   218,   219,   220,   224,   225,   229,   238,   252,   258,
     265,   278,   283,   294,   295,   299,   300,   301,   305,   315,
     316,   320,   326,   330,   334,   344,   357,   365,   377,   378,
     389,   398,   406,   415,   423,   430,   439,   450,   459,   460,
     461,   462,   470,   474,   475,   484,   485,   494,   495,   501,
     510,   511,   517,   523,   529,   538,   539,   545,   554,   555,
     561,   567,   576,   581,   587,   593,   603,   609,   615,   621,
     628,   629,   635,   636
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"-\"", "\"+\"", "\"%\"", "\"/\"",
  "\"*\"", "\"||\"", "\"&&\"", "\"!=\"", "\"==\"", "\">=\"", "\">\"",
  "\"<=\"", "\"<\"", "UMINUS", "LOWER_THAN_ELSE", "ELSE", "ID", "NUMBER",
  "CHAR_CONST", "STRING", "VOID", "INT", "FLOAT", "CONST", "IF", "WHILE",
  "RETURN", "BREAK", "CONTINUE", "PRINT", "\"=\"", "\"!\"", "LP", "RP",
  "LBRACE", "RBRACE", "LBRACK", "RBRACK", "SEMI", "COMMA", "OPERATOR",
  "$accept", "CompUnit", "CompUnitItem", "Decl", "ConstDecl",
  "ConstDefList", "ConstDef", "ConstInitVal", "ConstInitValList",
  "VarDecl", "VarDefList", "VarDef", "InitVal", "InitValList", "FuncDef",
  "FuncFParam", "FuncFParams", "FuncRParams", "BType", "Block",
  "BlockItem", "Item", "ConstSubscriptList", "NonEmptyConstSubscriptList",
  "SubscriptList", "LVal", "Stmt", "Exp", "LOrExp", "LAndExp", "EqExp",
  "RelExp", "AddExp", "MulExp", "UnaryExp", "Cond", "PrimaryExp", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    46,    46,    47,    47,    48,    49,
      49,    50,    51,    51,    52,    52,    53,    54,    54,    55,
      55,    56,    56,    56,    57,    57,    58,    58,    59,    59,
      59,    60,    60,    61,    61,    62,    62,    62,    63,    64,
      64,    65,    65,    66,    66,    66,    67,    67,    68,    68,
      69,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    71,    72,    72,    73,    73,    74,    74,    74,
      75,    75,    75,    75,    75,    76,    76,    76,    77,    77,
      77,    77,    78,    78,    78,    78,    79,    80,    80,    80,
      80,    80,    80,    80
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     4,     1,
       3,     4,     1,     3,     1,     3,     3,     1,     3,     2,
       4,     1,     2,     3,     1,     3,     5,     6,     2,     4,
       5,     1,     3,     1,     3,     1,     1,     1,     3,     0,
       2,     1,     1,     0,     3,     4,     3,     4,     0,     4,
       2,     4,     5,     4,     3,     5,     7,     5,     1,     2,
       2,     1,     1,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     2,     2,     2,     1,     3,     3,     4,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    35,    36,    37,     0,     0,     2,     5,     6,     7,
       4,     0,     0,     1,     3,    43,     0,    17,    43,     0,
       9,     0,     0,    19,    16,     0,     0,     8,     0,     0,
      31,     0,     0,     0,     0,    48,    91,    93,    92,     0,
       0,    90,     0,    75,    78,    82,     0,     0,    43,    18,
       0,    10,    39,    26,     0,     0,    28,    84,    83,     0,
      50,    85,     0,    62,    63,    65,    67,    70,     0,     0,
      44,     0,     0,     0,     0,    20,    21,     0,     0,    11,
      12,     0,    27,    32,     0,    88,     0,    33,     0,    87,
       0,     0,     0,     0,     0,     0,     0,     0,    77,    76,
      81,    80,    79,    22,    24,     0,    45,    14,     0,    48,
       0,     0,     0,     0,     0,    38,    61,    41,     0,    58,
      40,     0,    42,    29,    89,     0,     0,    64,    66,    69,
      68,    74,    73,    72,    71,    23,     0,    13,     0,     0,
       0,     0,     0,    59,    60,     0,     0,    30,    34,    49,
      25,    15,     0,     0,    86,     0,     0,    54,     0,     0,
       0,    51,     0,     0,     0,    53,    46,     0,    52,    55,
      57,    47,     0,    56
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    19,    20,    79,   108,     9,
      16,    17,    75,   105,    10,    30,    31,    86,    11,   119,
      81,   120,    23,   147,    60,    41,   122,    76,    63,    64,
      65,    66,    67,    43,    44,   155,    45
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -147
static const yytype_int16 yypact[] =
{
     117,  -147,  -147,  -147,    96,     8,  -147,  -147,  -147,  -147,
    -147,     2,    18,  -147,  -147,     0,    40,  -147,   -30,    49,
    -147,    37,   114,   -11,  -147,    30,   -10,  -147,    18,    -7,
    -147,    11,    48,   114,   114,    58,  -147,  -147,  -147,   114,
     114,  -147,    10,   121,  -147,  -147,    67,   114,   -30,  -147,
      75,  -147,  -147,  -147,    -7,    96,    61,  -147,  -147,   103,
      64,  -147,    72,   108,   141,   150,   163,   160,   114,   114,
    -147,   114,   114,   114,    21,  -147,  -147,    12,    75,  -147,
    -147,   128,  -147,  -147,   139,  -147,    15,  -147,   114,  -147,
     114,   114,   114,   114,   114,   114,   114,   114,   121,   121,
    -147,  -147,  -147,  -147,  -147,    26,  -147,  -147,    73,   119,
     148,   152,   114,   147,   149,  -147,  -147,  -147,    30,  -147,
    -147,   156,  -147,   153,  -147,   114,   151,   141,   150,   163,
     163,   160,   160,   160,   160,  -147,    67,  -147,    75,   110,
     114,   114,   154,  -147,  -147,   114,   173,   155,  -147,  -147,
    -147,  -147,   157,    27,   108,   161,   164,  -147,   158,   162,
     176,  -147,   165,   143,   143,  -147,  -147,   167,  -147,   183,
    -147,  -147,   143,  -147
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -147,  -147,   198,  -147,  -147,  -147,   177,   -73,  -147,   123,
    -147,   184,   -70,  -147,  -147,   159,  -147,    69,    -1,   -18,
    -147,  -147,   192,  -147,  -147,   -80,  -146,   -40,    41,   122,
     120,    93,   -20,    99,   -27,    74,  -147
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      62,   121,    42,    12,   104,   107,    57,    58,    13,    22,
      80,    53,    61,    68,    69,    68,    69,   169,   170,    87,
      32,    15,    46,    50,    33,    34,   173,    77,    47,    47,
      52,     1,     2,     3,     4,    21,    82,    18,    80,    22,
      35,    36,    37,    38,   100,   101,   102,    54,   126,    48,
      70,   124,   106,    55,    32,    39,    40,   125,    74,   103,
       1,     2,     3,   162,   135,   151,   150,    56,   136,   125,
      33,    34,   142,    29,   131,   132,   133,   134,    33,    34,
     118,    24,    25,   121,   121,   148,    35,    36,    37,    38,
      27,    28,   121,    59,    35,    36,    37,    38,    80,    87,
      84,    39,    40,    88,    74,   158,    33,    34,    89,    39,
      40,   137,    78,    33,    34,   138,    90,    33,    34,     1,
       2,     3,    35,    36,    37,    38,    71,    72,    73,    35,
      36,    37,    38,    35,    36,    37,    38,    39,    40,    85,
       1,     2,     3,     4,    39,    40,   152,   109,    39,    40,
      91,     1,     2,     3,   139,   110,   111,   112,   113,   114,
      92,    93,   109,    68,    69,    52,   115,    98,    99,   116,
     110,   111,   112,   113,   114,    94,    95,    96,    97,   123,
      52,   154,   154,   140,   116,   129,   130,   141,   143,   145,
     144,   149,   146,   159,   160,   157,   167,   163,   161,   165,
     164,   172,   166,    14,   117,    51,   168,   171,   153,    49,
      26,   128,   127,     0,    83,   156
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-147)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      40,    81,    22,     4,    74,    78,    33,    34,     0,    39,
      50,    29,    39,     3,     4,     3,     4,   163,   164,    59,
      21,    19,    33,    33,     3,     4,   172,    47,    39,    39,
      37,    23,    24,    25,    26,    35,    54,    19,    78,    39,
      19,    20,    21,    22,    71,    72,    73,    36,    88,    19,
      40,    36,    40,    42,    55,    34,    35,    42,    37,    38,
      23,    24,    25,    36,    38,   138,   136,    19,    42,    42,
       3,     4,   112,    36,    94,    95,    96,    97,     3,     4,
      81,    41,    42,   163,   164,   125,    19,    20,    21,    22,
      41,    42,   172,    35,    19,    20,    21,    22,   138,   139,
      39,    34,    35,    39,    37,   145,     3,     4,    36,    34,
      35,    38,    37,     3,     4,    42,     8,     3,     4,    23,
      24,    25,    19,    20,    21,    22,     5,     6,     7,    19,
      20,    21,    22,    19,    20,    21,    22,    34,    35,    36,
      23,    24,    25,    26,    34,    35,    36,    19,    34,    35,
       9,    23,    24,    25,    35,    27,    28,    29,    30,    31,
      10,    11,    19,     3,     4,    37,    38,    68,    69,    41,
      27,    28,    29,    30,    31,    12,    13,    14,    15,    40,
      37,   140,   141,    35,    41,    92,    93,    35,    41,    33,
      41,    40,    39,    20,    39,    41,    20,    36,    41,    41,
      36,    18,    40,     5,    81,    28,    41,    40,   139,    25,
      18,    91,    90,    -1,    55,   141
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    23,    24,    25,    26,    45,    46,    47,    48,    53,
      58,    62,    62,     0,    46,    19,    54,    55,    19,    49,
      50,    35,    39,    66,    41,    42,    66,    41,    42,    36,
      59,    60,    62,     3,     4,    19,    20,    21,    22,    34,
      35,    69,    76,    77,    78,    80,    33,    39,    19,    55,
      33,    50,    37,    63,    36,    42,    19,    78,    78,    35,
      68,    78,    71,    72,    73,    74,    75,    76,     3,     4,
      40,     5,     6,     7,    37,    56,    71,    76,    37,    51,
      71,    64,    63,    59,    39,    36,    61,    71,    39,    36,
       8,     9,    10,    11,    12,    13,    14,    15,    77,    77,
      78,    78,    78,    38,    56,    57,    40,    51,    52,    19,
      27,    28,    29,    30,    31,    38,    41,    53,    62,    63,
      65,    69,    70,    40,    36,    42,    71,    73,    74,    75,
      75,    76,    76,    76,    76,    38,    42,    38,    42,    35,
      35,    35,    71,    41,    41,    33,    39,    67,    71,    40,
      56,    51,    36,    61,    72,    79,    79,    41,    71,    20,
      39,    41,    36,    36,    36,    41,    40,    20,    41,    70,
      70,    40,    18,    70
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      yychar = YYLEX;
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

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
/* Line 1792 of yacc.c  */
#line 106 "parser.y"
    { ast_root=new_node("CompUnit"); add_child(ast_root,(yyvsp[(1) - (1)].node)); }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 108 "parser.y"
    { add_child(ast_root,(yyvsp[(2) - (2)].node)); }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 112 "parser.y"
    { (yyval.node)=(yyvsp[(1) - (1)].node); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 113 "parser.y"
    { (yyval.node)=(yyvsp[(1) - (1)].node); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 118 "parser.y"
    { (yyval.node)=(yyvsp[(1) - (1)].node); }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 119 "parser.y"
    { (yyval.node)=(yyvsp[(1) - (1)].node); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 124 "parser.y"
    {
        (yyval.node)=new_node("ConstDecl");
        add_child((yyval.node),new_node("const"));
        add_child((yyval.node),(yyvsp[(2) - (4)].node));
        add_child((yyval.node),(yyvsp[(3) - (4)].node));
        add_child((yyval.node),new_node(";"));
      }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 134 "parser.y"
    { (yyval.node)=new_node("ConstDefList"); add_child((yyval.node),(yyvsp[(1) - (1)].node)); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 135 "parser.y"
    { (yyval.node)=(yyvsp[(1) - (3)].node); add_child((yyval.node),(yyvsp[(3) - (3)].node)); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 140 "parser.y"
    {
        (yyval.node)=new_node("ConstDef");
        add_child((yyval.node), (yyvsp[(1) - (4)].node));
        add_child((yyval.node),(yyvsp[(2) - (4)].node));
        add_child((yyval.node),new_node("="));
        add_child((yyval.node),(yyvsp[(4) - (4)].node));
      }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 151 "parser.y"
    { (yyval.node)=new_node("ConstInitVal"); add_child((yyval.node), (yyvsp[(1) - (1)].node)); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 153 "parser.y"
    {
        (yyval.node)=new_node("ConstInitVal");
        add_child((yyval.node),new_node("{"));
        add_child((yyval.node),(yyvsp[(2) - (3)].node));
        add_child((yyval.node),new_node("}"));
      }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 162 "parser.y"
    { (yyval.node)=new_node("ConstInitValList"); add_child((yyval.node),(yyvsp[(1) - (1)].node)); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 163 "parser.y"
    { (yyval.node)=(yyvsp[(1) - (3)].node); add_child((yyval.node),(yyvsp[(3) - (3)].node)); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 168 "parser.y"
    {
        (yyval.node)=new_node("VarDecl");
        add_child((yyval.node),(yyvsp[(1) - (3)].node));
        add_child((yyval.node),(yyvsp[(2) - (3)].node));
        add_child((yyval.node),new_node(";"));
      }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 178 "parser.y"
    {
        (yyval.node) = new_node("VarDefList");
        add_child((yyval.node), (yyvsp[(1) - (1)].node));
      }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 183 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (3)].node);
        add_child((yyval.node), new_node(","));  // 显式加上逗号节点
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
      }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 192 "parser.y"
    {
        (yyval.node) = new_node("VarDef");
        add_child((yyval.node), (yyvsp[(1) - (2)].node));  // 添加变量名
        if ((yyvsp[(2) - (2)].node) == NULL) {  // 如果 ConstSubscriptList 是空的，加入 epsilon
          Node *epsilon = new_node("epsilon");
          add_child((yyval.node), epsilon);
        } else {
          add_child((yyval.node), (yyvsp[(2) - (2)].node));  // 否则，添加 ConstSubscriptList
        }
      }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 203 "parser.y"
    {
        (yyval.node) = new_node("VarDef");
        add_child((yyval.node), (yyvsp[(1) - (4)].node));
        if ((yyvsp[(2) - (4)].node) == NULL) {  // 处理空的 ConstSubscriptList
          Node *epsilon = new_node("epsilon");
          add_child((yyval.node), epsilon);
        } else {
          add_child((yyval.node), (yyvsp[(2) - (4)].node));
        }
        add_child((yyval.node), new_node("="));
        add_child((yyval.node), (yyvsp[(4) - (4)].node));
      }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 218 "parser.y"
    { (yyval.node) = new_node("InitVal"); add_child((yyval.node), (yyvsp[(1) - (1)].node)); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 219 "parser.y"
    { (yyval.node) = new_node("InitVal"); add_child((yyval.node), new_node("{")); add_child((yyval.node), new_node("}")); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 220 "parser.y"
    { (yyval.node) = new_node("InitVal"); add_child((yyval.node), new_node("{")); add_child((yyval.node), (yyvsp[(2) - (3)].node)); add_child((yyval.node), new_node("}")); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 224 "parser.y"
    { (yyval.node) = new_node("InitValList"); add_child((yyval.node), (yyvsp[(1) - (1)].node)); }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 225 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (3)].node); add_child((yyval.node), new_node(",")); add_child((yyval.node), (yyvsp[(3) - (3)].node)); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 230 "parser.y"
    {
        (yyval.node) = new_node("FuncDef");
        add_child((yyval.node), (yyvsp[(1) - (5)].node));
        add_child((yyval.node), (yyvsp[(2) - (5)].node));
        add_child((yyval.node), new_node("("));
        add_child((yyval.node), new_node(")"));
        add_child((yyval.node), (yyvsp[(5) - (5)].node));
      }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 239 "parser.y"
    {
        (yyval.node) = new_node("FuncDef");
        add_child((yyval.node), (yyvsp[(1) - (6)].node));
        add_child((yyval.node), (yyvsp[(2) - (6)].node));
        add_child((yyval.node), new_node("("));
        add_child((yyval.node), (yyvsp[(4) - (6)].node));
        add_child((yyval.node), new_node(")"));
        add_child((yyval.node), (yyvsp[(6) - (6)].node));
      }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 253 "parser.y"
    {
        (yyval.node) = new_node("FuncFParam");
        add_child((yyval.node), (yyvsp[(1) - (2)].node));
        add_child((yyval.node), (yyvsp[(2) - (2)].node));
      }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 259 "parser.y"
    {
        (yyval.node) = new_node("FuncFParam");
        add_child((yyval.node), (yyvsp[(1) - (4)].node));
        add_child((yyval.node), (yyvsp[(2) - (4)].node));
        add_child((yyval.node), new_node("[]"));
      }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 266 "parser.y"
    {
        (yyval.node) = new_node("FuncFParam");
        add_child((yyval.node), (yyvsp[(1) - (5)].node));
        add_child((yyval.node), (yyvsp[(2) - (5)].node));
        add_child((yyval.node), new_node("[]"));
        add_child((yyval.node), (yyvsp[(5) - (5)].node));
      }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 279 "parser.y"
    {
        (yyval.node) = new_node("FuncFParams");
        add_child((yyval.node), (yyvsp[(1) - (1)].node));
      }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 284 "parser.y"
    {
        (yyval.node) = (yyvsp[(1) - (3)].node);
        add_child((yyval.node), new_node(","));
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
      }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 294 "parser.y"
    { (yyval.node)=new_node("FuncRParams"); add_child((yyval.node), (yyvsp[(1) - (1)].node)); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 295 "parser.y"
    { (yyval.node)=(yyvsp[(1) - (3)].node); add_child((yyval.node),new_node(",")); add_child((yyval.node),(yyvsp[(3) - (3)].node)); }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 299 "parser.y"
    { (yyval.node)=new_node("BType"); add_child((yyval.node),new_node("void")); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 300 "parser.y"
    { (yyval.node)=new_node("BType"); add_child((yyval.node),new_node("int")); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 301 "parser.y"
    { (yyval.node)=new_node("BType"); add_child((yyval.node),new_node("float")); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 306 "parser.y"
    {
        (yyval.node)=new_node("Block");
        add_child((yyval.node),new_node("{"));
        add_child((yyval.node),(yyvsp[(2) - (3)].node));
        add_child((yyval.node),new_node("}"));
      }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 315 "parser.y"
    { (yyval.node)=new_node("BlockItem"); add_child((yyval.node),new_node("epsilon")); }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 316 "parser.y"
    { (yyval.node)=new_node("BlockItem"); add_child((yyval.node), (yyvsp[(1) - (2)].node)); add_child((yyval.node), (yyvsp[(2) - (2)].node)); }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 321 "parser.y"
    {
        Node *d=new_node("Decl");
        add_child(d,(yyvsp[(1) - (1)].node));
        (yyval.node)=d;
      }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 326 "parser.y"
    { (yyval.node)=(yyvsp[(1) - (1)].node); }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 330 "parser.y"
    {
      (yyval.node) = new_node("ConstSubscriptList");
      add_child((yyval.node), new_node("epsilon"));  // 确保空的列表添加 epsilon
  }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 334 "parser.y"
    {
    (yyval.node) = new_node("ConstSubscriptList");
    add_child((yyval.node), new_node("["));
    
    Node *constexp_node = new_node("ConstExp");
    add_child(constexp_node, (yyvsp[(2) - (3)].node));  // $2 是 AddExp
    add_child((yyval.node), constexp_node);  // 添加整个 ConstExp 节点

    add_child((yyval.node), new_node("]"));
}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 344 "parser.y"
    {
    (yyval.node) = (yyvsp[(1) - (4)].node);
    add_child((yyval.node), new_node("["));
    
    Node *constexp_node = new_node("ConstExp");
    add_child(constexp_node, (yyvsp[(3) - (4)].node));  // $3 是 AddExp
    add_child((yyval.node), constexp_node);

    add_child((yyval.node), new_node("]"));
}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 358 "parser.y"
    {
        (yyval.node) = new_node("ConstSubscriptList");
        add_child((yyval.node), new_node("["));
        add_child((yyval.node), new_node("constexp"));  // 打印 constexp
        add_child((yyval.node), (yyvsp[(2) - (3)].node));
        add_child((yyval.node), new_node("]"));
      }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 366 "parser.y"
    {
        add_child((yyval.node), new_node("["));
        add_child((yyval.node), new_node("constexp"));  // 打印 constexp
        add_child((yyval.node), (yyvsp[(3) - (4)].node));
        add_child((yyval.node), new_node("]"));
      }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 377 "parser.y"
    { (yyval.node)=new_node("SubscriptList"); add_child((yyval.node),new_node("epsilon")); }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 379 "parser.y"
    {
        (yyval.node)=new_node("SubscriptList");
        add_child((yyval.node), (yyvsp[(1) - (4)].node));
        add_child((yyval.node), new_node("["));
        add_child((yyval.node), (yyvsp[(3) - (4)].node));
        add_child((yyval.node), new_node("]"));
      }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 390 "parser.y"
    {
        (yyval.node)=new_node("LVal");
        add_child((yyval.node), (yyvsp[(1) - (2)].node));
        add_child((yyval.node),(yyvsp[(2) - (2)].node));
      }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 399 "parser.y"
    {
        (yyval.node)=new_node("Stmt");
        add_child((yyval.node), (yyvsp[(1) - (4)].node));
        add_child((yyval.node), new_node("("));
        add_child((yyval.node), new_node(")"));
        add_child((yyval.node), new_node(";"));
      }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 407 "parser.y"
    {
        (yyval.node)=new_node("Stmt");
        add_child((yyval.node), (yyvsp[(1) - (5)].node));
        add_child((yyval.node), new_node("("));
        add_child((yyval.node),(yyvsp[(3) - (5)].node));
        add_child((yyval.node), new_node(")"));
        add_child((yyval.node), new_node(";"));
      }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 416 "parser.y"
    {
        (yyval.node)=new_node("Stmt");
        add_child((yyval.node), (yyvsp[(1) - (4)].node));
        add_child((yyval.node), new_node("="));
        add_child((yyval.node), (yyvsp[(3) - (4)].node));
        add_child((yyval.node), new_node(";"));
      }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 424 "parser.y"
    {
        (yyval.node)=new_node("Stmt");
        add_child((yyval.node), new_node("return"));
        add_child((yyval.node),(yyvsp[(2) - (3)].node));
        add_child((yyval.node), new_node(";"));
      }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 431 "parser.y"
    {
        (yyval.node)=new_node("Stmt");
        add_child((yyval.node), new_node("if"));
        add_child((yyval.node), new_node("("));
        add_child((yyval.node),(yyvsp[(3) - (5)].node));
        add_child((yyval.node), new_node(")"));
        add_child((yyval.node),(yyvsp[(5) - (5)].node));
      }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 440 "parser.y"
    {
        (yyval.node)=new_node("Stmt");
        add_child((yyval.node), new_node("if"));
        add_child((yyval.node), new_node("("));
        add_child((yyval.node),(yyvsp[(3) - (7)].node));
        add_child((yyval.node), new_node(")"));
        add_child((yyval.node),(yyvsp[(5) - (7)].node));
        add_child((yyval.node), new_node("else"));
        add_child((yyval.node),(yyvsp[(7) - (7)].node));
      }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 451 "parser.y"
    {
        (yyval.node)=new_node("Stmt");
        add_child((yyval.node), new_node("while"));
        add_child((yyval.node), new_node("("));
        add_child((yyval.node),(yyvsp[(3) - (5)].node));
        add_child((yyval.node), new_node(")"));
        add_child((yyval.node),(yyvsp[(5) - (5)].node));
      }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 459 "parser.y"
    { (yyval.node)=(yyvsp[(1) - (1)].node); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 460 "parser.y"
    { (yyval.node) = new_node("Stmt"); add_child((yyval.node), new_node("break")); }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 461 "parser.y"
    { (yyval.node) = new_node("Stmt"); add_child((yyval.node), new_node("continue")); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 463 "parser.y"
    {
        (yyval.node) = new_node("Stmt");
        add_child((yyval.node), new_node(";")); // 表示空语句
      }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 470 "parser.y"
    { (yyval.node)=new_node("Exp"); add_child((yyval.node), (yyvsp[(1) - (1)].node)); }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 474 "parser.y"
    { (yyval.node)=(yyvsp[(1) - (1)].node); }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 475 "parser.y"
    {
        (yyval.node)=new_node("LOrExp");
        add_child((yyval.node), (yyvsp[(1) - (3)].node));
        add_child((yyval.node), new_node("||"));
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 484 "parser.y"
    { (yyval.node)=(yyvsp[(1) - (1)].node); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 485 "parser.y"
    {
        (yyval.node)=new_node("LAndExp");
        add_child((yyval.node), (yyvsp[(1) - (3)].node));
        add_child((yyval.node), new_node("&&"));
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 494 "parser.y"
    { (yyval.node)=(yyvsp[(1) - (1)].node); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 495 "parser.y"
    {
        (yyval.node)=new_node("EqExp");
        add_child((yyval.node), (yyvsp[(1) - (3)].node));
        add_child((yyval.node), new_node("=="));
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 501 "parser.y"
    {
        (yyval.node)=new_node("EqExp");
        add_child((yyval.node), (yyvsp[(1) - (3)].node));
        add_child((yyval.node), new_node("!="));
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 510 "parser.y"
    { (yyval.node)=(yyvsp[(1) - (1)].node); }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 511 "parser.y"
    {
        (yyval.node)=new_node("RelExp");
        add_child((yyval.node), (yyvsp[(1) - (3)].node));
        add_child((yyval.node), new_node("<"));
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 517 "parser.y"
    {
        (yyval.node)=new_node("RelExp");
        add_child((yyval.node), (yyvsp[(1) - (3)].node));
        add_child((yyval.node), new_node("<="));
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 523 "parser.y"
    {
        (yyval.node)=new_node("RelExp");
        add_child((yyval.node), (yyvsp[(1) - (3)].node));
        add_child((yyval.node), new_node(">"));
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 529 "parser.y"
    {
        (yyval.node)=new_node("RelExp");
        add_child((yyval.node), (yyvsp[(1) - (3)].node));
        add_child((yyval.node), new_node(">="));
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 538 "parser.y"
    { (yyval.node)=new_node("AddExp"); add_child((yyval.node), (yyvsp[(1) - (1)].node)); }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 539 "parser.y"
    {
        (yyval.node)=new_node("AddExp");
        add_child((yyval.node), (yyvsp[(1) - (3)].node));
        add_child((yyval.node), new_node("+"));
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 545 "parser.y"
    {
        (yyval.node)=new_node("AddExp");
        add_child((yyval.node), (yyvsp[(1) - (3)].node));
        add_child((yyval.node), new_node("-"));
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 554 "parser.y"
    { (yyval.node)=new_node("MulExp"); add_child((yyval.node), (yyvsp[(1) - (1)].node)); }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 555 "parser.y"
    {
        (yyval.node)=new_node("MulExp");
        add_child((yyval.node), (yyvsp[(1) - (3)].node));
        add_child((yyval.node), new_node("*"));
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 561 "parser.y"
    {
        (yyval.node)=new_node("MulExp");
        add_child((yyval.node), (yyvsp[(1) - (3)].node));
        add_child((yyval.node), new_node("/"));
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 567 "parser.y"
    {
        (yyval.node)=new_node("MulExp");
        add_child((yyval.node), (yyvsp[(1) - (3)].node));
        add_child((yyval.node), new_node("%"));
        add_child((yyval.node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 577 "parser.y"
    {
        (yyval.node) = new_node("UnaryExp");
        add_child((yyval.node), (yyvsp[(1) - (1)].node));
      }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 582 "parser.y"
    {
        (yyval.node) = new_node("UnaryExp");
        add_child((yyval.node), new_node("+"));
        add_child((yyval.node), (yyvsp[(2) - (2)].node));
      }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 588 "parser.y"
    {
        (yyval.node) = new_node("UnaryExp");
        add_child((yyval.node), new_node("-"));
        add_child((yyval.node), (yyvsp[(2) - (2)].node));
      }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 594 "parser.y"
    {
        (yyval.node) = new_node("UnaryExp");
        add_child((yyval.node), new_node("!"));
        add_child((yyval.node), (yyvsp[(2) - (2)].node));
    }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 603 "parser.y"
    { (yyval.node) = new_node("Cond"); add_child((yyval.node), (yyvsp[(1) - (1)].node)); }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 609 "parser.y"
    {
        (yyval.node)=new_node("PrimaryExp");
        add_child((yyval.node), new_node("("));
        add_child((yyval.node), (yyvsp[(2) - (3)].node));
        add_child((yyval.node), new_node(")"));
    }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 615 "parser.y"
    {
        (yyval.node)=new_node("PrimaryExp");
        add_child((yyval.node), (yyvsp[(1) - (3)].node));
        add_child((yyval.node), new_node("("));
        add_child((yyval.node), new_node(")"));
    }
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 621 "parser.y"
    {
        (yyval.node)=new_node("PrimaryExp");
        add_child((yyval.node), (yyvsp[(1) - (4)].node));
        add_child((yyval.node), new_node("("));
        add_child((yyval.node), (yyvsp[(3) - (4)].node));
        add_child((yyval.node), new_node(")"));
    }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 628 "parser.y"
    { (yyval.node)=new_node("PrimaryExp"); add_child((yyval.node), (yyvsp[(1) - (1)].node)); }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 629 "parser.y"
    {
    (yyval.node) = new_node("PrimaryExp");
    Node *n = new_node("Number");
    add_child(n, (yyvsp[(1) - (1)].node));       // $1 是 "3"
    add_child((yyval.node), n);       // 把 Number 加入 PrimaryExp
}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 635 "parser.y"
    { (yyval.node)=new_node("PrimaryExp"); add_child((yyval.node), (yyvsp[(1) - (1)].node)); }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 636 "parser.y"
    { (yyval.node)=new_node("PrimaryExp"); add_child((yyval.node), (yyvsp[(1) - (1)].node)); }
    break;


/* Line 1792 of yacc.c  */
#line 2440 "parser.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 639 "parser.y"

int yydebug = 1; // 启用 Bison 的调试模式熟悉这个代码 

