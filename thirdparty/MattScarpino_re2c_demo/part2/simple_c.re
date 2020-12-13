#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simple_c_grammar.h"

#define   YYCTYPE     char
#define   YYCURSOR    s->cur
#define   YYMARKER    s->ptr

/* functions to interface the lemon parser */
void *ParseAlloc();
void Parse();
void ParseFree();

typedef struct ParserCount {
  int numFunctionDefinitions;
  int numVariableDeclarations;
} ParserCount;

typedef struct Scanner {
  char *top, *cur, *ptr, *pos;
  int line;  
} Scanner;

int scan(Scanner* s, char *buff_end) {
  
regular:
  if (s->cur >= buff_end) {
    return END_TOKEN;
  }
  s->top = s->cur;

/*!re2c
  re2c:yyfill:enable = 0;
 
  ALPHANUMS = [a-zA-Z0-9]+;
  whitespace = [ \t\v\f]+;
  dig = [0-9];
  let = [a-zA-Z_];
  hex = [a-fA-F0-9];
  int_des = [uUlL]*;
  any = [\000-\377];
*/

/*!re2c
  "/*"                  { goto comment; }
  "="                   { return EQ; }
  '('                   { return LPAREN; }
  ")"                   { return RPAREN; }
  "{"                   { return LBRACE; }
  "}"                   { return RBRACE; }
  "["                   { return LBRACKET; }
  "]"                   { return RBRACKET; }  
  ";"                   { return SEMICOLON; }
  ","                   { return COMMA; }
  "?"                   { return QUESTION; }
  ":"                   { return COLON; }
  "~"                   { return TILDE; }

  "+"                   { return ADD; }
  "+="                  { return ADDEQ; }
  "++"                  { return ADDADD; }
  "-"                   { return SUB; }
  "-="                  { return SUBEQ; }
  "--"                  { return SUBSUB; }
  "*"                   { return STAR; }
  "*="                  { return MULEQ; }  
  "/"                   { return DIV; }
  "/="                  { return DIVEQ; }  
  "%"                   { return MOD; }
  "%="                  { return MODEQ; }

  "=="                  { return EQEQ; }
  "!="                  { return NOTEQ; }
  "<"                   { return LT; }
  ">"                   { return GT; }
  "<="                  { return LTEQ; }
  ">="                  { return GTEQ; }

  "!"                   { return NOT; }
	"&"			              { return AND; }
  "&="                  { return ANDEQ; }  
	"|"			              { return OR; }
	"|="		              { return OREQ; }
	"&&"			            { return ANDAND; }
	"||"			            { return OROR; }  
  "^"                   { return XOR; }
  "^="                  { return XOREQ; }

  ">>"                  { return SR; }
  ">>="                 { return SREQ; }
  "<<"                  { return SL; }
  "<<="                 { return SLEQ; }
  
  "void"                { return VOID; }
  "char"                { return CHAR; }
  "short"               { return SHORT; }
  "int"                 { return INT; }
  "long"                { return LONG; }
  "signed"              { return SIGNED; }
  "unsigned"            { return UNSIGNED; }
  "float"               { return FLOAT; }  
  "double"              { return DOUBLE; }  
  
  "const"               { return CONST; }
  "volatile"            { return VOLATILE; }
  
  "extern"              { return EXTERN; }
  "static"              { return STATIC; }
  "auto"                { return AUTO; }
  "register"            { return REGISTER; }
  
  "struct"              { return STRUCT; }
  "union"               { return UNION; }

  "return"              { return RETURN; }
  ["]([^"]+)["]         { return STRING_LITERAL; }
  let (let|dig)*        { return NAME; }
  whitespace            { goto regular; }

	("0" [xX] hex+ int_des?) | ("0" dig+ int_des?) | (dig+ int_des?)
  { return(INT_LITERAL); }

  "\r\n"|"\n"
  {
    s->pos = s->cur;
    s->line++;
    goto regular;
  }

  any
  {
    printf("unexpected character: %c\n", *s->cur);
    goto regular;
  }
*/

comment:
/*!re2c
  "*/"          { goto regular; }
  "\n"          { s->line++; goto comment; }
  any           { goto comment; }
*/
}

int main() {

  FILE *fp, *traceFile;
  long size;
  char *buff, *buff_end;
  char name_str[64];
  size_t bytes;
  int name_length, token;
  Scanner scanner;
  void *parser;
  ParserCount pCount;

  /* Open input file */
  fp = fopen("test.dat", "r");
  if(fp == NULL) {
    fprintf(stderr, "Can't open test file\n");
    exit(-1);
  }

  /* Open trace file */
  traceFile = fopen("trace.out", "w");
  if(traceFile == NULL) {
    fprintf(stderr, "Can't open trace file\n");
    exit(-1);
  }

  /* Get file size */
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  rewind(fp);

  /* Allocate buffer and read */
  buff = (char*) malloc(size * sizeof(char));
  bytes = fread(buff, 1, size, fp);  
  if (bytes != size) {
    fprintf(stderr, "Error reading input file\n");
    exit(-1);
  }

  /* Initialize scanner */
  scanner.top = buff;
  scanner.cur = buff;
  scanner.pos = buff;  
  scanner.line = 1;
  
  /* Initialize the parser state structure */
  pCount.numFunctionDefinitions = 0;
  pCount.numVariableDeclarations = 0;
  
  /* Pointer to the end of the buffer */
  buff_end = (char*) (((char*)buff) + size);

  /* Create parser and set up tracing */
  parser = ParseAlloc(malloc);
  ParseTrace(traceFile, "parser >> ");

  while(token = scan(&scanner, buff_end)) {
    
    // Send strings to the parser with NAME tokens
    if(token == NAME) {
      name_length = scanner.cur - scanner.top;
      strncpy(name_str, scanner.top, name_length);
      name_str[name_length] = '\0';
      Parse(parser, token, name_str, &pCount);
    }
    else {
      Parse(parser, token, "", &pCount);
    }

    // Execute Parse for the last time
    if(token == END_TOKEN) {
      Parse(parser, 0, NULL);
      break;
    }
  }

  /* Print results of parsing */
  printf("Number of function definitions: %d.\n", pCount.numFunctionDefinitions);
  printf("Number of variable declarations: %d.\n", pCount.numVariableDeclarations);

  /* Deallocate parser */
  ParseFree(parser, free);

  /* Close files and deallocate */
  fclose(fp);
  fclose(traceFile);
  free(buff);
  return(0);
}