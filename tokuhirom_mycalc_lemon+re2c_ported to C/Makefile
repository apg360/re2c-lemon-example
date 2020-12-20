# Prevent yacc from trying to build parsers.
# http://stackoverflow.com/a/5395195/79202
# You can see all of GNU make's built-in rules by running make -p -f /dev/null
%.c: %.y
%.c: %.l

all: mycalc

mycalc: scanner.h parser.c
	$(CXX) -o mycalc main.cc

parser.c: parser.yy
	lemon parser.yy

scanner.h: scanner.re
	re2c scanner.re > scanner.h -i

clean:
	rm -rf *.o parser.h parser.out parser.c scanner.h mycalc

.PHONY: all clean

