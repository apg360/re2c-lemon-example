// re2c $INPUT -o $OUTPUT -i
// french : https://fr.qaz.wiki/wiki/Re2c
// english : https://wikivisually.com/wiki/re2c
// https://www.systutorials.com/docs/linux/man/1-re2c

int lex(const char *YYCURSOR)
{
    int wordCount = 0; // count word, not letters
loop:
    /*!re2c                                      // start of re2c block
    re2c:define:YYCTYPE = char;                  // configuration
    re2c:yyfill:enable = 0;                      // configuration
    re2c:flags:case-ranges = 1;                  // configuration
    //re2c:define:YYLIMIT = last_char;
    //re2c:define:YYCURSOR = current_char;
    
    end = "\x00";    // end of line
    wsp = [ \t\r\n]; // whitespace
    
    *               { printf("err\n"); return -1; }  // default rule
    wsp             { goto loop;}                    // ignore any whitespace that shows up at the end //[^ \t\r\n]+
    end             { return wordCount; }            // whenever EOF
    // normal rule
    "reset"         { printf("Reset ....");wordCount=0;return 0; } // reset counter
    ","             { return(","); }
    [a-z]+          { ++wordCount; goto loop; }  //only letters are counted
    [ ]+            { goto loop; }               // everything else ignored
    */
    
    /*ident = [a-zA-Z_][a-zA-Z_0-9]*; // named definition
    ident { return 0; }*/
    //assert(lex("") == 0);
    //assert(lex("one two three") == 3);
    //assert(lex("f0ur") == -1);
}
