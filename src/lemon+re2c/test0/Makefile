CFLAGS := $(CFLAGS) -std=c11
# Prevent yacc from trying to build parsers.
# http://stackoverflow.com/a/5395195/79202
# You can see all of GNU make's built-in rules by running make -p -f /dev/null
%.c: %.y
%.c: %.l

all: mycalc

mycalc:
	lemon parser.lem -s -l
	re2c scanner.re2c -o scanner.h -i
	$(CC) -o mycalc main.c parser.c

shell: main.o parser.o
	$(CC) main.o parser.o -o mycalc

clean:
	rm -f *.o scanner.h parser.c parser.h parser.out mycalc

.PHONY: all clean
