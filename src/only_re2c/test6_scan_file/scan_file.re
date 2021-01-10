//inspired from : https://www.codeproject.com/Articles/1035799/Generating-a-High-Speed-Parser-Part-re-c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum token_type {
  END_TOKEN,
  RETURN, NAME,
  STRING_LITERAL,
  INT_LITERAL,
  INT_TYPE,
  SEMICOLON=';',
  EQUAL='=',
  LPAREN='(',
  RPAREN=')',
  LBRACE='{',
  RBRACE='}'
};

struct scanner_state {
  const char *cursor, *marker, *begin, *end, *lexeme;
  enum token_type token;
  char tokenvalue[255]; // no more than 255 characters
  int line_number,column_position;
};

struct scanner_state SCANNER_STATE;

void set_token_value(const char *token_type)
{
  sprintf( SCANNER_STATE.tokenvalue, "%s (\'%.*s\')",token_type, (int)(SCANNER_STATE.cursor - SCANNER_STATE.begin), SCANNER_STATE.begin );
}

void SCANNER(const char *the_text) {

    SCANNER_STATE.begin = the_text;
    SCANNER_STATE.end = the_text + strlen(the_text);
    SCANNER_STATE.cursor = the_text;
    SCANNER_STATE.lexeme = the_text;
    SCANNER_STATE.line_number = 1;
    SCANNER_STATE.column_position = 1;
    
    /*!re2c
      re2c:define:YYCURSOR = SCANNER_STATE.cursor;
      re2c:define:YYMARKER = SCANNER_STATE.marker;
      re2c:define:YYCTYPE = char;
      re2c:yyfill:enable = 0;
     
      ALPHANUMS = [a-zA-Z0-9]+;
      whitespace = [ \t\v\f]+;
      dig = [0-9];
      let = [a-zA-Z_];
      hex = [a-fA-F0-9];
      int_des = [uUlL]*;
      any = [\000-\377];
      end = "\r\n"|"\n"|"\x00"; //cariage return + new line or new line or 0
    */

  // Infinite loop
  for (;;) {
loop:
    if (SCANNER_STATE.cursor >= SCANNER_STATE.end) {
        SCANNER_STATE.token = END_TOKEN; goto end;
    }
    SCANNER_STATE.begin = SCANNER_STATE.cursor;

    /*!re2c
      "/*"            { goto comment; }
      "="             { SCANNER_STATE.token = EQUAL; goto end;}
      '('             { SCANNER_STATE.token = LPAREN; goto end;}
      ")"             { SCANNER_STATE.token = RPAREN; goto end;}
      "{"             { SCANNER_STATE.token = LBRACE; goto end;}
      "}"             { SCANNER_STATE.token = RBRACE; goto end;}
      ";"             { SCANNER_STATE.token = SEMICOLON; goto end;}
      "int"           { SCANNER_STATE.token = INT_TYPE; goto end;}
      "return"        { SCANNER_STATE.token = RETURN; goto end;}
      ["]([^"]+)["]   { SCANNER_STATE.token = STRING_LITERAL; goto end;}
      let (let|dig)*  { SCANNER_STATE.token = NAME; goto end;}
      whitespace      { goto loop; }

      ("0" [xX] hex+ int_des?) | ("0" dig+ int_des?) | (dig+ int_des?)
      { SCANNER_STATE.token=(INT_LITERAL); goto end;}

      
      end { SCANNER_STATE.lexeme = SCANNER_STATE.cursor; SCANNER_STATE.line_number++; goto loop; }
      // Default rule : Anything else
      any { printf("unexpected character: %c\n", *SCANNER_STATE.cursor); goto loop; }
    */

comment:
    /*!re2c
      "*/"          { goto loop; }
      "\n"          { SCANNER_STATE.line_number++; goto comment; }
      any           { goto comment; }
    */

end:
    switch(SCANNER_STATE.token) {
        case SEMICOLON: printf("SEMICOLON"); break;
        case LPAREN: printf("LPAREN"); break;
        case RPAREN: printf("RPAREN"); break;
        case LBRACE: printf("LBRACE"); break;
        case RBRACE: printf("RBRACE"); break;
        case EQUAL: printf("EQUAL"); break;
        case INT_TYPE: printf("INT_TYPE"); break;
        case RETURN: printf("RETURN"); break;
        case NAME:
          set_token_value("NAME");
          printf("%s",SCANNER_STATE.tokenvalue);
          break;
        case STRING_LITERAL:
          set_token_value("STRING_LITERAL");
          printf("%s",SCANNER_STATE.tokenvalue);
          break;
        case INT_LITERAL:
          set_token_value("INT_LITERAL");
          printf("%s",SCANNER_STATE.tokenvalue);
          break;
        default:
          break;
    }
    SCANNER_STATE.column_position=(int)(SCANNER_STATE.begin - SCANNER_STATE.lexeme);
    printf(" found on Line %d at Position %d\n", SCANNER_STATE.line_number, SCANNER_STATE.column_position);
    
    // end inifinite loop when END_TOKEN
    if(END_TOKEN == SCANNER_STATE.token) break;
  }//for loop
}

//------------------------------
int main() {

  FILE *fp;
  long size;
  char *buff, *buff_end;
  size_t bytes;

  /* Open input file */
  fp = fopen("test.cscript", "r");
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
  
  buff_end = buff + strlen(buff);//(char*) ( ((char*)buff) + size );
  
  //printf(">>>> buff : '%s'\n",buff);
  //printf(">>>> buff_end : '%s'\n",buff_end);
  
  /* Start scanning */
  SCANNER(buff); //, buff_end);

  /* Close file and deallocate */
  fclose(fp);
  free(buff);
  return(0);
}
