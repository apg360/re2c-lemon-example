#include <scanner.h>

//With Lemon it is the lexer/tokenizer - re2c in this case - that calls/initiate the parser

int main() {

    scanner_DebugMode=true;
    SCANNER("_Zer0");
    SCANNER("_ Zer 0");
    SCANNER("one");
    SCANNER("one two");
    SCANNER("one two three");
    SCANNER("one two three four");
    SCANNER("");
    SCANNER("4+4");
    SCANNER("(4+4)");

    PARSER_INIT(false);
    // First input: 
    //      15 / 5
    PARSER(TK_INT_LITERAL, (union Token){.number=15});
    PARSER(TK_DIV, (union Token){.number=0});
    PARSER(TK_INT_LITERAL, (union Token){.number=5});
    PARSER(TK_NEWLINE, (union Token){.number=0});
    PARSER(0, (union Token){.number=0});

    //  Second input:
    //      50 + 125
    /*PARSER(TK_INT_LITERAL, union Token.number=50);
    PARSER(TK_ADD, union Token.number=0);
    PARSER(TK_INT_LITERAL, union Token.number=125);
    PARSER(TK_NEWLINE, union Token.number=0);
    PARSER(0, 0);

    //  Third input:
    //      50 * 125 - 50 + 125
    PARSER(TK_INT_LITERAL, union Token.number=50);
    PARSER(TK_MUL, union Token.number=0);
    PARSER(TK_INT_LITERAL, union Token.number{125});
    PARSER(TK_SUB, union Token.number=0);
    PARSER(TK_INT_LITERAL, union Token.number=50);
    PARSER(TK_ADD, union Token.number=0);
    PARSER(TK_INT_LITERAL, union Token.number=125);
    PARSER(TK_NEWLINE, union Token.number=0);
    PARSER(0, 0);*/

    char *commandLine;
    while (  (commandLine = dynamic_fgets())  ){
      
      SCANNER(commandLine);
      
      free(commandLine); //dynamic_fgets do malloc, free the allocated memory now that variable is no more used
    }

    PARSER_FREE();
    return 0;
}

