#include <bcPrivate.h>

#include <stdlib.h>

bcStatus_t bcValueStackInit(bcValueStack_t* pStack, size_t total)
{
  if ((pStack == NULL) || (total == 0))
  {
    return BC_INVALID_ARG;
  }

  BC_VALUE* values = (BC_VALUE*) calloc(total, sizeof(BC_VALUE));
  if (values == NULL)
  {
    return BC_NO_MEMORY;
  }

  pStack->bottom = values;
  pStack->top = values;
  pStack->total = total;
  return BC_OK;
}

bcStatus_t bcValueStackCleanup(bcValueStack_t* pStack)
{
  if (pStack == NULL)
  {
    return BC_INVALID_ARG;
  }

  for (BC_VALUE* cursor = pStack->bottom; cursor < pStack->top; ++cursor)
  {
    bcValueCleanup(*cursor);
  }

  free(pStack->bottom);

  pStack->bottom = NULL;
  pStack->top = NULL;
  pStack->total = 0;
  return BC_OK;
}

bcStatus_t bcValueStackPush(bcValueStack_t* pStack, const BC_VALUE value)
{
  if ((pStack == NULL) || (value == NULL))
  {
    return BC_INVALID_ARG;
  }

  if ((size_t)(pStack->top-pStack->bottom) >= pStack->total)
  {
    return BC_OVERFLOW;
  } 

  *pStack->top = bcValueCopy(value);
  ++pStack->top;
  return BC_OK;
}

bcStatus_t bcValueStackPop(bcValueStack_t* pStack)
{
  if (pStack == NULL)
  {
    return BC_INVALID_ARG;
  }

  if (pStack->top == pStack->bottom)
  {
    return BC_UNDERFLOW;
  }

  bcValueCleanup(pStack->top[-1]);
  --pStack->top;
  return BC_OK;
}
