/**
 * Example code for flex/yacc
 * Makefile and part of main.c taken from Kyle R. Burton <mortis@voicenet.com>
 * and http://www.gnu.org/manual/bison-1.35/bison.html and modified.
 * 
 * 
 * Author: Mike Chirico <mchirico@med.upenn.edu>
 *  
 * Copyright 2003  Mike Chirico, All rights reserved.
 * This source code is copyrighted under the GNU GPL.
 *
 * Input can be read 1 of 2 ways.  From a file ./main file or
 * if no file is given, it will read from buff and buff2.
 *
 * Note, to show how parser.y handles errors, buff2 is incorrect.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


#define BUFS 1024




/**
 * We have to declare these here - they're not  in any header files 
 * we can inclde.  yyparse() is declared with an empty argument list  
 * so that it is compatible with the generated C code from bison.
 *
 */
extern int yyparse();
extern FILE *yyin;
extern int yy_scan_string(const char *);
extern void reset_lexer(void);
extern void reset_parser(void);


int main(int argc,char** argv)
{

  int n;
  char buf[BUFS+1];


  fprintf(stdout,"Enter some input:\n"
                 "  r=23+35\n"
                 "  r\n"
	  "        58\n"
	  "Terminate input with ^D\n\n");


  /**
   * take input from file only,then, exit
   */
    if ( argc == 2 )
      {
            yyin = fopen( argv[1], "r" );
	    reset_lexer();
	    reset_parser();
	    yyparse();
	    return(1);
	    /*Exit program  from here */
	  }
	    reset_lexer();
	    reset_parser();

 while ( ( n=read(fileno(stdin), buf, BUFS )) >  0)
   {
     buf[n]='\0';
	yy_scan_string(buf);               
	yyparse();

   }





  return 0;
}

