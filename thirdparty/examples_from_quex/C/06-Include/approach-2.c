#include "approach-2/Easy.h"
#include "approach-2/Easy-token_ids.h"
#include <stdio.h>

static void  space(size_t N);
static void  print_token(Easy* qlex, Easy_Token* token_p); 

int 
main(int argc, char** argv) 
{        
    Easy        qlex;
    Easy_Token* token_p = NULL;
    int         number_of_tokens = 0;

    Easy_from_file_name(&qlex, argc == 1 ? "example-shallow.txt" : argv[1], NULL); 

    do {
        qlex.receive(&qlex, &token_p);
        if( ! token_p ) break;

        print_token(&qlex, token_p);

        ++number_of_tokens;

    } while( token_p->id != QUEX_TKN_TERMINATION );

    printf("[END] number of tokens = %i\n", number_of_tokens);
    if( qlex.error_code != E_Error_None ) qlex.print_this(&qlex); 

    Easy_destruct(&qlex);
    return 0;
}

static void  
space(size_t N)
{ size_t i = 0; for(i=0; i<N; ++i) printf("    "); }

static void  
print_token(Easy* qlex, Easy_Token* token_p)
{ 
    const size_t    BufferSize = 1024;
    char            buffer[1024];
    space(qlex->include_depth);
    printf("(%02i, %02i) ", (int)token_p->line_n, (int)token_p->column_n);

    switch( token_p->id ) {
    case QUEX_TKN_TERMINATION: 
        /* In this case, the token still might carry an old lexeme. 
         * Printing it would be confusing.                                    */
        printf("%s\n", Easy_map_token_id_to_name(token_p->id));
        break;
    case QUEX_TKN_NUMBER: 
        /* In this case, the token still might carry an old lexeme. 
         * Printing it would be confusing.                                    */
        printf("%s: %i\n", Easy_map_token_id_to_name(token_p->id), (int)token_p->number);
        break;
    default:
        printf("%s \n", Easy_Token_get_string(token_p, buffer, BufferSize));
        break;
    }
}

void 
my_print(Easy* qlex, const char* Str1, 
         const char* Str2 /* = 0x0 */, const char* Str3 /* = 0x0*/)
{
    space(qlex->include_depth);
    if( Str1 ) printf("%s", Str1);
    if( Str2 ) printf("%s", Str2);
    if( Str3 ) printf("%s", Str3);
    printf("\n");
}
