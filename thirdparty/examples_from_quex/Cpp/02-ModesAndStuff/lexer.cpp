#include <fstream>    
#include <iostream> 

#include "easy/Easy"

static void print_token(Easy_Token* token_p);

int 
main(int argc, char** argv) 
{        
    Easy         qlex(argc == 1 ? "example.txt" : argv[1]);
    Easy_Token*  token_p = 0;
    int          number_of_tokens = 0;

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
    case QUEX_TKN_BRACKET_O:
    case QUEX_TKN_BRACKET_C:
    case QUEX_TKN_CURLY_BRACKET_O:
    case QUEX_TKN_CURLY_BRACKET_C:
    case QUEX_TKN_OP_ASSIGNMENT:
    case QUEX_TKN_IF:
    case QUEX_TKN_STRUCT:
    case QUEX_TKN_SEMICOLON:
    case QUEX_TKN_QUOTE:
    case QUEX_TKN_TERMINATION: 
        /* In this case, the token still might carry an old lexeme. 
         * Printing it would be confusing.                                    */
        std::cout << token_p->id_name() << std::endl;
        break;
    case QUEX_TKN_NUMBER: 
        /* In this case, the token still might carry an old lexeme. 
         * Printing it would be confusing.                                    */
        std::cout << token_p->id_name() << ": " << token_p->number << std::endl;
        break;
    default:
        std::cout << std::string(*token_p) << std::endl;
        break;
    }
}
