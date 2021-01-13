
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ENDFILE = 258,
     ERROR = 259,
     IF = 260,
     ELSE = 261,
     INT = 262,
     RETURN = 263,
     VOID = 264,
     WHILE = 265,
     ID = 266,
     NUM = 267,
     ASSIGN = 268,
     EQ = 269,
     NOTEQ = 270,
     LTEQ = 271,
     GTEQ = 272,
     LT = 273,
     GT = 274,
     PLUS = 275,
     MINUS = 276,
     TIMES = 277,
     OVER = 278,
     LPAREN = 279,
     RPAREN = 280,
     LBRACK = 281,
     RBRACK = 282,
     LCURL = 283,
     RCURL = 284,
     SEMI = 285,
     COMMA = 286
   };
#endif
#define ENDFILE 258
#define ERROR 259
#define IF 260
#define ELSE 261
#define INT 262
#define RETURN 263
#define VOID 264
#define WHILE 265
#define ID 266
#define NUM 267
#define ASSIGN 268
#define EQ 269
#define NOTEQ 270
#define LTEQ 271
#define GTEQ 272
#define LT 273
#define GT 274
#define PLUS 275
#define MINUS 276
#define TIMES 277
#define OVER 278
#define LPAREN 279
#define RPAREN 280
#define LBRACK 281
#define RBRACK 282
#define LCURL 283
#define RCURL 284
#define SEMI 285
#define COMMA 286




/* Copy the first part of user declarations.  */
#line 17 "cminus.y"

#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "symtab.h"

TreeNode * parseTree; /* stores syntax tree for later return */

int scopenum = 0;
void yyerror (const char *s);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 40 "cminus.y"
typedef union YYSTYPE { TreeNode * tnode;
         TokenType tok; } YYSTYPE;
/* Line 191 of yacc.c.  */
#line 154 "cminus.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 166 "cminus.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */
#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   96

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  35
/* YYNRULES -- Number of rules. */
#define YYNRULES  68
/* YYNRULES -- Number of states. */
#define YYNSTATES  107

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    18,    19,
      27,    29,    31,    32,    40,    42,    44,    48,    50,    53,
      54,    60,    65,    68,    69,    72,    73,    75,    77,    79,
      81,    83,    86,    88,    94,   102,   108,   111,   115,   119,
     121,   123,   124,   130,   134,   136,   138,   140,   142,   144,
     146,   148,   152,   154,   156,   158,   162,   164,   166,   168,
     172,   174,   176,   178,   179,   185,   187,   188,   192
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      33,     0,    -1,    34,    -1,    34,    35,    -1,    35,    -1,
      36,    -1,    39,    -1,    38,    11,    30,    -1,    -1,    38,
      11,    26,    12,    37,    27,    30,    -1,     7,    -1,     9,
      -1,    -1,    38,    11,    40,    24,    41,    25,    45,    -1,
      42,    -1,     9,    -1,    42,    31,    43,    -1,    43,    -1,
      38,    11,    -1,    -1,    38,    11,    44,    26,    27,    -1,
      28,    46,    47,    29,    -1,    46,    36,    -1,    -1,    47,
      48,    -1,    -1,    49,    -1,    45,    -1,    50,    -1,    51,
      -1,    52,    -1,    53,    30,    -1,    30,    -1,     5,    24,
      53,    25,    48,    -1,     5,    24,    53,    25,    48,     6,
      48,    -1,    10,    24,    53,    25,    48,    -1,     8,    30,
      -1,     8,    53,    30,    -1,    54,    13,    53,    -1,    56,
      -1,    11,    -1,    -1,    11,    55,    26,    53,    27,    -1,
      58,    57,    58,    -1,    58,    -1,    14,    -1,    15,    -1,
      16,    -1,    17,    -1,    18,    -1,    19,    -1,    58,    59,
      60,    -1,    60,    -1,    20,    -1,    21,    -1,    60,    61,
      62,    -1,    62,    -1,    22,    -1,    23,    -1,    24,    53,
      25,    -1,    54,    -1,    63,    -1,    12,    -1,    -1,    11,
      64,    24,    65,    25,    -1,    66,    -1,    -1,    66,    31,
      53,    -1,    53,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,    55,    55,    61,    72,    76,    78,    82,    91,    90,
     107,   109,   114,   113,   129,   132,   138,   149,   153,   161,
     160,   171,   186,   198,   201,   213,   216,   218,   220,   222,
     224,   228,   230,   234,   239,   247,   254,   256,   262,   267,
     271,   276,   275,   285,   291,   295,   297,   299,   301,   303,
     305,   309,   315,   319,   321,   325,   331,   335,   337,   341,
     343,   345,   347,   354,   353,   364,   367,   370,   381
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ENDFILE", "ERROR", "IF", "ELSE", "INT", 
  "RETURN", "VOID", "WHILE", "ID", "NUM", "ASSIGN", "EQ", "NOTEQ", "LTEQ", 
  "GTEQ", "LT", "GT", "PLUS", "MINUS", "TIMES", "OVER", "LPAREN", 
  "RPAREN", "LBRACK", "RBRACK", "LCURL", "RCURL", "SEMI", "COMMA", 
  "$accept", "program", "declaration_list", "declaration", 
  "var_declaration", "@1", "type_specifier", "fun_declaration", "@2", 
  "params", "param_list", "param", "@3", "compound_stmt", 
  "local_declarations", "statement_list", "statement", "expression_stmt", 
  "selection_stmt", "iteration_stmt", "return_stmt", "expression", "var", 
  "@4", "simple_expression", "relop", "additive_expression", "addop", 
  "term", "mulop", "factor", "call", "@5", "args", "arg_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    36,    37,    36,
      38,    38,    40,    39,    41,    41,    42,    42,    43,    44,
      43,    45,    46,    46,    47,    47,    48,    48,    48,    48,
      48,    49,    49,    50,    50,    51,    52,    52,    53,    53,
      54,    55,    54,    56,    56,    57,    57,    57,    57,    57,
      57,    58,    58,    59,    59,    60,    60,    61,    61,    62,
      62,    62,    62,    64,    63,    65,    65,    66,    66
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     0,     7,
       1,     1,     0,     7,     1,     1,     3,     1,     2,     0,
       5,     4,     2,     0,     2,     0,     1,     1,     1,     1,
       1,     2,     1,     5,     7,     5,     2,     3,     3,     1,
       1,     0,     5,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     0,     5,     1,     0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,    10,    11,     0,     2,     4,     5,     0,     6,     1,
       3,    12,     0,     7,     0,     8,     0,     0,    11,     0,
       0,    14,    17,     0,    18,     0,     0,     9,     0,    23,
      13,    16,     0,    25,    20,    22,     0,     0,     0,     0,
       0,     0,    40,    62,     0,    21,    32,    27,    24,    26,
      28,    29,    30,     0,    60,    39,    44,    52,    56,    61,
       0,    36,     0,     0,     0,     0,     0,    31,     0,    45,
      46,    47,    48,    49,    50,    53,    54,     0,     0,    57,
      58,     0,     0,    37,     0,     0,    66,    59,    38,    60,
      43,    51,    55,     0,     0,     0,    68,     0,    65,    33,
      35,    42,    64,     0,     0,    67,    34
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     3,     4,     5,     6,    17,     7,     8,    14,    20,
      21,    22,    28,    47,    33,    37,    48,    49,    50,    51,
      52,    53,    54,    64,    55,    77,    56,    78,    57,    81,
      58,    59,    65,    97,    98
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -58
static const yysigned_char yypact[] =
{
      -6,   -58,   -58,    14,    -6,   -58,   -58,    -5,   -58,   -58,
     -58,     8,    50,   -58,    41,   -58,    49,    37,    42,    55,
      43,    38,   -58,    44,    45,    47,    -6,   -58,    46,   -58,
     -58,   -58,    51,    -6,   -58,   -58,    59,    -3,     8,    52,
       0,    53,    33,   -58,     7,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,    54,    60,   -58,    34,    20,   -58,   -58,
       7,   -58,    56,     7,    57,    58,    62,   -58,     7,   -58,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,     7,     7,   -58,
     -58,     7,    63,   -58,    64,     7,     7,   -58,   -58,   -58,
      40,    20,   -58,     5,     5,    65,   -58,    66,    48,    74,
     -58,   -58,   -58,     7,     5,   -58,   -58
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -58,   -58,   -58,    77,    61,   -58,     6,   -58,   -58,   -58,
     -58,    67,   -58,    70,   -58,   -58,   -57,   -58,   -58,   -58,
     -58,   -40,   -37,   -58,   -58,   -58,    13,   -58,    18,   -58,
       4,   -58,   -58,   -58,   -58
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -64
static const yysigned_char yytable[] =
{
      62,     1,    39,     2,    66,    40,    11,    41,    42,    43,
      39,    42,    43,    40,     9,    41,    42,    43,    42,    43,
      82,    44,    19,    84,    44,    29,    45,    46,    88,    44,
      61,    44,    19,    29,    12,    46,    99,   100,    13,    36,
      89,    89,    79,    80,    89,    95,    96,   106,    69,    70,
      71,    72,    73,    74,    75,    76,     1,   -63,    18,   -41,
      75,    76,    15,   105,    23,    16,    24,   -15,    25,    26,
      38,   -19,    32,    68,    27,    29,    60,    63,    34,   103,
     104,    10,    86,    85,    67,    92,    83,    87,    93,    94,
      90,   102,   101,    31,    35,    30,    91
};

static const unsigned char yycheck[] =
{
      40,     7,     5,     9,    44,     8,    11,    10,    11,    12,
       5,    11,    12,     8,     0,    10,    11,    12,    11,    12,
      60,    24,    16,    63,    24,    28,    29,    30,    68,    24,
      30,    24,    26,    28,    26,    30,    93,    94,    30,    33,
      77,    78,    22,    23,    81,    85,    86,   104,    14,    15,
      16,    17,    18,    19,    20,    21,     7,    24,     9,    26,
      20,    21,    12,   103,    27,    24,    11,    25,    25,    31,
      11,    26,    26,    13,    30,    28,    24,    24,    27,    31,
       6,     4,    24,    26,    30,    81,    30,    25,    25,    25,
      77,    25,    27,    26,    33,    25,    78
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     7,     9,    33,    34,    35,    36,    38,    39,     0,
      35,    11,    26,    30,    40,    12,    24,    37,     9,    38,
      41,    42,    43,    27,    11,    25,    31,    30,    44,    28,
      45,    43,    26,    46,    27,    36,    38,    47,    11,     5,
       8,    10,    11,    12,    24,    29,    30,    45,    48,    49,
      50,    51,    52,    53,    54,    56,    58,    60,    62,    63,
      24,    30,    53,    24,    55,    64,    53,    30,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    57,    59,    22,
      23,    61,    53,    30,    53,    26,    24,    25,    53,    54,
      58,    60,    62,    25,    25,    53,    53,    65,    66,    48,
      48,    27,    25,    31,     6,    53,    48
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
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
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
#line 56 "cminus.y"
    { parseTree = yyvsp[0].tnode;
			    YYACCEPT;
			  ;}
    break;

  case 3:
#line 62 "cminus.y"
    { TreeNode * t = yyvsp[-1].tnode;
                            if (t != NULL)
                            { 
			      while (t->sibling != NULL)
				    t = (TreeNode *) t->sibling;
                              t->sibling = yyvsp[0].tnode;
                              yyval.tnode = yyvsp[-1].tnode; 
			    }
                            else yyval.tnode = yyvsp[0].tnode;
			  ;}
    break;

  case 4:
#line 73 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode;;}
    break;

  case 5:
#line 77 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 6:
#line 79 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 7:
#line 83 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(VarDeclK);
			    yyval.tnode->attr.op = yyvsp[-2].tok;
			    yyval.tnode->child[0] = (TreeNode *) newNode(IdK);
			    yyval.tnode->child[0]->attr.name = (char *) copyString(lastid);
			    insert_simple_var_record(lastid,scopenum);
  			    printf("\nINT VAR: %s\tSCOPE: %d\n",lastid,scopenum);
			   ;}
    break;

  case 8:
#line 91 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(VarDeclK);
			    yyval.tnode->attr.op = yyvsp[-3].tok;
			    yyval.tnode->child[0] = (TreeNode *) newNode(IdK);
			    yyval.tnode->child[0]->attr.name = (char *) copyString(lastid);
			    printf("\nARRAY VAR: %s\t",lastid);
			    yyval.tnode->child[0]->child[0] = (TreeNode *) newNode(ConstK);
			    yyval.tnode->child[0]->child[0]->attr.val = atoi(curToken.tokString); 
			    insert_array_var_record(lastid, scopenum, atoi(curToken.tokString));
			    printf("LENGTH: %d\tSCOPE: %d\n",atoi(curToken.tokString),scopenum);
			  ;}
    break;

  case 9:
#line 102 "cminus.y"
    {
			    yyval.tnode = yyvsp[-2].tnode;
			  ;}
    break;

  case 10:
#line 108 "cminus.y"
    {yyval.tok = INT;;}
    break;

  case 11:
#line 110 "cminus.y"
    {yyval.tok = VOID;;}
    break;

  case 12:
#line 114 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(FunDeclK);
			    yyval.tnode->attr.op = yyvsp[-1].tok;
			    yyval.tnode->child[0] = (TreeNode *) newNode(IdK);
			    yyval.tnode->child[0]->attr.name = (char *) copyString(lastid);
         		    insert_function_record(lastid, scopenum);
			    printf("\nFUNCTION: %s\tRETURN TYPE:%d\n",lastid,yyvsp[-1].tok);
                            scopenum++;
			   ;}
    break;

  case 13:
#line 123 "cminus.y"
    { yyval.tnode = yyvsp[-4].tnode;
			    yyval.tnode->child[1] = yyvsp[-2].tnode;
			    yyval.tnode->child[2] = yyvsp[0].tnode;
      			  ;}
    break;

  case 14:
#line 130 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode;
			  ;}
    break;

  case 15:
#line 133 "cminus.y"
    { yyval.tnode = NULL; 
			    printf("  PARA_LIST:\tVOID\n");
			  ;}
    break;

  case 16:
#line 139 "cminus.y"
    { TreeNode * t = yyvsp[-2].tnode;
                            if (t != NULL)
                            { 
			      while (t->sibling != NULL)
				    t = (TreeNode *) t->sibling;
                              t->sibling = yyvsp[0].tnode;
                              yyval.tnode = yyvsp[-2].tnode; 
			    }
                            else yyval.tnode = yyvsp[0].tnode;
			  ;}
    break;

  case 17:
#line 150 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 18:
#line 154 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(VarDeclK);
			    yyval.tnode->attr.op = yyvsp[-1].tok;
			    yyval.tnode->child[0] = (TreeNode *) newNode(IdK);
			    yyval.tnode->child[0]->attr.name = (char *) copyString(lastid);
			     printf("  INT VAR: %s \n",lastid);
			  ;}
    break;

  case 19:
#line 161 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(VarDeclK);
			    yyval.tnode->attr.op = yyvsp[-1].tok;
			    yyval.tnode->child[0] = (TreeNode *) newNode(IdK);
			    yyval.tnode->child[0]->attr.name = (char *) copyString(lastid);
			    printf("  ARRAY VAR: %s \n",lastid);
			  ;}
    break;

  case 20:
#line 168 "cminus.y"
    { yyval.tnode = yyvsp[-2].tnode; ;}
    break;

  case 21:
#line 172 "cminus.y"
    { 
			    TreeNode * t = yyvsp[-2].tnode;
                if (t != NULL)
                { 
			      while (t->sibling != NULL)
			      	    t = (TreeNode *) t->sibling;
                  t->sibling = yyvsp[-1].tnode;
                  yyval.tnode = yyvsp[-2].tnode; 
			    }
                else yyval.tnode = yyvsp[-1].tnode;
                scopenum--;        
			  ;}
    break;

  case 22:
#line 187 "cminus.y"
    { TreeNode * t = yyvsp[-1].tnode;
                            if (t != NULL)
                            { 
			      while (t->sibling != NULL)
				    t = (TreeNode *) t->sibling;
                              t->sibling = yyvsp[0].tnode;
                              yyval.tnode = yyvsp[-1].tnode; 
			    }
                            else yyval.tnode = yyvsp[0].tnode;
			  ;}
    break;

  case 23:
#line 198 "cminus.y"
    { yyval.tnode = NULL; ;}
    break;

  case 24:
#line 202 "cminus.y"
    { TreeNode * t = yyvsp[-1].tnode;
                            if (t != NULL)
                            { 
			      while (t->sibling != NULL)
				    t = (TreeNode *) t->sibling;
                              t->sibling = yyvsp[0].tnode;
                              yyval.tnode = yyvsp[-1].tnode; 
			    }
                            else yyval.tnode = yyvsp[0].tnode;
			  ;}
    break;

  case 25:
#line 213 "cminus.y"
    { yyval.tnode = NULL; ;}
    break;

  case 26:
#line 217 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 27:
#line 219 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 28:
#line 221 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 29:
#line 223 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 30:
#line 225 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 31:
#line 229 "cminus.y"
    { yyval.tnode = yyvsp[-1].tnode; ;}
    break;

  case 32:
#line 231 "cminus.y"
    { yyval.tnode = NULL; ;}
    break;

  case 33:
#line 235 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(IfK);
			    yyval.tnode->child[0] = yyvsp[-2].tnode;
			    yyval.tnode->child[1] = yyvsp[0].tnode;
			  ;}
    break;

  case 34:
#line 240 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(IfK);
			    yyval.tnode->child[0] = yyvsp[-4].tnode;
			    yyval.tnode->child[1] = yyvsp[-2].tnode;
			    yyval.tnode->child[2] = yyvsp[0].tnode;
			  ;}
    break;

  case 35:
#line 248 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(WhileK);
			    yyval.tnode->child[0] = yyvsp[-2].tnode;
			    yyval.tnode->child[1] = yyvsp[0].tnode;
			  ;}
    break;

  case 36:
#line 255 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(ReturnK); ;}
    break;

  case 37:
#line 257 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(ReturnK); 
			    yyval.tnode->child[0] = yyvsp[-1].tnode;
			  ;}
    break;

  case 38:
#line 263 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(AssignK);
			    yyval.tnode->child[0] = yyvsp[-2].tnode;
			    yyval.tnode->child[1] = yyvsp[0].tnode;
			  ;}
    break;

  case 39:
#line 268 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 40:
#line 272 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(IdK);
			    yyval.tnode->attr.name = (char *) copyString(lastid);
			  ;}
    break;

  case 41:
#line 276 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(IdK);
			    yyval.tnode->attr.name = (char *) copyString(lastid);
			  ;}
    break;

  case 42:
#line 280 "cminus.y"
    { yyval.tnode = yyvsp[-3].tnode;
			    yyval.tnode->child[0] = yyvsp[-1].tnode;
			  ;}
    break;

  case 43:
#line 286 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(OpK);
			    yyval.tnode->attr.op = yyvsp[-1].tok;
			    yyval.tnode->child[0] = yyvsp[-2].tnode;
			    yyval.tnode->child[1] = yyvsp[0].tnode;
			  ;}
    break;

  case 44:
#line 292 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 45:
#line 296 "cminus.y"
    { yyval.tok = EQ; ;}
    break;

  case 46:
#line 298 "cminus.y"
    { yyval.tok = NOTEQ; ;}
    break;

  case 47:
#line 300 "cminus.y"
    { yyval.tok = LTEQ; ;}
    break;

  case 48:
#line 302 "cminus.y"
    { yyval.tok = GTEQ; ;}
    break;

  case 49:
#line 304 "cminus.y"
    { yyval.tok = LT; ;}
    break;

  case 50:
#line 306 "cminus.y"
    { yyval.tok = GT; ;}
    break;

  case 51:
#line 310 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(OpK);
			    yyval.tnode->attr.op = yyvsp[-1].tok;
			    yyval.tnode->child[0] = yyvsp[-2].tnode;
			    yyval.tnode->child[2] = yyvsp[0].tnode;
			  ;}
    break;

  case 52:
#line 316 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 53:
#line 320 "cminus.y"
    { yyval.tok = PLUS; ;}
    break;

  case 54:
#line 322 "cminus.y"
    { yyval.tok = MINUS; ;}
    break;

  case 55:
#line 326 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(OpK);
			    yyval.tnode->attr.op = yyvsp[-1].tok;
			    yyval.tnode->child[0] = yyvsp[-2].tnode;
			    yyval.tnode->child[2] = yyvsp[0].tnode;
			  ;}
    break;

  case 56:
#line 332 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 57:
#line 336 "cminus.y"
    { yyval.tok = TIMES; ;}
    break;

  case 58:
#line 338 "cminus.y"
    { yyval.tok = OVER; ;}
    break;

  case 59:
#line 342 "cminus.y"
    { yyval.tnode = yyvsp[-1].tnode; ;}
    break;

  case 60:
#line 344 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 61:
#line 346 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 62:
#line 348 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(ConstK);
			    yyval.tnode->attr.val = atoi(curToken.tokString);
			  ;}
    break;

  case 63:
#line 354 "cminus.y"
    { yyval.tnode = (TreeNode *) newNode(CallK);
			    yyval.tnode->child[0] = (TreeNode *) newNode(IdK);
			    yyval.tnode->child[0]->attr.name = (char *) copyString(lastid);
			  ;}
    break;

  case 64:
#line 359 "cminus.y"
    { yyval.tnode = yyvsp[-3].tnode; 
			    yyval.tnode->child[1] = yyvsp[-1].tnode;
			  ;}
    break;

  case 65:
#line 365 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;

  case 66:
#line 367 "cminus.y"
    { yyval.tnode = NULL; ;}
    break;

  case 67:
#line 371 "cminus.y"
    { TreeNode * t = yyvsp[-2].tnode;
                            if (t != NULL)
                            { 
			      while (t->sibling != NULL)
				    t = (TreeNode *) t->sibling;
                              t->sibling = yyvsp[0].tnode;
                              yyval.tnode = yyvsp[-2].tnode; 
			    }
                            else yyval.tnode = yyvsp[0].tnode;
			  ;}
    break;

  case 68:
#line 382 "cminus.y"
    { yyval.tnode = yyvsp[0].tnode; ;}
    break;


    }

/* Line 991 of yacc.c.  */
#line 1611 "cminus.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab2;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:

  /* Suppress GCC warning that yyerrlab1 is unused when no action
     invokes YYERROR.  */
#if defined (__GNUC_MINOR__) && 2093 <= (__GNUC__ * 1000 + __GNUC_MINOR__)
  __attribute__ ((__unused__))
#endif


  goto yyerrlab2;


/*---------------------------------------------------------------.
| yyerrlab2 -- pop states until the error token can be shifted.  |
`---------------------------------------------------------------*/
yyerrlab2:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 385 "cminus.y"


void yyerror(char * message)
{ printf("\nSyntax error at line %d: %s\n",lineno,message);
}
