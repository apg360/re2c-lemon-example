#include <iostream>
#include "tiny/tiny"

int main(int argc, char** argv)
{         
    tiny_Token*  token_p = 0x0;
    tiny    tlex("example.txt", /* Converter */NULL);

    while( tlex.error_code == E_Error_None ) {
        tlex.receive(&token_p);
        std::cout << token_p->id_name();
        if( token_p->id == QUEX_TKN_TERMINATION ) break;
        std::cout << ": " << token_p->text << std::endl;
    }
    return 0;
}
