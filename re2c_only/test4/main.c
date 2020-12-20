#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "scanner.h"
//#include "parser.c"

int main()
{
    const char *fname = "input";
    const char str[] = "'qu\0tes' 'are' 'fine: \\'' ";
    FILE *f;
    Input in;

    // prepare input file: a few times the size of the buffer,
    // containing strings with zeroes and escaped quotes
    //f = fopen(fname, "w");
    //for (int i = 0; i < SIZE; ++i) {
    //    fwrite(str, 1, sizeof(str) - 1, f);
    //}
    //fclose(f);

    f = fopen(fname, "r");
    init(&in, f);
    printf( "The size is %d \n", lex(&in) );
    assert(lex(&in) == SIZE * 3);
    fclose(f);

    //remove(fname);
    
    //printf("'_Zer0' result: %d\n", lex("_Zer0"));
    return 0;
}
