all: lexer

tiny/tiny.c: tiny.qx
	# (1) Generate the lexical analyzer
	quex -i tiny.qx -o tiny --language C

lexer: lexer.c tiny/tiny.c
	# (2) Compile the lexical analyzer
	gcc lexer.c tiny/tiny.c -I. -Wall -Werror -o lexer 

clean:
	rm -rf lexer tiny/ build
