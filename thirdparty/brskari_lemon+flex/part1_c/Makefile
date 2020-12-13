CFLAGS := $(CFLAGS) -std=c11

shell: main.o shellparser.o
	$(CC) main.o shellparser.o -o shell

main.o: main.c shellparser.h

shellparser.c: lemonfiles

shellparser.h: lemonfiles

.PHONY: lemonfiles
lemonfiles: shellparser.y
	lemon shellparser.y -s

# Prevent yacc from trying to build parsers.
# http://stackoverflow.com/a/5395195/79202
%.c: %.y

.PHONY: clean
clean:
	rm -f *.o
	rm -f shellparser.c
	rm -f shellparser.h
	rm -f shell
	rm -f shellparser.out
