CFLAGS := $(CFLAGS) -std=c11
# Prevent yacc from trying to build parsers.
# http://stackoverflow.com/a/5395195/79202
%.c: %.y

shell: main.o shellparser.o shellscanner.yy.o
	$(CC) main.o shellparser.o shellscanner.yy.o -o shell

main.o: main.c shellscanner.yy.h shellparser.h

#Parser#
shellparser.c: lemonfiles
shellparser.h: lemonfiles

.PHONY: lemonfiles
lemonfiles: shellparser.y
	lemon shellparser.y -s

#Scanner#
shellscanner.o: shellscanner.yy.h shellscanner.yy.c
 
shellscanner.yy.c: flexfiles
shellscanner.yy.h: flexfiles

.PHONY: flexfiles
flexfiles: shellscanner.l
	flex --outfile=shellscanner.yy.c --header-file=shellscanner.yy.h shellscanner.l

#make clean#
.PHONY: clean
clean:
	rm -f *.o
	rm -f shellscanner.yy.c shellscanner.yy.h
	rm -f shellparser.c shellparser.h shellparser.out
	rm -f shell
