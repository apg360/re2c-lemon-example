#include <stdio.h>
#include "tiny/tiny.h"

 int main(int argc, char** argv)
 {
     tiny_Token* token_p = 0x0;
     tiny        tlex;

     tiny_from_file_name(&tlex, "example.txt", /* Converter */NULL);

     while( tlex.error_code == E_Error_None ) {
         tlex.receive(&tlex, &token_p);
         printf("%s", tiny_map_token_id_to_name(token_p->id));
         if( token_p->id == QUEX_TKN_TERMINATION ) break;
         printf(": %s\n", token_p->text);
     } 

     tiny_destruct(&tlex);
     return 0;
 }
