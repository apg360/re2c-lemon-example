#pragma once

#include <parser.h>  // All tokens type definition, generated by grammar in lemon

#define MACRO_VALUE_AND_NAME(X)  X, #X  // eg : this call MACRO_VALUE_AND_NAME(TK_NEWLINE) will return 5,TK_NEWLINE

struct _scanner_state
{
    const char *cursor;                 // current_char : the next input character to be read.  A pointer-like l-value that stores the current input position
    const char *begin;                  // first_char
    const char *end;                    // last_char, limit, YYLIMIT  : the position after the last available input character.   A pointer-like r-value that stores the end of input position
                                        //                Lexer compares YYCURSOR to YYLIMIT in order to determine if there is enough input characters left
    const char *marker;                 // marker - the position of the most recent match
    const char *lexemes;                // unconsumed part -> the next input remaining to be scanned.
    
    int line_number, column_position;   // line number, column position
    
    int token_id;                       // int value as found in <parser.h>
    const char * token_name;            // string name as found in <parser.h>
    char token_value[255];              // the current assigned value. No more than 255 characters
};

struct _parser_state {
    bool error;
};

