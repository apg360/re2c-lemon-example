/* Generated by re2c 2.0.3 on Thu Jan  7 10:38:29 2021 */
#line 1 "simple_c.re"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Token_value {
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
  enum Token_value token;
  char tokenvalue[255]; // no more than 255 characters
  int line_number,column_position;
};

struct scanner_state SCANNER_STATE;

void SCANNER(char *buff, char *buff_end) {

    SCANNER_STATE.begin = buff;
    SCANNER_STATE.cursor = buff;
    SCANNER_STATE.lexeme = buff;
    SCANNER_STATE.line_number = 1;
    SCANNER_STATE.column_position = 1;
    
    #line 50 "simple_c.re"


  // Infinite loop
  for (;;) {
loop:
    if (SCANNER_STATE.cursor >= buff_end) {
        SCANNER_STATE.token = END_TOKEN; goto end;
    }
    SCANNER_STATE.begin = SCANNER_STATE.cursor;

    
#line 51 "simple_c.c"
{
	char yych;
	yych = *SCANNER_STATE.cursor;
	switch (yych) {
	case 0x00:
	case '\n':	goto yy2;
	case '\t':
	case '\v':
	case '\f':
	case ' ':	goto yy6;
	case '\r':	goto yy9;
	case '"':	goto yy10;
	case '(':	goto yy11;
	case ')':	goto yy13;
	case '/':	goto yy15;
	case '0':	goto yy16;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy18;
	case ';':	goto yy20;
	case '=':	goto yy22;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy24;
	case 'i':	goto yy27;
	case 'r':	goto yy28;
	case '{':	goto yy29;
	case '}':	goto yy31;
	default:	goto yy4;
	}
yy2:
	++SCANNER_STATE.cursor;
#line 78 "simple_c.re"
	{ SCANNER_STATE.lexeme = SCANNER_STATE.cursor; SCANNER_STATE.line_number++; goto loop; }
#line 140 "simple_c.c"
yy4:
	++SCANNER_STATE.cursor;
yy5:
#line 80 "simple_c.re"
	{ printf("unexpected character: %c\n", *SCANNER_STATE.cursor); goto loop; }
#line 146 "simple_c.c"
yy6:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '\t':
	case '\v':
	case '\f':
	case ' ':	goto yy6;
	default:	goto yy8;
	}
yy8:
#line 72 "simple_c.re"
	{ goto loop; }
#line 159 "simple_c.c"
yy9:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '\n':	goto yy2;
	default:	goto yy5;
	}
yy10:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '"':	goto yy5;
	default:	goto yy33;
	}
yy11:
	++SCANNER_STATE.cursor;
#line 63 "simple_c.re"
	{ SCANNER_STATE.token = LPAREN; goto end;}
#line 176 "simple_c.c"
yy13:
	++SCANNER_STATE.cursor;
#line 64 "simple_c.re"
	{ SCANNER_STATE.token = RPAREN; goto end;}
#line 181 "simple_c.c"
yy15:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '*':	goto yy35;
	default:	goto yy5;
	}
yy16:
	yych = *(SCANNER_STATE.marker = ++SCANNER_STATE.cursor);
	switch (yych) {
	case 'X':
	case 'x':	goto yy39;
	default:	goto yy19;
	}
yy17:
#line 75 "simple_c.re"
	{ SCANNER_STATE.token=(INT_LITERAL); goto end;}
#line 198 "simple_c.c"
yy18:
	yych = *++SCANNER_STATE.cursor;
yy19:
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy18;
	case 'L':
	case 'U':
	case 'l':
	case 'u':	goto yy37;
	default:	goto yy17;
	}
yy20:
	++SCANNER_STATE.cursor;
#line 67 "simple_c.re"
	{ SCANNER_STATE.token = SEMICOLON; goto end;}
#line 223 "simple_c.c"
yy22:
	++SCANNER_STATE.cursor;
#line 62 "simple_c.re"
	{ SCANNER_STATE.token = EQUAL; goto end;}
#line 228 "simple_c.c"
yy24:
	yych = *++SCANNER_STATE.cursor;
yy25:
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy24;
	default:	goto yy26;
	}
yy26:
#line 71 "simple_c.re"
	{ SCANNER_STATE.token = NAME; goto end;}
#line 301 "simple_c.c"
yy27:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'n':	goto yy41;
	default:	goto yy25;
	}
yy28:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'e':	goto yy42;
	default:	goto yy25;
	}
yy29:
	++SCANNER_STATE.cursor;
#line 65 "simple_c.re"
	{ SCANNER_STATE.token = LBRACE; goto end;}
#line 318 "simple_c.c"
yy31:
	++SCANNER_STATE.cursor;
#line 66 "simple_c.re"
	{ SCANNER_STATE.token = RBRACE; goto end;}
#line 323 "simple_c.c"
yy33:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '"':	goto yy43;
	default:	goto yy33;
	}
yy35:
	++SCANNER_STATE.cursor;
#line 61 "simple_c.re"
	{ goto comment; }
#line 334 "simple_c.c"
yy37:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'L':
	case 'U':
	case 'l':
	case 'u':	goto yy37;
	default:	goto yy17;
	}
yy39:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':	goto yy45;
	default:	goto yy40;
	}
yy40:
	SCANNER_STATE.cursor = SCANNER_STATE.marker;
	goto yy17;
yy41:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 't':	goto yy47;
	default:	goto yy25;
	}
yy42:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 't':	goto yy49;
	default:	goto yy25;
	}
yy43:
	++SCANNER_STATE.cursor;
#line 70 "simple_c.re"
	{ SCANNER_STATE.token = STRING_LITERAL; goto end;}
#line 390 "simple_c.c"
yy45:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':	goto yy45;
	case 'L':
	case 'U':
	case 'l':
	case 'u':	goto yy37;
	default:	goto yy17;
	}
yy47:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy24;
	default:	goto yy48;
	}
yy48:
#line 68 "simple_c.re"
	{ SCANNER_STATE.token = INT_TYPE; goto end;}
#line 493 "simple_c.c"
yy49:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'u':	goto yy50;
	default:	goto yy25;
	}
yy50:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'r':	goto yy51;
	default:	goto yy25;
	}
yy51:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'n':	goto yy52;
	default:	goto yy25;
	}
yy52:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy24;
	default:	goto yy53;
	}
yy53:
#line 69 "simple_c.re"
	{ SCANNER_STATE.token = RETURN; goto end;}
#line 583 "simple_c.c"
}
#line 81 "simple_c.re"


comment:
    
#line 590 "simple_c.c"
{
	char yych;
	yych = *SCANNER_STATE.cursor;
	switch (yych) {
	case '\n':	goto yy58;
	case '*':	goto yy60;
	default:	goto yy56;
	}
yy56:
	++SCANNER_STATE.cursor;
yy57:
#line 87 "simple_c.re"
	{ goto comment; }
#line 604 "simple_c.c"
yy58:
	++SCANNER_STATE.cursor;
#line 86 "simple_c.re"
	{ SCANNER_STATE.line_number++; goto comment; }
#line 609 "simple_c.c"
yy60:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '/':	goto yy61;
	default:	goto yy57;
	}
yy61:
	++SCANNER_STATE.cursor;
#line 85 "simple_c.re"
	{ goto loop; }
#line 620 "simple_c.c"
}
#line 88 "simple_c.re"


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
          sprintf( SCANNER_STATE.tokenvalue, "NAME (\'%.*s\')", (int)(SCANNER_STATE.cursor - SCANNER_STATE.begin), SCANNER_STATE.begin );
          printf("%s",SCANNER_STATE.tokenvalue);
          break;
        case STRING_LITERAL:
          sprintf( SCANNER_STATE.tokenvalue, "STRING_LITERAL (\'%.*s\')", (int)(SCANNER_STATE.cursor - SCANNER_STATE.begin), SCANNER_STATE.begin );
          printf("%s",SCANNER_STATE.tokenvalue);
          break;
        case INT_LITERAL:
          sprintf( SCANNER_STATE.tokenvalue, "INT_LITERAL (\'%.*s\')", (int)(SCANNER_STATE.cursor - SCANNER_STATE.begin), SCANNER_STATE.begin );
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
  
  buff_end = (char*) ( ((char*)buff) + size );
  
  //printf(">>>> buff : '%s'\n",buff);
  //printf(">>>> buff_end : '%s'\n",buff_end);
  
  /* Start scanning */
  SCANNER(buff, buff_end);

  /* Close file and deallocate */
  fclose(fp);
  free(buff);
  return(0);
}