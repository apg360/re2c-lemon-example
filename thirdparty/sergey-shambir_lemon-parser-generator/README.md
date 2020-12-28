# lemon-parser-generator
Lemon parser generator &mdash; the modern C parser generator, extracted from SQLite sources
- `lemon.c` keeps Lemon implementation
- `lempar.c` is template file for code generation

You should distribute `lemon` executable and `lempar.c` template file together

## How to Build
With CMake and Visual Studio 2015:
```bash
cmake -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 2015" .
# now open lemon.sln and build
```
With CMake on Linux:
```bash
cmake -DCMAKE_BUILD_TYPE=Release . && make -s
```
You can also build `lemon.c` manually.

## Command line syntax

Example usage:

```bash
# Generates CalcGrammar.h CalcGrammar.cpp
lemon -q -s -l CalcGrammar.lemon

# If you prefer C++, just rename .c to .cpp
rm -f CalcGrammar.cpp
mv CalcGrammar.c CalcGrammar.cpp
```

Valid command line options for "lemon" are:

```
  -b           Print only the basis in report.
  -c           Don't compress the action table.
  -D<string>   Define an %ifdef macro.
  -f<string>   Ignored.  (Placeholder for -f compiler options.)
  -g           Print grammar without actions.
  -I<string>   Ignored.  (Placeholder for '-I' compiler options.)
  -m           Output a makeheaders compatible file.
  -l           Do not print #line statements.
  -O<string>   Ignored.  (Placeholder for '-O' compiler options.)
  -p           Show conflicts resolved by precedence rules
  -q           (Quiet) Don't print the report file.
  -r           Do not sort or renumber states
  -s           Print parser stats to standard output.
  -x           Print the version number.
  -T<string>   Specify a template file.
  -W<string>   Ignored.  (Placeholder for '-W' compiler options.)
```

## Small Grammar Example


The example below generates the following header:

```c
#define TK_PLUS                            1
#define TK_MINUS                           2
#define TK_STAR                            3
#define TK_SLASH                           4
#define TK_PERCENT                         5
#define TK_LPAREN                          6
#define TK_RPAREN                          7
#define TK_NUMBER                          8
```

And also source files which declares following functions:

```c
void *ParseCalcGrammarAlloc(void *(*mallocProc)(size_t));

// CCalcParser* is our extra argument, see `%extra_argument` directive in grammar
void ParseCalcGrammar(void*, int, Token, CCalcParser*);

void ParseCalcGrammarFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */);
#ifndef NDEBUG
void ParseCalcGrammarTrace(FILE * TraceFILE, char * zTracePrompt);
#endif
```

- names of generated function depend on `%name` directive, e.g. `%name ParseCalcGrammar`
- extra argument passed with `%extra_argument {CCalcParser *pParse}`
- token type set with `%token_type {Token}`
- `ParseCalcGrammarAlloc` constructs new parser object using function pointer to allocate memory
- `ParseCalcGrammar` consumes one token and advances parser state
- `ParseCalcGrammarFree` destructs parser object using function pointer to free memory
- `ParseCalcGrammarTrace` is debug-only function to enable state transitions and LALR stack tracing during `ParseCalcGrammar(...)` calls

This is grammar example:

```c
// All token codes are small integers with #defines that begin with "TK_"
%token_prefix TK_

// The type of the data attached to each token is Token.  This is also the
// default type for non-terminals.
//
%token_type {Token}
%default_type {Token}

// The generated parser function takes a 4th argument as follows:
%extra_argument {CCalcParser *pParse}

// This code runs whenever there is a syntax error
//
%syntax_error {
    (void)yymajor;  // Silence some compiler warnings
    pParse->OnError(TOKEN); // TOKEN has type defined in '%token_type'
}

// This code runs on LALR stack overflow
%stack_overflow {
    (void)yypMinor; // Silence compiler warnings.
    pParse->OnStackOverflow();
}

// Destructor set just to disable compiler warnings
//
%token_destructor {
    (void)yypParser;
    (void)yypminor;
    (void)pParse;
}

// The name of the generated procedure that implements the parser
// is as follows:
%name ParseCalcGrammar

// The following text is included near the beginning of the C source
// code file that implements the parser.
//
%include {
// Generated function: void ParseCalcGrammar(void*, int, Token, CCalcParser*);

#include "Token.h"
#include "CalcParser.h"
#include <assert.h>
#include <math.h>

// Disable all error recovery processing in the parser push-down automaton.
#define YYNOERRORRECOVERY 1
// Indicate that ParseCalcGrammarFree() will never be called with a nullptr.
#define YYPARSEFREENEVERNULL 1

struct SRecord
{
    double value;
};

} // end %include

/////////////////////////
////////////////////////
///////////////////////

// An IDENTIFIER can be a generic identifier, or one of several
// keywords.  Any non-standard keyword can also be an identifier.
//
%type expression SRecord
%left PLUS MINUS.
%left STAR SLASH PERCENT.

translation_unit ::= expression(A).
{
    pParse->PrintResult(A.value);
}

expression(X) ::= LPAREN expression(A) RPAREN.
{
    X.value = A.value;
}

expression(X) ::= expression(A) PLUS expression(B).
{
    X.value = A.value + B.value;
}

expression(X) ::= expression(A) MINUS expression(B).
{
    X.value = A.value - B.value;
}

expression(X) ::= expression(A) STAR expression(B).
{
    X.value = A.value * B.value;
}

expression(X) ::= expression(A) SLASH expression(B).
{
    X.value = A.value / B.value;
}

expression(X) ::= expression(A) PERCENT expression(B).
{
    X.value = fmod(A.value, B.value);
}

expression(X) ::= PLUS expression(A).
{
    X.value = A.value;
}

expression(X) ::= MINUS expression(A).
{
    X.value = -A.value;
}

expression(X) ::= NUMBER(A).
{
    X.value = A.value;
}
```

## Object-Oriented Wrapper Class

We merged header and cpp file here, actually you should separate them:

```cpp
#include "Token.h"
#include <stdlib.h>
#include <new>
#include <iostream>


// pre-declaration of generated functions.
void *ParseCalcGrammarAlloc(void *(*mallocProc)(size_t));
void ParseCalcGrammar(void*, int, Token, CCalcParser*);
void ParseCalcGrammarFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */);
#ifndef NDEBUG
void ParseCalcGrammarTrace(FILE * TraceFILE, char * zTracePrompt);
#endif


class CCalcParser
{
public:
    CCalcParser()
    {
        // This lambda has no capture and can be converted to function pointer.
        auto allocate = [](size_t size) -> void* {
            return new (std::nothrow) char[size];
        };
        m_parser = ParseCalcGrammarAlloc(allocate);
    }

    ~CCalcParser()
    {
        // This lambda has no capture and can be converted to function pointer.
        auto retain = [](void *pointer) -> void {
            auto array = reinterpret_cast<char *>(pointer);
            delete[] array;
        };
        ParseCalcGrammarFree(m_parser, retain);
    }

    bool Advance(int tokenId, const Token &tokenData)
    {
        ParseCalcGrammar(m_parser, tokenId, tokenData, this);
        return !m_isErrorState;
    }

#ifndef NDEBUG
    void StartDebugTrace(FILE *output)
    {
        m_tracePrompt = "";
        ParseCalcGrammarTrace(output, &m_tracePrompt[0]);
    }
#endif

    void OnError(const Token &token)
    {
        std::cerr << "Syntax error at position " << token.position << std::endl;
        m_isErrorState = true;
    }

    void OnStackOverflow()
    {
        std::cerr << "LALR parser stack overflow occured." << std::endl;
        m_isErrorState = true;
    }

    void PrintResult(double value)
    {
        std::cerr << value << std::endl;
    }

private:
#ifndef NDEBUG
    // C++ code owns trace prompt memory, even for empty prompt.
    std::string m_tracePrompt;
#endif
    bool m_isErrorState = false;
    void *m_parser = nullptr;
};
```
