#pragma once

#include <parser.h>  // All tokens type definition, generated by grammar in lemon

#define MACRO_VALUE_AND_NAME(X)  X, #X  // eg : this call MACRO_VALUE_AND_NAME(TK_NEWLINE) will return 5,TK_NEWLINE

//https://zestedesavoir.com/tutoriels/755/le-langage-c-1/notions-avancees/les-unions
// https://data-flair.training/blogs/union-in-c-language
// union means only one member can be accessed at a time in a union.
// Only one data member of a union can be accessed at one time.
// Not a struct with many members but a struct with one single member, that can be one of those.
// A union prohibits the initialization of all its data members. The first member of the union can only be initialized through an object.
// ll the data members of a union share the same memory location. Hence, changes made in one data member inevitably affects the other.
union _Tokenvalue {
    double   value_is_a_number;
    char     value_is_a_string[255]; // the current assigned value. No more than 255 characters
};

struct _Token {
    int  type;                  // int value as found in <parser.h>
    const char * type_name;     // string name as found in <parser.h>
    union
    {
        double   value_is_a_number;
        char     value_is_a_string[255]; // the current assigned value. No more than 255 characters
    };
};

struct _scanner_state
{
    const char *cursor;                 // current_char : the next input character to be read.  A pointer-like l-value that stores the current input position
    const char *begin;                  // first_char
    const char *end;                    // last_char, limit, YYLIMIT  : the position after the last available input character.   A pointer-like r-value that stores the end of input position
                                        //                Lexer compares YYCURSOR to YYLIMIT in order to determine if there is enough input characters left
    const char *marker;                 // marker - the position of the most recent match
    const char *lexeme;                 // the next input remaining to be scanned.

    int line_number, column_position;   // line number, column position
    
    struct _Token Token;                // token code, token type and token value

};

struct _parser_state {
    union _Tokenvalue result_value;
    bool error;
};
