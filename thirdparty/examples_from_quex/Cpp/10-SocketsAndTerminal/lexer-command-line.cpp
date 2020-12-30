/* Lexical FSM fed from a Command Line
 * -----------------------------------------
 *
 * In this example, user interaction results in a command line which is then
 * lexically analyzed. This example requires the 'GNU readline' library to
 * be installed.
 *_____________________________________________________________________________
 *
 *  EXAMPLE:
 *  
 *    Ascii-codec command line:
 *
 *          > ./lexer-command-line
 *        
 *          type here: A message of a kilobyte
 *              read: 24 [byte]
 *              Token: ARTICLE 'A'
 *              Token: SUBJECT 'message'
 *              Token: PREPOSITION 'of'
 *              Token: ARTICLE 'a'
 *              Token: SUBJECT 'kilobyte'
 *              Token: <TERMINATION> ''
 *          type here: starts with a single bit
 *              read: 25 [byte]
 *              Token: SUBJECT 'starts'
 *              Token: PREPOSITION 'with'
 *              Token: ARTICLE 'a'
 *              Token: ATTRIBUTE 'single'
 *              Token: STORAGE_UNIT 'bit'
 *              Token: <TERMINATION> ''
 *          type here: ^C
 *        
 *    Similarly, the UTF8 command line parser may be used:
 *        
 *          > ./lexer-command-line-utf8
 *          
 *_____________________________________________________________________________
 *
 * (C) Frank-Rene Schaefer                                                   */

#include <stdio.h>
#if ! defined(WITH_UTF8)
#   include <lex_ascii/Lexer>
#else
#   include <lex_utf8/Lexer>
#   include <lex_utf8/lib/quex/converter/iconv/Converter_IConv>
#   include <lex_utf8/lib/quex/converter/iconv/Converter_IConv.i>
#endif


int 
main(int argc, char** argv) 
{        

    using namespace std;
    Lexer_Token*  token;
    Lexer*        qlex;   
    char          buffer[4096];
    ssize_t       received_n;
    (void)argc; (void)argv;
#if defined(WITH_UTF8)
    quex::Converter*    converter = new quex::Converter_IConv(sizeof(Lexer_lexatom_t)<<3, "UTF8", NULL);
#   else
#   define              converter NULL
#endif

    qlex = Lexer::from_ByteLoader(NULL, converter);

    while( ! token || token->id != QUEX_TKN_BYE ) {
        printf("type here: ");

		cin.getline((std::basic_istream<char>::char_type*)&buffer[0], sizeof(buffer)-1);
        if( (received_n = cin.gcount()) == 0 ) break;

        /* Last received byte is the terminating zero! => -1 !               
         *                                                                   */
        printf("    read: %i [byte]\n", (int)received_n - 1);

        qlex->reset();

        /* NOTE: If the character index of the pipe needs to be traced properly
         * the 'newline' character needs to be inserted manually, because, it
         * is cut out of the stream by 'getline()'. Trick: replace the
         * terminating zero (which is not needed by the engine) by the line's
         * newline, i.e:                                
         *
         *            buffer[received_n-1] = '\n';      // not with 'getline()'
         *            qlex->buffer.fill( ... &buffer[received_n]);                 
         *                                                                   */
        qlex->buffer.fill(&qlex->buffer, &buffer[0], &buffer[received_n-1]);

        do {
            qlex->receive(&token);
            printf("   Token: %s\n", token->get_string().c_str()); 
        } while( token->id != QUEX_TKN_TERMINATION && token->id != QUEX_TKN_BYE );
    }
        
    delete qlex; 
    printf("<terminated>\n");
    return 0;
}


