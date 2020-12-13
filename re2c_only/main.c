#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "scanner.h"
//#include "parser.c"

// https://re2c.org/manual/manual_c.html

int main() {
    
    printf("lex '_Zer0' result: %d\n", lex("_Zer0"));
    printf("lex 'one two three' result: %d\n", lex("one two three"));
    printf("lex '' result: %d\n", lex(""));
    printf("lex 'one two three four' result: %d\n", lex("one two three four"));
    
    char commandLine[100];
    while ( fgets(commandLine, 100, stdin) ) {
        // remove carriage return and newline
        //char newL[100];
        //for (char *p=commandLine,j=0; *p; p++) if (*p != '\r' && *p != '\0' && *p != '\n') newL[j++]=*p;
        
        printf("Result > %d \n", lex(commandLine)  );
        //
        //int tokenID = lex(commandLine);
        // exit when scanner return 0 when get EOF.
        //if (-1 == tokenID) {break;}
        // show the token
        //printf("GET TOKEN: %d\n", tokenID);

    }

    return 0;
}

