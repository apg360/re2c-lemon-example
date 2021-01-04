#pragma once

#include <assert.h>
#include <stdio.h>   // output on screen
#include <stdlib.h>  // os access: open file, read/write file, delete file etc...
#include <stddef.h>  // size_t
#include <string.h>  // strlen
#include <stdbool.h> // bool

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
