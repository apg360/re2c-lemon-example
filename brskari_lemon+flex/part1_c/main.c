#include <stdlib.h>
#include <stdio.h>
#include "shellparser.h"
 
void* ParseAlloc(void* (*allocProc)(size_t));
void Parse(void* parser, int token, const char*);
void ParseFree(void* parser, void(*freeProc)(void*));
 
int main()
{
    void* shellParser = ParseAlloc(malloc);
    // Simulate a command line such as "cat main.cpp | wc"
    Parse(shellParser, FILENAME, "cat");
    Parse(shellParser, ARGUMENT, "main.c");
    Parse(shellParser, PIPE, 0);
    Parse(shellParser, FILENAME, "wc");
    Parse(shellParser, PIPE, 0); //error  cat main.cpp | | wc
    Parse(shellParser, 0, 0); // Signal end of tokens
    ParseFree(shellParser, free);
    return 0;
}
