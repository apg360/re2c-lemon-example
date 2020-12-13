#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "scanner.h"
//#include "parser.c"

// https://re2c.org/manual/manual_c.html

int main() {
    
    printf("lex '_Zer0' result: %d\n", lex("_Zer0"));
    
    char commandLine[100];
    while ( fgets(commandLine, 100, stdin) ) {
        //
        int tokenID = lex(commandLine);
        // exit when scanner return 0 when get EOF.
        if (-1 == tokenID) {break;}
        // show the token
        printf("GET TOKEN: %d\n", tokenID);

    }

    return 0;
}

