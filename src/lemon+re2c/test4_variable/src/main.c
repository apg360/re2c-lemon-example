#include <scanner.h>

//With Lemon it is the lexer/tokenizer - re2c in this case - that calls/initiate the parser

void validation_test()
{
    //Some validation testing
    //
    assert( eval("    1+       1")                == 2);
    assert( eval("	1+		1")                   == 2);
    //
    assert( eval("0 - 0")                         == 0);
    assert( eval("0 - 1")                         == -1);
    assert( eval("1 - 0")                         == 1);
    assert( eval("1 - 1")                         == 0);
    assert( eval("1 - 2")                         == -1);
    assert( eval("2 - 1")                         == 1);
    assert( eval("4 - 2 - 1")                     == 1);
    assert( eval("(4 - 2) - 1")                   == 1);
    assert( eval("4 - (2 - 1)")                   == 3);
    assert( eval("-1 - 1")                        == -2);
    assert( eval("1 - -1")                        == 2);
    assert( eval("-1 - -1")                       == 0);
    //
    assert( eval("0 * 0")                         == 0);
    assert( eval("0 * 1")                         == 0);
    assert( eval("1 * 0")                         == 0);
    assert( eval("1 * 1")                         == 1);
    assert( eval("1 * 2")                         == 2);
    assert( eval("2 * 1")                         == 2);
    assert( eval("2 * 3 * 4")                     == 24);
    assert( eval("(2 * 3) * 4")                   == 24);
    assert( eval("2 * (3 * 4)")                   == 24);
    assert( eval("-1 * 1")                        == -1);
    assert( eval("1 * -1")                        == -1);
    assert( eval("-1 * -1")                       == 1);
    //
    assert( eval("0 / 1")                         == 0);
    assert( eval("1 / 1")                         == 1);
    assert( eval("1 / 2")                         == 0.5);
    assert( eval("2 / 1")                         == 2);
    assert( eval("2 / 3 / 4")                     == 0.16666666666666666);
    assert( eval("(2 / 3) / 4")                   == 0.16666666666666666);
    assert( eval("2 / (3 / 4)")                   == 2.6666666666666665);
    assert( eval("-1 / 1")                        == -1);
    assert( eval("1 / -1")                        == -1);
    assert( eval("-1 / -1")                       == 1);
    //
    assert( eval("4 + 4 + 4")                     == 12);
    assert( eval("4 - 2 - 1")                     == 1);
    assert( eval("1 + 2 * 3")                     == 7);
    assert( eval("(1 + 2) * 3")                   == 9);
    assert( eval("(1 + 3 * 5) / 2 - 1")           == 7);
    assert( eval("20 - 4 - 6")                    == 10);
    assert( eval("-(4 + 2 ^ 3 ^ 0 * 5 ^ 2) + 7")  == -47);
    //
    assert( eval("1 ^ 0")                         == 1);
    assert( eval("1 ^ 1")                         == 1);
    assert( eval("1 ^ 2")                         == 1);
    assert( eval("2 ^ 0")                         == 1);
    assert( eval("2 ^ 1")                         == 2);
    assert( eval("2 ^ 2")                         == 4);
    assert( eval("2 ^ 3")                         == 8);
    assert( eval("3 ^ 2")                         == 9);
    assert( eval("2 ^ 3 ^ 2")                     == 512);
    assert( eval("(2 ^ 3) ^ 2")                   == 64);
    assert( eval("2 ^ (3 ^ 2)")                   == 512);
    assert( eval("2 ^ -1")                        == 0.5);
    assert( eval("-2 ^ 1")                        == -2);
    //
    assert( eval("0 % 4")                         == 0);
    assert( eval("1 % 4")                         == 1);
    assert( eval("2 % 4")                         == 2);
    assert( eval("3 % 4")                         == 3);
    assert( eval("4 % 4")                         == 0);
    assert( eval("5 % 4")                         == 1);
    assert( eval("6 % 4")                         == 2);
    assert( eval("7 % 4")                         == 3);
    assert( eval("8 % 4")                         == 0);
}

int main() {

    scanner_DebugMode=false;
    PARSER_INIT(false);
    
    validation_test();
    
    SCANNER("50+125");
    SCANNER("15/5");
    SCANNER("50*125-50+125");
    SCANNER("   4 + 5 - 20 + 7\n \
(24/2)*5\n \
");
    
    //Process test.dat
    //SCANNER( readFile() );
    
    char *commandLine;
    while (  (commandLine = dynamic_fgets())  ){
      
      SCANNER(commandLine);
      
      free(commandLine); //dynamic_fgets do malloc, free the allocated memory now that variable is no more used
    }
    
    PARSER_FREE();
    return 0;
}

