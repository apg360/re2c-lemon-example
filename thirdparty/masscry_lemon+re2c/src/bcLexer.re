/*!re2c re2c:flags:i = 0; */

/*!max:re2c*/
/*!re2c
    id = [a-zA-Z_][a-zA-Z_0-9]*;
    string = ["][^"]*["];
    digit = [0-9];
    integer = digit+;
    spaces = [\t ]+;
    add = '+';
    sub = '-';
    mul = '*';
    div = '/';
    mod = '%';
    eq = '=';
    neq = '!=';
    gr = '>';
    ls = '<';
    gre = '>=';
    lse = '<=';
    lnd = '&&';
    lor = '||';
    bnd = '&';
    bor = '|';
    xor = '^';
    bls = '<<';
    brs = '>>';
    openbr = '(';
    closebr = ')';
    lnot = '!';
    bnot = '~';
    frac = [0-9]* "." [0-9]+ | [0-9]+ ".";
    exp = 'e' [+-]? [0-9]+;
    number = (frac exp? | [0-9]+ exp);
    int = 'int';
    num = 'num';
    str = 'str';
    set = '<-';
*/

#include <bcParser.h>
#include <bcPrivate.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const char* AfterSpaces(const char* head)
{
  assert(head != NULL);
  while((*head == ' ') || (*head == '\t'))
  {
    ++head;
  }
  return head;
}

int bcGetToken(const char* head, const char** tail, BC_VALUE* pData, bcParseContext_t* parseContext)
{
  // head - first character of new token
  // YYCURSOR - last character of new token

  const uint8_t* YYMARKER; // inner lexer variable is used when there can be longer string to match
  const uint8_t* YYCURSOR = (const uint8_t*) head; // initialize cursor to first character position

  if (parseContext->newline != 0)
  {
    const char* afterSpaces = AfterSpaces(head);
    int newIndent = (int)(afterSpaces - head);

    if (newIndent > *parseContext->indentTop)
    {
      ++parseContext->indentTop;
      *parseContext->indentTop = newIndent;

      *pData = NULL;
      return TOK_INDENT;
    }

    if (newIndent < *parseContext->indentTop)
    {
      --parseContext->indentTop;
      if (newIndent > *parseContext->indentTop)
      { // tab error!
        *pData = NULL;
        return 0;
      }

      *pData = NULL;
      return TOK_DEDENT;
    }
    parseContext->newline = 0;
    head = afterSpaces;
  }

GET_NEXT_TOKEN: // jump to this label, if processed token is skipped (like spaces)
  /*!re2c

    re2c:define:YYCTYPE = uint8_t;
    re2c:yyfill:enable = 0; // this disable interactive character read

    * {
      // Exit with error on any unknown symbols.
      fprintf(stderr, "Unknown Symbol: '%c' (0x%02x)\n", *head, *head);
      *tail = head;
      return 0;
    }

    '\n' {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      parseContext->newline = 1;
      return TOK_EXPR_END;
    }

    '\\' [ \t]* '\n'? '\x00' {
      // code continues on next line
      *tail = (const char*) (YYCURSOR - 1); // leave \0 at tail for safety
      *pData = NULL;
      parseContext->newline = 0; // do not count for indentation
      return -1; // special token, tells that more data expected
    }

    '\\' [ \t]* '\n' {
      // Skips any amount of spaces, tabs and newlines.
      head = (const char*) YYCURSOR;
      parseContext->newline = 0; // do not count for indentation
      goto GET_NEXT_TOKEN;
    }

    ':' [ \t]* '\n' {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      parseContext->newline = 1; 
      return TOK_BLOCK;
    }

    set {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_SET;
    }

    str {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_STR;
    }

    int {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_INT;
    }

    num {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_NUM;
    }

    lnot {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_LNOT;
    }

    bnot {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_BNOT;
    }

    openbr {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_OPENBR;
    }

    closebr {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_CLOSEBR;
    }

    add {
      // '+'
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_ADD;
    }

    sub {
      // '-'
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_SUB;
    }

    mul {
      // '*'
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_MUL;
    }
    
    div {
      // '/'
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_DIV;
    }

    mod {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_MOD;
    }

    eq  {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_EQ;
    }

    neq {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_NEQ;
    }

    gr {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_GR;
    }

    ls {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_LS;
    }

    gre {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_GRE;
    }

    lse {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_LSE;
    }

    lnd {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_LND;
    }

    lor {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_LOR;
    }

    bnd {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_BND;
    }

    bor {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_BOR;
    }

    xor {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_XOR;
    }

    bls {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_BLS;
    }

    brs {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_BRS;
    }

    spaces {
      // Skips any amount of spaces, tabs and newlines.
      head = (const char*) YYCURSOR;
      goto GET_NEXT_TOKEN;
    }

    'if' {
      *tail = (const char*) YYCURSOR;
      *pData = NULL;
      return TOK_IF;
    }

    integer {
      // Simple C integer.

      char* tmpInteger = (char*) malloc((size_t)((YYCURSOR - (const uint8_t*) head) + 1));
      if (tmpInteger == NULL)
      { // no memory error, we need better error checking!
        assert(0);
        *tail = (const char*) YYCURSOR;
        return TOK_EXPR_END;
      }

      memcpy(tmpInteger, head, (size_t)(YYCURSOR - (const uint8_t*) head)); // copy token symbols to temp buffer
      tmpInteger[YYCURSOR - (const uint8_t*) head] = 0;
      *pData = bcValueInteger(strtoll(tmpInteger, NULL, 10));
      // currently there are no checks for strtoll produced a valid integer.

      free(tmpInteger);

      *tail = (const char*) YYCURSOR;
      return TOK_CONSTANT;
    }

    number {
      // Simple C float

      char* tmpNumber = (char*) malloc((size_t)((YYCURSOR - (const uint8_t*) head) + 1));
      if (tmpNumber == NULL)
      { // no memory error, we need better error checking!
        assert(0);
        *tail = (const char*) YYCURSOR;
        return TOK_EXPR_END;
      }

      memcpy(tmpNumber, head, (size_t)(YYCURSOR - (const uint8_t*) head)); // copy token symbols to temp buffer
      tmpNumber[YYCURSOR - (const uint8_t*) head] = 0;
      *pData = bcValueNumber(strtod(tmpNumber, NULL));
      // currently there are no checks for strtod produced a valid number

      free(tmpNumber);

      *tail = (const char*) YYCURSOR;
      return TOK_CONSTANT;
    }

    string {
      char* tmpString = (char*) malloc((size_t)((YYCURSOR - (const uint8_t*)(head+1))));
      if (tmpString == NULL)
      { // no memory error, we need better error checking!
        assert(0);
        *tail = (const char*) YYCURSOR;
        return TOK_EXPR_END;
      }

      memcpy(tmpString, head+1, (size_t)(YYCURSOR - (const uint8_t*)(head+1) - 1)); // copy token symbols to temp buffer
      tmpString[YYCURSOR - (const uint8_t*)(head+1)-1] = 0;

      *pData = bcValueString(tmpString);

      free(tmpString);

      *tail = (const char*) YYCURSOR;
      return TOK_CONSTANT;
    }

    id {
      char* tmpString = (char*) malloc((size_t)((YYCURSOR - (const uint8_t*)head) + 1));
      if (tmpString == NULL)
      { // no memory error, we need better error checking!
        assert(0);
        *tail = (const char*) YYCURSOR;
        return TOK_EXPR_END;
      }

      memcpy(tmpString, head, (size_t)(YYCURSOR - (const uint8_t*)head)); // copy token symbols to temp buffer
      tmpString[YYCURSOR - (const uint8_t*)head] = 0;

      *pData = bcValueString(tmpString);

      free(tmpString);

      *tail = (const char*) YYCURSOR;
      return TOK_ID;
    }

  */

}
