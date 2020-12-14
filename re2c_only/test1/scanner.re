// re2c $INPUT -o $OUTPUT -i
// french : https://fr.qaz.wiki/wiki/Re2c
// english : https://wikivisually.com/wiki/re2c
// https://www.systutorials.com/docs/linux/man/1-re2c
// https://re2c.org/manual/manual_c.html

static int lex(const char *str, unsigned int len) // const char *YYCURSOR) 
{
    const char *YYCURSOR = str;                  // current_char : the next input character to be read. 					A pointer-like l-value that stores the current input position
    const char *YYLIMIT = str + len;             // last_char    : the position after the last available input character. 	A pointer-like r-value that stores the end of input position
                                                                                                                            // Lexer compares YYCURSOR to YYLIMIT in order to determine if there is enough input characters left
    const char *YYMARKER;                        // marker_char  : the position of the most recent match
    int wordCount = 0;                           // count word, not letters
    
loop:
    /*!re2c                                      // start of re2c block
    re2c:eof = 0; 								 // zero byte \x00 
                                                 // Specifies the sentinel symbol used with EOF rule $ to check for the end of input in the generated lexer. 
                                                 // The default value is -1 (EOF rule is not used).
                                                 // Other possible values include all valid code units. Only decimal numbers are recognized.
    
    re2c:define:YYCTYPE = char;                  // The type of the input characters (code units). For ASCII, EBCDIC and UTF-8 encodings it should be 1-byte unsigned integer.
    re2c:yyfill:enable = 0;                      // configuration
    re2c:flags:case-ranges = 1;                  // configuration
    
    wsp = [ \t\r\n];                             // whitespace
    
    *               { return -1; }    			 // default rule
    $               { return wordCount; }        // whenever EOF
    
    // normal rule
    wsp             { goto loop;}                      // ignore any whitespace that shows up at the end //[^ \t\r\n]+
    [a-z]+          { ++wordCount; goto loop; }        //only letters are counted
    [ ]+            { goto loop; }                     // everything else ignored
    */
}
