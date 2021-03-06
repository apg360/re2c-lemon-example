#include <stdio.h> 

// (*) include lexical analyser header
#include "utf16-other/UTF16Lex.h"

int 
main(int argc, char** argv) 
{        
    bool                      BigEndianF  = (argc < 2 || (strcmp(argv[1], "BE") == 0)); 
    const char*               file_name   = BigEndianF ? "example-other-utf16be.txt" : "example-other-utf16le.txt";
    quex_ByteLoader*          byte_loader = quex_ByteLoader_FILE_new_from_file_name(file_name);
    UTF16Lex                  qlex;
    UTF16Lex_Token*           token_p     = 0x0;
    const UTF16Lex_lexatom_t* iterator    = 0x0;
    bool                      byte_order_reversion_f;

    if( argc == 1 ) {
        printf("Required at least one argument: 'LE' or 'BE'.\n");
        return -1;
    }
   
    UTF16Lex_from_ByteLoader(&qlex, byte_loader, NULL);
    /* System's endianness is 'little' => reversion if 'big'
     *                     is 'big'    => reversion if 'little' (not 'big'). */
    byte_order_reversion_f = quex_system_is_little_endian() ? BigEndianF : ! BigEndianF;
    qlex.byte_order_reversion_set(&qlex, byte_order_reversion_f);

    printf("## input file           = %s\n", file_name);
    printf("## byte order reversion = %s\n", E_Boolean_NAME(qlex.byte_order_reversion(&qlex)));
    
    do {
        qlex.receive(&qlex, &token_p);

        printf("%s\t", UTF16Lex_map_token_id_to_name(token_p->id));
        for(iterator = token_p->text; *iterator; ++iterator) {
            printf("%04X.", (int)*iterator);
        }
        printf("\n");

        // (*) check against 'termination'
    } while( token_p->id != TKN_TERMINATION );

    UTF16Lex_destruct(&qlex);

    return 0;
}
