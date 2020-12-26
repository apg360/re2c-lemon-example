#include <bcPrivate.h>

#include <stdlib.h>
#include <string.h>
#include <assert.h>

static int bcCompareGlobals(const void* a,const void* b)
{
  const BC_GLOBAL* aVal = (const BC_GLOBAL*)a;
  const BC_GLOBAL* bVal = (const BC_GLOBAL*)b;
  return strcmp((*aVal)->name, (*bVal)->name);
}

BC_GLOBAL bcGlobalNew(const char* name, const BC_VALUE value)
{
  assert(name != NULL);

  size_t nameLen = strlen(name) + 1;

  BC_GLOBAL result = (BC_GLOBAL) malloc(sizeof(bcGlobalVar_t)+nameLen);
  if (result == NULL)
  {
    return NULL;
  }

  result->value = bcValueCopy(value);
  memcpy(result->name, name, nameLen);
  return result;
}

void bcGlobalDelete(BC_GLOBAL global)
{
  if(global != NULL)
  {
    bcValueCleanup(global->value);
    free(global);
  }
}

bcStatus_t bcCoreSetGlobal(BC_CORE core, const char* name, const BC_VALUE value)
{
  BC_GLOBAL newGlobalVal = bcGlobalNew(name, value);
  if (newGlobalVal == NULL)
  {
    return BC_NO_MEMORY;
  }

  BC_GLOBAL* itemInArray = bsearch(&newGlobalVal, core->globals, core->globalSize, sizeof(BC_GLOBAL), bcCompareGlobals);
  if (itemInArray != NULL)
  {
    bcGlobalDelete(*itemInArray);
    *itemInArray = newGlobalVal;
    return BC_OK;
  }

  if (core->globalSize == core->globalCap)
  {
    BC_GLOBAL* newGlobals = (BC_GLOBAL*) calloc(core->globalCap*3/2, sizeof(BC_GLOBAL));
    if (newGlobals == NULL)
    {
      bcGlobalDelete(newGlobalVal);
      return BC_NO_MEMORY;
    }

    memcpy(newGlobals, core->globals, core->globalCap*sizeof(BC_GLOBAL));
    free(core->globals);

    core->globals = newGlobals;
    core->globalCap = core->globalCap*3/2;
  }

  core->globals[core->globalSize++] = newGlobalVal;
  qsort(core->globals, core->globalSize, sizeof(BC_GLOBAL), bcCompareGlobals);
  return BC_OK;
}

BC_VALUE bcCoreGetGlobal(BC_CORE core, const char* name)
{
  BC_GLOBAL keyGlobal = bcGlobalNew(name, NULL);
  if (keyGlobal == NULL)
  {
    return NULL;
  }

  BC_GLOBAL* itemInArray = bsearch(&keyGlobal, core->globals, core->globalSize, sizeof(BC_GLOBAL), bcCompareGlobals);
  if (itemInArray != NULL)
  {
    bcGlobalDelete(keyGlobal);
    return bcValueCopy((*itemInArray)->value);
  }
  bcGlobalDelete(keyGlobal);
  return NULL;
}
