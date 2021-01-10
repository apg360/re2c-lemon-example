
example1: example1.c
	gcc -o example1   example1.c  -lfl

example1.c: example1.l 
	flex example1.l
	test -e lex.yy.c && mv lex.yy.c example1.c


clean:
	rm -f *.o a.out example1 example1.c


