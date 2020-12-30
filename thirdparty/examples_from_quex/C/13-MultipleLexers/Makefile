# PURPOSE: Multiple Lexers
#
# License: MIT; Project http://quex.sourceforge.net
# (C) Frank-Rene Schaefer; FREE OF CHARGE--ABSOLUTELY NO WARRANTY.
#_______________________________________________________________________________
.PHONY: clean
.SECONDARY:

COMPILER := gcc -pedantic -Wconversion -Wall -Werror -W 
LD       := $(COMPILER) -I./ -Iboeck $(ADD_FLAGS) 
# HINTS:    -DQUEX_OPTION_ASSERTS_DISABLED_EXT
#           -DQUEX_OPTION_ASSERTS_WARNING_MESSAGE_DISABLED_EXT 
#           -DQUEX_OPTION_DEBUG_SHOW_EXT

all: lexer

lexer: lexer.c max/max.c moritz/moritz.c boeck/boeck.c
	$(LD) $^ -o $@ 
	 
max/max.c:    max.qx
	quex -i token.qx $< -o max -b 4 \
	     --token-id-prefix MAX_TKN_ --suppress 6 --language C --no-lib-quex

moritz/moritz.c: moritz.qx
	quex -i token.qx $< -o moritz -b 2 \
		 --token-id-prefix MORITZ_TKN_ --suppress 6 --language C --no-lib-quex

boeck/boeck.c:  boeck.qx
	quex -i token.qx $< -o boeck --encoding utf8 \
		--token-id-prefix TKN_ --suppress 6 --language C # for once: lib-quex

clean:
	rm -rf max/ moritz/ boeck/ *.o lexer tmp.* build
