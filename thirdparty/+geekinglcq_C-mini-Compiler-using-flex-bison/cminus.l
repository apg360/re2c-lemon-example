/* cminus.l
 * James Niehaus
 * lex specification for the cminus language
 * to be compiled with flex, then gcc
 * taken and modified from tiny.l by Kenneth C. Louden
 */

%{
#include "globals.h"
#include "util.h"

TokenStruct build(TokenType tok);
TokenStruct curToken;
char * lastid;
int lineno = 0;


%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+

%%

"if"            {build(IF); return IF;}
"else"          {build(ELSE); return ELSE;}
"int"           {build(INT); return INT;}
"void"          {build(VOID); return VOID;}
"return"        {build(RETURN); return RETURN;}
"while"         {build(WHILE); return WHILE;}
"="             {build(ASSIGN); return ASSIGN;}
"<="            {build(LTEQ); return LTEQ;}
">="            {build(GTEQ); return GTEQ;}
"<"             {build(LT); return LT;}
">"             {build(GT); return GT;}
"=="            {build(EQ); return EQ;}
"!="            {build(NOTEQ); return NOTEQ;}
"+"             {build(PLUS); return PLUS;}
"-"             {build(MINUS); return MINUS;}
"*"             {build(TIMES); return TIMES;}
"/"             {build(OVER); return OVER;}
"("             {build(LPAREN); return LPAREN;}
")"             {build(RPAREN); return RPAREN;}
"["             {build(LBRACK); return LBRACK;}
"]"             {build(RBRACK); return RBRACK;}
"{"             {build(LCURL); return LCURL;}
"}"             {build(RCURL); return RCURL;}
";"             {build(SEMI); return SEMI;}
","             {build(COMMA); return COMMA;}
{number}        {build(NUM); return NUM;}
{identifier}    { if (lastid != NULL)
                  {
		    free(lastid);
		  }
                  build(ID); 
		  lastid = (char *) copyString(curToken.tokString); 
		  return ID;}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}
"/*"            { char c;
                  char d;
                  c = input();
                  if (c != EOF)
                  {
                    do
                    { 
                      d = c;
                      c = input();
                      if (c == EOF) break;
                      if (c == '\n') lineno++;
                    } while (!(d == '*' && c == '/'));
                  }
                }
.               {build(ERROR); return ERROR;}

%%

TokenStruct build(TokenType tok)
{
  curToken.tok = tok;
  curToken.tokString = yytext;
  printToken(tok,yytext); 
  return curToken;
}
