#include <scanner.h>

//With Lemon it is the lexer/tokenizer - re2c in this case - that calls/initiate the parser

int main() {

    scanner_DebugMode=false;
    PARSER_INIT(false);
    
    SCANNER("50 + 125");
    SCANNER("15 / 5");
    SCANNER("50 * 125 - 50 + 125");
    
    char *commandLine;
    while (  (commandLine = dynamic_fgets())  ){
      
      SCANNER(commandLine);
      
      free(commandLine); //dynamic_fgets do malloc, free the allocated memory now that variable is no more used
    }
    
    PARSER_FREE();
    return 0;
}

