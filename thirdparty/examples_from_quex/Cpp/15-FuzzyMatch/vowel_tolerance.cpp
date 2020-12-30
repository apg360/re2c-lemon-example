#include <stdio.h>
#include "TolerantLex/TolerantLex"

 int main(int argc, char** argv)
 {
     if( argc < 2 ) { printf("Missing file name.\n"); exit(-1); }

     TolerantLex_Token* token_p = 0x0;
     TolerantLex        tlex(&argv[1][0], /* Converter */NULL);

     while( tlex.error_code == E_Error_None ) {
         tlex.receive(&token_p);
         printf("%s", TolerantLex_map_token_id_to_name(token_p->id));
         if( token_p->id == QUEX_TKN_TERMINATION ) break;
         printf(": %s\n", token_p->text);
     } 

     TolerantLex_destruct(&tlex);
     return 0;
 }
