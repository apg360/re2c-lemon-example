#include<cstdio> 

#include "moritz/moritz"
#include "max/max"
#include "boeck/lib/quex/converter/iconv/Converter_IConv"
#include "boeck/lib/quex/converter/iconv/Converter_IConv.i"
#include "boeck/boeck"

using namespace std;


int 
main(int argc, char** argv) 
{        
    // we want to have error outputs in stdout, so that the unit test could see it.
    lexer::max            max_lex("example-utf16.txt",   new quex::Converter_IConv(sizeof(lexer::max_lexatom_t)<<3, "UTF16", NULL));
    lexer::moritz         moritz_lex("example-ucs2.txt", new quex::Converter_IConv(sizeof(lexer::moritz_lexatom_t)<<3, "UCS-2", NULL));
    lexer::boeck          boeck_lex("example-utf8.txt");
    lexer::max_Token*     max_token    = 0x0;
    lexer::moritz_Token*  moritz_token = 0x0;
    lexer::boeck_Token*   boeck_token  = 0x0;
    (void)argc; (void)argv;

    // Different lexers produce different interpretations on same lexeme.
    printf("                Max:        Moritz:      Boeck:\n");

    do {
        max_lex.receive(&max_token);
        moritz_lex.receive(&moritz_token);
        boeck_lex.receive(&boeck_token);

        /* Lexeme is same for all three. */
        size_t   L = lexer::max_lexeme_length(max_token->text);

        printf("%s", (char*)lexer::max_lexeme_to_pretty_char(max_token->text).c_str());

        for(size_t i=0; i < 10 - L ; ++i) printf(" ");
        printf("\t");
        printf("%s   %s   %s\n", 
               max_token->id_name(), 
               moritz_token->id_name(), 
               boeck_token->id_name());

    } while( boeck_token->id != TKN_TERMINATION );

    return 0;
}

