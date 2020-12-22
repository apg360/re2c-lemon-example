#include "util.h"
#include "parser.c"

#define TEST(s) printf("'%s' => result= %d\n",s, SCANNER(s) )
int main() {
    
    TEST("_Zer0");
    TEST("");
    TEST("one");
    TEST("one two");
    TEST("one two three");
    TEST("one two three four");
    
    YYSTYPE yylval;
    void *pParser = ParseAlloc(malloc);
    int tokenID;
    
#if 0
    ParseTrace(stderr, (char*)"[Parser] >> ");
#endif
    
    ParserState state;
    // scanner.scan return 0 when get EOF.
    while (tokenID == SCANNER( &yylval ) ) {
        printf("GET TOKEN: %d\n", tokenID);
        Parse(pParser, tokenID, yylval, &state);
    }
    Parse(pParser, 0, yylval, &state);
    ParseFree(pParser, free);
    printf("RESULT: %d\n", state.result);
    
    /*char *commandLine;
    while (  (commandLine = dynamic_fgets())  ){
      size_t size = strlen(commandLine);
      printf(">Number characters %zu \n",size);
      printf(">Number words %d \n", SCANNER(commandLine, size)  );
      
      free(commandLine); //free the memory allocated with malloc
    }*/
    
    return 0;
}

