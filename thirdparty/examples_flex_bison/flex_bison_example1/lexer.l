%{
#include "parser.h"
#include "symtab.h"
#include <string.h>
#include <math.h>

int line = 1, col = 1;


%}

%%
([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?)   { col += (int) strlen(yytext); yylval.dval = atof(yytext); return NUM; } 
[ \t]   { col += (int) strlen(yytext); }               /* ignore but count white space */
[A-Za-z][A-Za-z0-9]*                           { 
                                                col += (int) strlen(yytext); 
                                                struct symtab *sp = symlook(yytext);
                                                yylval.symp = sp;
                                                return NAME; 
                                               }
\n      { col = 0; ++line; return yytext[0]; }
.       { col += (int) strlen(yytext); return yytext[0]; }
%%
/**
 * reset the line and column count
 *
 *
 */
void reset_lexer(void)
{

  line = 1;
  col  = 1;

}

/**
 * yyerror() is invoked when the lexer or the parser encounter
 * an error. The error message is passed via *s
 * 
 *
 */
void yyerror(char *s)
{
  printf("error: %s at line: %d col: %d\n",s,line,col);

}

/**
 * Normaly, the scanner reads from file handles, this function
 * is responsible for telling the scanner that there is no more
 * input.  It should return true if there are no more input files,
 * or if there are, it should close the previous file, open the next,
 * and return false (0).
 *
 *
 */
int yywrap(void)
{
  return 1;
}

