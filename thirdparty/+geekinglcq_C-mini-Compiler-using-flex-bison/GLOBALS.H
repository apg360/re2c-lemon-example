

#ifndef _GLOBALS_DOT_H
#define _GLOBALS_DOT_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define MAXTOKENSIZE 50  //��ʶ�����󳤶ȣ�

typedef int TokenType;   //���ŵ��������ͣ�

typedef struct
{

	TokenType tok;
	char * tokString;
} TokenStruct;          //�洢���ŵ����ݽṹ��

typedef enum {IfK,WhileK,AssignK,ReturnK,CallK,VarDeclK,FunDeclK,OpK,ConstK,IdK} NodeKind;//ö�ٽ������ͣ�

typedef enum {Void,Integer,Boolean} ExpType;     //ö�ٷ��ر	������ͣ�

#define MAXCHILDREN 3                   //����һ�����������������ӽ��㣻

typedef struct treeNode
{
	struct treeNode * child[MAXCHILDREN];
	struct treeNode * sibling;
	int lineno;
	NodeKind kind;
	union      //���ݽ�������NodeKind
	{
		TokenType op;
		int val;
		char * name;
	} attr;
	ExpType type; /* for type checking of exps */
} TreeNode;

typedef struct siyuanzu
{
	int type1;
	int type2;
	int o1;
	int o2;
	char op1[10];
	char op2[10];
	char operation[10];
	int result_no;
}siyuanzu;

#ifndef YYPARSER
// tokens from bison parser
#include "parse.h"
#endif

extern TokenStruct curToken;
extern char * lastid;
extern int lineno;
extern TreeNode * parseTree;
 siyuanzu SYZ[200];
 int N;

#endif
