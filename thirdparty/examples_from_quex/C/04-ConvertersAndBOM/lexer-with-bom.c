#include "Easy/Easy.h"
#include <Easy/lib/quex/converter/iconv/Converter_IConv>
#include <Easy/lib/quex/converter/iconv/Converter_IConv.i>
#include <Easy/lib/quex/bom.i>
#include <stdio.h>    

static void print_token(Easy_Token* token_p);

int 
main(int argc, char** argv) 
/* 1st arg: input file, default = 'example.txt'
 * 2nd arg: input character encoding name, 0x0 --> no conversion              */
{        
    Easy        qlex;
    Easy_Token* token_p = 0x0;
    int         number_of_tokens = 0;
    FILE*       fh = fopen(argc > 1 ? argv[1] : "example.txt", "rb");

    /* The lexer must be constructed AFTER the BOM-cut                        */
    quex_ByteLoader*    byte_loader = quex_ByteLoader_FILE_new(fh, true);
    /* QUEX_GNAME_LIB(Converter)*  converter   = QUEX_NAME_LIB(Converter_ICU_new)(NULL, NULL); */
    E_ByteOrderMark     bom_id = quex_bom_snap(byte_loader);
    quex_Converter*     converter;

    printf("Found BOM: %s\n", quex_bom_name(bom_id));

    if( bom_id == QUEX_BOM_NONE ) {
        /* No BOM in data stream => try to interpret data as UTF8             */
        bom_id = QUEX_BOM_UTF_8;
    }
    converter = quex_Converter_IConv_new_from_BOM(sizeof(Easy_lexatom_t)<<3, bom_id);
    if( ! converter ) {
        printf("Cannot treat encoding given by BOM.\n");
        fclose(fh);
        quex_ByteLoader_delete(&byte_loader);
        return 0;
    }
    Easy_from_ByteLoader(&qlex, byte_loader, converter);

    do {
        qlex.receive(&qlex, &token_p);

        print_token(token_p);

        ++number_of_tokens;
    } while( token_p->id != QUEX_TKN_TERMINATION );

    printf("| [END] number of token = %i\n", number_of_tokens);

    Easy_destruct(&qlex);

    fclose(fh);
    return 0;
}

static void
print_token(Easy_Token* token_p)
{
    const size_t    BufferSize = 1024;
    char            buffer[1024];

    printf("(%i, %i)  \t", (int)token_p->line_n, (int)token_p->column_n);

    switch( token_p->id ) {
    case QUEX_TKN_INDENT: 
    case QUEX_TKN_DEDENT: 
    case QUEX_TKN_NODENT: 
    case QUEX_TKN_TERMINATION: 
        printf("%s\n", Easy_map_token_id_to_name(token_p->id));
        break;
    default:
        printf("%s \n", Easy_Token_get_string(token_p, buffer, BufferSize));
        break;
    }
}
