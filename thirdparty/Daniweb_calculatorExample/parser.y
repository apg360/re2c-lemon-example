%include {
    #include <stdio.h>
    #include <stdlib.h>
    #include "scanner.h"
    #include "parser.h"
    #include "lemon_parser.h"
}
%token_type {scanner_token*}
%default_type {scanner_token*}
 
%type expr {scanner_token*}
%type OP_INTEGER {scanner_token*}
 
 
 
%left OP_ADD OP_SUB.
%left OP_MUL OP_DIV.
 
 
%syntax_error {
    printf("syntax error\n");
}
 
in ::= expr(A). {
   printf("in expr(A):\n");
}
 
expr(A) ::= expr(B) OP_ADD expr(C). {
    A->data.n = B->data.n + C->data.n;
}
 
expr(A) ::= expr(B) OP_SUB expr(C). {
    A->data.n = B->data.n - C->data.n;
}
 
expr(A) ::= expr(B) OP_MUL expr(C). {
    A->data.n = B->data.n * C->data.n;
}
 
expr(A) ::= expr(B) OP_DIV expr(C). {
    /* TODO: fix division by 0 */
    A->data.n = B->data.n / C->data.n;
}
expr(A) ::= OP_INTEGER(B). { A->data.n = B->data.n; }
