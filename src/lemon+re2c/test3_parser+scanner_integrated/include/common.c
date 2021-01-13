
#include "common.h"

void println(const char *str) {
  printf("%s\n",str);
}

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

char* dynamic_fgets (void) //read_stdin
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

// Below function extracts characters present in src
// between m and n (excluding n)
// returns the substring of the source string starting at the position m and ending at position n-1
/*
    char src[] = "substr function Implementation";
    int m = 7;
    int n = 12;
    char* dest = substr(src, m, n);
    printf("%s\n", dest);
*/
/*
char* substr(const char *src, int m, int n)
{
    // get length of the destination string
    int len = n - m;
 
    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
 
    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
 
    // null-terminate the destination string
    *dest = '\0';
 
    // return the destination string
    return dest - len;
}*/
// another implementation that uses C library’s strncpy() function
char* substr(const char *src, int m, int n)
{
    // get length of the destination string
    int len = n - m;
 
    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
 
    // start with m'th char and copy 'len' chars into destination
    strncpy(dest, (src + m), len);
 
    // return the destination string
    return dest;
}

// strtok() function to split a string (and specify the delimiter to use).
// Note that strtok() will modify the string passed into it.
// If the original string is required elsewhere make a copy of it and pass the copy to strtok().
char** str_split(char* a_str, const char a_delim)
{
/*
    char months[] = "JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC";
    char** tokens;
    printf("months=[%s]\n\n", months);
    tokens = str_split(months, ',');
    if (tokens)
    {
        int i;
        for (i = 0; *(tokens + i); i++)
        {
            printf("month=[%s]\n", *(tokens + i));
            free(*(tokens + i));
        }
        printf("\n");
        free(tokens);
    }
*/
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

/*
    char* str = malloc(strlen("abcdef")+1);
    strcpy(str, "abcdbbbef");
    removeChar(str, 'b');
    printf("%s", str);
    free(str);

output
acdef
*/
void removeChar(char *str, char garbage)
{

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

/*
To remove characters from a string, you have to shift the contents of the string to the left (including the null terminator) using memmove

char str[12] = "hello world";
if (removechars(str, 5, 4) == 0)  // remove 4 chars starting at str[5]
    printf("%s\n", str);          // hellold
*/
int removechars(char *str, size_t pos, size_t cnt)
{
    size_t len = strlen(str);
    if (pos + cnt > len)
        return -1;

    memmove(str + pos, str + pos + cnt, len - pos - cnt + 1);
    return 0;
}
