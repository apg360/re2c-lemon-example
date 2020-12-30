# PURPOSE: Makefile Demo Application of Quex
#
# ABSOLUTELY NO WARRANTY
#_______________________________________________________________________________
.PHONY: clean
.SECONDARY:

COMPILER := g++ -ggdb -pedantic -Wconversion -Wall -Werror -W
LD       := $(COMPILER) -I./ $(ADD_FLAGS) 
# HINTS: -DQUEX_OPTION_ASSERTS_DISABLED_EXT
#        -DQUEX_OPTION_ASSERTS_WARNING_MESSAGE_DISABLED_EXT 
#        -DQUEX_OPTION_DEBUG_SHOW_EXT

all:   lexer lexer2

lexer: easy.qx 
	quex -i patterns.qx tokens.qx common.qx easy.qx -o Easy
	$(LD) lexer.cpp Easy/Easy.cpp -o $@ 
         
lexer2: easy2.qx 
	quex -i patterns.qx tokens.qx common.qx easy2.qx -o Easy2
	$(LD) -DLEXER2 lexer.cpp Easy2/Easy2.cpp -o $@ 

clean:	
	rm -rf lexer lexer2 Easy/ Easy2/ *.o tmp.* build
