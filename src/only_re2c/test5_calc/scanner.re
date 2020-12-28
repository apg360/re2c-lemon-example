// re2c $INPUT -o $OUTPUT -i
// french : https://fr.qaz.wiki/wiki/Re2c
// english : https://wikivisually.com/wiki/re2c
// https://www.systutorials.com/docs/linux/man/1-re2c
// https://re2c.org/manual/manual_c.html

/*!include:re2c "definitions.h" */

void show(const char *str) {
  printf("> %s\n",str);
}

static int SCANNER(const char *str) // const char *YYCURSOR) 
{
    unsigned int lensize = strlen(str);
    const char *YYCURSOR = str;                  // current_char : the next input character to be read.                     A pointer-like l-value that stores the current input position
    const char *YYLIMIT = str + lensize;             // last_char    : the position after the last available input character.   A pointer-like r-value that stores the end of input position
                                                                                                                            // Lexer compares YYCURSOR to YYLIMIT in order to determine if there is enough input characters left
    const char *YYMARKER;                        // marker_char  : the position of the most recent match
    int wordCount = 0;                           // count word, not letters
    
    printf("Scanning : '%s'\n",str);
    printf("> Number of characters %u\n",lensize);
    
    const char *lexeme;
loop:
    lexeme = YYCURSOR;
    /*!re2c                                      // start of re2c block
    re2c:eof = 0;                                // zero byte \x00
                                                 // Specifies the sentinel symbol used with EOF rule $ to check for the end of input in the generated lexer. 
                                                 // The default value is -1 (EOF rule is not used).
                                                 // Other possible values include all valid code units. Only decimal numbers are recognized.
    
    re2c:define:YYCTYPE = char;                  // The type of the input characters (code units). For ASCII, EBCDIC and UTF-8 encodings it should be 1-byte unsigned integer.
    re2c:yyfill:enable = 0;                      // configuration
    
    *               { show("Failed"); return FAIL; }
    $               { printf("> Number of words = %d\n",wordCount);
                      return OK;}                // whenever EOF stop scanning
    wsp             { goto loop;}                // ignore any whitespace that shows up at the end
    
    "+" { show("TOKEN_PLUS");     goto loop; }
    "-" { show("TOKEN_MINUS");    goto loop; }
    "*" { show("TOKEN_TIMES");    goto loop; }
    "/" { show("TOKEN_DIVIDE");   goto loop; }
    "^" { show("TOKEN_EXPONENT"); goto loop; }
    "(" { show("TOKEN_LPAREN");   goto loop; }
    ")" { show("TOKEN_RPAREN");   goto loop; }
    
    number
    {
        //token->num = atof(str);
        //printf("> %f \n",atof(str));
        show(lexeme);
        goto loop;
    }
    
    letter          { ++wordCount; goto loop; }        //only letters are counted
    [ ]+            { goto loop; }                     // everything else ignored
    */
}
