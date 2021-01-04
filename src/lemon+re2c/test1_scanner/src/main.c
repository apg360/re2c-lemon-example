#include <scanner.h>

//With Lemon it is the lexer/tokenizer - re2c in this case - that calls/initiate the parser

int main() {

    SCANNER("_Zer0");
    SCANNER("");
    SCANNER("one");
    SCANNER("one two");
    SCANNER("one two three");
    SCANNER("one two three four");
    SCANNER("4+4");
    SCANNER("(4+4)");

    char *commandLine;
    while (  (commandLine = dynamic_fgets())  ){
      
      SCANNER(commandLine);
      
      free(commandLine); //dynamic_fgets do malloc, free the allocated memory now that variable is no more used
    }
    
    return 0;
}

