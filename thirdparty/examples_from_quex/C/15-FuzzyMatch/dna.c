#include <stdio.h>
#include "DnaLex/DnaLex.h"

static int  DnaCountDb_compare(const void*, const void*);
static void DnaCountDb_print(DnaCountDbEntry* Begin, size_t Size);

 int main(int argc, char** argv)
 {
     DnaLex_Token* token_p = 0x0;
     DnaLex        dna_lex;

     if( argc < 2 ) { printf("Missing file name.\n"); exit(-1); }
     
     DnaLex_from_file_name(&dna_lex, &argv[1][0], /* Converter */NULL);

     printf("\nRANGES:\n\n");

     while( dna_lex.error_code == E_Error_None ) {
         dna_lex.receive(&dna_lex, &token_p);
         if( token_p->id == QUEX_TKN_TERMINATION ) break;
         printf(": %s\n", token_p->text);
     } 

     DnaCountDb_print(&dna_lex.count_db[0], 
                      /* entry number = */ sizeof(dna_lex.count_db)/sizeof(DnaCountDbEntry));

     DnaLex_destruct(&dna_lex);
     return 0;
 }

static void
DnaCountDb_print(DnaCountDbEntry* Begin, size_t Size)
{
     printf("\nOCCURRENCE COUNTS:\n\n");

     size_t                 ElementSize  = sizeof(DnaCountDbEntry);
     const DnaCountDbEntry* End = &Begin[Size];

     qsort(Begin, 
           /* array size:          */ Size, 
           /* array element size:  */ ElementSize, 
           /* comparison function: */ DnaCountDb_compare);

     for(const DnaCountDbEntry * it = Begin; it != End ; ++it) {
         printf("%6i: %s\n", (int)it->count, it->name);
     }
    printf("\n");
 }

static int 
DnaCountDb_compare(const void* A, const void* B)
{
    const DnaCountDbEntry* First  = (const DnaCountDbEntry*)A;
    const DnaCountDbEntry* Second = (const DnaCountDbEntry*)B;

    return First->count < Second->count;
}

void
DnaCountDb_begin_mismatch(DnaLex* dna_lex)
{
    long position = (long)dna_lex->tell(dna_lex);
    if( dna_lex->mismatch_begin_position == -1L ) {
        dna_lex->mismatch_begin_position = position - 1L;
    }

    ++dna_lex->count_db[ID_NONE].count; 
}

void
DnaCountDb_register(DnaLex* dna_lex, ptrdiff_t Id, size_t LexemeL)
{
    long end_position = (long)dna_lex->tell(dna_lex);
    if( dna_lex->mismatch_begin_position != -1L ) {
        printf("    %3i -%3i: <NONE>\n", (int)dna_lex->mismatch_begin_position, 
               (int)end_position - (int)LexemeL);
        dna_lex->mismatch_begin_position = -1L;
    }
    printf("    %3i -%3i: '%s'\n", (int)(end_position - LexemeL), (int)end_position, dna_lex->count_db[Id].name);

    ++dna_lex->count_db[Id].count; 
}
