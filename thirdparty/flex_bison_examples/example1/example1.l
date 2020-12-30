/*  Flex Scanner Example1.l


    Compile:

       $ flex example1.l
       $ test -e lex.yy.c && mv lex.yy.c example1.c
       $ gcc -o example1   example1.c  -lfl


*/
%{


/*  headers can go here if needed 
#include <math.h>
#include <string.h>
*/

int num_lines = 0, num_chars = 0, num_ctl = 0, num_punct = 0;
int num_int = 0, num_float = 0, num_space = 0;
%}




%%

\n           ++num_lines;  ++num_chars;




[\`|\*|\\|\"|\'|\!|\.]      {  
                        ++num_punct;  
                        ++num_chars;
                        fprintf(stderr,"->%s<- punct char\n",yytext);
                      }



([0-9])+             {
                       fprintf(stderr,"--> Int digit(s) %s\n",yytext);
                       num_chars += yyleng;
                       ++num_int;

                     }


                     /* Longest rule get's matched.  If 2 rules are the same size, it is the top rule. */
([0-9])+"."([0-9])*  {
                       fprintf(stderr,"--> Float digit(s) %s\n",yytext);
                       num_chars += yyleng;
                       ++num_float;

                     }


[ ]                  {
                       ++num_space;

                     }

[^A-Z\n|^a-z\n|^0-9\n|^ ]   {
                         ++num_ctl;    
                         ++num_chars;
                         fprintf(stderr,"ctl dec val=%d\n",yytext[0]);

                       }





.            ++num_chars;

%%
int main(void)
{
	yylex();
	printf("\nSTATS:\n # of lines = %d, # of chars = %d  # of ctl-chars %d\n"
               " # of floats %d  # of ints %d\n"
               " # of punct = %d # of spaces = %d\n", 
                num_lines, num_chars, num_ctl, num_float, num_int, num_punct,num_space);

        return 0;
}
