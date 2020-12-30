#include <fstream>    
#include <iostream> 

#include "easy/Easy"

static void print_token(Easy_Token* token_p);

int 
main(int argc, char** argv) 
{        
    Easy    qlex(argc == 1 ? "example.txt" : argv[1]);
    Easy_Token*  token_p = 0;
    int           number_of_tokens = 0;

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
print_token(Easy_Token* token_p)
{
    std::cout << "(" << token_p->line_n << ", " << token_p->column_n << ")  \t";

    switch( token_p->id ) {
    case QUEX_TKN_TERMINATION: 
        std::cout << token_p->id_name() << std::endl;
        break;
    default:
        std::cout << std::string(*token_p) << std::endl;
        break;
    }
}
