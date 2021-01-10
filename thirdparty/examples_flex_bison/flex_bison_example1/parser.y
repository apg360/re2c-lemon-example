%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "symtab.h"


extern int yyerror(char *s);
extern int yylex( void );
extern char* yytext;

int num = 0;
%}

%union {
  double dval;
  struct symtab *symp;
}
%token <symp> NAME
%token <dval> NUM
%left '-' '+'
%left '*' '/'  /* order defines precedence '+' and '-' are at lowest level */
%right '^'    /* exponentiation        */
%nonassoc NEG     /* negation--unary minus */
%type <dval> exp
%expect 4


/* Grammar follows */
%%
 input:    /* empty string */
        | statement '\n'
	| input statement '\n'
;

 statement:    NAME '=' exp { $1->value = $3; }
        | exp   { printf ("\t%g\n", $1); }
;
/* Precedence for '+','-' vs '*',  '/' is NOT defined here.
 * Instead, the two %left commands above perform that role.
 */
 exp:  exp '+' exp        { $$ = $1 + $3;    }
        | exp '-' exp        { $$ = $1 - $3;    }
        | exp '*' exp        { $$ = $1 * $3;    }
        | exp '/' exp        { if ( $3 == 0.0)
                                 yyerror("divide by zero error");
                               else 
	                          $$ = $1 / $3;    }
        | '-' exp  %prec NEG { $$ = -$2;        }
        | exp '^' exp        { $$ =  pow ($1, $3); }
        | '(' exp ')'        { $$ = $2;         }
        | NUM
	| NAME		     { $$ = $1->value; }
;
%%

struct symtab * symlook(char *s)
{
  char *p;
  struct symtab *sp;
 
  for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
    if(sp->name && !strcmp(sp->name,s))
      return sp;

    if(!sp->name) {
      sp->name = (char *) strdup(s);
      return sp;
    }
  }
  yyerror("** Too many symbols check symlook in parser.y **");
    exit(1);
}



void reset_parser(void)
{
  num = 0;
}
