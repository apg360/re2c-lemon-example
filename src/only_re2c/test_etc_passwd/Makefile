CFLAGS := $(CFLAGS) -std=c11
# Prevent yacc from trying to build parsers.
# http://stackoverflow.com/a/5395195/79202
%.c: %.y

all: etc_passwd

#parser.c
mycalc: scanner.h
	
	$(CC) etc_passwd.c -o etc_passwd

scanner.h: etc_passwd.re
	re2c -o etc_passwd.c etc_passwd.re

clean:
	rm -rf *.o etc_passwd.c etc_passwd

.PHONY: all clean

