main: main.o lexer.o parser.o
	cc -o main  main.c lexer.o parser.c -lm
#	if you know you'll be using gcc
#	 gcc -o main -Wall main.c lexer.o parser.c -lm


parser.o: parser.c

parser.c: parser.y
	bison -d parser.y
	test -e parser.tab.c && mv parser.tab.c parser.c
	test -e parser.tab.h && mv parser.tab.h parser.h
parser.h: parser.c

lexer.o: lexer.c

lexer.c: lexer.l parser.h
	flex lexer.l
	test -e lex.yy.c && mv lex.yy.c lexer.c


clean:
	rm -f main *.o parser.h parser.c lexer.c a.out 

test: main
	./main
