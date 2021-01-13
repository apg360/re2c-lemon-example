
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

static int hash ( char * key )   //定义哈稀结构函数;
{ 
  int temp = 0;
  int i = 0;
  while (key[i] != '\0')
  {
    temp = ((temp << SHIFT) + key[i]) % SIZE;
    ++i;
  }
  return temp;
}

int insert_record(struct symtab_entry * to_insert, unsigned int loc)   //在符号表的loc位置插入元素;
{
  int retval;

  retval = 0;
  if (loc < SIZE)
  {
    to_insert->next = hashTable[loc];
    hashTable[loc] = to_insert;
  } 
  else
  {
    retval = 1;
  }
  return retval;
}

int insert_simple_var_record(char * name, int scope)    //链表头结点的属性;
{
  int h, retval;
  struct symtab_entry * l;

  h = symtab_lookup(name, scope);
  if (h == -1)
  {
    h = hash(name);
    l = (struct symtab_entry*) malloc(sizeof(struct symtab_entry));
    l->name = name;
    l->scope = scope;
    l->t = SIMPLE_VAR_RECORD;
    retval = insert_record(l, h);
  }
  else
  {
    retval = -1;
  }
  return retval;
}

int insert_array_var_record(char * name, int scope, unsigned int length)  //开辟一个链表头结点;
{
  int h, retval;
  struct symtab_entry * l;

  h = symtab_lookup(name, scope);
  if (h == -1)
  {
    h = hash(name);
    l = (struct symtab_entry*) malloc(sizeof(struct symtab_entry));
    l->name = name;
    l->scope = scope;
    l->t = ARRAY_VAR_RECORD;
    (l->u).array_var_record.length = length;
    retval = insert_record(l, h);
  }
  else
  {
    retval = -1;
  }
  return retval;
}

int insert_function_record(char * name, int scope)   //增加函数名到哈稀表;
{
  int h, retval;
  struct symtab_entry * l;

  h = symtab_lookup(name, scope);
  if (h == -1)
  {
    h = hash(name);
    l = (struct symtab_entry*) malloc(sizeof(struct symtab_entry));
    l->name = name;
    l->scope = scope;
    l->t = FUNCTION_RECORD;
    retval = insert_record(l, h);
  }
  else
  {
    retval = -1;
  }
  return retval;
}

int symtab_lookup(char * name, int scope)     //查找;
{
  int retval, h;
  struct symtab_entry * l;

  h = hash(name);
  l = hashTable[h];

  while ((l != NULL) && 
	 !((strcmp(name,l->name) == 0) && 
	   (scope == l->scope)))
  {
    l = l->next;
  }
  if (l != NULL)
  {
    retval = h;
  }
  else
  {
    retval = -1;
  }
 
  return retval;
}

int print_symtab()
{
  int i;
  struct ParamList * param_list;
  struct symtab_entry * l;
  printf("SymbolTable:\n");
  for (i = 0; i < SIZE; i++)
  {
    l = hashTable[i];
    while (l != NULL)
    {
      switch (l->t)
      {
      case SIMPLE_VAR_RECORD:
	printf("Simple Variable: %s, Scope: %d\n", l->name, l->scope);
	break;
      case ARRAY_VAR_RECORD:
	printf("Array Variable : %s, Scope: %d, Length: %d\n", 
	       l->name, l->scope, (l->u).array_var_record.length);
	break;
      case FUNCTION_RECORD:
	printf("Function       : %s, Scope: %d ",
	       l->name, l->scope);
	param_list = NULL;
	while(param_list != NULL)
	{
	  printf("%d, ", param_list->type);
	  param_list = param_list->next;
	}
	printf("\n");
	break;
      default:
	break;
      }
      l = l->next;
    }
  }
  return 0;
}
