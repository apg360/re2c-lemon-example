CFLAGS := $(CFLAGS) -std=c11
# Prevent yacc from trying to build parsers.
# http://stackoverflow.com/a/5395195/79202
%.c: %.y

all: mycalc

#parser.c
mycalc: scanner.h
	$(CC) main.c -o build/testre2c

#parser.c: parser.yy
#	lemon parser.yy

scanner.h: scanner.re
	re2c scanner.re -o build/scanner.h -i

clean:
	rm -rf *.o parser.h parser.out parser.c scanner.h testre2c

.PHONY: all clean

