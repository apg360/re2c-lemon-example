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

    PARSER_INIT();
    /* First input: 
          15 / 5
                                    */
    PARSER(INTEGER, 15);
    PARSER(DIVIDE, 0);
    PARSER(INTEGER, 5);
    PARSER(0, 0);

    /*  Second input:
            50 + 125
                                   */
    PARSER(INTEGER, 50);
    PARSER(PLUS, 0);
    PARSER(INTEGER, 125);
    PARSER(0, 0);

    /*  Third input:
            50 * 125 + 125
                                   */
    PARSER(INTEGER, 50);
    PARSER(TIMES, 0);
    PARSER(INTEGER, 125);
    PARSER(PLUS, 0);
    PARSER(INTEGER, 125);
    PARSER(0, 0);

    char *commandLine;
    while (  (commandLine = dynamic_fgets())  ){
      
      SCANNER(commandLine);
      
      free(commandLine); //dynamic_fgets do malloc, free the allocated memory now that variable is no more used
    }

    PARSER_FREE();
    return 0;
}

