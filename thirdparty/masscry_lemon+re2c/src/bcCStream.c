#include <bcPrivate.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

bcStatus_t bcCodeStreamInit(bcCodeStream_t* cs)
{
  uint8_t* opcodes = (uint8_t*) calloc(BC_CODE_STREAM_INITIAL_OPCODE_CAP, sizeof(uint8_t));
  if (opcodes == NULL)
  {
    return BC_NO_MEMORY;
  }

  BC_VALUE* cons = (BC_VALUE*) calloc(BC_CODE_STREAM_INITIAL_CONST_CAP, sizeof(BC_VALUE));
  if (cons == NULL)
  {
    free(opcodes);
    return BC_NO_MEMORY;
  }

  cs->opcodes = opcodes;
  cs->opSize = 0;
  cs->opCap = BC_CODE_STREAM_INITIAL_OPCODE_CAP;

  cs->cons = cons;
  cs->conSize = 0;
  cs->conCap = BC_CODE_STREAM_INITIAL_CONST_CAP;
  return BC_OK;
}

bcStatus_t bcCodeStreamCleanup(bcCodeStream_t* cs)
{
  free(cs->opcodes);
  cs->opcodes = NULL;
  cs->opSize = 0;
  cs->opCap = 0;

  for (BC_VALUE* cursor = cs->cons, *end = cs->cons+cs->conSize;  cursor!=end; ++cursor)
  {
    bcValueCleanup(*cursor);
  }
  free(cs->cons);
  cs->cons = NULL;
  cs->conSize = 0;
  cs->conCap = 0;
  return BC_OK;
}

bcStatus_t bcCodeStreamAppendOpcode(bcCodeStream_t* cs, uint8_t opcode)
{
  if (cs == NULL) 
  {
    return BC_INVALID_ARG;
  }

  if (cs->opSize == cs->opCap)
  {
    uint8_t* newCodes = (uint8_t*) calloc(cs->opCap*3/2, sizeof(uint8_t));
    if (newCodes == NULL)
    {
      return BC_NO_MEMORY;
    }

    memcpy(newCodes, cs->opcodes, cs->opCap*sizeof(uint8_t));
    free(cs->opcodes);

    cs->opcodes = newCodes;
    cs->opCap = cs->opCap*3/2;
  }

  cs->opcodes[cs->opSize++] = opcode;
  return BC_OK;
}

bcStatus_t bcCodeStreamAppendConstant(bcCodeStream_t* cs, const BC_VALUE con, uint8_t* pCon)
{
  if ((cs == NULL) || (pCon == NULL) || (con == NULL))
  {
    return BC_INVALID_ARG;
  }

  if (cs->conSize == (UINT8_MAX+1))
  {
    return BC_TOO_MANY_CONSTANTS;
  }

  if (cs->conSize == cs->conCap)
  {
    BC_VALUE* newCons = (BC_VALUE*) calloc(cs->conCap*3/2, sizeof(BC_VALUE));
    if (newCons == NULL)
    {
      return BC_NO_MEMORY;
    }

    memcpy(newCons, cs->cons, cs->conCap*sizeof(BC_VALUE));
    free(cs->cons);

    cs->cons = newCons;
    cs->conCap = cs->conCap*3/2;
  }

  *pCon = (uint8_t) (cs->conSize & 0xFF);
  cs->cons[cs->conSize++] = bcValueCopy(con);
  return BC_OK;  
}

static bcStatus_t bcCodeStreamProduce(bcCodeStream_t* cs, const bcTreeItem_t* item)
{
  if ((cs == NULL) || (item == NULL))
  {
    return BC_INVALID_ARG;
  }

  for (const bcTreeItem_t* cursor = item; cursor != NULL; cursor = cursor->next)
  {
    switch (cursor->type)
    {
    case TIT_BIN_OP:
      {
        bcBinOp_t* binop = (bcBinOp_t*) cursor;
        bcStatus_t status = bcCodeStreamProduce(cs, binop->lbr);
        if (status != BC_OK)
        {
          return status;
        }
        status = bcCodeStreamProduce(cs, binop->rbr);
        if (status != BC_OK)
        {
          return status;
        }
        status = bcCodeStreamAppendOpcode(cs, (uint8_t) binop->tag);
        if (status != BC_OK)
        {
          return status;
        }
      }
      break;
    case TIT_UN_OP:
      {
        bcUnOp_t* unop = (bcUnOp_t*) cursor;
        bcStatus_t status = bcCodeStreamProduce(cs, unop->br);
        if (status != BC_OK)
        {
          return status;
        }

        status = bcCodeStreamAppendOpcode(cs, (uint8_t) unop->tag);
        if (status != BC_OK)
        {
          return status;
        }
      }
      break;
    case TIT_CONSTANT:
      {
        bcConstant_t* cns = (bcConstant_t*) cursor;
        uint8_t conCode;
        bcStatus_t status = bcCodeStreamAppendConstant(cs, cns->constVal, &conCode);
        if (status != BC_OK)
        {
          return status;
        }
        status = bcCodeStreamAppendOpcode(cs, BC_PSH);
        if (status != BC_OK)
        {
          return status;
        }
        status = bcCodeStreamAppendOpcode(cs, conCode);
        if (status != BC_OK)
        {
          return status;
        }
      }
      break;
    case TIT_IF_STATEMENT:
      {
        bcIfStatement_t* ifstat = (bcIfStatement_t*) cursor;
        BC_VALUE compiledBody = bcValueCode(ifstat->body);
        if (compiledBody == NULL)
        {
          return BC_NO_MEMORY;
        }

        uint8_t conCode;
        bcStatus_t status = bcCodeStreamAppendConstant(cs, compiledBody, &conCode);
        bcValueCleanup(compiledBody);
        if (status != BC_OK)
        {
          return status;
        }

        status = bcCodeStreamProduce(cs, ifstat->cond);
        if (status != BC_OK)
        {
          return status;
        }

        status = bcCodeStreamAppendOpcode(cs, BC_IFS);
        if (status != BC_OK)
        {
          return status;
        }
        status = bcCodeStreamAppendOpcode(cs, conCode);
        if (status != BC_OK)
        {
          return status;
        }
      }
      break;
    default:
      return BC_NOT_IMPLEMENTED;
    }
  }
  return BC_OK;
}

bcStatus_t bcCodeStreamCompile(bcCodeStream_t* cs, const bcTree_t* tree)
{
  if ((cs == NULL) || (tree == NULL))
  {
    return BC_INVALID_ARG;
  }

  if (tree->root != NULL)
  {
    bcStatus_t result = bcCodeStreamProduce(cs, tree->root);
    if (result != BC_OK)
    {
      return result;
    }
  }
  return bcCodeStreamAppendOpcode(cs, BC_HALT);
}
