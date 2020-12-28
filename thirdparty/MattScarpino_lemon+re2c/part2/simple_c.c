/* Generated by re2c 2.0.3 on Mon Dec 28 08:31:53 2020 */
#line 1 "simple_c.re"
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
void ParseTrace();

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

#line 44 "simple_c.re"



#line 41 "simple_c.c"
{
	YYCTYPE yych;
	yych = *YYCURSOR;
	switch (yych) {
	case '\t':
	case '\v':
	case '\f':
	case ' ':	goto yy4;
	case '\n':	goto yy7;
	case '\r':	goto yy9;
	case '!':	goto yy10;
	case '"':	goto yy12;
	case '%':	goto yy13;
	case '&':	goto yy15;
	case '(':	goto yy17;
	case ')':	goto yy19;
	case '*':	goto yy21;
	case '+':	goto yy23;
	case ',':	goto yy25;
	case '-':	goto yy27;
	case '/':	goto yy29;
	case '0':	goto yy31;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy33;
	case ':':	goto yy35;
	case ';':	goto yy37;
	case '<':	goto yy39;
	case '=':	goto yy41;
	case '>':	goto yy43;
	case '?':	goto yy45;
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
	case 'b':
	case 'g':
	case 'h':
	case 'j':
	case 'k':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 't':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy47;
	case '[':	goto yy50;
	case ']':	goto yy52;
	case '^':	goto yy54;
	case 'a':	goto yy56;
	case 'c':	goto yy57;
	case 'd':	goto yy58;
	case 'e':	goto yy59;
	case 'f':	goto yy60;
	case 'i':	goto yy61;
	case 'l':	goto yy62;
	case 'r':	goto yy63;
	case 's':	goto yy64;
	case 'u':	goto yy65;
	case 'v':	goto yy66;
	case '{':	goto yy67;
	case '|':	goto yy69;
	case '}':	goto yy71;
	case '~':	goto yy73;
	default:	goto yy2;
	}
yy2:
	++YYCURSOR;
yy3:
#line 133 "simple_c.re"
	{
    printf("unexpected character: %c\n", *s->cur);
    goto regular;
  }
#line 149 "simple_c.c"
yy4:
	yych = *++YYCURSOR;
	switch (yych) {
	case '\t':
	case '\v':
	case '\f':
	case ' ':	goto yy4;
	default:	goto yy6;
	}
yy6:
#line 120 "simple_c.re"
	{ goto regular; }
#line 162 "simple_c.c"
yy7:
	++YYCURSOR;
#line 126 "simple_c.re"
	{
    s->pos = s->cur;
    s->line++;
    goto regular;
  }
#line 171 "simple_c.c"
yy9:
	yych = *++YYCURSOR;
	switch (yych) {
	case '\n':	goto yy7;
	default:	goto yy3;
	}
yy10:
	yych = *++YYCURSOR;
	switch (yych) {
	case '=':	goto yy75;
	default:	goto yy11;
	}
yy11:
#line 81 "simple_c.re"
	{ return NOT; }
#line 187 "simple_c.c"
yy12:
	yych = *++YYCURSOR;
	switch (yych) {
	case '"':	goto yy3;
	default:	goto yy77;
	}
yy13:
	yych = *++YYCURSOR;
	switch (yych) {
	case '=':	goto yy79;
	default:	goto yy14;
	}
yy14:
#line 71 "simple_c.re"
	{ return MOD; }
#line 203 "simple_c.c"
yy15:
	yych = *++YYCURSOR;
	switch (yych) {
	case '&':	goto yy81;
	case '=':	goto yy83;
	default:	goto yy16;
	}
yy16:
#line 82 "simple_c.re"
	{ return AND; }
#line 214 "simple_c.c"
yy17:
	++YYCURSOR;
#line 49 "simple_c.re"
	{ return LPAREN; }
#line 219 "simple_c.c"
yy19:
	++YYCURSOR;
#line 50 "simple_c.re"
	{ return RPAREN; }
#line 224 "simple_c.c"
yy21:
	yych = *++YYCURSOR;
	switch (yych) {
	case '=':	goto yy85;
	default:	goto yy22;
	}
yy22:
#line 67 "simple_c.re"
	{ return STAR; }
#line 234 "simple_c.c"
yy23:
	yych = *++YYCURSOR;
	switch (yych) {
	case '+':	goto yy87;
	case '=':	goto yy89;
	default:	goto yy24;
	}
yy24:
#line 61 "simple_c.re"
	{ return ADD; }
#line 245 "simple_c.c"
yy25:
	++YYCURSOR;
#line 56 "simple_c.re"
	{ return COMMA; }
#line 250 "simple_c.c"
yy27:
	yych = *++YYCURSOR;
	switch (yych) {
	case '-':	goto yy91;
	case '=':	goto yy93;
	default:	goto yy28;
	}
yy28:
#line 64 "simple_c.re"
	{ return SUB; }
#line 261 "simple_c.c"
yy29:
	yych = *++YYCURSOR;
	switch (yych) {
	case '*':	goto yy95;
	case '=':	goto yy97;
	default:	goto yy30;
	}
yy30:
#line 69 "simple_c.re"
	{ return DIV; }
#line 272 "simple_c.c"
yy31:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'X':
	case 'x':	goto yy101;
	default:	goto yy34;
	}
yy32:
#line 123 "simple_c.re"
	{ return(INT_LITERAL); }
#line 283 "simple_c.c"
yy33:
	yych = *++YYCURSOR;
yy34:
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
	case '9':	goto yy33;
	case 'L':
	case 'U':
	case 'l':
	case 'u':	goto yy99;
	default:	goto yy32;
	}
yy35:
	++YYCURSOR;
#line 58 "simple_c.re"
	{ return COLON; }
#line 308 "simple_c.c"
yy37:
	++YYCURSOR;
#line 55 "simple_c.re"
	{ return SEMICOLON; }
#line 313 "simple_c.c"
yy39:
	yych = *++YYCURSOR;
	switch (yych) {
	case '<':	goto yy103;
	case '=':	goto yy105;
	default:	goto yy40;
	}
yy40:
#line 76 "simple_c.re"
	{ return LT; }
#line 324 "simple_c.c"
yy41:
	yych = *++YYCURSOR;
	switch (yych) {
	case '=':	goto yy107;
	default:	goto yy42;
	}
yy42:
#line 48 "simple_c.re"
	{ return EQ; }
#line 334 "simple_c.c"
yy43:
	yych = *++YYCURSOR;
	switch (yych) {
	case '=':	goto yy109;
	case '>':	goto yy111;
	default:	goto yy44;
	}
yy44:
#line 77 "simple_c.re"
	{ return GT; }
#line 345 "simple_c.c"
yy45:
	++YYCURSOR;
#line 57 "simple_c.re"
	{ return QUESTION; }
#line 350 "simple_c.c"
yy47:
	yych = *++YYCURSOR;
yy48:
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
	case 'z':	goto yy47;
	default:	goto yy49;
	}
yy49:
#line 119 "simple_c.re"
	{ return NAME; }
#line 423 "simple_c.c"
yy50:
	++YYCURSOR;
#line 53 "simple_c.re"
	{ return LBRACKET; }
#line 428 "simple_c.c"
yy52:
	++YYCURSOR;
#line 54 "simple_c.re"
	{ return RBRACKET; }
#line 433 "simple_c.c"
yy54:
	yych = *++YYCURSOR;
	switch (yych) {
	case '=':	goto yy113;
	default:	goto yy55;
	}
yy55:
#line 88 "simple_c.re"
	{ return XOR; }
#line 443 "simple_c.c"
yy56:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'u':	goto yy115;
	default:	goto yy48;
	}
yy57:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'h':	goto yy116;
	case 'o':	goto yy117;
	default:	goto yy48;
	}
yy58:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'o':	goto yy118;
	default:	goto yy48;
	}
yy59:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'x':	goto yy119;
	default:	goto yy48;
	}
yy60:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'l':	goto yy120;
	default:	goto yy48;
	}
yy61:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'n':	goto yy121;
	default:	goto yy48;
	}
yy62:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'o':	goto yy122;
	default:	goto yy48;
	}
yy63:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'e':	goto yy123;
	default:	goto yy48;
	}
yy64:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'h':	goto yy124;
	case 'i':	goto yy125;
	case 't':	goto yy126;
	default:	goto yy48;
	}
yy65:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'n':	goto yy127;
	default:	goto yy48;
	}
yy66:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'o':	goto yy128;
	default:	goto yy48;
	}
yy67:
	++YYCURSOR;
#line 51 "simple_c.re"
	{ return LBRACE; }
#line 517 "simple_c.c"
yy69:
	yych = *++YYCURSOR;
	switch (yych) {
	case '=':	goto yy129;
	case '|':	goto yy131;
	default:	goto yy70;
	}
yy70:
#line 84 "simple_c.re"
	{ return OR; }
#line 528 "simple_c.c"
yy71:
	++YYCURSOR;
#line 52 "simple_c.re"
	{ return RBRACE; }
#line 533 "simple_c.c"
yy73:
	++YYCURSOR;
#line 59 "simple_c.re"
	{ return TILDE; }
#line 538 "simple_c.c"
yy75:
	++YYCURSOR;
#line 75 "simple_c.re"
	{ return NOTEQ; }
#line 543 "simple_c.c"
yy77:
	yych = *++YYCURSOR;
	switch (yych) {
	case '"':	goto yy133;
	default:	goto yy77;
	}
yy79:
	++YYCURSOR;
#line 72 "simple_c.re"
	{ return MODEQ; }
#line 554 "simple_c.c"
yy81:
	++YYCURSOR;
#line 86 "simple_c.re"
	{ return ANDAND; }
#line 559 "simple_c.c"
yy83:
	++YYCURSOR;
#line 83 "simple_c.re"
	{ return ANDEQ; }
#line 564 "simple_c.c"
yy85:
	++YYCURSOR;
#line 68 "simple_c.re"
	{ return MULEQ; }
#line 569 "simple_c.c"
yy87:
	++YYCURSOR;
#line 63 "simple_c.re"
	{ return ADDADD; }
#line 574 "simple_c.c"
yy89:
	++YYCURSOR;
#line 62 "simple_c.re"
	{ return ADDEQ; }
#line 579 "simple_c.c"
yy91:
	++YYCURSOR;
#line 66 "simple_c.re"
	{ return SUBSUB; }
#line 584 "simple_c.c"
yy93:
	++YYCURSOR;
#line 65 "simple_c.re"
	{ return SUBEQ; }
#line 589 "simple_c.c"
yy95:
	++YYCURSOR;
#line 47 "simple_c.re"
	{ goto comment; }
#line 594 "simple_c.c"
yy97:
	++YYCURSOR;
#line 70 "simple_c.re"
	{ return DIVEQ; }
#line 599 "simple_c.c"
yy99:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'L':
	case 'U':
	case 'l':
	case 'u':	goto yy99;
	default:	goto yy32;
	}
yy101:
	yych = *++YYCURSOR;
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
	case 'f':	goto yy135;
	default:	goto yy102;
	}
yy102:
	YYCURSOR = YYMARKER;
	goto yy32;
yy103:
	yych = *++YYCURSOR;
	switch (yych) {
	case '=':	goto yy137;
	default:	goto yy104;
	}
yy104:
#line 93 "simple_c.re"
	{ return SL; }
#line 648 "simple_c.c"
yy105:
	++YYCURSOR;
#line 78 "simple_c.re"
	{ return LTEQ; }
#line 653 "simple_c.c"
yy107:
	++YYCURSOR;
#line 74 "simple_c.re"
	{ return EQEQ; }
#line 658 "simple_c.c"
yy109:
	++YYCURSOR;
#line 79 "simple_c.re"
	{ return GTEQ; }
#line 663 "simple_c.c"
yy111:
	yych = *++YYCURSOR;
	switch (yych) {
	case '=':	goto yy139;
	default:	goto yy112;
	}
yy112:
#line 91 "simple_c.re"
	{ return SR; }
#line 673 "simple_c.c"
yy113:
	++YYCURSOR;
#line 89 "simple_c.re"
	{ return XOREQ; }
#line 678 "simple_c.c"
yy115:
	yych = *++YYCURSOR;
	switch (yych) {
	case 't':	goto yy141;
	default:	goto yy48;
	}
yy116:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'a':	goto yy142;
	default:	goto yy48;
	}
yy117:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'n':	goto yy143;
	default:	goto yy48;
	}
yy118:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'u':	goto yy144;
	default:	goto yy48;
	}
yy119:
	yych = *++YYCURSOR;
	switch (yych) {
	case 't':	goto yy145;
	default:	goto yy48;
	}
yy120:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'o':	goto yy146;
	default:	goto yy48;
	}
yy121:
	yych = *++YYCURSOR;
	switch (yych) {
	case 't':	goto yy147;
	default:	goto yy48;
	}
yy122:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'n':	goto yy149;
	default:	goto yy48;
	}
yy123:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'g':	goto yy150;
	case 't':	goto yy151;
	default:	goto yy48;
	}
yy124:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'o':	goto yy152;
	default:	goto yy48;
	}
yy125:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'g':	goto yy153;
	default:	goto yy48;
	}
yy126:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'a':	goto yy154;
	case 'r':	goto yy155;
	default:	goto yy48;
	}
yy127:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'i':	goto yy156;
	case 's':	goto yy157;
	default:	goto yy48;
	}
yy128:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'i':	goto yy158;
	case 'l':	goto yy159;
	default:	goto yy48;
	}
yy129:
	++YYCURSOR;
#line 85 "simple_c.re"
	{ return OREQ; }
#line 771 "simple_c.c"
yy131:
	++YYCURSOR;
#line 87 "simple_c.re"
	{ return OROR; }
#line 776 "simple_c.c"
yy133:
	++YYCURSOR;
#line 118 "simple_c.re"
	{ return STRING_LITERAL; }
#line 781 "simple_c.c"
yy135:
	yych = *++YYCURSOR;
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
	case 'f':	goto yy135;
	case 'L':
	case 'U':
	case 'l':
	case 'u':	goto yy99;
	default:	goto yy32;
	}
yy137:
	++YYCURSOR;
#line 94 "simple_c.re"
	{ return SLEQ; }
#line 817 "simple_c.c"
yy139:
	++YYCURSOR;
#line 92 "simple_c.re"
	{ return SREQ; }
#line 822 "simple_c.c"
yy141:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'o':	goto yy160;
	default:	goto yy48;
	}
yy142:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'r':	goto yy162;
	default:	goto yy48;
	}
yy143:
	yych = *++YYCURSOR;
	switch (yych) {
	case 's':	goto yy164;
	default:	goto yy48;
	}
yy144:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'b':	goto yy165;
	default:	goto yy48;
	}
yy145:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'e':	goto yy166;
	default:	goto yy48;
	}
yy146:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'a':	goto yy167;
	default:	goto yy48;
	}
yy147:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy148;
	}
yy148:
#line 99 "simple_c.re"
	{ return INT; }
#line 930 "simple_c.c"
yy149:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'g':	goto yy168;
	default:	goto yy48;
	}
yy150:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'i':	goto yy170;
	default:	goto yy48;
	}
yy151:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'u':	goto yy171;
	default:	goto yy48;
	}
yy152:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'r':	goto yy172;
	default:	goto yy48;
	}
yy153:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'n':	goto yy173;
	default:	goto yy48;
	}
yy154:
	yych = *++YYCURSOR;
	switch (yych) {
	case 't':	goto yy174;
	default:	goto yy48;
	}
yy155:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'u':	goto yy175;
	default:	goto yy48;
	}
yy156:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'o':	goto yy176;
	default:	goto yy48;
	}
yy157:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'i':	goto yy177;
	default:	goto yy48;
	}
yy158:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'd':	goto yy178;
	default:	goto yy48;
	}
yy159:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'a':	goto yy180;
	default:	goto yy48;
	}
yy160:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy161;
	}
yy161:
#line 111 "simple_c.re"
	{ return AUTO; }
#line 1068 "simple_c.c"
yy162:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy163;
	}
yy163:
#line 97 "simple_c.re"
	{ return CHAR; }
#line 1140 "simple_c.c"
yy164:
	yych = *++YYCURSOR;
	switch (yych) {
	case 't':	goto yy181;
	default:	goto yy48;
	}
yy165:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'l':	goto yy183;
	default:	goto yy48;
	}
yy166:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'r':	goto yy184;
	default:	goto yy48;
	}
yy167:
	yych = *++YYCURSOR;
	switch (yych) {
	case 't':	goto yy185;
	default:	goto yy48;
	}
yy168:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy169;
	}
yy169:
#line 100 "simple_c.re"
	{ return LONG; }
#line 1236 "simple_c.c"
yy170:
	yych = *++YYCURSOR;
	switch (yych) {
	case 's':	goto yy187;
	default:	goto yy48;
	}
yy171:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'r':	goto yy188;
	default:	goto yy48;
	}
yy172:
	yych = *++YYCURSOR;
	switch (yych) {
	case 't':	goto yy189;
	default:	goto yy48;
	}
yy173:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'e':	goto yy191;
	default:	goto yy48;
	}
yy174:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'i':	goto yy192;
	default:	goto yy48;
	}
yy175:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'c':	goto yy193;
	default:	goto yy48;
	}
yy176:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'n':	goto yy194;
	default:	goto yy48;
	}
yy177:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'g':	goto yy196;
	default:	goto yy48;
	}
yy178:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy179;
	}
yy179:
#line 96 "simple_c.re"
	{ return VOID; }
#line 1356 "simple_c.c"
yy180:
	yych = *++YYCURSOR;
	switch (yych) {
	case 't':	goto yy197;
	default:	goto yy48;
	}
yy181:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy182;
	}
yy182:
#line 106 "simple_c.re"
	{ return CONST; }
#line 1434 "simple_c.c"
yy183:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'e':	goto yy198;
	default:	goto yy48;
	}
yy184:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'n':	goto yy200;
	default:	goto yy48;
	}
yy185:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy186;
	}
yy186:
#line 103 "simple_c.re"
	{ return FLOAT; }
#line 1518 "simple_c.c"
yy187:
	yych = *++YYCURSOR;
	switch (yych) {
	case 't':	goto yy202;
	default:	goto yy48;
	}
yy188:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'n':	goto yy203;
	default:	goto yy48;
	}
yy189:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy190;
	}
yy190:
#line 98 "simple_c.re"
	{ return SHORT; }
#line 1602 "simple_c.c"
yy191:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'd':	goto yy205;
	default:	goto yy48;
	}
yy192:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'c':	goto yy207;
	default:	goto yy48;
	}
yy193:
	yych = *++YYCURSOR;
	switch (yych) {
	case 't':	goto yy209;
	default:	goto yy48;
	}
yy194:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy195;
	}
yy195:
#line 115 "simple_c.re"
	{ return UNION; }
#line 1692 "simple_c.c"
yy196:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'n':	goto yy211;
	default:	goto yy48;
	}
yy197:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'i':	goto yy212;
	default:	goto yy48;
	}
yy198:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy199;
	}
yy199:
#line 104 "simple_c.re"
	{ return DOUBLE; }
#line 1776 "simple_c.c"
yy200:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy201;
	}
yy201:
#line 109 "simple_c.re"
	{ return EXTERN; }
#line 1848 "simple_c.c"
yy202:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'e':	goto yy213;
	default:	goto yy48;
	}
yy203:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy204;
	}
yy204:
#line 117 "simple_c.re"
	{ return RETURN; }
#line 1926 "simple_c.c"
yy205:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy206;
	}
yy206:
#line 101 "simple_c.re"
	{ return SIGNED; }
#line 1998 "simple_c.c"
yy207:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy208;
	}
yy208:
#line 110 "simple_c.re"
	{ return STATIC; }
#line 2070 "simple_c.c"
yy209:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy210;
	}
yy210:
#line 114 "simple_c.re"
	{ return STRUCT; }
#line 2142 "simple_c.c"
yy211:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'e':	goto yy214;
	default:	goto yy48;
	}
yy212:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'l':	goto yy215;
	default:	goto yy48;
	}
yy213:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'r':	goto yy216;
	default:	goto yy48;
	}
yy214:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'd':	goto yy218;
	default:	goto yy48;
	}
yy215:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'e':	goto yy220;
	default:	goto yy48;
	}
yy216:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy217;
	}
yy217:
#line 112 "simple_c.re"
	{ return REGISTER; }
#line 2244 "simple_c.c"
yy218:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy219;
	}
yy219:
#line 102 "simple_c.re"
	{ return UNSIGNED; }
#line 2316 "simple_c.c"
yy220:
	yych = *++YYCURSOR;
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
	case 'z':	goto yy47;
	default:	goto yy221;
	}
yy221:
#line 107 "simple_c.re"
	{ return VOLATILE; }
#line 2388 "simple_c.c"
}
#line 137 "simple_c.re"


comment:

#line 2395 "simple_c.c"
{
	YYCTYPE yych;
	yych = *YYCURSOR;
	switch (yych) {
	case '\n':	goto yy226;
	case '*':	goto yy228;
	default:	goto yy224;
	}
yy224:
	++YYCURSOR;
yy225:
#line 143 "simple_c.re"
	{ goto comment; }
#line 2409 "simple_c.c"
yy226:
	++YYCURSOR;
#line 142 "simple_c.re"
	{ s->line++; goto comment; }
#line 2414 "simple_c.c"
yy228:
	yych = *++YYCURSOR;
	switch (yych) {
	case '/':	goto yy229;
	default:	goto yy225;
	}
yy229:
	++YYCURSOR;
#line 141 "simple_c.re"
	{ goto regular; }
#line 2425 "simple_c.c"
}
#line 144 "simple_c.re"

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

  while(token == scan(&scanner, buff_end)) {
    
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