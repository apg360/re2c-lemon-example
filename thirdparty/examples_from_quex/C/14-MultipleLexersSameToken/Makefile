# PURPOSE: Multiple Lexers same Token
#
# License: MIT; Project http://quex.sourceforge.net
# (C) Frank-Rene Schaefer; FREE OF CHARGE--ABSOLUTELY NO WARRANTY.
#_______________________________________________________________________________
.PHONY:     clean
.SECONDARY:

COMPILER := gcc -pedantic -Wconversion -Wall -Werror -W # -ggdb
LD       := $(COMPILER) -I./ -IA_B_C $(ADD_FLAGS) 
# HINTS:    -DQUEX_OPTION_ASSERTS_DISABLED_EXT
#           -DQUEX_OPTION_ASSERTS_WARNING_MESSAGE_DISABLED_EXT 
#           -DQUEX_OPTION_DEBUG_SHOW_EXT

all: lexer

lexer: max/max_Lexer.c moritz/moritz_Lexer.c boeck/boeck_Lexer.c lexer.c A_B_C/Global-token.c
	$(LD) $^ -o  $@ `icu-config --ldflags` 
	 
COMMON_TOKEN_OPTIONS = --token-class-file A_B_C/Global-token.h \
	                   --suppress         0 1 6 

max/max_Lexer.c:       max.qx    A_B_C/Global-token.c 
	quex -i $< -o max_Lexer --odir max -b 4 --token-id-prefix MAX_TKN_ \
		        $(COMMON_TOKEN_OPTIONS) --no-lib-quex --language C 

moritz/moritz_Lexer.c: moritz.qx A_B_C/Global-token.c 
	quex -i $< -o moritz_Lexer --odir moritz -b 4 --token-id-prefix MORITZ_TKN_ \
		        $(COMMON_TOKEN_OPTIONS) --no-lib-quex --language C 

boeck/boeck_Lexer.c:   boeck.qx  A_B_C/Global-token.c 
	quex -i $< -o boeck_Lexer --odir boeck -b 4 --token-id-prefix TKN_ \
		        $(COMMON_TOKEN_OPTIONS) --no-lib-quex --language C 

A_B_C/Global-token.c: 
	quex -i token_ids.qx --token-class-only -o Global --token-class Common_Token \
		 --odir A_B_C -b 4  --language C  
		 # generate lib-quex

clean:
	rm -rf max/ moritz/ boeck/ A_B_C/ *.o lexer tmp.* C build
