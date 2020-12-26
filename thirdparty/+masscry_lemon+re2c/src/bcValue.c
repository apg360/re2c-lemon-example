#include <bcPrivate.h>

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

BCAPI bcStatus_t bcValueCleanup(BC_VALUE value)
{
  if (value == NULL)
  {
    return BC_INVALID_ARG;
  }

  --value->refCount;
  if (value->refCount == 0)
  {
    switch (value->type)
    {
    case BC_INTEGER:
    case BC_NUMBER:
    case BC_STRING:
      free(value);
      return BC_OK;
    case BC_CODE:
      {
        bcCode_t* code = (bcCode_t*) value;
        bcCodeStreamCleanup(&code->code);
        free(code);
      }
      return BC_OK;
    default:
      return BC_NOT_IMPLEMENTED;
    }
  }
  return BC_OK;
}

BCAPI BC_VALUE bcValueCopy(const BC_VALUE val)
{
  if (val == NULL)
  {
    return NULL;
  }

  BC_VALUE result = (BC_VALUE) val;
  ++result->refCount;
  return result;
}

BCAPI BC_VALUE bcValueInteger(int64_t val)
{
  bcInteger_t* result = (bcInteger_t*) malloc(sizeof(bcInteger_t));
  if (result == NULL)
  {
    return NULL;
  }

  result->head.type = BC_INTEGER;
  result->head.refCount = 1;
  result->data = val;

  return &result->head;
}

BCAPI BC_VALUE bcValueNumber(double val)
{
  bcNumber_t* result = (bcNumber_t*) malloc(sizeof(bcNumber_t));
  if (result == NULL)
  {
    return NULL;
  }

  result->head.type = BC_NUMBER;
  result->head.refCount = 1;
  result->data = val;

  return &result->head;
}

BCAPI BC_VALUE bcValueString(const char* str)
{
  size_t len = strlen(str) + 1;
  bcString_t* result = (bcString_t*) malloc(sizeof(bcString_t) + len);
  if (result == NULL)
  {
    return NULL;
  }

  result->head.type = BC_STRING;
  result->head.refCount = 1;
  result->len = len;
  memcpy(result->data, str, len);

  return &result->head;
}

BCAPI bcStatus_t bcValueAsInteger(const BC_VALUE val, int64_t* oval)
{
  if ((val == NULL) || (oval == NULL))
  {
    return BC_INVALID_ARG;
  }

  switch (val->type)
  {
  case BC_INTEGER:
    {
      const bcInteger_t* ival = (const bcInteger_t*)val;
      *oval = ival->data;
      return BC_OK;
    }
  case BC_NUMBER:
    {
      const bcNumber_t* nval = (const bcNumber_t*)val;
      *oval = (int64_t) nval->data;
      return BC_OK;
    }
  case BC_STRING:
    {
      const bcString_t* sval = (const bcString_t*)val;
      errno = 0;
      int64_t tmpVal = strtoll(sval->data, NULL, 10);
      if (errno != 0)
      {
        return BC_CANT_CONVERT;
      }
      *oval = tmpVal;
      return BC_OK;
    }
  default:
    return BC_NOT_IMPLEMENTED;
  }
}

BCAPI bcStatus_t bcValueAsString(const BC_VALUE val, char** pBuf, size_t bufSize)
{
  if ((val == NULL) || (pBuf == NULL))
  {
    return BC_INVALID_ARG;
  }

  if (((*pBuf != NULL) && (bufSize == 0)) || ((*pBuf == NULL) && (bufSize != 0)))
  {
    return BC_INVALID_ARG;
  }

  if (*pBuf == NULL)
  {
    switch (val->type)
    {
    case BC_INTEGER:
      {
        char* tbuf = NULL;
        const bcInteger_t* iVal = (const bcInteger_t*) val;
        int printResult = asprintf(&tbuf, "%ld", iVal->data);
        if (printResult < 0)
        {
          return BC_NO_MEMORY;
        }
        *pBuf = tbuf;
        return BC_OK;
      }
    case BC_NUMBER:
      {
        char* tbuf = NULL;
        const bcNumber_t* dVal = (const bcNumber_t*) val;
        int printResult = asprintf(&tbuf, "%g", dVal->data);
        if (printResult < 0)
        {
          return BC_NO_MEMORY;
        }
        *pBuf = tbuf;
        return BC_OK;
      }
    case BC_STRING:
      {
        char* tbuf = NULL;
        const bcString_t* sVal = (const bcString_t*) val;
        int printResult = asprintf(&tbuf, "%s", sVal->data);
        if (printResult < 0)
        {
          return BC_NO_MEMORY;
        }
        *pBuf = tbuf;
        return BC_OK;
      }
    default:
      return BC_NOT_IMPLEMENTED;
    }
  }
  else
  {
    switch (val->type)
    {
    case BC_INTEGER:
      {
        const bcInteger_t* iVal = (const bcInteger_t*) val;
        int result = snprintf(*pBuf, bufSize, "%ld", iVal->data);
        if ((result < 0) || (bufSize <= (size_t)result))
        {
          return BC_TOO_SMALL;
        }
        return BC_OK;
      }
    case BC_NUMBER:
      {
        const bcNumber_t* dVal = (const bcNumber_t*) val;
        int result = snprintf(*pBuf, bufSize, "%g", dVal->data);
        if ((result < 0) || (bufSize <= (size_t)result))
        {
          return BC_TOO_SMALL;
        }
        return BC_OK;
      }
    case BC_STRING:
      {
        const bcString_t* sVal = (const bcString_t*) val;
        int result = snprintf(*pBuf, bufSize, "%s", sVal->data);
        if ((result < 0) || (bufSize <= (size_t)result))
        {
          return BC_TOO_SMALL;
        }
        return BC_OK;
      }
    default:
      return BC_NOT_IMPLEMENTED;
    }
  }

  // can't reach here
  assert(0);
  return BC_NOT_IMPLEMENTED;
}

BCAPI bcStatus_t bcValueAsNumber(const BC_VALUE val, double* oval)
{
  if ((val == NULL) || (oval == NULL))
  {
    return BC_INVALID_ARG;
  }

  switch (val->type)
  {
  case BC_INTEGER:
    {
      const bcInteger_t* ival = (const bcInteger_t*)val;
      *oval = (double) ival->data;
      return BC_OK;
    }
  case BC_NUMBER:
    {
      const bcNumber_t* nval = (const bcNumber_t*)val;
      *oval = nval->data;
      return BC_OK;
    }
  case BC_STRING:
    {
      const bcString_t* sval = (const bcString_t*)val;
      errno = 0;
      double tmpVal = strtod(sval->data, NULL);
      if (errno != 0)
      {
        return BC_CANT_CONVERT;
      }
      *oval = tmpVal;
      return BC_OK;
    }
  default:
    return BC_NOT_IMPLEMENTED;
  }  
}

BCAPI int bcValuePrint(FILE* stream, const BC_VALUE val)
{
  switch (val->type)
  {
  case BC_INTEGER:
    return fprintf(stream, "%ld", ((const bcInteger_t*)val)->data);
  case BC_NUMBER:
    return fprintf(stream, "%g", ((const bcNumber_t*)val)->data);
  case BC_STRING:
    return fprintf(stream, "%s", ((const bcString_t*)val)->data);
  default:
    return fprintf(stream, "%s", "NOT-IMPLEMENTED");
  }
}
