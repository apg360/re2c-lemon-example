
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




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 40 "cminus.y"
typedef union YYSTYPE { TreeNode * tnode;
         TokenType tok; } YYSTYPE;
/* Line 1248 of yacc.c.  */
#line 101 "cminus.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


