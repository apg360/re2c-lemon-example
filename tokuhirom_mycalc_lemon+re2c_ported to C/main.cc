#include "scanner.h"
#include "parser.c"

int main() {
    YYSTYPE yylval;
    SCANNER_INIT(&std::cin);
    void *pParser = ParseAlloc(malloc);
    int tokenID;

#if 0
    ParseTrace(stderr, (char*)"[Parser] >> ");
#endif

    ParserState state;
    // scanner.scan return 0 when get EOF.
    while (tokenID == SCAN(yylval)) {
        printf("GET TOKEN: %d\n", tokenID);
        Parse(pParser, tokenID, yylval, &state);
    }
    Parse(pParser, 0, yylval, &state);
    ParseFree(pParser, free);
    SCANNER_DELETE();
    
    printf("RESULT: %d\n", state.result);
    return 0;
}

