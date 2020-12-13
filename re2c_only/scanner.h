/* Generated by re2c 2.0.3 on Sun Dec 13 18:43:00 2020 */
// re2c $INPUT -o $OUTPUT -i
// https://www.systutorials.com/docs/linux/man/1-re2c

int lex(const char *YYCURSOR)
{
    int wordCount = 0; // count word, not letters
loop:
    
{
	char yych;
	yych = *YYCURSOR;
	switch (yych) {
	case 0x00: goto yy2;
	case '\t' ... '\n':
	case '\r': goto yy6;
	case ' ': goto yy8;
	case 'a' ... 'z': goto yy9;
	default: goto yy4;
	}
yy2:
	++YYCURSOR;
	{ return wordCount; }
yy4:
	++YYCURSOR;
	{ printf("err\n"); return -1; }
yy6:
	++YYCURSOR;
yy7:
	{ goto loop;}
yy8:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ': goto yy12;
	default: goto yy7;
	}
yy9:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'a' ... 'z': goto yy9;
	default: goto yy11;
	}
yy11:
	{ ++wordCount; goto loop; }
yy12:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ': goto yy12;
	default: goto yy14;
	}
yy14:
	{ goto loop; }
}

    
    /*ident = [a-zA-Z_][a-zA-Z_0-9]*; // named definition
    ident { return 0; }*/
    //assert(lex("") == 0);
    //assert(lex("one two three") == 3);
    //assert(lex("f0ur") == -1);
}
