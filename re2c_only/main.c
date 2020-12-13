#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "scanner.h"
//#include "parser.c"

// https://re2c.org/manual/manual_c.html

/*
 https://stackoverflow.com/questions/2667648/what-does-it-mean-to-be-terminated-by-a-zero

  What does it mean to be “terminated by a zero”?
 
  Take the string Hi in ASCII. Its simplest representation in memory is two bytes:
  0x48
  0x69
  But where does that piece of memory end? 

  Unless you're also prepared to pass around the number of bytes in the string,
  you don't know - pieces of memory don't intrinsically have a length.

  So C has a standard that strings end with a zero byte, also known as a NUL character:
  0x48
  0x69
  0x00

  The string is now unambiguously two characters long, because there are two characters before the NUL.
*/
int main() {
    
    printf("'_Zer0' result: %d\n", lex("_Zer0"));
    printf("'one two three' result: %d\n", lex("one two three"));
    printf(" '' result: %d\n", lex(""));
    printf(" 'one two three four' result: %d\n", lex("one two three four"));
    
    char commandLine[100];
    while ( fgets(commandLine, 100, stdin) ) {
        //commandLine without carriage return and 0 at end
        char wordsProper[100];
        // remove carriage return and newline
        for (char *p=commandLine,j=0; *p; p++) if (*p != '\r' && *p != '\x00' && *p != '\n') wordsProper[j++]=*p;
        
        printf("Result> %d \n", lex(wordsProper)  );
        //
        //int tokenID = lex(commandLine);
        // exit when scanner return 0 when get EOF.
        //if (-1 == tokenID) {break;}
        // show the token
        //printf("GET TOKEN: %d\n", tokenID);

    }

    return 0;
}

