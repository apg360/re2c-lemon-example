#include <assert.h>
#include <stdio.h>  // output on screen
#include <stdlib.h> // os access: open file, read/write file, delete file etc...
#include <stddef.h> // size_t
#include <string.h> // strlen
#include "scanner.h"
//#include "parser.c"

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

static char* dynamic_fgets (void) //read_stdin
{
  size_t cap = 4096, /* Initial capacity for the char buffer */
         len =    0; /* Current offset of the buffer */
  char *buffer = malloc(cap * sizeof (char));
  int c;
  
  if (NULL == buffer) { printf("ERR_OUT_OF_MEMORY") ; exit(0); }

  /* Read char by char, breaking if we reach EOF or a newline */
  while ((c = fgetc(stdin)) != '\n' && !feof(stdin))
    {
      buffer[len] = c;

      /* When cap == len, we need to resize the buffer
       * so that we don't overwrite any bytes
       */
      if (++len == cap)
        /* Make the output buffer twice its current size */
        buffer = realloc(buffer, (cap *= 2) * sizeof (char));
        if (NULL == buffer) { printf("ERR_OUT_OF_MEMORY") ; exit(0); }
    }

  /* Trim off any unused bytes from the buffer */
  buffer = realloc(buffer, (len + 1) * sizeof (char));
  if (NULL == buffer) { printf("ERR_OUT_OF_MEMORY") ; exit(0); }
  
  /* Pad the last byte so we don't overread the buffer in the future */
  buffer[len] = '\0';

  return buffer;
}

#define TEST(s) printf("'%s' => result= %d\n",s,lex(s, sizeof(s) - 1) )
int main() {
    
    TEST("_Zer0");
    TEST("");
    TEST("one");
    TEST("one two");
    TEST("one two three");
    TEST("one two three four");
    
    char *commandLine;
    while (  commandLine=dynamic_fgets() ) {     
      size_t size = strlen(commandLine);
      printf(">Number characters %d \n",size);
      printf(">Number words %d \n", lex(commandLine, size)  );
      
      free(commandLine); //free the memory allocated with malloc
    }

    //for (int j=0; j<=size; j++) printf("'%s'\n", &commandLine[j++] ); // remove carriage return and newline
    
    // char wordsProper[100]; //commandLine without carriage return and 0 at end
    // for (char *p=commandLine,j=0; *p; p++) if (*p != '\r' && *p != '\x00' && *p != '\n') wordsProper[j++]=*p; // remove carriage return and newline
    // char* rtr = realloc(rtr, strlen(commandLine)+strlen(rtr));
    
    /*
    char commandLine[100];
    while ( fgets(commandLine, 100, stdin) ) {
        //printf("Result> '%s' = %d \n", commandLine, lex(commandLine, strlen(commandLine) -1)  );
        free(commandLine);
    }
    */

    return 0;
}

