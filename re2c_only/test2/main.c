#include "util.h"
#include "scanner.h"

#define TEST(s) printf("'%s' => result= %d\n",s, SCANNER(s, sizeof(s) - 1) )
int main() {
    
    TEST("_Zer0");
    TEST("");
    TEST("one");
    TEST("one two");
    TEST("one two three");
    TEST("one two three four");
    
    char *commandLine;
    while (  (commandLine = dynamic_fgets())  ){
      size_t size = strlen(commandLine);
      printf(">Number characters %zu \n",size);
      printf(">Number words %d \n", SCANNER(commandLine, size)  );
      
      free(commandLine); //free the memory allocated with malloc
    }
    
    return 0;
}

