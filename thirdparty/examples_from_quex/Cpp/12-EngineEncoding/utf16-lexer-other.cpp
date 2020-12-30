#include<cstdio> 

// (*) include lexical analyser header
#include "utf16-other/UTF16Lex"

using namespace std;

int 
main(int argc, char** argv) 
{        


    if( argc == 1 ) {
       printf("Required at least one argument: 'LE' or 'BE'.\n");
       return -1;
    }

    bool                BigEndianF  = (strcmp(argv[1], "BE") == 0); 
    const char*         file_name   = BigEndianF ? "example-other-utf16be.txt" : "example-other-utf16le.txt";
    quex::ByteLoader*   byte_loader = new quex::ByteLoader_FILE(file_name);
    UTF16Lex*           qlex;
    UTF16Lex_Token*     token;

    qlex = UTF16Lex::from_ByteLoader(byte_loader, NULL);
    /* System's endianness is 'little' => reversion if 'big'
     *                     is 'big'    => reversion if 'little' (not 'big').  */
    qlex->byte_order_reversion_set(quex::system_is_little_endian() ? 
                                   BigEndianF : ! BigEndianF);

    printf("## input file           = %s\n", file_name);
    printf("## byte order reversion = %s\n", E_Boolean_NAME(qlex->byte_order_reversion()));
    
    do {
        qlex->receive(&token);

        /* Print the lexeme in hex format. */
        printf("%s\t", (char*)token->id_name());
        for(const UTF16Lex_lexatom_t* iterator = token->get_text(); *iterator ; ++iterator) {
            printf("%04X.", *iterator);
        }
        printf("\n");

        // (*) check against 'termination'
    } while( token->id != TKN_TERMINATION );

    delete qlex;
    delete byte_loader;
    return 0;
}
