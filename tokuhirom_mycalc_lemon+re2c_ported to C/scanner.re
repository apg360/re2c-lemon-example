// re2c $INPUT -o $OUTPUT -i
// french : https://fr.qaz.wiki/wiki/Re2c
// english : https://wikivisually.com/wiki/re2c
// https://www.systutorials.com/docs/linux/man/1-re2c
// https://re2c.org/manual/manual_c.html

/*!include:re2c "definitions.h" */

 // current position
 char* m_cursor;     // current_char : the next input character to be read.                     A pointer-like l-value that stores the current input position
 char* m_limit;      // last_char    : the position after the last available input character.   A pointer-like r-value that stores the end of input position
                     //                Lexer compares YYCURSOR to YYLIMIT in order to determine if there is enough input characters left
 char* m_token;      // token_char   : 
 char* m_marker;     // marker_char  : the position of the most recent match
 int m_lineno;

void increment_line_number() {
    m_lineno++;
}
int length() {
    return (m_cursor-m_token);
}
char* text() {
    return m_token; //std::string( m_token, m_token+length() );
}
int lineno() {
    return m_lineno;
}

static int SCANNER(char *str, unsigned int len) // const char *YYCURSOR) 
{
    m_cursor = str;
    m_limit = str + len;
    int wordCount = 0;                           // count word, not letters
    
loop:
    m_token = m_cursor;
    
    /*!re2c                                      // start of re2c block
    re2c:eof = 0;                                // zero byte \x00
                                                 // Specifies the sentinel symbol used with EOF rule $ to check for the end of input in the generated lexer. 
                                                 // The default value is -1 (EOF rule is not used).
                                                 // Other possible values include all valid code units. Only decimal numbers are recognized.
    
    re2c:define:YYCTYPE = char;                  // The type of the input characters (code units). For ASCII, EBCDIC and UTF-8 encodings it should be 1-byte unsigned integer.
    re2c:define:YYCURSOR = m_cursor;
    re2c:define:YYMARKER = m_marker;
    re2c:define:YYLIMIT = m_limit;
    re2c:yyfill:enable = 0;                      // configuration
    re2c:indent:top = 2;
    re2c:indent:string="    ";
    re2c:flags:case-ranges = 1;                  // configuration
    
    *               { return -1; }               // default rule
    $               { return wordCount; }        // whenever EOF
    
    // normal rule
    INTEGER {
        yylval.int_value = atoi(m_token);
        return TOKEN_INT;
    }
    "+" { return TOKEN_ADD; }
    "-" { return TOKEN_SUB; }
    "*" { return TOKEN_MUL; }
    "/" { return TOKEN_DIV; }
    WS  { goto loop; }
    ANY_CHARACTER {
        printf("unexpected character: '%c(%d)'\n", *m_token, *m_token);
        goto loop;
    }
    */
}
