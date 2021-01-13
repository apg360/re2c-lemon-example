/* source code courtesy of Frank Thomas Braun */

/* calc3d.c: Generation of the graph of the syntax tree */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GLOBALS.H"
//#include "y.tab.h"

int del = 1; /* distance of graph columns */
int eps = 3; /* distance of graph lines */
char graph[100][100]; /* 图形化矩阵 */
/* interface for drawing (can be replaced by "real" graphic using GD or other) */
void graphInit (void);
void graphFinish();
void graphBox (char *s, int *w, int *h);
void graphDrawBox (char *s, int c, int l);
void graphDrawArrow (int c1, int l1, int c2, int l2);

void exNode (TreeNode *p, int c, int l, int *ce, int *cm);

/*****************************************************************************/

/* main entry point of the manipulation of the syntax tree */
int ex (TreeNode *p) {
    int rte, rtm;

    graphInit ();

    exNode (p, 0, 0, &rte, &rtm);
    graphFinish();
    return 0;
}

/*c----cm---ce---->                       drawing of leaf-nodes
 l leaf-info
 */

/*c---------------cm--------------ce----> drawing of non-leaf-nodes
 l            node-info
 *                |
 *    -------------     ...----
 *    |       |               |
 *    v       v               v
 * child1  child2  ...     child-n
 *        che     che             che
 *cs      cs      cs              cs
 *
 */

/*void exNode(
		TreeNode *p
        int c, int l,        /* start column and line of node
        int *ce, int *cm     /* resulting end column and mid of node
    )*/
/* recursive drawing of the syntax tree */
void exNode (TreeNode *p, int c, int l, int *ce, int *cm)
{

    int w, h;           /* 节点宽度和高度*/
    /*节点的文本 */
	  char *s;
    int cbar;           /* 节点横向的起点 */
    int k,ks;              /* 用于计数儿子&兄弟的数量 */
    int che, chm;       /* 横向终点和子树的中点*/
    int cs;             /* 子树起点  */
    int ji;
    char word[20];      /* extended node text */

    if (!p) return;

    strcpy (word, "???"); /* should never appear */
    s = word;
    printf("%d ",p->kind);
    switch(p->kind) {
        case ConstK: sprintf (word, "c(%d)", p->attr.val); break;
        case IdK:  sprintf (word, "id(%s)", p->attr.name); break;
        case IfK:   s="if"; break;
        case WhileK:    s="while"; break;
        case AssignK:   s="[=]";break;
        case ReturnK:   s="return";break;
        case CallK:     s="call";  break;
        case VarDeclK:
            switch (p->attr.op) {
              case 262:       s="int";    break;
              case 264:       s="void";   break;
              default:        break;
            }break;
        case FunDeclK:  s="FunDecl";break;
        case OpK:
            switch(p->attr.op){
                case 268:       s = "[=]";     break;
                case 275:       s = "[+]";     break;
                case 276:       s = "[-]";     break;
                case 277:       s = "[*]";     break;
                case 278:       s = "[/]";     break;
                case 273:       s = "[<]";     break;
                case 274:       s = "[>]";     break;
                case 272:        s = "[>=]";    break;
                case 271:        s = "[<=]";    break;
                case 270:        s = "[!=]";    break;
                case 269:        s = "[==]";    break;
                case 279:        s="[(]";        break;
                case 280:        s="[)]";       break;
                case 281:        s="[[]";       break;
                case 282:         s="[]]";      break;
                case 283:         s="[{]";      break;
                case 284:         s="[}]";      break;
                case 286:        s="[,]";       break;
                case 285:       s = "[;]";     break;
                default:         break;
            }
            break;
    }

    /* 构建文本框 */
    graphBox (s, &w, &h);
    cbar = c;
    *ce = c + w;
    *cm = c + w / 2;

    /* 叶子结点 */
    if (!p->child[0]) {
        graphDrawBox (s, cbar, l);
        return;
    }

    //for (ji = 0; ji <= 30; ji++) printf ("\n%s", graph[ji]);
    //graphFinish();
    /* 有子女的节点 */
    cs = c;
  /*  for (k = 0; k < p->opr.nops; k++) {
        exNode (p->opr.op[k], cs, l+h+eps, &che, chm);
        cs = che;
    }*/
    k=0;
    ks=0;
    printf("%s\n",s);
    while(p->child[k]!=NULL)
    {
      exNode(p->child[k],cs,l+h+eps,&che,&chm);
     /* if(p->child[k]->sibling!=NULL)
      {
        exNode(p->child[k]->sibling,cs,l+h+eps,&che,&chm);
        cs=che;
        ks++;
      }*/
      printf("%d",k);
      cs=che;
      k++;
    }
    /* 节点 总宽度 */
    if (w < che - c) {
        cbar += (che - c - w) / 2;
        *ce = che;
        *cm = (c + che) / 2;
    }

    /* 绘制该节点 */
    graphDrawBox (s, cbar, l);

    /* draw arrows (not optimal: children are drawn a second time) */
    cs = c;
    k=0;
    while(p->child[k]){
        exNode (p->child[k], cs, l+h+eps, &che, &chm);
        graphDrawArrow (*cm, l+h, chm, l+h+eps-1);
        cs = che;
	/*	if(p->child[k]->sibling!=NULL)
      {
        exNode(p->child[k]->sibling,cs,l+h+eps,&che,&chm);
        graphDrawArrow (*cm, l+h, chm, l+h+eps-1);
        cs=che;

      }*/
        k++;
    }
    	if(p->sibling!=NULL)
      {
        exNode(p->sibling,cs,l+h+eps,&che,&chm);
        //graphDrawArrow (*cm, l+h, chm, l+h+eps-1);
        cs=che;

      }
}

/* 画图接口 */

#define lmax 100
#define cmax 100


int graphNumber = 0;
/*测试是否超出图画*/
void graphTest (int l, int c)
{   int ok;
    ok = 1;
    if (l < 0) ok = 0;
    if (l >= lmax) ok = 0;
    if (c < 0) ok = 0;
    if (c >= cmax) ok = 0;
    if (ok) return;
    printf ("\n+++error: l=%d, c=%d not in drawing rectangle 0, 0 ... %d, %d",
        l, c, lmax, cmax);
    exit(1);
}

void graphInit (void) {
    int i, j;
    for (i = 0; i < lmax; i++) {
        for (j = 0; j < cmax; j++) {
            graph[i][j] = ' ';
        }
    }
}

void graphFinish() {
    int i, j;
    for (i = 0; i < lmax; i++) {
        for (j = cmax-1; j > 0 && graph[i][j] == ' '; j--);
        graph[i][cmax-1] = 0;
        if (j < cmax-1) graph[i][j+1] = 0;
        if (graph[i][j] == ' ') graph[i][j] = 0;
    }
    for (i = lmax-1; i > 0 && graph[i][0] == 0; i--);
    printf ("\n\nGraph %d:\n", graphNumber++);
    for (j = 0; j <= i; j++) printf ("\n%s", graph[j]);
    printf("\n");
}

void graphBox (char *s, int *w, int *h) {
    *w = strlen (s) + del;
    *h = 1;
}

void graphDrawBox (char *s, int c, int l) {
    int i;
    graphTest (l, c+strlen(s)-1+del);
    for (i = 0; i < strlen (s); i++) {
        graph[l][c+i+del] = s[i];
      }
}
void graphDrawArrow (int c1, int l1, int c2, int l2) {
    int m;
    graphTest (l1, c1);
    graphTest (l2, c2);
    m = (l1 + l2) / 2;
    while (l1 != m) { graph[l1][c1] = '|'; if (l1 < l2) l1++; else l1--; }
    while (c1 != c2) { graph[l1][c1] = '-'; if (c1 < c2) c1++; else c1--; }
    while (l1 != l2) { graph[l1][c1] = '|'; if (l1 < l2) l1++; else l1--; }
    graph[l1][c1] = '|';
}
