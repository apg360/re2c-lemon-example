#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _IN_SCANNER
#include "scanner.h"
 
#if 0
#define DEBUG(stmt) stmt
#else
#define DEBUG(stmt)
#endif
 
int scan(scanner_state *s, scanner_token *token) {
//  char *cursor = s->start;
    int r=SCANNER_RETCODE_IMPOSSIBLE;
    char *q=s->start;//keep initial start
#define YYCTYPE     char
#define YYCURSOR    (s->start)
#define YYLIMIT     (s->end)
 
    while(SCANNER_RETCODE_IMPOSSIBLE == r) {
/*!re2c
    re2c:indent:top = 2;
    re2c:yyfill:enable = 0;
 
    INTEGER     = [0-9]+;
 
 
    INTEGER     {
                char *num;
                int n;
                num = strndup(q,YYCURSOR - q);
                n = atoi(num);
                DEBUG(printf("scanner num: '%s', YYCURSOR: '%s' YYLIMIT: '%s' q: '%s'\n",num,YYCURSOR,YYLIMIT,q));
                free(num);
                q = YYCURSOR;
            //  DEBUG(printf("integer, cursor: %s, number len: %ld, number: %d\n",YYCURSOR,YYCURSOR-s->start,n));
                token->data.n = n;
                token->opcode = TOKEN_INTEGER;
                return 0;
            }
    "+"     {
                token->opcode = TOKEN_ADD;
                return 0;
            }
    "-"     {
                token->opcode = TOKEN_SUB;
                return 0;
            }
    "*"     {
                token->opcode = TOKEN_MUL;
                return 0;
            }
    "/"     {
                token->opcode = TOKEN_DIV;
                return 0;
            }
    "("     {
                token->opcode = TOKEN_ROUND_BRACKET_OPEN;
                return 0;
            }
    ")"     {
                token->opcode = TOKEN_ROUND_BRACKET_CLOSE;
                return 0;
            }
 
    "\000"      { r = SCANNER_RETCODE_EOF; break; }
    [^]     { r = SCANNER_RETCODE_ERR; break; }
*/
    }
    return r;
}
