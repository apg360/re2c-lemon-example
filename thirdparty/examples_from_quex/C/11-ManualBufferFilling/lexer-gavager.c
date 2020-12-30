#include <stdio.h>

#ifdef QUEX_DEMO_WITH_CONVERTER
#   include "converter/Lexer.h"
#   include "converter/lib/quex/converter/iconv/Converter_IConv"
#   include "converter/lib/quex/converter/iconv/Converter_IConv.i"
#   include "converter/lib/analyzer/adaptors/Gavager.i"
#   include "converter/lib/buffer/Buffer_print"
#else
#   include "plain/Lexer.h"
#   include "plain/lib/analyzer/adaptors/Gavager.i"
#   include "plain/lib/buffer/Buffer_print"
#endif


#include "receiver.h"

static void show_buffer(Lexer* lexer, 
                        const uint8_t* RawBeginP, const uint8_t* RawEndP);

int 
main(int argc, char** argv) 
{        
    Lexer_Token*       token;
#   if   defined(QUEX_DEMO_OPTION_CONVERTER_ICONV)
    quex_Converter*    converter = quex_Converter_IConv_new(sizeof(Lexer_lexatom_t)<<3, "UTF8", NULL);
#   elif defined(QUEX_DEMO_OPTION_CONVERTER_ICU)
    quex_Converter*    converter = quex_Converter_ICU_new(sizeof(Lexer_lexatom_t)<<3, "UTF8", NULL);
#   else
#   define             converter NULL
#   endif
    Lexer           lexer;
    Lexer_Gavager   gavager;
    ptrdiff_t       received_n;
    uint8_t*        begin_p;
    const uint8_t*  end_p;
    char            buffer[256];
    (void)argc; (void)argv;

    Lexer_from_ByteLoader(&lexer, (quex_ByteLoader*)0, converter);
    Lexer_Gavager_construct(&gavager, &lexer, QUEX_TKN_BYE);

    token = (Lexer_Token*)0;
    while( ! token || token->id != QUEX_TKN_BYE ) {

        if( ! token ) {
            gavager.access(&gavager, (void**)&begin_p, (const void**)&end_p); 
            
            received_n = (ptrdiff_t)receiver_receive_in_this_place(begin_p, end_p);

            gavager.gavage(&gavager, received_n);

            show_buffer(&lexer, &begin_p[0], &begin_p[received_n]);
        }

        token = gavager.deliver(&gavager);
        /* token == NULL, if the feeder only requires more content.
         * else,          if a valid token that has been returned.       */

        if( token ) {
            printf("   TOKEN: %s\n", Lexer_Token_get_string(token, &buffer[0], sizeof(buffer)));
        }
    }

    show_buffer(&lexer, &begin_p[0], &begin_p[received_n]);

    Lexer_destruct(&lexer);
    /* Gavagers do not need destruction. */
}

static void
show_buffer(Lexer* lexer, const uint8_t* RawBeginP, const uint8_t* RawEndP)
{
#   ifdef QUEX_DEMO_WITH_CONVERTER
    printf("     raw: ");
    Lexer_Buffer_print_content_core(1, RawBeginP, &RawEndP[-1], 
                                    (const uint8_t*)0, RawEndP,
                                    /* BordersF */ false);
    printf("\n");
#   endif
    (void)RawBeginP; (void)RawEndP;
    printf("        : ");
    Lexer_Buffer_print_content(&lexer->buffer);
    printf("\n");
}
