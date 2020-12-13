#include <bcPrivate.h>
#include <bcParseTree.h>

#include <stdlib.h>
#include <assert.h>

bcStatus_t bcTreeItemCleanup(bcTreeItem_t* treeItem)
{
  if (treeItem == NULL)
  {
    return BC_INVALID_ARG;
  }

  for (bcTreeItem_t* cursor = treeItem; cursor != NULL;)
  {
    bcTreeItem_t* next = cursor->next; // stored, because later cursor is freed
    switch (cursor->type)
    {
    case TIT_BIN_OP:
      {
        bcBinOp_t* binop = (bcBinOp_t*) cursor;
        bcStatus_t status = bcTreeItemCleanup(binop->lbr);
        if (status != BC_OK)
        {
          return status;
        }
        status = bcTreeItemCleanup(binop->rbr);
        if (status != BC_OK)
        {
          return status;
        }
      }
      break;
    case TIT_UN_OP:
      {
        bcUnOp_t* unop = (bcUnOp_t*) cursor;
        bcStatus_t status = bcTreeItemCleanup(unop->br);
        if (status != BC_OK)
        {
          return status;
        }
      }
      break;
    case TIT_CONSTANT:
      {
        bcConstant_t* cns = (bcConstant_t*) cursor;
        bcStatus_t status = bcValueCleanup(cns->constVal);
        if (status != BC_OK)
        {
          return status;
        }
      }
      break;
    case TIT_IF_STATEMENT:
      {
        bcIfStatement_t* ifstate = (bcIfStatement_t*) cursor;
        bcStatus_t status = bcTreeItemCleanup(ifstate->cond);
        if (status != BC_OK)
        {
          return status;
        }
        status = bcTreeCleanup(ifstate->body);
        if (status != BC_OK)
        {
          return status;
        }
      }
      break;
    default:
      return BC_NOT_IMPLEMENTED;
    }
    free(cursor);
    cursor = next;
  }
  return BC_OK;
}

bcStatus_t bcTreeCleanup(bcTree_t* tree)
{
  if (tree == NULL)
  {
    return BC_INVALID_ARG;
  }

  bcStatus_t status = bcTreeItemCleanup(tree->root);
  free(tree);
  return status;
}

bcTreeItem_t* bcBinOp(bcTreeItem_t* lbr, bcTreeItem_t* rbr, int tag)
{
  bcBinOp_t* result = (bcBinOp_t*) malloc(sizeof(bcBinOp_t));
  if (result == NULL)
  {
    return NULL;
  }
  result->head.type = TIT_BIN_OP;
  result->head.next = NULL;

  result->lbr = lbr;
  result->rbr = rbr;
  result->tag = tag;
  return &result->head;
}

bcTreeItem_t* bcUnOp(bcTreeItem_t* br, int tag)
{
  bcUnOp_t* result = (bcUnOp_t*) malloc(sizeof(bcUnOp_t));
  if (result == NULL)
  {
    return NULL;
  }

  result->head.type = TIT_UN_OP;
  result->head.next = NULL;

  result->br = br;
  result->tag = tag;
  return &result->head;
}

bcTreeItem_t* bcConstant(const BC_VALUE value)
{
  bcConstant_t* result = (bcConstant_t*) malloc(sizeof(bcConstant_t));
  if (result == NULL)
  {
    return NULL;
  }

  result->head.type = TIT_CONSTANT;
  result->head.next = NULL;

  result->constVal = bcValueCopy(value);

  return &result->head;
}

bcTreeItem_t* bcAppend(bcTreeItem_t* head, bcTreeItem_t* tail)
{
  if (head == NULL)
  { // must not happen in valid code!
    assert(0);
    return NULL;
  }

  bcTreeItem_t* last = head;
  while(last->next != NULL)
  {
    last = last->next;
  }

  last->next = tail;
  return head;
}

bcTreeItem_t* bcIfStatement(bcTreeItem_t* cond, bcTreeItem_t* body)
{
  bcIfStatement_t* result = (bcIfStatement_t*) malloc(sizeof(bcIfStatement_t));
  if (result == NULL)
  {
    return NULL;
  }
  result->head.type = TIT_IF_STATEMENT;
  result->head.next = NULL;

  result->cond = cond;
  result->body = bcTree(body);
  return &result->head;
}

bcTree_t* bcTree(bcTreeItem_t* root)
{
  bcTree_t* result = (bcTree_t*) malloc(sizeof(bcTree_t));
  if (result == NULL)
  {
    return NULL;
  }

  result->root = root;
  return result;
}

