
#include "moritz/moritz.h"
#include "max/max.h"
#include "boeck/lib/quex/converter/iconv/Converter_IConv"
#include "boeck/lib/quex/converter/iconv/Converter_IConv.i"
#include "boeck/boeck.h"

#include <stdio.h> 

int 
main(int argc, char** argv) 
{        
    /* We want to have error outputs in stdout, so that the unit test could 
     * see it.                                                               */
    max           max_lex;
    max_Token*    max_token    = 0x0;
    moritz        moritz_lex;
    moritz_Token* moritz_token = 0x0;
    boeck         boeck_lex;
    boeck_Token*  boeck_token  = 0x0;
    size_t        i, preL, L;
    (void)argc; (void)argv;

    quex_Converter*  converter_utf16 = quex_Converter_IConv_new(sizeof(max_lexatom_t)<<3, "UTF16", NULL);
    quex_Converter*  converter_ucs2  = quex_Converter_IConv_new(sizeof(moritz_lexatom_t)<<3, "UCS-2", NULL);

    max_from_file_name(&max_lex,       "example-utf16.txt", converter_utf16);
    moritz_from_file_name(&moritz_lex, "example-ucs2.txt",  converter_ucs2);
    boeck_from_file_name(&boeck_lex,   "example-utf8.txt",  NULL);

    /* Different lexers produce different interpretations on same lexeme.     */
    printf("                Max:        Moritz:      Boeck:\n");

    do {
        max_lex.receive(&max_lex, &max_token);
        moritz_lex.receive(&moritz_lex, &moritz_token);
        boeck_lex.receive(&boeck_lex, &boeck_token);

        /* Lexeme is same for all three. */
        preL   = (size_t)strlen((const char*)boeck_token->text);
        L      = preL < 10 ? preL : 10;
        printf("%s", boeck_token->text);

        for(i=0; i < 10 - L ; ++i) printf(" ");

        printf("\t");
        printf("%s   %s   %s\n", 
               max_map_token_id_to_name(max_token->id),
               moritz_map_token_id_to_name(moritz_token->id),
               boeck_map_token_id_to_name(boeck_token->id));

    } while( boeck_token->id != TKN_TERMINATION );

    boeck_destruct(&boeck_lex);
    max_destruct(&max_lex);
    moritz_destruct(&moritz_lex);

    return 0;
}

