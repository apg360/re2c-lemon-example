#include "util.h"
#include "scanner.h"

#define TEST(s) SCANNER(s, strlen(s))

int main() {
    
    TEST("_Zer0");
    TEST("");
    TEST("one");
    TEST("one two");
    TEST("one two three");
    TEST("one two three four");
    TEST("(4+4)");
    
    char *commandLine;
    while (  (commandLine = dynamic_fgets())  ){
      
      SCANNER( commandLine, strlen(commandLine) );
      
      free(commandLine); //free the memory allocated with malloc
    }
    
    return 0;
}

