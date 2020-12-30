#include <stdio.h>
#include "TolerantLex/TolerantLex.h"

 int main(int argc, char** argv)
 {
     TolerantLex_Token* token_p = 0x0;
     TolerantLex        tlex;
     const char*        file_name = (const char*)NULL;

     if( argc < 2 ) { printf("Missing file name.\n"); exit(-1); }
     file_name = &argv[1][0];
     
     TolerantLex_from_file_name(&tlex, file_name, /* Converter */NULL);

     while( tlex.error_code == E_Error_None ) {
         tlex.receive(&tlex, &token_p);
         printf("%s", TolerantLex_map_token_id_to_name(token_p->id));
         if( token_p->id == QUEX_TKN_TERMINATION ) break;
         printf(": %s\n", token_p->text);
     } 

     TolerantLex_destruct(&tlex);
     return 0;
 }
