#include <iostream> 

#include "lexical_analysis/LexerForC"

static void print_token(LexerForC_Token* token_p);

int 
main(int argc, char** argv) 
{        
    LexerForC qlex(argc == 1 ? "example.txt" : argv[1]);
    LexerForC_Token*    token_p = 0;
    int             number_of_tokens = 0;

    do {
        qlex.receive(&token_p);
        if( ! token_p ) break;

        print_token(token_p);

        ++number_of_tokens;

    } while( token_p->id != QUEX_TKN_TERMINATION );

    std::cout << "[END] number of tokens = " << number_of_tokens << std::endl;
    if( qlex.error_code != E_Error_None ) qlex.print_this(); 

    return 0;
}

static void
print_token(LexerForC_Token* token_p)
{
    std::cout << "(" << token_p->line_n << ", " << token_p->column_n << ")  \t";

    switch( token_p->id ) {
    case QUEX_TKN_TERMINATION: 
        /* In this case, the token still might carry an old lexeme. 
         * Printing it would be confusing.                                    */
        std::cout << token_p->id_name() << std::endl;
        break;
    default:
        std::cout << std::string(*token_p) << std::endl;
        break;
    }
}
