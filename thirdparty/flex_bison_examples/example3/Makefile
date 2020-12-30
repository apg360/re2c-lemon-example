


main: main.c example2.c
	gcc -o main main.c example2.c -lfl


example2.c: example2.l 
	flex example2.l
	test -e lex.yy.c && mv lex.yy.c example2.c


clean:
	rm -f *.o a.out example2 example2.c main


