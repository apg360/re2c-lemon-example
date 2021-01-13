
#include "globals.h"
#include "util.h"

/*�ú���������ӡtoken����parse�����е���scan���̣�������token
 */
char* tokenStr(TokenType token, const char* str){
    char* result = malloc(sizeof(char)*40);
    switch (token) {
        case IF:
        case ELSE:
        case WHILE:
        case RETURN:
            sprintf(result,"Reserved word: %s",str);
            break;
        case INT:
      	     sprintf(result,"int");
      	      break;
        case VOID:
          	  sprintf(result,"void");
          	  break;
        case ASSIGN:
          	  sprintf(result,"=");
          	  break;
        case LT:
          	  sprintf(result,"<");
          	  break;
        case GT:
          	  sprintf(result,">");
          	  break;
        case EQ:
          	  sprintf(result,"==");
          	  break;
        case LTEQ:
          	  sprintf(result,"<=");
          	  break;
        case GTEQ:
          	  sprintf(result,">=");
          	  break;
        case LPAREN:
          	  sprintf(result,"(");
          	  break;
        case RPAREN:
          	  sprintf(result,")");
          	  break;
        case LBRACK:
          	  sprintf(result,"[");
          	  break;
        case RBRACK:
          	  sprintf(result,"]");
          	  break;
        case LCURL:
          	  sprintf(result,"{");
          	  break;
        case RCURL:
          	  sprintf(result,"}");
          	  break;
        case SEMI:
          	  sprintf(result,";");
          	  break;
        case COMMA:
          	  sprintf(result,",");
          	  break;
        case PLUS:
          	  sprintf(result,"+");
          	  break;
        case MINUS:
          	  sprintf(result,"-");
          	  break;
        case TIMES:
      	  sprintf(result,"*");
      	  break;
        case OVER:
      	  sprintf(result,"/");
      	  break;
        case ENDFILE: sprintf(result,"EOF");
      	  break;
        case NUM:
            sprintf(result," NUM, val= %s",str);
            break;
        case ID:
      	  sprintf(result," ID, name= %s",str);
            break;
        case ERROR:
      	  sprintf(result,"ERROR: %s",str);
            break;
        default:
            sprintf(result,"Unknown token: %d\n",token);
			break;
    }
	return result;
}

void printToken( TokenType token, const char* tokenString)
{
    fprintf(yyout, "%s\n", tokenStr(token, tokenString));
}

/*�����﷨���½���
 */

TreeNode * newNode(NodeKind kind) {
    TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if (t==NULL) {
      fprintf(yyout,"Out of memory error at line %d\n",lineno);
    }
    else {
      for (i=0; i<MAXCHILDREN; i++)
        t->child[i] = NULL;
      t->sibling = NULL;
      t->kind = kind;
      t->lineno = lineno;
    }
    return t;
}

/*
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(yyout,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}


static unsigned indentno = 0;
static unsigned tempCount = 0;
static unsigned labelCount = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{
	int i;
	for (i=0;i<indentno;i++)
		fprintf(yyout," ");
}
/* ��ӡ�﷨�� */
void printTree( TreeNode * tree)
{
  int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    switch (tree->kind) {
        case IfK:
          fprintf(yyout,"If\n");
          break;
        case WhileK:
          fprintf(yyout,"While\n");
          break;
        case AssignK:
          fprintf(yyout,"Assign to: \n",tree->attr.name);
          break;
        case ReturnK:
          fprintf(yyout,"Return: \n",tree->attr.name);
          break;
        case CallK:
          fprintf(yyout,"Call: \n",tree->attr.name);
          break;
        case VarDeclK:
          fprintf(yyout,"Var Decl: ");
	       printToken(tree->attr.op,'\0');
          break;
        case FunDeclK:
          fprintf(yyout,"Fun Decl: ");
	        printToken(tree->attr.op,'\0');
          break;
        case OpK:
          fprintf(yyout,"Op: ");
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          fprintf(yyout,"Const: %d\n",tree->attr.val);
          break;
        case IdK:
          fprintf(yyout,"Id: %s\n",tree->attr.name);
          break;
        default:
          fprintf(yyout,"Unknown ExpNode kind\n");
          break;
    }
	for (i=0;i<MAXCHILDREN;i++)
		printTree(tree->child[i]);
  tree = tree->sibling;
  }
  UNINDENT;
}
//��Ԫ�鹹��;

char* nodeStr(TreeNode* node){
    char* result = NULL;
    switch (node->kind) {
    case ConstK:
        result = malloc(sizeof(char)*10);
        sprintf(result, "%d", node->attr.val);
        break;
    case IdK:
        result = malloc(sizeof(char)*20);
        sprintf(result, "%s", node->attr.name);
        break;
    case VarDeclK:
        result = malloc(sizeof(char)*20);
        sprintf(result, "%s %s", tokenStr(node->attr.op, ""), nodeStr(node->child[0]));
        break;
    }
    return result;
}

void printFour( TreeNode * node)
{
    int i,count,n,t;
    int label1, label2, label3;
    TreeNode* tempNode = NULL;
    n=0;
    count=-1;
    while (node != NULL) {
        printSpaces();
        switch (node->kind) {
        case OpK:
            //运算式, 先计算子节点, 再计算根节点
            for (i=0;i<MAXCHILDREN;i++) {
                if(node->child[i] != NULL) {
                    printFour(node->child[i]);
                }
            }
            tempNode = node->child[1];
            tempNode = tempNode?tempNode:node->child[2];
            tempNode = tempNode?tempNode:node->child[0]->sibling;
            if (tempNode) {
                printf("\tT%d = %s %s %s\n", ++tempCount, nodeStr(node->child[0]), tokenStr(node->attr.op, ""), nodeStr(tempNode));
                node->kind = IdK;
                for (i=0; i<MAXCHILDREN; ++i) {
                    //free(node->child[i]);
                    node->child[i] = NULL;
                }
				node->attr.name = malloc(sizeof(char)*5);
                sprintf(node->attr.name, "T%d", tempCount);
            }
            else {
                printf("Not enough operation number: %s %s\n", nodeStr(node->child[0]), tokenStr(node->attr.op,""));
            }
            break;
        case AssignK:
            //赋值式, 先计算子节点, 再计算根节点
            for (i=0;i<MAXCHILDREN;i++) {
                if(node->child[i] != NULL) {
                    printFour(node->child[i]);
                }
            }
            tempNode = node->child[1];
            tempNode = tempNode?tempNode:node->child[2];
            tempNode = tempNode?tempNode:node->child[0]->sibling;
            if (tempNode) {
                printf("\t%s = %s\n", nodeStr(node->child[0]), nodeStr(tempNode));
            }
            break;
        case IfK:
            printFour(node->child[0]);
            label1 = ++labelCount;
            printf("\tIf %s goto L%d\n", nodeStr(node->child[0]), label1);
            if (node->child[2]) {
                label2 = ++labelCount;
                printf("\telse goto L%d\n", label2);
            }
            printf("L%d:", label1);
            printFour(node->child[1]);
            if (node->child[2]) {
                label3 = ++labelCount;
                printf("\tgoto L%d\n", label3);
                printf("L%d:", label2);
                printFour(node->child[2]);
                printf("L%d:", label3);
            }
            break;
        case WhileK:
            label1 = ++labelCount;
            label2 = ++labelCount;
            printf("L%d:", label1);
            printFour(node->child[0]);
            printf("\tIf %s goto L%d:\n", nodeStr(node->child[0]), label2);
            tempNode = node->child[1];
            tempNode = tempNode?tempNode:node->child[2];
            tempNode = tempNode?tempNode:node->child[0]->sibling;
            printFour(tempNode);
            printf("L%d:", label2);
            break;
        case CallK:
            tempNode = node->child[1];
            while (tempNode != NULL) {
                printFour(tempNode);
                tempNode = tempNode->sibling;
            }
            printf("\tT%d = Call %s ", ++tempCount, nodeStr(node->child[0]));
            tempNode = node->child[1];
            while (tempNode != NULL) {
                printf("%s ", nodeStr(tempNode));
                tempNode = tempNode->sibling;
            }
            printf("\n");
            node->kind = IdK;
            node->attr.name = malloc(sizeof(char)*5);
            sprintf(node->attr.name, "T%d", tempCount);
            break;
        case FunDeclK:
            printf("\tEntry %s ( ", nodeStr(node->child[0]));
            tempNode = node->child[1];
            while (tempNode) {
                printf("%s ", nodeStr(tempNode));
                tempNode = tempNode->sibling;
            }
            printf(")\n");
            printFour(node->child[2]);
            break;
        case ReturnK:
            printFour(node->child[0]);
            printf("\tReturn: %s\n", nodeStr(node->child[0]));
            break;
        default:
            for (i=0;i<MAXCHILDREN;i++) {
                if(node->child[i] != NULL) {
                    printFour(node->child[i]);
                }
            }
            //printf(yyout,"Unknown ExpNode kind\n");
            break;
        }
        node = node->sibling;
  }
  N=count;
}

printCode()
{
	int count;
	for(count=0;count<N;count++)
	{
		printf("(%s",SYZ[count].operation);
		if(SYZ[count].type1==0)
			printf("%s",SYZ[count].op1);
		else
			printf("%d",SYZ[count].o1);
		if(SYZ[count].type2==0)
			printf("%s",SYZ[count].op2);
		else
			printf("%d",SYZ[count].o2);
		printf("T%d)\n",SYZ[count].result_no);
	}
	N=0;
}
