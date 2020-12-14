CFLAGS := $(CFLAGS) -std=c11
# Prevent yacc from trying to build parsers.
# http://stackoverflow.com/a/5395195/79202
# You can see all of GNU make's built-in rules by running make -p -f /dev/null
%.c: %.y
%.c: %.l

shell: main.o parser.o
	$(CC) main.o parser.o -o shell

main.o: main.c scanner.re2c.h parser.h

#Parser#
parser.c: lemonfiles
parser.h: lemonfiles

.PHONY: lemonfiles
lemonfiles: parser.lem
	lemon parser.lem -s

#Scanner#
scanner.o: scanner.re2c.h

scanner.re2c.h: flexfiles

.PHONY: flexfiles
flexfiles: scanner.re2c
	re2c scanner.re2c -o scanner.re2c.h -i

#make clean#
.PHONY: clean
clean:
	rm -f *.o
	rm -f scanner.re2c.h
	rm -f parser.c parser.h parser.out
	rm -f shell
