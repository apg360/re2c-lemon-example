#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//defines the parse() function
#include "lemon_parser.h"
 
int main(int argc, char **argv) {
    scanner_token result;
    result = parse_math_expr(argv[1]);
    printf("calc(%s) = %d\n",argv[1],result.data.n);
    return EXIT_SUCCESS;
}
