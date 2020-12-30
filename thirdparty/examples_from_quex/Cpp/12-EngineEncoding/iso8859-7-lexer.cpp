#include<cstdio> 

// (*) include lexical analyser header
#include "iso8859-7/ISO8859_7_Lex"

using namespace std;

int 
main(int argc, char** argv) 
{        


    ISO8859_7_Lex_Token* token_p;
    ISO8859_7_Lex        qlex("example-iso8859-7.txt");
    
    (void)argc; (void)argv; 

    // (*) loop until the 'termination' token arrives
    do {
        // (*) get next token from the token stream
        qlex.receive(&token_p);

        // (*) print out token information
        cout << string(*token_p) << endl;

        // (*) check against 'termination'
    } while( token_p->id != TKN_TERMINATION );

    return 0;
}
