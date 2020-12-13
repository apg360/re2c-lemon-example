#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokens.h"

#define   YYCTYPE     char
#define   YYCURSOR    s->cur
#define   YYMARKER    s->ptr

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
  "/*"            { goto comment; }
  "="             { return EQUAL; }
  '('             { return LPAREN; }
  ")"             { return RPAREN; }
  "{"             { return LBRACE; }
  "}"             { return RBRACE; }
  ";"             { return SEMICOLON; }
  "int"           { return INT_TYPE; }
  "return"        { return RETURN; }
  ["]([^"]+)["]   { return STRING_LITERAL; }
  let (let|dig)*  { return NAME; }
  whitespace      { goto regular; }

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

  FILE *fp;
  long size;
  char *buff, *buff_end;
  size_t bytes;
  int token = 0;
  Scanner scanner;

  /* Open input file */
  fp = fopen("test.dat", "r");
  if(fp == NULL) {
    fprintf(stderr, "Can't open test file\n");
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
    fprintf(stderr, "Reading error"); 
    exit(-1);
  }

  /* Start scanning */
  scanner.top = buff;
  scanner.cur = buff;
  scanner.pos = buff;  
  scanner.line = 1;
  
  buff_end = (char*) (((char*)buff) + size);
  while(token = scan(&scanner, buff_end)) {
    switch(token) {
    case SEMICOLON: printf("SEMICOLON"); break;      
    case LPAREN: printf("LPAREN"); break;
    case RPAREN: printf("RPAREN"); break;
    case LBRACE: printf("LBRACE"); break;
    case RBRACE: printf("RBRACE"); break;
    case EQUAL: printf("EQUAL"); break;
    case INT_TYPE: printf("INT_TYPE"); break;
    case RETURN: printf("RETURN"); break;
    case NAME:
      printf("NAME (\'%.*s\')", scanner.cur - scanner.top, scanner.top);
      break;
    case STRING_LITERAL:
      printf("STRING_LITERAL (\'%.*s\')", scanner.cur - scanner.top, scanner.top);
      break;
    case INT_LITERAL:
      printf("INT_LITERAL (\'%.*s\')", scanner.cur - scanner.top, scanner.top);
      break;
    default:
      break;
    }
    if(END_TOKEN == token) {
      break;
    }
    printf(" found on Line %d at Position %d\n", scanner.line, (int)(scanner.top - scanner.pos));
  }

  /* Close file and deallocate */
  fclose(fp);
  free(buff);
  return(0);
}
