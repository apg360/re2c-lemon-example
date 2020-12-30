# PURPOSE: Multiple Lexers same Token
#
# License: MIT; Project http://quex.sourceforge.net
# (C) Frank-Rene Schaefer; FREE OF CHARGE--ABSOLUTELY NO WARRANTY.
#_______________________________________________________________________________
.PHONY:     clean
.SECONDARY:

COMPILER := g++ -pedantic -Wconversion -Wall -Werror -W # -ggdb
LD       := $(COMPILER) -I./ -IA_B_C $(ADD_FLAGS) 
# HINTS:    -DQUEX_OPTION_ASSERTS_DISABLED_EXT
#           -DQUEX_OPTION_ASSERTS_WARNING_MESSAGE_DISABLED_EXT 
#           -DQUEX_OPTION_DEBUG_SHOW_EXT

all: lexer

lexer: max/Lexer.cpp moritz/Lexer.cpp boeck/Lexer.cpp lexer.cpp A_B_C/Global-token.cpp
	$(LD) $^ -o  $@ `icu-config --ldflags` 
	 
COMMON_TOKEN_OPTIONS = --token-class-file A_B_C/Global-token \
	                   --suppress         0 1 6

max/Lexer.cpp:    max.qx A_B_C/Global-token.cpp 
	quex -i $< -o max::Lexer --odir max -b 4 --token-id-prefix MAX_TKN_ \
	     $(COMMON_TOKEN_OPTIONS) --no-lib-quex

moritz/Lexer.cpp: moritz.qx A_B_C/Global-token.cpp 
	quex -i $< -o moritz::Lexer --odir moritz -b 4 --token-id-prefix MORITZ_TKN_ \
	     $(COMMON_TOKEN_OPTIONS) --no-lib-quex

boeck/Lexer.cpp:  boeck.qx A_B_C/Global-token.cpp 
	quex -i $< -o boeck::Lexer --odir boeck -b 4 --token-id-prefix TKN_ \
	     $(COMMON_TOKEN_OPTIONS) --no-lib-quex

A_B_C/Global-token.cpp: 
	quex -i token_ids.qx --token-class-only -o Global --token-class Common::Token \
		 --odir A_B_C    -b 4
		 # generate lib-quex

clean:
	rm -rf max/ moritz/ boeck/ A_B_C/ *.o lexer tmp.* build
