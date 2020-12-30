# PURPOSE: Makefile Demo Application of Quex
#
# ABSOLUTELY NO WARRANTY
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

lexer: lexer.o Easy.o
	$(LD) -o $@ lexer.o Easy.o 
          
Easy.o: easy/Easy.cpp 
	$(CC) $< -o $@ 

lexer.o: lexer.cpp easy/Easy
	$(CC) $< -o $@ 

easy/Easy.cpp \
easy/Easy: simple.qx 
	quex -i simple.qx common.qx -o Easy --odir easy \
		 --token-id-offset  0x1000 

clean:	
	rm -rf lexer easy/ *.o tmp.* build
