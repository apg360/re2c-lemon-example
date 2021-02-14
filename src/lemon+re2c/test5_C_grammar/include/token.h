#pragma once

#include <parser.h>  // All tokens type definition, generated by grammar in lemon

#define MACRO_VALUE_AND_NAME(X)  X, #X  // eg : this call MACRO_VALUE_AND_NAME(TK_NEWLINE) will return 5,TK_NEWLINE

struct _scanner_state
{
    /*
    Example : 50+125
    STEP1: lexemes : 50+125, cursor : +125
    STEP2: lexemes : +125, cursor : 125
    STEP3: lexemes : 125, cursor :
    STEP4: lexemes : , cursor :
    */
    const char *linetext;               // The full string of current line being scanned
    const char *lexemes;                // unconsumed part -> the next input remaining to be scanned.
    const char *cursor;                 // the next input character to be read.  A pointer-like l-value that stores the current input position
    const char *marker;                 // marker - the position of the most recent match
    const char *end;                    // last_char, limit, YYLIMIT  : the position after the last available input character.   A pointer-like r-value that stores the end of input position
                                        //                Lexer compares YYCURSOR to YYLIMIT in order to determine if there is enough input characters left
    
    int line_number, column_position;   // line number, column position
    
    int token_id, token_text_len;       // int value of the token as found in <parser.h>
    const char *token_name;             // string name of the token as found in <parser.h>
    char token_stringvalue[255];        // the text value of the token. No more than 255 characters
};

struct _parser_state {
    bool error;
};

