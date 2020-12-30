#include <stdio.h>
#include "EdLex/EdLex.h"

int
main(int argc, char** argv)
{
    return 0;
}

const char*
fuzzy_match(const char* Begin, size_t N, int* edit_distance) {
// INPUT:
//    Begin: pointer to first character of lexeme.
//    N:     number of bytes in lexeme.
// ADAPTS:
//    edit_distance: edit distance of the closest lexeme matching
// RETURNS:
//    Pointer to zero-terminated name of the closest lexeme matching. 
//    If nothing matches, then "<none>" is returned.
    EdLex        ed; 
    EdLex_Token* token_p = NULL;
    const char*  name = NULL;

    EdLex_from_memory(&ed, (EdLex_lexatom_t*)&Begin[0], N+1,
                      (EdLex_lexatom_t*)&Begin[N]);
    ed.receive(&ed, &token_p);

    switch(token_p->id) {
    case QUEX_TKN_HANDKERCHIEF: name = "handkerchief"; break;
    case QUEX_TKN_CONSCIENCE:   name = "conscience"; break;
    case QUEX_TKN_PLAYWRIGHT:   name = "playwright"; break;
    default:                    name = "<none>"; break;
    }
    *edit_distance = token_p->number;
    return name;
}
