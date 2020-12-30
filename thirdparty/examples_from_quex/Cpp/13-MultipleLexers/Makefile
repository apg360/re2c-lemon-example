# PURPOSE: Multiple Lexers
#
# License: MIT; Project http://quex.sourceforge.net
# (C) Frank-Rene Schaefer; FREE OF CHARGE--ABSOLUTELY NO WARRANTY.
#_______________________________________________________________________________
.PHONY: clean
.SECONDARY:

COMPILER := g++ -pedantic -Wconversion -Wall -Werror -W
LD       := $(COMPILER) -I./ -Iboeck $(ADD_FLAGS) 
# HINTS:    -DQUEX_OPTION_ASSERTS_DISABLED_EXT
#           -DQUEX_OPTION_ASSERTS_WARNING_MESSAGE_DISABLED_EXT 
#           -DQUEX_OPTION_DEBUG_SHOW_EXT

all: lexer

lexer: lexer.cpp max/max.cpp moritz/moritz.cpp boeck/boeck.cpp
	$(LD) $^ -o $@ 
	 
max/max.cpp:    max.qx
	quex -i token.qx $< -o lexer::max -b 4 \
	     --token-id-prefix MAX_TKN_ --suppress 6 --no-lib-quex

moritz/moritz.cpp: moritz.qx
	quex -i token.qx $< -o lexer::moritz -b 2 \
		 --token-id-prefix MORITZ_TKN_ --suppress 6 --no-lib-quex

boeck/boeck.cpp:  boeck.qx
	quex -i token.qx $< -o lexer::boeck --encoding utf8 \
		 --token-id-prefix TKN_ --suppress 6 # for once: lib-quex

clean:
	rm -rf max/ moritz/ boeck/ *.o lexer tmp.* build
