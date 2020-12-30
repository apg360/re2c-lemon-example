#include <stdio.h>
#include "SpellLex/SpellLex.h"

void notify(const char* Name, const char* Lexeme);

int main(int argc, char** argv)
{
     SpellLex_Token* token_p = NULL;
     SpellLex        tlex;
     const char*     file_name = (const char*)NULL;

     if( argc < 2 ) { printf("Missing file name. Try 'spelling.txt'.\n"); exit(-1); }
     file_name = &argv[1][0];

     SpellLex_from_file_name(&tlex, file_name, /* Converter */NULL);

     printf("\n\nAnalysing file '%s'\n\n", file_name);

     while( tlex.error_code == E_Error_None ) {
         tlex.receive(&tlex, &token_p);
         if( token_p->id == QUEX_TKN_TERMINATION ) break;
         printf("%s", SpellLex_map_token_id_to_name(token_p->id));
         printf(": %s\n", token_p->text);
     } 

     printf("\n");
     SpellLex_destruct(&tlex);
     return 0;
}

void notify(const char* Name, const char* Lexeme)
{
    printf("    no match for '%s'. Did you mean '%s'?\n", Lexeme, Name);
}
