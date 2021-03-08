
#include <stdlib.h> //malloc, free, size_t
#include "example1.h"

void* ParseAlloc(void* (*allocProc)(size_t));
void ParseFree(void* parser, void(*freeProc)(void*));
void Parse(void* parser, int token, const int); //, bool* valid); //parser.lem added extra_argument bool valid

int main()
{
  void* pParser = ParseAlloc (malloc);
  ParseTrace(stderr, "[Parser] >> ");
  
  /* First input: 
      15 / 5
                                */
  Parse (pParser, INTEGER, 15);
  Parse (pParser, DIVIDE, 0);
  Parse (pParser, INTEGER, 5);
  Parse (pParser, 0, 0);

  /*  Second input:
        50 + 125
                               */

  Parse (pParser, INTEGER, 50);
  Parse (pParser, PLUS, 0);
  Parse (pParser, INTEGER, 125);
  Parse (pParser, 0, 0);

  /*  Third input:
        50 * 125 + 125
                               */


  Parse (pParser, INTEGER, 50);
  Parse (pParser, TIMES, 0);
  Parse (pParser, INTEGER, 125);
  Parse (pParser, PLUS, 0);
  Parse (pParser, INTEGER, 125);
  Parse (pParser, 0, 0);


  ParseFree(pParser, free );

}
