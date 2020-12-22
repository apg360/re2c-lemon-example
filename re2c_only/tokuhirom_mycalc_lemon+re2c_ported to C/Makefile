CFLAGS := $(CFLAGS) -std=c11
# Prevent yacc from trying to build parsers.
# http://stackoverflow.com/a/5395195/79202
%.c: %.y

all: mycalc

#parser.c
mycalc: scanner.h parser.c
	$(CC) main.c -o testre2c

parser.c: parser.lem
	lemon parser.lem

scanner.h: scanner.re
	re2c scanner.re -o scanner.h -i

clean:
	rm -rf *.o parser.h parser.out parser.c scanner.h testre2c

.PHONY: all clean

