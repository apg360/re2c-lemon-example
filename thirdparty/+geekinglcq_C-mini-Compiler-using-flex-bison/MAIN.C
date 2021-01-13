//主函数；

#include "globals.h"
#include "symtab.h"
#include "print.h"
extern FILE * yyin;
extern FILE * yyout;
extern void yyparse();
extern void printTree(TreeNode *);
void printTime();
void printSkin();
char in[20];
char out[20];
main()
{
	char filename[20] = "function.txt";
	char c;	
	printSkin();
	//printf("请输入代码文件名:");
	//scanf("%s",filename);
	strcpy(in,filename);
	strcpy(out,filename);
	if (strchr (in, '.') == NULL)
		strcat(in,".c--");
	if (strchr (out, '.') == NULL)
		strcat(out,".cout");
	else
	{
		char* pt = strchr (out, '.');
		strncpy(pt,".out",4);
	}
    yyin = (FILE *) fopen(in, "r" );
	if(yyin == NULL){
		printf("代码文件 %s 打开失败:\n", in);
		system("pause");
		return 0;
	}
	printf("%s 已打开，按任意键将进行词法分析....\n",in); 
	getchar();
	getchar();
	system("cls");
	printSkin();	
	printf("代码文件 %s 词法分析如下:\n",in);
	yyparse();
	printf("\n词法分析完毕! 是否进行语法分析(Y/N)? ");
	c=getchar();	
	if(c=='Y'||c=='y')
	{  
		printf("\n语法分析开始....");
		printf("\n语法树如下...\n");		
		printTree(parseTree);		
		//打印图形化语法树 
		//ex(parseTree);
		yyin = (FILE *) fopen(in, "r" );
		yyout = (FILE *) fopen(out,"w");
		yyparse();
		printTree(parseTree);     
		printf("\n");  	
		getchar();
		printf("语法分析结束!\n");
		printf("是否打印四元式(Y/N)? ");
		c=getchar();
		if(c=='Y'||c=='y')
		{
			printFour(parseTree);
		}
		else
			exit(0);	
	}
	else
		exit(0);	
}
void printSkin()
{
	printf("================================================================\n");
	printf("                      欢迎使用 C-MINUS!\n");printTime();
	printf("================================================================\n");
}
void printTime( )
{
	time_t T;  
	struct tm  *TimeNow;
	time(&T);TimeNow=localtime(&T);
	printf("                        %d年%d月%d日\n",1900+TimeNow->tm_year,1+(TimeNow->tm_mon),TimeNow->tm_mday);
}
