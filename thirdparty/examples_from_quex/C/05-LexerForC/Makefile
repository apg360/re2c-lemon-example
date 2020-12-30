# PURPOSE: Lexer for the C-Programming language
#
# License: MIT; Project http://quex.sourceforge.net
# (C) Frank-Rene Schaefer; FREE OF CHARGE--ABSOLUTELY NO WARRANTY.
#_______________________________________________________________________________
.PHONY: clean
.SECONDARY:

COMPILER := gcc -ggdb -pedantic -Wconversion -Wall -Werror -W
LD       := $(COMPILER) 
CC       := $(COMPILER) -c -I./ $(ADD_FLAGS) 
# HINTS: -DQUEX_OPTION_ASSERTS_DISABLED_EXT
#        -DQUEX_OPTION_ASSERTS_WARNING_MESSAGE_DISABLED_EXT 
#        -DQUEX_OPTION_DEBUG_SHOW_EXT

all: lexer

lexer:          lexer.o LexerForC.o
	$(LD) -o $@ lexer.o LexerForC.o 
          
LexerForC.o:  lexical_analysis/LexerForC.c 
	$(CC) $< -o $@ 

lexer.o:      lexer.c lexical_analysis/LexerForC.c
	$(CC) $< -o $@ 

lexical_analysis/LexerForC.c: c.qx 
	quex -i c.qx -o LexerForC --odir lexical_analysis --language C

clean:	
	rm -rf lexer lexical_analysis *.o tmp.* build
