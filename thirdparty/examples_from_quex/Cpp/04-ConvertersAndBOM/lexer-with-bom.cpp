#include "Easy/Easy"
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


    Easy_Token* token_p          = 0x0;
    int         number_of_tokens = 0;
    FILE*       fh               = fopen(argc > 1 ? argv[1] : "example.txt", "rb");

    /* The lexer must be constructed AFTER the BOM-cut                        */
    quex::ByteLoader*   byte_loader = quex::ByteLoader_FILE_new(fh, true);
    E_ByteOrderMark     bom_id      = quex::bom_snap(byte_loader);

    printf("Found BOM: %s\n", quex::bom_name(bom_id));

    if( bom_id == QUEX_BOM_NONE ) {
        /* No BOM in data stream => try to interpret data as UTF8             */
        bom_id = QUEX_BOM_UTF_8;
    }
    quex::Converter* converter = quex::Converter_IConv_new_from_BOM(sizeof(Easy_lexatom_t)<<3, bom_id);
    if( ! converter ) {
        printf("Cannot treat encoding given by BOM.\n");
        fclose(fh);
        quex::Converter_delete(&converter);
        quex::ByteLoader_delete(&byte_loader);
        return 0;
    }
    Easy             qlex(byte_loader, converter);
    do {
        qlex.receive(&token_p);

        print_token(token_p);

        ++number_of_tokens;
    } while( token_p->id != QUEX_TKN_TERMINATION );

    std::cout << "| [END] number of token = " << number_of_tokens << std::endl;

    fclose(fh);
    return 0;
}

static void
print_token(Easy_Token* token_p)
{
    std::cout << "(" << token_p->line_n << ", " << token_p->column_n << ")  \t";

    switch( token_p->id ) {
    case QUEX_TKN_INDENT: 
    case QUEX_TKN_DEDENT: 
    case QUEX_TKN_NODENT: 
    case QUEX_TKN_TERMINATION: 
        std::cout << token_p->id_name() << std::endl;
        break;
    default:
        std::cout << std::string(*token_p) << std::endl;
        break;
    }
}
