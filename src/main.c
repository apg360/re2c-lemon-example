#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "scanner.re2c.h"


void* ParseAlloc(void* (*allocProc)(size_t));
void ParseFree(void* parser, void(*freeProc)(void*));
void Parse(void* parser, int token, const char*); //, bool* valid); //parser.lem added extra_argument bool valid

int main()
{
    void* shellParser = ParseAlloc(malloc);
    // Simulate a command line such as "cat main.cpp | wc"
    Parse(shellParser, FILENAME, "cat");
    Parse(shellParser, ARGUMENT, "main.c");
    Parse(shellParser, PIPE, 0);
    Parse(shellParser, FILENAME, "wc");
    Parse(shellParser, PIPE, 0); // error cat main.cpp | | wc
    Parse(shellParser, 0, 0); // Signal end of tokens
    ParseFree(shellParser, free);
    
    //assert(lex("_Zer0") == 0);
    return 0;
}
