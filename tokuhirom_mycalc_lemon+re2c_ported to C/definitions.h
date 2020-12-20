#pragma once

typedef enum { FAIL, OK } Result;

typedef union {
    int int_value;
} YYSTYPE;

struct ParserState {
    int result;
    ParserState() :result(0) {}
};

/*!re2c
    INTEGER                = [1-9][0-9]*;
    WS                     = [ \r\n\t\f];
    ANY_CHARACTER          = [^];
*/
