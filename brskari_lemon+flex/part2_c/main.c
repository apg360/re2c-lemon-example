#include <stdlib.h>
#include <stdio.h>
#include "shellparser.h"
#include "shellscanner.yy.h"
#include <stdbool.h>
 
void* ParseAlloc(void* (*allocProc)(size_t));
void Parse(void* parser, int token, const char*, bool* valid);
void ParseFree(void* parser, void(*freeProc)(void*));

void parse(const char* commandLine) {
    // Set up the scanner
    yyscan_t scanner;
    yylex_init(&scanner);
    YY_BUFFER_STATE bufferState = yy_scan_string(commandLine, scanner);
 
    // Set up the parser
    void* shellParser = ParseAlloc(malloc);
 
    bool validParse = true;
    int lexCode;
    do {
        lexCode = yylex(scanner);
        Parse(shellParser, lexCode, NULL, &validParse);
    }
    while (lexCode > 0 && validParse);
 
    if (-1 == lexCode) {
        printf("The scanner encountered an error.\n");
    }
 
    if (!validParse) {
        printf("The parser encountered an error.\n");
    }
 
    // Cleanup the scanner and parser
    yy_delete_buffer(bufferState, scanner);
    yylex_destroy(scanner);
    ParseFree(shellParser, free);
}
 
int main()
{
    char commandLine[100];
    while ( fgets(commandLine, 100, stdin) ) {
        parse(commandLine);
    }
    return 0;
}
