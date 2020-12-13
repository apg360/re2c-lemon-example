#include <bcPrivate.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

bcDataType_t bcPromote(const BC_VALUE a, const BC_VALUE b)
{
  switch (a->type)
  {
  case BC_INTEGER:
    switch (b->type)
    {
    case BC_INTEGER:
      return BC_INTEGER;
    case BC_NUMBER:
      return BC_NUMBER;
    default:
      return BC_NULL;
    }
  case BC_NUMBER:
    switch (b->type)
    {
    case BC_INTEGER:
    case BC_NUMBER:
      return BC_NUMBER;
    default:
      return BC_NULL;
    }
  default:
    if (b->type != a->type)
    { // invalid conversion
      return BC_NULL;
    }
    return a->type;
  }
}

bcStatus_t bcValueBinaryOperatorAlgebra(const BC_VALUE a, const BC_VALUE b, uint8_t binop, BC_VALUE* result)
{
  assert((result != NULL) && (a != NULL) && (b != NULL));

  bcDataType_t promotedType = bcPromote(a, b);
  if (promotedType == BC_NULL)
  {
    return BC_NOT_IMPLEMENTED;
  }

  switch (promotedType)
  {
    case BC_NULL:
    default:
      return BC_NOT_IMPLEMENTED;
    case BC_INTEGER:
      {
        int64_t aVal;
        int64_t bVal;
        bcValueAsInteger(a, &aVal);
        bcValueAsInteger(b, &bVal);
        switch (binop)
        {
        case BC_ADD:
          aVal += bVal;
          break;
        case BC_SUB:
          aVal -= bVal;
          break;
        case BC_MUL:
          aVal *= bVal;
          break;
        case BC_DIV:
          if (bVal == 0)
          {
            return BC_DIVIDE_BY_ZERO;
          }
          aVal /= bVal;
          break;
        case BC_MOD:
          if (bVal == 0)
          {
            return BC_DIVIDE_BY_ZERO;
          }
          aVal %= bVal;
          break;
        default:
          return BC_NOT_IMPLEMENTED;
        }
        *result = bcValueInteger(aVal);
        return BC_OK;
      }
    case BC_NUMBER:
      {
        double aVal;
        double bVal;
        bcValueAsNumber(a, &aVal);
        bcValueAsNumber(b, &bVal);
        switch (binop)
        {
        case BC_ADD:
          aVal += bVal;
          break;
        case BC_SUB:
          aVal -= bVal;
          break;
        case BC_MUL:
          aVal *= bVal;
          break;
        case BC_DIV:
          aVal /= bVal;
          break;
        case BC_MOD:
          aVal = fmod(aVal, bVal);
          break;
        default:
          return BC_NOT_IMPLEMENTED;
        }
        *result = bcValueNumber(aVal);
        return BC_OK;
      }
  }
}

bcStatus_t bcValueBinaryOperatorCompare(const BC_VALUE a, const BC_VALUE b, uint8_t binop, BC_VALUE* result)
{
  assert((result != NULL) && (a != NULL) && (b != NULL));

  bcDataType_t promotedType = bcPromote(a, b);
  if (promotedType == BC_NULL)
  {
    return BC_NOT_IMPLEMENTED;
  }

  switch (promotedType)
  {
    case BC_NULL:
    default:
      return BC_NOT_IMPLEMENTED;
    case BC_INTEGER:
      {
        int64_t aVal;
        int64_t bVal;
        int64_t cmpResult;
        bcValueAsInteger(a, &aVal);
        bcValueAsInteger(b, &bVal);
        switch (binop)
        {
        case BC_EQ:
          cmpResult = (aVal == bVal);
          break;
        case BC_NEQ:
          cmpResult = (aVal != bVal);
          break;
        case BC_GR:
          cmpResult = (aVal > bVal);
          break;
        case BC_LS:
          cmpResult = (aVal < bVal);
          break;
        case BC_GRE:
          cmpResult = (aVal >= bVal);
          break;
        case BC_LSE:
          cmpResult = (aVal <= bVal);
          break;
        default:
          return BC_NOT_IMPLEMENTED;
        }
        *result = bcValueInteger(cmpResult);
        return BC_OK;
      }
    case BC_NUMBER:
      {
        double aVal;
        double bVal;
        int64_t cmpResult;
        bcValueAsNumber(a, &aVal);
        bcValueAsNumber(b, &bVal);
        switch (binop)
        {
        case BC_EQ:
          cmpResult = (aVal == bVal);
          break;
        case BC_NEQ:
          cmpResult = (aVal != bVal);
          break;
        case BC_GR:
          cmpResult = (aVal > bVal);
          break;
        case BC_LS:
          cmpResult = (aVal < bVal);
          break;
        case BC_GRE:
          cmpResult = (aVal >= bVal);
          break;
        case BC_LSE:
          cmpResult = (aVal <= bVal);
          break;
        default:
          return BC_NOT_IMPLEMENTED;
        }
        *result = bcValueInteger(cmpResult);
        return BC_OK;
      }
  }
}

bcStatus_t bcValueBinaryOperatorLogicBitwise(const BC_VALUE a, const BC_VALUE b, uint8_t binop, BC_VALUE* result)
{
  assert((result != NULL) && (a != NULL) && (b != NULL));

  if ((a->type != BC_INTEGER) || (b->type != BC_INTEGER))
  {
    return BC_NOT_IMPLEMENTED;
  }
  int64_t aVal;
  int64_t bVal;

  bcValueAsInteger(a, &aVal);
  bcValueAsInteger(b, &bVal);

  switch (binop)
  {
  case BC_LND:
    aVal = (aVal != 0) && (bVal != 0);
    break;
  case BC_LOR:
    aVal = (aVal != 0) || (bVal != 0);
    break;
  case BC_BND:
    aVal &= bVal;
    break;
  case BC_BOR:
    aVal |= bVal;
    break;
  case BC_XOR:
    aVal ^= bVal;
    break;
  case BC_BLS:
    aVal = aVal << bVal;
    break;
  case BC_BRS:
    aVal = aVal >> bVal;
    break;
  default:
    return BC_NOT_IMPLEMENTED;
  }
  *result = bcValueInteger(aVal);
  return BC_OK;
}

bcStatus_t bcValueBinaryOperator(const BC_VALUE a, const BC_VALUE b, uint8_t binop, BC_VALUE* result)
{
  switch (binop)
  {
  case BC_ADD:
  case BC_SUB:
  case BC_MUL:
  case BC_DIV:
  case BC_MOD:
    return bcValueBinaryOperatorAlgebra(a, b, binop, result);
  case BC_EQ:
  case BC_NEQ:
  case BC_GR:
  case BC_LS:
  case BC_GRE:
  case BC_LSE:
    return bcValueBinaryOperatorCompare(a, b, binop, result);
  case BC_LND:
  case BC_LOR:
  case BC_BND:
  case BC_BOR: 
  case BC_XOR:
  case BC_BLS:
  case BC_BRS:
    return bcValueBinaryOperatorLogicBitwise(a, b, binop, result);
  default:
    return BC_NOT_IMPLEMENTED;
  }
}

bcStatus_t bcValueUnaryOperator(const BC_VALUE a, uint8_t unop, BC_VALUE* result)
{
  assert((result != NULL) && (a != NULL));

  switch (unop)
  {
  case BC_NEG:
    switch (a->type)
    {
    case BC_INTEGER:
      {
        const bcInteger_t* aVal = (const bcInteger_t*)a;
        *result = bcValueInteger(-aVal->data);
        return BC_OK;
      }
      break;
    case BC_NUMBER:
      {
        const bcNumber_t* aVal = (const bcNumber_t*)a;
        *result = bcValueNumber(-aVal->data);
        return BC_OK;
      }
      break;
    default:
      return BC_NOT_IMPLEMENTED;
    }
    break;
  case BC_LNT:
  case BC_BNT:
    {
      if (a->type != BC_INTEGER)
      {
        return BC_NOT_IMPLEMENTED;
      }
      const bcInteger_t* aVal = (const bcInteger_t*)a;
      if (unop == BC_LNT)
      {
        *result = bcValueInteger(!aVal->data);
      }
      else
      {
        *result = bcValueInteger(~aVal->data);
      }
      return BC_OK;
    }
    break;
  case BC_INT:
    {
      int64_t aVal;
      bcStatus_t status = bcValueAsInteger(a, &aVal);
      if (status != BC_OK)
      {
        return status;
      }
      *result = bcValueInteger(aVal);
      return BC_OK;
    }
    break;
  case BC_NUM:
    {
      double aVal;
      bcStatus_t status = bcValueAsNumber(a, &aVal);
      if (status != BC_OK)
      {
        return status;
      }
      *result = bcValueNumber(aVal);
      return BC_OK;
    }
    break;
  case BC_STR:
    {
      char* aVal = NULL;
      bcStatus_t status = bcValueAsString(a, &aVal, 0);
      if (status != BC_OK)
      {
        return status;
      }
      *result = bcValueString(aVal);
      free(aVal);
      return BC_OK;
    }
    break;
  default:
    return BC_NOT_IMPLEMENTED;
  }
}

const char* bcOpcodeString(uint8_t opcode)
{
  switch (opcode)
  {
  case BC_HALT: return "HALT";/**< Halt VM Execution */
  case BC_PSH: return "PSH"; /**< push(A) */
  case BC_POP: return "POP"; /**< pop() */
  case BC_ADD: return "ADD"; /**< A + B */
  case BC_SUB: return "SUB"; /**< A - B */
  case BC_MUL: return "MUL"; /**< A * B */
  case BC_DIV: return "DIV"; /**< A / B */
  case BC_MOD: return "MOD"; /**< A % B */
  case BC_EQ: return "EQ";  /**< A = B */
  case BC_NEQ: return "NEQ"; /**< A != B */
  case BC_GR: return "GR";  /**< A > B */
  case BC_LS: return "LS";  /**< A < B */
  case BC_GRE: return "GRE"; /**< A >= B */
  case BC_LSE: return "LSE"; /**< A <= B */
  case BC_LND: return "LND"; /**< A && B */
  case BC_LOR: return "LOR"; /**< A || B */
  case BC_BND: return "BND"; /**< A & B */
  case BC_BOR: return "BOR"; /**< A | B */ 
  case BC_XOR: return "XOR"; /**< A ^ B */
  case BC_BLS: return "BLS"; /**< A << B */
  case BC_BRS: return "BRS"; /**< A >> B */
  case BC_NEG: return "NEG"; /**< -A */
  case BC_LNT: return "LNT"; /**< !A */
  case BC_BNT: return "BNT"; /**< ~A */
  case BC_INT: return "INT"; /**< (int) A */
  case BC_NUM: return "NUM"; /**< (num) A */
  case BC_STR: return "STR"; /**< (str) A */
  case BC_SET: return "SET"; /**< A <- B */
  case BC_VAL: return "VAL"; /**< ValueOf(A) */
  case BC_IND: return "IND"; /**< A[B] */
  case BC_ADR: return "ADR"; /**< &A */
  case BC_ITM: return "ITM"; /**< A.B */
  case BC_CLL: return "CLL"; /**< A() */
  case BC_LST: return "LST"; /**< toList(A) */
  case BC_DCT: return "DCT"; /**< toDict(A) */
  default:
    assert(0);
    return "???";
  }
}
