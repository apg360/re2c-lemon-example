CFLAGS := $(CFLAGS) -std=c11
# Prevent yacc from trying to build parsers.
# http://stackoverflow.com/a/5395195/79202
%.c: %.y
%.c: %.l

all: mycalc

mycalc:
	lemon example1.lem -l
	$(CC) -o testlemon main.c example1.c

clean:
	rm -rf *.o example1.h example1.out example1.c scanner.h testlemon

.PHONY: all clean

