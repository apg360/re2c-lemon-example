%token_type {BC_VALUE}
%token_destructor { if ($$ != NULL) { bcValueCleanup($$); }; }
%token_prefix TOK_
%extra_argument { bcTree_t** tree }
%start_symbol program

%default_type { bcTreeItem_t* }
%default_destructor { if ($$ != NULL) { bcTreeItemCleanup($$); } }

%right SET.
%left LOR.
%left LND.
%left BOR.
%left XOR.
%left BND.
%nonassoc EQ NEQ.
%nonassoc GR GRE LS LSE.
%left BLS BRS.
%left ADD SUB.
%left DIV MUL MOD.
%right LNOT BNOT.
%right INT NUM STR.

%include {
  #include <bcPrivate.h>
  #include <bcParseTree.h>

  #include <stdio.h>
  #include <stdlib.h>
  #include <stdint.h>

}

%syntax_error {
  fprintf(stderr, "Syntax Error: Unexpected token %s (%d)\n", yyTokenName[yymajor], yymajor);
}

program ::= statementList(LIST). { *tree = bcTree(LIST);  }

statementList(RESULT) ::= statementList(HEAD) statement(TAIL). { if (HEAD == NULL) { RESULT = TAIL; } else { RESULT = bcAppend(HEAD, TAIL); } }
statementList(RESULT) ::= statement(HEAD). { RESULT = HEAD; }

statement(RESULT) ::= IF rightExpr(COND) BLOCK INDENT statementList(BODY) DEDENT. {
  RESULT = bcIfStatement(COND, BODY);
}

statement(RESULT) ::= rightExpr(HEAD) EXPR_END. { RESULT = bcUnOp(HEAD, BC_RET); }
statement(RESULT) ::= EXPR_END. { RESULT = NULL; }

rightExpr(RESULT) ::=  leftExpr(LHS) SET rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_SET); }
rightExpr(RESULT) ::= rightExpr(LHS) LOR rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_LOR); }
rightExpr(RESULT) ::= rightExpr(LHS) LND rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_LND); }
rightExpr(RESULT) ::= rightExpr(LHS) BOR rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_BOR); }
rightExpr(RESULT) ::= rightExpr(LHS) XOR rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_XOR); }
rightExpr(RESULT) ::= rightExpr(LHS) BND rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_BND); }
rightExpr(RESULT) ::= rightExpr(LHS) EQ  rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_EQ);  }
rightExpr(RESULT) ::= rightExpr(LHS) NEQ rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_NEQ); }
rightExpr(RESULT) ::= rightExpr(LHS) GR  rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_GR);  }
rightExpr(RESULT) ::= rightExpr(LHS) GRE rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_GRE); }
rightExpr(RESULT) ::= rightExpr(LHS) LS  rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_LS);  }
rightExpr(RESULT) ::= rightExpr(LHS) LSE rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_LSE); }
rightExpr(RESULT) ::= rightExpr(LHS) BLS rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_BLS); }
rightExpr(RESULT) ::= rightExpr(LHS) BRS rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_BRS); }
rightExpr(RESULT) ::= rightExpr(LHS) SUB rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_SUB); }
rightExpr(RESULT) ::= rightExpr(LHS) ADD rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_ADD); }
rightExpr(RESULT) ::= rightExpr(LHS) MUL rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_MUL); }
rightExpr(RESULT) ::= rightExpr(LHS) DIV rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_DIV); }
rightExpr(RESULT) ::= rightExpr(LHS) MOD rightExpr(RHS). { RESULT = bcBinOp(LHS, RHS, BC_MOD); }
rightExpr(RESULT) ::= OPENBR rightExpr(EXPR) CLOSEBR.    { RESULT = EXPR; }
rightExpr(RESULT) ::= LNOT rightExpr(BR).                { RESULT = bcUnOp(BR, BC_LNT); }
rightExpr(RESULT) ::= BNOT rightExpr(BR).                { RESULT = bcUnOp(BR, BC_BNT); }
rightExpr(RESULT) ::= SUB rightExpr(BR). [LNOT]          { RESULT = bcUnOp(BR, BC_NEG); }
rightExpr(RESULT) ::= OPENBR INT CLOSEBR rightExpr(BR).  { RESULT = bcUnOp(BR, BC_INT); }
rightExpr(RESULT) ::= OPENBR NUM CLOSEBR rightExpr(BR).  { RESULT = bcUnOp(BR, BC_NUM); }
rightExpr(RESULT) ::= OPENBR STR CLOSEBR rightExpr(BR).  { RESULT = bcUnOp(BR, BC_STR); }

rightExpr(RESULT) ::= CONSTANT(VALUE). {
  RESULT = bcConstant(VALUE);
  bcValueCleanup(VALUE);
}

rightExpr(RESULT) ::= leftExpr(BR). {
  RESULT = bcUnOp(BR, BC_VAL);
}

leftExpr(RESULT) ::= ID(NAME). {
  RESULT = bcConstant(NAME),
  bcValueCleanup(NAME);
}

%code {

  #include "bcParser.h"

  bcStatus_t bcParseString(const char* str, bcTree_t** parseTree, char** endp, bcParseContext_t* parseContext)
  {
    if ((parseTree == NULL) || (str == NULL) || (parseContext == NULL))
    {
      return BC_INVALID_ARG;
    }

    void* parser = NULL;

    if (parseContext->context == NULL)
    {
      parser = ParseAlloc(malloc);
    }
    else
    {
      parser = parseContext->context;
    }

    if (parser == NULL)
    {
      if (endp != NULL)
      {
        *endp = (char*) str;
      }
      return BC_NO_MEMORY;
    }

    BC_VALUE tmptok = NULL;
    const char* cursor = str;

//    ParseTrace(stderr, "trace: ");

    //
    // I didn't found info on how properly raise internal errors from parser,
    // Internet says, that parsing context must have some error flags when 
    // some internal error happened and break on parsing in outer loop.
    //
    // So, now we just don't do any checks.
    //
    // Later, I'll add them.
    //

    bcTree_t* tree = NULL;

    int prevTok;
    for(int tok = bcGetToken(cursor, &cursor, &tmptok, parseContext); tok != 0; tok = bcGetToken(cursor, &cursor, &tmptok, parseContext))
    {
      if (tok == -1)
      { // special case, when more data expected
        parseContext->context = parser;
        return BC_PARSE_NOT_FINISHED;
      }

      Parse(parser, tok, bcValueCopy(tmptok), &tree);
      bcValueCleanup(tmptok);
      tmptok = NULL;
      prevTok = tok;

      if (*cursor == '\0')
      {
        break;
      }
    }

    if ((prevTok == TOK_BLOCK) || (parseContext->indentTop != parseContext->indentStack))
    { // not all block were closed
      parseContext->context = parser;
      return BC_PARSE_NOT_FINISHED;
    }

    // When no more tokens are available, we need to give parser to know about it.
    Parse(parser, 0, 0, &tree);

    //
    // Here parser done it's job and dies
    //
    ParseFree(parser, free);

    *parseTree = tree;
    parseContext->context = NULL;
    if (endp != NULL)
    {
      *endp = (char*) cursor;
    }
    return BC_OK;
  }

}