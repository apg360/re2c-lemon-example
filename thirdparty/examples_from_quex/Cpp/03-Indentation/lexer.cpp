#include<fstream>    
#include<iostream> 

#ifndef LEXER2
#   include "Easy/Easy"
typedef Easy       Lexer;
typedef Easy_Token Token;
#else
#   include "Easy2/Easy2"
typedef Easy2        Lexer;
typedef Easy2_Token  Token;
#endif

static void print_token(Token* token_p);

int 
main(int argc, char** argv) 
{        
    Lexer   qlex(argc == 1 ? "example.txt" : argv[1]);
    Token*  token_p = 0;

    int number_of_tokens = 0;
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
print_token(Token* token_p)
{
    std::cout << "(" << token_p->line_n << ", " << token_p->column_n << ")  \t";

    switch( token_p->id ) {
    case QUEX_TKN_INDENT:
    case QUEX_TKN_DEDENT:
    case QUEX_TKN_NODENT:
    case QUEX_TKN_BRACKET_O:
    case QUEX_TKN_BRACKET_C:
    case QUEX_TKN_CURLY_BRACKET_O:
    case QUEX_TKN_CURLY_BRACKET_C:
    case QUEX_TKN_OP_EQUAL:
    case QUEX_TKN_IF:
    case QUEX_TKN_ELSE:
    case QUEX_TKN_AND:
    case QUEX_TKN_OR:
    case QUEX_TKN_COLON:
    case QUEX_TKN_FOR:
    case QUEX_TKN_IN:
    case QUEX_TKN_INDENTATION:
    case QUEX_TKN_STRUCT:
    case QUEX_TKN_SEMICOLON:
    case QUEX_TKN_ERROR_MISALIGNED_INDENTATION:
    case QUEX_TKN_DOTS:
    case QUEX_TKN_FAILURE:
    case QUEX_TKN_TERMINATION: 
        std::cout << token_p->id_name() << std::endl;
        break;
    case QUEX_TKN_NUMBER: 
        std::cout << token_p->id_name() << ": " << token_p->number << std::endl;
        break;
    default:
        std::cout << std::string(*token_p) << std::endl;
        break;
    }
}
