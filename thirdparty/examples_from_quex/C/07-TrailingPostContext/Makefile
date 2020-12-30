# PURPOSE: Demo with trailing post context.
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

lexer: lexer.o Easy.o
	$(LD) -o $@ lexer.o Easy.o 
          
Easy.o: easy/Easy.c 
	$(CC) $< -I. -o $@ 

lexer.o: lexer.c easy/Easy.c
	$(CC) $< -o $@ 

easy/Easy.c: easy.qx 
	quex -i easy.qx -o Easy --odir easy --token-id-offset 0x1000 --language C

clean:	
	rm -rf lexer easy/ *.o build
