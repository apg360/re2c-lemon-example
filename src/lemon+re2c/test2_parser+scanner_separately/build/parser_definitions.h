//parser definitions.h START -----------------------
#include <stdlib.h>
#include <stdbool.h>

struct parser_state {
    double result;
    bool error;
};

void* ParseAlloc(void* (*allocProc)(size_t));
void ParseFree(void* parser, void(*freeProc)(void*));
void ParseTrace(FILE *TraceFILE, char *str);
void Parse(
    void * parser,                       // The parser
    int token,                           // The major token code number
    double tokenvalue,                   // Value associated with a token %token_type { double }
    struct parser_state * PARSER_STATE   // Optional %extra_argument parameter
);

//parser definitions.h END -----------------------
