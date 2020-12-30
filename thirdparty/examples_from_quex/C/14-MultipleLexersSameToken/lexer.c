#include<stdio.h> 

#include "moritz/moritz_Lexer.h"
#include "max/max_Lexer.h"
#include "boeck/boeck_Lexer.h"
#include "A_B_C/lib/quex/converter/icu/Converter_ICU"
#include "A_B_C/lib/quex/converter/icu/Converter_ICU.i"
#include "A_B_C/lib/quex/converter/Converter.i"

int 
main(int argc, char** argv) 
{        
    max_Lexer     max_lex;
    moritz_Lexer  moritz_lex;
    boeck_Lexer   boeck_lex;
    Common_Token* max_token    = 0x0;
    Common_Token* moritz_token = 0x0;
    Common_Token* boeck_token  = 0x0;
    const size_t  BufferSize = 1024;
    char          buffer[1024];
    size_t        i = 0;
    (void)argc; (void)argv;

    quex_Converter*  max_converter    = quex_Converter_ICU_new(sizeof(max_Lexer_lexatom_t)<<3, "UCS4", NULL);
    quex_Converter*  moritz_converter = quex_Converter_ICU_new(sizeof(moritz_Lexer_lexatom_t)<<3, "UCS4", NULL);
    quex_Converter*  boeck_converter  = quex_Converter_ICU_new(sizeof(boeck_Lexer_lexatom_t)<<3, "UCS4", NULL);

    max_Lexer_from_file_name(&max_lex,       "ucs4.txt", max_converter);
    moritz_Lexer_from_file_name(&moritz_lex, "ucs4.txt", moritz_converter);
    boeck_Lexer_from_file_name(&boeck_lex,   "ucs4.txt", boeck_converter);

    printf("                Max:        Moritz:      Boeck:\n");

    do {
        max_lex.receive(&max_lex, &max_token);
        moritz_lex.receive(&moritz_lex, &moritz_token);
        boeck_lex.receive(&boeck_lex, &boeck_token);

        /* Lexeme is same for all three.                                      */
        (void)Global_lexeme_to_pretty_char(boeck_token->text, buffer, &buffer[BufferSize]);

        printf("%s", &buffer[0]);

        size_t      preL   = (size_t)strlen((const char*)boeck_token->text);
        size_t      L      = preL < 10 ? preL : 10;
        for(i=0; i < 10 - L ; ++i) printf(" ");
        printf("\t");
        printf("%s   %s   %s\n", 
               max_Lexer_map_token_id_to_name(max_token->id),
               moritz_Lexer_map_token_id_to_name(moritz_token->id),
               boeck_Lexer_map_token_id_to_name(boeck_token->id));

    } while( boeck_token->id != TKN_TERMINATION );

    boeck_Lexer_destruct(&boeck_lex);
    max_Lexer_destruct(&max_lex);
    moritz_Lexer_destruct(&moritz_lex);

    return 0;
}

