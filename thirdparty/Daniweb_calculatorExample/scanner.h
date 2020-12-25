#ifndef _SCANNER_H
# define _SCANNER_H
 
/*
 * opcodes:
 */
#define SCANNER_RETCODE_EOF -1
#define SCANNER_RETCODE_ERR -2
#define SCANNER_RETCODE_IMPOSSIBLE -3
 
#define TOKEN_INTEGER 257
#define TOKEN_ADD '+'
#define TOKEN_SUB '-'
#define TOKEN_MUL '*'
#define TOKEN_DIV '/'
#define TOKEN_ROUND_BRACKET_OPEN '('
#define TOKEN_ROUND_BRACKET_CLOSE ')'
 
typedef struct _scanner_state {
    char* start;
    char* end;
} scanner_state;
 
typedef struct _scanner_token {
    int opcode;
    union {
        int n;
        char* str;
    } data;
} scanner_token;
 
int scan(scanner_state *state, scanner_token *token);
//TODO: some functions to manipulate scanner states
#endif
