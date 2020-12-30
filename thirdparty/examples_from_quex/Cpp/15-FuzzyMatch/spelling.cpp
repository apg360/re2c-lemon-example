#include <stdio.h>
#include "SpellLex/SpellLex"

void notify(const char* Name, const char* Lexeme);

 int main(int argc, char** argv)
 {
     if( argc < 2 ) { printf("Missing file name. Try 'spelling.txt'.\n"); exit(-1); }

     SpellLex_Token* token_p = 0x0;
     const char*     file_name = &argv[1][0];
     SpellLex        tlex(file_name, /* Converter */NULL);

     printf("\n\nAnalysing file '%s'\n\n", file_name);

     while( tlex.error_code == E_Error_None ) {
         tlex.receive(&token_p);
         if( token_p->id == QUEX_TKN_TERMINATION ) break;
         printf("%s", SpellLex_map_token_id_to_name(token_p->id));
         printf(": %s\n", token_p->text);
     } 

     printf("\n");
     return 0;
 }

void notify(const char* Name, const char* Lexeme)
{
    printf("    no match for '%s'. Did you mean '%s'?\n", Lexeme, Name);
}
