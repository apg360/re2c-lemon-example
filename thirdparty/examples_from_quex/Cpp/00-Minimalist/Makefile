all: lexer

tiny/tiny.cpp: tiny.qx
	# (1) Generate the lexical analyzer
	quex -i tiny.qx -o tiny

lexer: lexer.cpp tiny/tiny.cpp
	# (2) Compile the lexical analyzer
	g++ lexer.cpp tiny/tiny.cpp -I. -Wall -Werror -o lexer 

clean:
	rm -rf lexer tiny/ build
