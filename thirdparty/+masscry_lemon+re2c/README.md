# BadCode

An example learning interpreter using [re2c](https://github.com/skvadrik/re2c)
and [The LEMON Parser Generator](https://www.hwaci.com/sw/lemon/).

## Project Structure

 * [CMakeLists.txt](https://github.com/masscry/badcode/blob/master/CMakeLists.txt)
    Single build script;
 * [include/badcode.h](https://github.com/masscry/badcode/blob/master/include/badcode.h)
    Public API header;
 * [src/badcode.c](https://github.com/masscry/badcode/blob/master/src/badcode.c)
    Interpreter implementation;
 * [src/bcLexer.re](https://github.com/masscry/badcode/blob/master/src/bcLexer.re)
    Lexer implementation using re2c;
 * [src/bcParser.y](https://github.com/masscry/badcode/blob/master/src/bcParser.y)
    Parser implementation using LEMON;
 * [src/bcValue.c](https://github.com/masscry/badcode/blob/master/src/bcValue.c)
    BC_VALUE implementation;
 * [src/bcValueStack.c](https://github.com/masscry/badcode/blob/master/src/bcValueStack.c)
    Interpreter BC_VALUE stack implementation;
 * [src/private/bcPrivate.h](https://github.com/masscry/badcode/blob/master/src/private/bcPrivate.h)
    Private BadCode declarations;
 * [src/private/bcValue.h](https://github.com/masscry/badcode/blob/master/src/private/bcValue.h)
    BC_VALUE declarations.
 * [src/private/bcValueStack.h](https://github.com/masscry/badcode/blob/master/src/private/bcValueStack.h)
    Interpreter BC_VALUE stack implementation;
 * [tests/basic.c](https://github.com/masscry/badcode/blob/master/tests/basic.c)
    Simple test program, check whole Read-Eval-Print-Loop.

## How To Build

See [build.sh](https://github.com/masscry/badcode/blob/master/build.sh) script.

```bash
  ./build.sh
```

Build script (aka [CMakeLists.txt](https://github.com/masscry/badcode/blob/master/CMakeLists.txt)
downloads dependencies automaticaly from respective sites.

## Generated sources

 * `${CMAKE_CURRENT_BUILD_DIR}/bcLexer.c`
    Generated lexer from [src/bcLexer.re](https://github.com/masscry/badcode/blob/master/src/bcLexer.re)
 * `${CMAKE_CURRENT_BUILD_DIR}/bcParser.c` `${CMAKE_CURRENT_BUILD_DIR}/bcParser.h`
    Generated parser from [src/bcParser.y](https://github.com/masscry/badcode/blob/master/src/bcParser.y)

