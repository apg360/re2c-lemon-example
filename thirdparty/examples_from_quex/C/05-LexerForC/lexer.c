#include <stdio.h>    
#include "lexical_analysis/LexerForC.h"

static void print_token(LexerForC_Token* token_p);

int 
main(int argc, char** argv) 
{        
    LexerForC         qlex;
    LexerForC_Token*  token_p = NULL;
    int               number_of_tokens = 0;

    LexerForC_from_file_name(&qlex, argc == 1 ? "example.txt" : argv[1], NULL); 

    do {
        qlex.receive(&qlex, &token_p);
        if( ! token_p ) break;

        print_token(token_p);

        ++number_of_tokens;

    } while( token_p->id != QUEX_TKN_TERMINATION );

    printf("[END] number of tokens = %i\n", number_of_tokens);
    if( qlex.error_code != E_Error_None ) qlex.print_this(&qlex); 

    LexerForC_destruct(&qlex);
    return 0;
}

static void
print_token(LexerForC_Token* token_p)
{
    const size_t    BufferSize = 1024;
    char            buffer[1024];
    printf("(%i, %i)  \t", (int)token_p->line_n, (int)token_p->column_n);

    switch( token_p->id ) {
    case QUEX_TKN_TERMINATION: 
        /* In this case, the token still might carry an old lexeme. 
         * Printing it would be confusing.                                    */
        printf("%s\n", LexerForC_map_token_id_to_name(token_p->id));
        break;
    default:
        printf("%s \n", LexerForC_Token_get_string(token_p, buffer, BufferSize));
        break;
    }
}
