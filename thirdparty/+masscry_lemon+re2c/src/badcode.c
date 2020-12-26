#include <bcPrivate.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

uint32_t bcVersion()
{
  return BC_VER_FULL;
}

bcStatus_t bcCoreNew(BC_CORE* pCore)
{
  if (pCore == NULL)
  {
    return BC_INVALID_ARG;
  }

  BC_CORE result = (BC_CORE) malloc(sizeof(struct bcCore_t));
  if (result == NULL)
  {
    return BC_NO_MEMORY;
  }

  bcStatus_t status = bcValueStackInit(&result->stack, BC_CORE_VALUE_STACK_SIZE);
  if (status != BC_OK)
  {
    free(result);
    return status;
  }

  result->globalCap = BC_CORE_GLOBAL_INITIAL_CAP;
  result->globalSize = 0;
  result->globals = (BC_GLOBAL*) calloc(BC_CORE_GLOBAL_INITIAL_CAP, sizeof(BC_GLOBAL));
  if (result->globals == NULL)
  {
    bcValueStackCleanup(&result->stack);
    free(result);
    return BC_NO_MEMORY;
  }
  result->parseContext.context = NULL;
  result->parseContext.newline = 1;

  memset(result->parseContext.indentStack, 0, sizeof(result->parseContext.indentStack));
  result->parseContext.indentTop = result->parseContext.indentStack;
  result->result = NULL;

  *pCore = result;
  return BC_OK;
}

void bcCoreDelete(BC_CORE core)
{
  if (core != NULL)
  {
    if (core->result != NULL)
    {
      bcValueCleanup(core->result);
    }

    for (BC_GLOBAL* cursor = core->globals, *end = core->globals + core->globalSize; cursor != end; ++cursor)
    {
      bcGlobalDelete(*cursor);
    }
    free(core->globals);

    bcValueStackCleanup(&core->stack);
    free(core);
  }
}

static bcStatus_t bcCodeStreamExecute(BC_CORE core, const bcCodeStream_t* codeStream)
{
  for(const uint8_t* cursor = codeStream->opcodes, *end = codeStream->opcodes + codeStream->opSize; cursor != end; ++cursor)
  {
    switch (*cursor)
    {
    case BC_HALT:
      return BC_OK;
    case BC_PSH:
      {
        ++cursor;
        if (cursor == end)
        {
          return BC_MALFORMED_CODE;
        }

        uint8_t conID = *cursor;
        if (conID >= codeStream->conSize)
        {
          return BC_CONST_NOT_FOUND;
        }

        bcStatus_t status = bcValueStackPush(&core->stack, codeStream->cons[conID]);
        if (status != BC_OK)
        {
          return status;
        }
      }
      break;
    case BC_POP:
    CASE_BC_POP:
      {
        bcStatus_t status = bcValueStackPop(&core->stack);
        if (status != BC_OK)
        {
          return status;
        }
      }
      break;
    case BC_ADD:
    case BC_SUB:
    case BC_MUL:
    case BC_DIV:
    case BC_MOD:
    case BC_EQ:
    case BC_NEQ:
    case BC_GR:
    case BC_LS:
    case BC_GRE:
    case BC_LSE:
    case BC_LND:
    case BC_LOR:
    case BC_BND:
    case BC_BOR: 
    case BC_XOR:
    case BC_BLS:
    case BC_BRS:
      {
        if ((core->stack.top - core->stack.bottom) < 2)
        {
          return BC_UNDERFLOW;
        }

        BC_VALUE result;

        bcStatus_t status = bcValueBinaryOperator(
          core->stack.top[-2],
          core->stack.top[-1],
          *cursor,
          &result
        );

        if (status != BC_OK)
        {
          return status;
        }

        bcValueStackPop(&core->stack);
        bcValueStackPop(&core->stack);
        bcValueStackPush(&core->stack, result);
        bcValueCleanup(result);
      }
      break;
    case BC_SET:
      {
        if ((core->stack.top - core->stack.bottom) < 2)
        {
          return BC_UNDERFLOW;
        }

        BC_VALUE id = core->stack.top[-2];
        if (id->type != BC_STRING)
        {
          return BC_INVALID_ID;
        }

        BC_VALUE result = bcValueCopy(core->stack.top[-1]);

        bcStatus_t status = bcCoreSetGlobal(core, ((bcString_t*)id)->data, core->stack.top[-1]);
        if (status != BC_OK)
        {
          return status;
        }
        bcValueStackPop(&core->stack);
        bcValueStackPop(&core->stack);
        bcValueStackPush(&core->stack, result);
        bcValueCleanup(result);
      }
      break;
    case BC_NEG:
    case BC_LNT:
    case BC_BNT:
    case BC_INT:
    case BC_NUM:
    case BC_STR:
      {
        if ((core->stack.top - core->stack.bottom) < 1)
        {
          return BC_UNDERFLOW;
        }

        BC_VALUE result;

        bcStatus_t status = bcValueUnaryOperator(
          core->stack.top[-1],
          *cursor,
          &result
        );

        if (status != BC_OK)
        {
          return status;
        }

        bcValueStackPop(&core->stack);
        bcValueStackPush(&core->stack, result);
        bcValueCleanup(result);
      }
      break;
    case BC_VAL:
      {
        if ((core->stack.top - core->stack.bottom) < 1)
        {
          return BC_UNDERFLOW;
        }

        BC_VALUE id = core->stack.top[-1];
        if (id->type != BC_STRING)
        {
          return BC_INVALID_ID;
        }

        BC_VALUE result = bcCoreGetGlobal(core, ((bcString_t*)id)->data);
        if (result == NULL)
        {
          return BC_NOT_DEFINED;
        }

        bcValueStackPop(&core->stack);
        bcValueStackPush(&core->stack, result);
        bcValueCleanup(result);
      }
      break;
    case BC_IFS:
      {
        ++cursor;
        if (cursor == end)
        {
          return BC_MALFORMED_CODE;
        }

        if ((core->stack.top - core->stack.bottom) < 1)
        {
          return BC_UNDERFLOW;
        }

        int64_t value;

        bcStatus_t status = bcValueAsInteger(core->stack.top[-1], &value);
        if (status != BC_OK)
        {
          return status;
        }

        bcValueStackPop(&core->stack);

        if (value != 0)
        {
          uint8_t conID = *cursor;
          if (conID >= codeStream->conSize)
          {
            return BC_CONST_NOT_FOUND;
          }

          bcCode_t* code = (bcCode_t*) codeStream->cons[conID];
          if (code->head.type != BC_CODE)
          {
            return BC_MALFORMED_CODE;
          }

          status = bcCodeStreamExecute(core, &code->code);
          if (status != BC_OK)
          {
            return status;
          }
        }
      }
      break;
    case BC_RET:
      {
        if ((core->stack.top - core->stack.bottom) < 1)
        {
          return BC_UNDERFLOW;
        }
        if (core->result != NULL)
        {
          bcValueCleanup(core->result);
        }
        core->result = bcValueCopy(core->stack.top[-1]);
        goto CASE_BC_POP;
      }
      break;
    default:
      fprintf(stderr, "Unknown opcode: 0x%02X\n", *cursor);
      return BC_NOT_IMPLEMENTED;
    }
  }
  return BC_HALT_EXPECTED;
}

bcStatus_t bcCoreExecute(BC_CORE core, const char* code, char** endp)
{
  #define BC_CORE_RETURN(STATUS) coreResult = (STATUS); goto CORE_EXIT

  if ((core == NULL) || (code == NULL))
  {
    return BC_INVALID_ARG;
  }

  bcTree_t* tree = NULL;
  bcStatus_t coreResult = bcParseString(code, &tree, endp, &core->parseContext);
  if (coreResult != BC_OK)
  {
    return coreResult;
  }

  if (tree->root == NULL)
  {
    bcTreeCleanup(tree);
    return BC_EMPTY_EXPR;
  }

  bcCodeStream_t codeStream;
  coreResult = bcCodeStreamInit(&codeStream);
  if (coreResult != BC_OK)
  {
    bcTreeCleanup(tree);
    return coreResult;
  }

  coreResult = bcCodeStreamCompile(&codeStream, tree);
  if (coreResult != BC_OK)
  {
    bcTreeCleanup(tree);
    bcCodeStreamCleanup(&codeStream);
    return coreResult;
  }

  bcTreeCleanup(tree);

  coreResult = bcCodeStreamExecute(core, &codeStream);
  bcCodeStreamCleanup(&codeStream);
  return coreResult;
}

BCAPI bcStatus_t bcCoreTop(const BC_CORE core, BC_VALUE* val)
{
  if ((core == NULL) || (val == NULL))
  {
    return BC_INVALID_ARG;
  }

  if (core->stack.top == core->stack.bottom)
  {
    return BC_UNDERFLOW;
  }

  *val = core->stack.top[-1];
  return BC_OK;
}

BCAPI bcStatus_t bcCoreResult(const BC_CORE core, BC_VALUE* pVal)
{
  if ((core == NULL) || (pVal == NULL))
  {
    return BC_INVALID_ARG;
  }

  *pVal = core->result;
  return BC_OK;
}

BCAPI bcStatus_t bcCorePop(BC_CORE core)
{
  if (core == NULL)
  {
    return BC_INVALID_ARG;
  }

  if (core->stack.top == core->stack.bottom)
  {
    return BC_UNDERFLOW;
  }

  bcValueCleanup(core->stack.top[-1]);
  --core->stack.top;
  return BC_OK;
}

BC_VALUE bcValueCode(const bcTree_t* parseTree)
{
  bcCode_t* result = (bcCode_t*) malloc(sizeof(bcCode_t));
  if (result == NULL)
  {
    return NULL;
  }

  result->head.type = BC_CODE;
  result->head.refCount = 1;

  bcStatus_t status = bcCodeStreamInit(&result->code);
  if (status != BC_OK)
  {
    free(result);
    return NULL;
  }

  status = bcCodeStreamCompile(&result->code, parseTree);
  if (status != BC_OK)
  {
    bcCodeStreamCleanup(&result->code);
    free(result);
    return NULL;
  }

  return &result->head;
}

BCAPI const char* bcStatusString(bcStatus_t status)
{
  switch (status)
  {
    case BC_OK:
      return "OK";
    case BC_INVALID_ARG:
      return "INVALID_ARG";
    case BC_NOT_IMPLEMENTED:
      return "NOT_IMPLEMENTED";
    case BC_NO_MEMORY:
      return "NO_MEMORY";
    case BC_TOO_MANY_CONSTANTS:
      return "TOO_MANY_CONSTANTS";
    case BC_UNDERFLOW:
      return "UNDERFLOW";
    case BC_OVERFLOW:
      return "OVERFLOW";
    case BC_MALFORMED_CODE:
      return "MALFORMED_CODE";
    case BC_CONST_NOT_FOUND:
      return "CONST_NOT_FOUND";
    case BC_HALT_EXPECTED:
      return "HALT_EXPECTED";
    case BC_DIVIDE_BY_ZERO:
      return "DIVIDE_BY_ZERO";
    case BC_CANT_CONVERT:
      return "CANT_CONVERT";
    case BC_TOO_SMALL:
      return "TOO_SMALL";
    case BC_INVALID_ID:
      return "INVALID_ID";
    case BC_NOT_DEFINED:
      return "NOT_DEFINED";
    case BC_PARSE_NOT_FINISHED:
      return "PARSE_NOT_FINISHED";
    default:
      return "???";
  }
}
