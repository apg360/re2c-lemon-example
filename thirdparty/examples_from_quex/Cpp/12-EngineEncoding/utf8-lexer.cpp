#include<cstdio> 

// (*) include lexical analyser header
#include "utf8/UTF8Lex"

using namespace std;

int 
main(int argc, char** argv) 
{        


    UTF8Lex_Token*  token;
    UTF8Lex         qlex("example-utf8.txt");
    (void)argc; (void)argv;
    

    do {
        qlex.receive(&token);

        printf("%s\n", (char*)(string(*token).c_str()));

    } while( token->id != TKN_TERMINATION );

    return 0;
}
