#include<cstdio> 

// (*) include lexical analyser header
#include "utf16/UTF16Lex"

using namespace std;

int 
main(int argc, char** argv) 
{        

    (void)argc; (void)argv;

    if( argc == 1 ) {
       printf("Required at least one argument: 'LE' or 'BE'.\n");
       return -1;
    }

    bool                BigEndianF  = (strcmp(argv[1], "BE") == 0); 
    const char*         file_name   = BigEndianF ? "example-utf16be.txt" : "example-utf16le.txt";
    quex::ByteLoader*   byte_loader = new quex::ByteLoader_FILE(file_name);
    UTF16Lex*           qlex;
    UTF16Lex_Token*     token;

    qlex = UTF16Lex::from_ByteLoader(byte_loader, NULL);
    /* System's endianness is 'little' => reversion if 'big'
     *                     is 'big'    => reversion if 'little' (not 'big'). */
    qlex->byte_order_reversion_set(quex::system_is_little_endian() ? 
                                   BigEndianF : ! BigEndianF);

    printf("## input file           = %s\n", file_name);
    printf("## byte order reversion = %s\n", E_Boolean_NAME(qlex->byte_order_reversion()));
    
    do {
        qlex->receive(&token);

        /* Print the lexeme in utf8 format. */
        printf("%s\n", (char*)(string(*token).c_str()));

        // (*) check against 'termination'
    } while( token->id != TKN_TERMINATION );

    delete qlex;
    delete byte_loader;
    return 0;
}
