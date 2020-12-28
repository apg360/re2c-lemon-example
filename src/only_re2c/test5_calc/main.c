#include "util.h"
#include "scanner.h"

int main() {
    
    SCANNER("_Zer0");
    SCANNER("");
    SCANNER("one");
    SCANNER("one two");
    SCANNER("one two three");
    SCANNER("one two three four");
    SCANNER("(4+4)");
    
    char *commandLine;
    while (  (commandLine = dynamic_fgets())  ){
      
      SCANNER( commandLine );
      
      free(commandLine); //free the memory allocated with malloc
    }
    
    return 0;
}

