# PURPOSE: Lexer for the C-Programming language
#
# License: MIT; Project http://quex.sourceforge.net
# (C) Frank-Rene Schaefer; FREE OF CHARGE--ABSOLUTELY NO WARRANTY.
#_______________________________________________________________________________
.PHONY: clean
.SECONDARY:

COMPILER := g++ -ggdb -pedantic -Wconversion -Wall -Werror -W
LD       := $(COMPILER) 
CC       := $(COMPILER) -c -I./ $(ADD_FLAGS) 
# HINTS: -DQUEX_OPTION_ASSERTS_DISABLED_EXT
#        -DQUEX_OPTION_ASSERTS_WARNING_MESSAGE_DISABLED_EXT 
#        -DQUEX_OPTION_DEBUG_SHOW_EXT

all: lexer

lexer:          lexer.o LexerForC.o
	$(LD) -o $@ lexer.o LexerForC.o 
          
LexerForC.o:  lexical_analysis/LexerForC.cpp 
	$(CC) $< -o $@ 

lexer.o:      lexer.cpp lexical_analysis/LexerForC.cpp
	$(CC) $< -o $@ 

lexical_analysis/LexerForC.cpp: c.qx 
	quex -i c.qx -o LexerForC --odir lexical_analysis 

clean:	
	rm -rf lexer lexical_analysis *.o tmp.* build
