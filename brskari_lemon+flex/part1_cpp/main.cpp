#include <cstdlib>
#include <iostream>
#include "shellparser.hpp"
using namespace std;
 
void* ParseAlloc(void* (*allocProc)(size_t));
void Parse(void*, int, const char*);
void ParseFree(void*, void(*freeProc)(void*));
 
int main()
{
    void* shellParser = ParseAlloc(malloc);
    // Simulate a command line such as "cat main.cpp | wc"
    Parse(shellParser, FILENAME, "cat");
    Parse(shellParser, ARGUMENT, "main.cpp");
    Parse(shellParser, PIPE, 0);
    //Parse(shellParser, PIPE, 0); // cat main.cpp | | wc
    Parse(shellParser, FILENAME, "wc");
    Parse(shellParser, 0, 0); // Signal end of tokens
    ParseFree(shellParser, free);
    return 0;
}
