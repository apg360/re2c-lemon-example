/* Generated by re2c 2.0.3 on Mon Jan 11 00:06:49 2021 */
// re2c $INPUT -o $OUTPUT -i
// french : https://fr.qaz.wiki/wiki/Re2c
// english : https://wikivisually.com/wiki/re2c
// https://www.systutorials.com/docs/linux/man/1-re2c
// https://re2c.org/manual/manual_c.html
//
// With Lemon it is the lexer/tokenizer that calls/initiate the parser
// re2c calls lemon
//----------------------------------------------------------------------

// the contents of 'definitions.re2c' are copy-pasted verbatim in place of the directive
//definitions.re2c START -----------------------
#include <common.h>

typedef enum { FAIL, OK } Result; //typedef enum { false, true } bool; // 0, 1

bool scanner_DebugMode = false;

/*
    'a' means the value of the character a.
    "a" means the address of the memory location where the string "a" is stored 
    (which will generally be in the data section of your program's memory space).
    At that memory location, you will have two bytes -- the character 'a' and the null terminator for the string.
*/
enum scanner_tokentype {
  END_TOKEN,
  RETURN,
  NAME,
  STRING_LITERAL,
  INT_LITERAL,
  INT_TYPE,
  WHITESPACE,
  UNDERSCORE='_',
  SEMICOLON=';',
  DOT='.',
  COMMA=',',
  ADD='+', SUB='-', MUL='*', DIV='/',
  ASSIGN='=',
  CEQ,//='==',
  CNE,//='!=',
  CLT='<',
  CLE,//='<=',
  CGT='>',
  CGE,//='>=',
  LPAREN='(',
  RPAREN=')',
  LBRACE='{',
  RBRACE='}'
};
// https://data-flair.training/blogs/union-in-c-language/
// union means only one member can be accessed at a time in a union.
// Only one data member of a union can be accessed at one time.
// Not a struct with many members but a struct with one single member, that can be one of those.
// A union prohibits the initialization of all its data members. The first member of the union can only be initialized through an object.
// ll the data members of a union share the same memory location. Hence, changes made in one data member inevitably affects the other.
union scanner_tokenvalue
{
    int   number;
    char  string[255];
};

void println(const char *str) {
  printf("%s\n",str);
}

struct scanner_state
{
    const char *cursor;             // current_char : the next input character to be read.  A pointer-like l-value that stores the current input position
    const char *begin;              //first_char
    const char *end;                //last_char, limit, YYLIMIT  : the position after the last available input character.   A pointer-like r-value that stores the end of input position
                                    //                Lexer compares YYCURSOR to YYLIMIT in order to determine if there is enough input characters left
    const char *marker;             // marker - the position of the most recent match
    const char *lexeme;             // the next input remaining to be scanned.

    enum scanner_tokentype tokentype;      //
    char tokenvalue[255];                  // the current matched value.  no more than 255 characters
    union scanner_tokenvalue *tokenvaluestruct;//not used

    int line_number, column_position;       //line number, column position
};


/*
R* : zero or more occurrences of the regular expression R.
R+ : one or more repetition of the regular expression R.
R? : zero or one R. That means, there maybe an R or not.
*/

//definitions.re2c END -----------------------



struct scanner_state SCANNER_STATE;

void set_token_value(const char *token_type)
{
  sprintf( SCANNER_STATE.tokenvalue, "%s (\'%.*s\')",token_type, (int)(SCANNER_STATE.cursor - SCANNER_STATE.begin), SCANNER_STATE.begin );
}

void SCANNER(const char *the_text)
{
    SCANNER_STATE.begin = the_text;
    SCANNER_STATE.end = the_text + strlen(the_text);
    SCANNER_STATE.cursor = the_text;
    SCANNER_STATE.lexeme = the_text;
    SCANNER_STATE.line_number = 1;
    SCANNER_STATE.column_position = 1;
    
    if (scanner_DebugMode == true) printf("\n ** START Scanning : '%s', ",the_text);
    if (scanner_DebugMode == true) printf("Number of characters %lu\n\n", strlen(the_text));
    bool bFoundSomething_and_token_handled; // if token found and handled in switch case
    
    
    
    // Infinite loop
    for (;;) {
loop:
    if (SCANNER_STATE.cursor >= SCANNER_STATE.end) {
        SCANNER_STATE.tokentype = END_TOKEN; goto end;
    }
    SCANNER_STATE.begin = SCANNER_STATE.cursor;
    bFoundSomething_and_token_handled = true; // by default assume something were found and handled
    
    
{
	char yych;
	unsigned int yyaccept = 0;
	yych = *SCANNER_STATE.cursor;
	switch (yych) {
	case 0x00:	goto yy2;
	case '\t':
	case '\n':
	case '\v':
	case '\f':
	case '\r':
	case ' ':	goto yy6;
	case '"':	goto yy9;
	case '(':	goto yy10;
	case ')':	goto yy12;
	case '*':	goto yy14;
	case '+':	goto yy16;
	case ',':	goto yy18;
	case '-':	goto yy20;
	case '.':	goto yy22;
	case '/':	goto yy24;
	case '0':	goto yy26;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy28;
	case ';':	goto yy30;
	case '=':	goto yy32;
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
	case 's':
	case 't':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy34;
	case '_':	goto yy37;
	case 'r':	goto yy39;
	case 'u':	goto yy40;
	case '{':	goto yy41;
	case '}':	goto yy43;
	default:	goto yy4;
	}
yy2:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.lexeme = SCANNER_STATE.cursor; SCANNER_STATE.line_number++; goto loop; }
yy4:
	++SCANNER_STATE.cursor;
yy5:
	{ printf("unexpected character: %c\n", *SCANNER_STATE.cursor+1); goto loop; }
yy6:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '\t':
	case '\n':
	case '\v':
	case '\f':
	case '\r':
	case ' ':	goto yy6;
	default:	goto yy8;
	}
yy8:
	{ SCANNER_STATE.tokentype = WHITESPACE; goto end;}
yy9:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '"':	goto yy5;
	default:	goto yy45;
	}
yy10:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.tokentype = LPAREN; goto end;}
yy12:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.tokentype = RPAREN; goto end;}
yy14:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.tokentype = MUL; goto end;}
yy16:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.tokentype = ADD; goto end;}
yy18:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.tokentype = COMMA; goto end;}
yy20:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.tokentype = SUB; goto end;}
yy22:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.tokentype = DOT; goto end;}
yy24:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '*':	goto yy47;
	default:	goto yy25;
	}
yy25:
	{ SCANNER_STATE.tokentype = DIV; goto end;}
yy26:
	yyaccept = 0;
	yych = *(SCANNER_STATE.marker = ++SCANNER_STATE.cursor);
	switch (yych) {
	case 'X':
	case 'x':	goto yy52;
	default:	goto yy29;
	}
yy27:
	{ SCANNER_STATE.tokentype = INT_LITERAL; goto end;}
yy28:
	yych = *++SCANNER_STATE.cursor;
yy29:
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
	case '9':	goto yy28;
	case 'L':
	case 'U':
	case 'l':
	case 'u':	goto yy49;
	default:	goto yy27;
	}
yy30:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.tokentype = SEMICOLON; goto end;}
yy32:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '=':	goto yy54;
	default:	goto yy33;
	}
yy33:
	{ SCANNER_STATE.tokentype = ASSIGN; goto end;}
yy34:
	yych = *++SCANNER_STATE.cursor;
yy35:
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
	case 'z':	goto yy34;
	default:	goto yy36;
	}
yy36:
	{ SCANNER_STATE.tokentype = NAME; goto end;}
yy37:
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
	case 'z':	goto yy34;
	default:	goto yy38;
	}
yy38:
	{ SCANNER_STATE.tokentype = UNDERSCORE; goto end;}
yy39:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'e':	goto yy56;
	default:	goto yy35;
	}
yy40:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '8':	goto yy57;
	default:	goto yy35;
	}
yy41:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.tokentype = LBRACE; goto end;}
yy43:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.tokentype = RBRACE; goto end;}
yy45:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '"':	goto yy58;
	default:	goto yy45;
	}
yy47:
	++SCANNER_STATE.cursor;
	{ goto comment; }
yy49:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'L':
	case 'U':
	case 'l':
	case 'u':	goto yy49;
	default:	goto yy51;
	}
yy51:
	{ SCANNER_STATE.tokentype=(INT_LITERAL); goto end;}
yy52:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '0':	goto yy60;
	default:	goto yy53;
	}
yy53:
	SCANNER_STATE.cursor = SCANNER_STATE.marker;
	switch (yyaccept) {
	case 0:
		goto yy27;
	case 1:
		goto yy36;
	default:
		goto yy51;
	}
yy54:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.tokentype = CEQ; goto end;}
yy56:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 't':	goto yy61;
	default:	goto yy35;
	}
yy57:
	yyaccept = 1;
	yych = *(SCANNER_STATE.marker = ++SCANNER_STATE.cursor);
	switch (yych) {
	case '|':	goto yy62;
	default:	goto yy35;
	}
yy58:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.tokentype = STRING_LITERAL; goto end;}
yy60:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'X':
	case 'x':	goto yy63;
	default:	goto yy53;
	}
yy61:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'u':	goto yy64;
	default:	goto yy35;
	}
yy62:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'u':	goto yy65;
	default:	goto yy53;
	}
yy63:
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
	case 'f':	goto yy66;
	default:	goto yy53;
	}
yy64:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'r':	goto yy68;
	default:	goto yy35;
	}
yy65:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '1':	goto yy69;
	default:	goto yy53;
	}
yy66:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '0':	goto yy70;
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
	case 'f':	goto yy66;
	case 'L':
	case 'U':
	case 'l':
	case 'u':	goto yy49;
	default:	goto yy51;
	}
yy68:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'n':	goto yy72;
	default:	goto yy35;
	}
yy69:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '6':	goto yy74;
	default:	goto yy53;
	}
yy70:
	yyaccept = 2;
	yych = *(SCANNER_STATE.marker = ++SCANNER_STATE.cursor);
	switch (yych) {
	case '0':	goto yy70;
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
	case 'f':	goto yy66;
	case 'L':
	case 'U':
	case 'l':
	case 'u':	goto yy49;
	case 'X':
	case 'x':	goto yy63;
	default:	goto yy51;
	}
yy72:
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
	case 'z':	goto yy34;
	default:	goto yy73;
	}
yy73:
	{ SCANNER_STATE.tokentype = RETURN; goto end;}
yy74:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '|':	goto yy75;
	default:	goto yy53;
	}
yy75:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'u':	goto yy76;
	default:	goto yy53;
	}
yy76:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '3':	goto yy77;
	default:	goto yy53;
	}
yy77:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '2':	goto yy78;
	default:	goto yy53;
	}
yy78:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '|':	goto yy79;
	default:	goto yy53;
	}
yy79:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'u':	goto yy80;
	default:	goto yy53;
	}
yy80:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '6':	goto yy81;
	default:	goto yy53;
	}
yy81:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '4':	goto yy82;
	default:	goto yy53;
	}
yy82:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '|':	goto yy83;
	default:	goto yy53;
	}
yy83:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'u':	goto yy84;
	default:	goto yy53;
	}
yy84:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '1':	goto yy85;
	default:	goto yy53;
	}
yy85:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '2':	goto yy86;
	default:	goto yy53;
	}
yy86:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '8':	goto yy87;
	default:	goto yy53;
	}
yy87:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '|':	goto yy88;
	default:	goto yy53;
	}
yy88:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'f':	goto yy89;
	default:	goto yy53;
	}
yy89:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '1':	goto yy90;
	default:	goto yy53;
	}
yy90:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '6':	goto yy91;
	default:	goto yy53;
	}
yy91:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '|':	goto yy92;
	default:	goto yy53;
	}
yy92:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'f':	goto yy93;
	default:	goto yy53;
	}
yy93:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '3':	goto yy94;
	default:	goto yy53;
	}
yy94:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '2':	goto yy95;
	default:	goto yy53;
	}
yy95:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '|':	goto yy96;
	default:	goto yy53;
	}
yy96:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'f':	goto yy97;
	default:	goto yy53;
	}
yy97:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '6':	goto yy98;
	default:	goto yy53;
	}
yy98:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '4':	goto yy99;
	default:	goto yy53;
	}
yy99:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '|':	goto yy100;
	default:	goto yy53;
	}
yy100:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'i':	goto yy101;
	default:	goto yy53;
	}
yy101:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '8':	goto yy102;
	default:	goto yy53;
	}
yy102:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '|':	goto yy103;
	default:	goto yy53;
	}
yy103:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'i':	goto yy104;
	default:	goto yy53;
	}
yy104:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '1':	goto yy105;
	default:	goto yy53;
	}
yy105:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '6':	goto yy106;
	default:	goto yy53;
	}
yy106:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '|':	goto yy107;
	default:	goto yy53;
	}
yy107:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'i':	goto yy108;
	default:	goto yy53;
	}
yy108:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '3':	goto yy109;
	default:	goto yy53;
	}
yy109:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '2':	goto yy110;
	default:	goto yy53;
	}
yy110:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '|':	goto yy111;
	default:	goto yy53;
	}
yy111:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'i':	goto yy112;
	default:	goto yy53;
	}
yy112:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '6':	goto yy113;
	default:	goto yy53;
	}
yy113:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '4':	goto yy114;
	default:	goto yy53;
	}
yy114:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '|':	goto yy115;
	default:	goto yy53;
	}
yy115:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case 'i':	goto yy116;
	default:	goto yy53;
	}
yy116:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '1':	goto yy117;
	default:	goto yy53;
	}
yy117:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '2':	goto yy118;
	default:	goto yy53;
	}
yy118:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '8':	goto yy119;
	default:	goto yy53;
	}
yy119:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.tokentype = INT_TYPE; goto end;}
}


comment:
    
{
	char yych;
	yych = *SCANNER_STATE.cursor;
	switch (yych) {
	case '\n':	goto yy125;
	case '*':	goto yy127;
	default:	goto yy123;
	}
yy123:
	++SCANNER_STATE.cursor;
yy124:
	{ goto comment; }
yy125:
	++SCANNER_STATE.cursor;
	{ SCANNER_STATE.line_number++; goto comment; }
yy127:
	yych = *++SCANNER_STATE.cursor;
	switch (yych) {
	case '/':	goto yy128;
	default:	goto yy124;
	}
yy128:
	++SCANNER_STATE.cursor;
	{ goto loop; }
}


end:
    // end inifinite loop when END_TOKEN
    if(END_TOKEN == SCANNER_STATE.tokentype) break;
    
    switch(SCANNER_STATE.tokentype) {
        case SEMICOLON: printf("SEMICOLON"); break;
        case LPAREN: printf("LPAREN"); break;
        case RPAREN: printf("RPAREN"); break;
        case LBRACE: printf("LBRACE"); break;
        case RBRACE: printf("RBRACE"); break;
        case ASSIGN: printf("ASSIGN"); break;
        case CEQ: printf("CEQ"); break;
        case ADD: printf("ADD"); break;
        case SUB: printf("SUB"); break;
        case MUL: printf("MUL"); break;
        case DIV: printf("DIV"); break;
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
          //if we ever come here it means nothing were found but NOT handled. No case for the token in switch case
          bFoundSomething_and_token_handled=false;
          set_token_value("Tokentype");
          printf("%s found but not handled, Line %d at Position %d\n",SCANNER_STATE.tokenvalue, SCANNER_STATE.line_number, SCANNER_STATE.column_position);
          break;
    }
    SCANNER_STATE.column_position=(int)(SCANNER_STATE.begin - SCANNER_STATE.lexeme);
    
    if ( bFoundSomething_and_token_handled == true ) {
      printf(" found on Line %d at Position %d\n", SCANNER_STATE.line_number, SCANNER_STATE.column_position);
    }

    }//end for loop
    if (scanner_DebugMode == true) printf("\n ** THE END ** \n");
}

//Parser START----------------------------------------------------------
//header for functions in parser.c  Make sure parser.c is added at compilation time.

#include <parser_definitions.h>
#include <parser.h> // tokens type definition

bool parser_DebugMode = false;
void* theParser;
struct parser_state PARSER_STATE;

void PARSER_INIT(){
  theParser = ParseAlloc(malloc);
  if (parser_DebugMode == true) ParseTrace(stderr, "[Parser] >> ");
}
void PARSER(int token, const double tokenvalue){
  Parse(theParser, token, tokenvalue, &PARSER_STATE);
}
void PARSER_FREE(){
  ParseFree(theParser, free);
}

//Parser END-----------------------------------------------------------
