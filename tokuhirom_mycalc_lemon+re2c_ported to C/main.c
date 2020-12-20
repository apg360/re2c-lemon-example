#include "util.h"
#include "build/scanner.h"
#include "parser.c"

#define TEST(s) printf("'%s' => result= %d\n",s, SCANNER(s, sizeof(s) - 1) )
int main() {
    
    TEST("_Zer0");
    TEST("");
    TEST("one");
    TEST("one two");
    TEST("one two three");
    TEST("one two three four");
    
    YYSTYPE yylval;
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
    
    char *commandLine;
    while (  (commandLine = dynamic_fgets())  ){
      size_t size = strlen(commandLine);
      printf(">Number characters %zu \n",size);
      printf(">Number words %d \n", SCANNER(commandLine, size)  );
      
      free(commandLine); //free the memory allocated with malloc
    }
    
    return 0;
}

