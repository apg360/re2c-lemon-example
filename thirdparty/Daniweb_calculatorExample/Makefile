CC = gcc
RE2C = re2c
CFLAGS = -Wall -ggdb -c
RE2C_FLAGS =
 
all: calc handcrafted_parser parser
 
calc: scanner.o main.o parser.o
	$(CC) -Wall -o $@ $?
 
scanner.o: scanner.c
	$(CC) $(CFLAGS) $?
scanner.c: scanner.re
	$(RE2C) $(RE2C_FLAGS) -o $@ $?
	$(RE2C) -D -o scanner.graphviz $?
main.o: main.c
	$(CC) $(CFLAGS) $?
handcrafted_parser: handcrafted_parser.o
	$(CC) -Wall -o $@ $?
handcrafted_parser.o: handcrafted_parser.c
	$(CC) $(CFLAGS) $?
parser.o: parser.c
	cat lemon_parser.c >> parser.c
	$(CC) $(CFLAGS) $?
 
parser.c: lemon
	./lemon parser.y
 
lemon: lemon.o
	$(CC) -Wall -o $@ $?
lemon.o:
	$(CC) -o $@ $(CFLAGS) lemon.c $<
 
clean:
	rm -f *.o calc handcrafted_parser parser.{c,h,out}
distclean: clean
	rm -f scanner.c scanner.graphviz lemon
