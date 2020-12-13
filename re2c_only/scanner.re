// re2c $INPUT -o $OUTPUT -i

int lex(const char *YYCURSOR)
{
    int wordCount = 0; // count word, not letters
    
loop:
    /*!re2c                         // start of re2c block
    re2c:define:YYCTYPE = char;     // configuration
    re2c:yyfill:enable = 0;         // configuration
    re2c:flags:case-ranges = 1;     // configuration

    *      { return -1; }           // default rule
    // normal rule
    [\x00] { return wordCount; } // whenever we find zero
    [a-z]+ { ++wordCount; goto loop; } //only letters are counted
    [ ]+   { goto loop; } // everything else ignored
    
    */
    
    /*ident = [a-zA-Z_][a-zA-Z_0-9]*; // named definition
    ident { return 0; }*/
    //assert(lex("") == 0);
    //assert(lex("one two three") == 3);
    //assert(lex("f0ur") == -1);
}
