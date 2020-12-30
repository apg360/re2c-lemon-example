/* Stdandard-Input-Based Lexical FSM
 * --------------------------------------
 *
 * This application implements a lexical analyzer that reads from the Standard
 * Input, often referred to as 'stdin'. It does so by means of a POSIX byte
 * loader (while a FILE byte loader may equally do). The lexical analysis
 * terminates with the termination character on the standard input 'Ctrl-D'.
 *_____________________________________________________________________________
 *
 * EXAMPLE:
 *
 *  Under Unix/Linux use the 'pipe' character to redirect the output of a 
 *  command to the standard input of the lexical analyzer.
 *  
 *     > cat example-feed.txt | ./lexer-stdin
 *
 *  Or, respectively for a UTF8 lexer:
 *
 *     > cat example-feed-utf8.txt | ./lexer-stdin-utf8
 *  
 *_____________________________________________________________________________
 *
 * (C) Frank-Rene Schaefer                                                   */

#include <stdio.h>
#if ! defined(WITH_UTF8)
#   include <lex_ascii/Lexer.h>
#   include <lex_ascii/lib/quex/byte_loader/ByteLoader_POSIX>
#   include <lex_ascii/lib/quex/byte_loader/ByteLoader_POSIX.i>
#else
#   include <lex_utf8/Lexer.h>
#   include <lex_utf8/lib/quex/converter/iconv/Converter_IConv>
#   include <lex_utf8/lib/quex/converter/iconv/Converter_IConv.i>
#   include <lex_utf8/lib/quex/byte_loader/ByteLoader_POSIX>
#   include <lex_utf8/lib/quex/byte_loader/ByteLoader_POSIX.i>
#endif

static void  print_token(Lexer_Token*  token);

int 
main(int argc, char** argv) 
{        
    Lexer_Token*      token;
    Lexer             qlex;   
#if defined(WITH_UTF8)
    quex_Converter*  converter = quex_Converter_IConv_new(sizeof(Lexer_lexatom_t)<<3, "UTF8", NULL);
#   else
#   define            converter NULL
#endif
    quex_ByteLoader* loader = quex_ByteLoader_POSIX_new(0); /* 0 = stdin */
    (void)argc; (void)argv;

    quex_ByteLoader_seek_disable(loader);

    Lexer_from_ByteLoader(&qlex, loader, converter);

    do {
        qlex.receive(&qlex, &token);
        print_token(token);
    } while( token->id != QUEX_TKN_TERMINATION && token->id != QUEX_TKN_BYE );
        
    Lexer_destruct(&qlex);
    return 0;
}

static void
print_token(Lexer_Token*  token)
{
    size_t PrintBufferSize = 1024;
    char   print_buffer[1024];

    printf("   Token: %s\n", Lexer_Token_get_string(token, print_buffer, PrintBufferSize));
}

