


#ifndef _UTIL_H_
#define _UTIL_H_


void printToken( TokenType, const char*);//������ӡtoken����

TreeNode * newNode(NodeKind kind);       //�⺯���������뿪���﷨������


char * copyString( char * );

void printTree( TreeNode *);//��ӡ�﷨��

void printFour(TreeNode*);

extern FILE* yyout;

#endif
