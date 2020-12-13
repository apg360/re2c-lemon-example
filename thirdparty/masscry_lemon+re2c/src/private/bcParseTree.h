#pragma once
#ifndef DECI_SPACE_BADCODE_PRIVATE_PARSE_TREE_HEADER
#define DECI_SPACE_BADCODE_PRIVATE_PARSE_TREE_HEADER

#include "bcPrivate.h"

typedef enum bcTreeItemType_t
{
  TIT_UNDEF = 0,
  TIT_BIN_OP,
  TIT_UN_OP,
  TIT_CONSTANT,
  TIT_IF_STATEMENT
} bcTreeItemType_t;

typedef struct bcTreeItem_t
{
  bcTreeItemType_t type;
  struct bcTreeItem_t* next;
} bcTreeItem_t;

typedef struct bcBinOp_t
{
  bcTreeItem_t head;
  int tag;
  bcTreeItem_t* lbr;
  bcTreeItem_t* rbr;
} bcBinOp_t;

typedef struct bcUnOp_t
{
  bcTreeItem_t head;
  int tag;
  bcTreeItem_t* br;
} bcUnOp_t;

typedef struct bcConstant_t
{
  bcTreeItem_t head;
  BC_VALUE constVal;
} bcConstant_t;

typedef struct bcTree_t
{
  bcTreeItem_t* root;
} bcTree_t;

typedef struct bcIfStatement_t
{
  bcTreeItem_t head;
  bcTreeItem_t* cond;
  bcTree_t* body;
} bcIfStatement_t;

bcStatus_t bcTreeItemCleanup(bcTreeItem_t* treeItem);

bcStatus_t bcTreeCleanup(bcTree_t* tree);

bcTreeItem_t* bcBinOp(bcTreeItem_t* lbr, bcTreeItem_t* rbr, int tag);

bcTreeItem_t* bcUnOp(bcTreeItem_t* br, int tag);

bcTreeItem_t* bcConstant(const BC_VALUE value);

bcTreeItem_t* bcIfStatement(bcTreeItem_t* cond, bcTreeItem_t* body);

bcTreeItem_t* bcAppend(bcTreeItem_t* head, bcTreeItem_t* tail);

bcTree_t* bcTree(bcTreeItem_t* root);

#endif /* DECI_SPACE_BADCODE_PRIVATE_PARSE_TREE_HEADER */
