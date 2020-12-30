#include <stdio.h> 

// (*) include lexical analyser header
#include "utf8/UTF8Lex.h"

int 
main(int argc, char** argv) 
{        
    size_t          BufferSize = 1024;
    char            buffer[1024];
    UTF8Lex         qlex;
    UTF8Lex_Token*  token_p = 0x0;
    (void)argc; (void)argv;

    UTF8Lex_from_file_name(&qlex, "example-utf8.txt", NULL);

    // (*) loop until the 'termination' token arrives
    do {
        // (*) get next token from the token stream
        qlex.receive(&qlex, &token_p);

        /* (*) print out token information
         *     'get_string' automagically converts codec bytes into utf8 */
        printf("%s \n", UTF8Lex_Token_get_string(token_p, buffer, BufferSize));

        // (*) check against 'termination'
    } while( token_p->id != TKN_TERMINATION );

    UTF8Lex_destruct(&qlex);
    return 0;
}
