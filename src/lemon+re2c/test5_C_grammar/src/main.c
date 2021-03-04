#include <scanner.h>

//With Lemon it is the lexer/tokenizer - re2c in this case - that calls/initiate the parser

int main() {

    scanner_DebugMode=true;
    PARSER_INIT(false);
    
    //validation_test();
    
    //SCANNER("x=50\n");
    //SCANNER("50");
    //SCANNER("50+125");
    //SCANNER("void main() {return 0+2;}");
    SCANNER("main ()");
    //SCANNER("int main() {");
    //SCANNER("50*125-50+125");
    //SCANNER("   4 + 5 - 20 + 7\n \
(24/2)*5\n \
");
    
    //Process test.dat
    //SCANNER( readFile() );
    
    /*char *commandLine;
    while (  (commandLine = dynamic_fgets())  ){
      
      SCANNER(commandLine);
      
      free(commandLine); //dynamic_fgets do malloc, free the allocated memory now that variable is no more used
    }*/
    
    PARSER_FREE();
    return 0;
}

