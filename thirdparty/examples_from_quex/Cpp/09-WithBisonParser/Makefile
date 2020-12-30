# PURPOSE: Linking Lexical Analysis with Bison generated Parser.
#
# License: MIT; Project http://quex.sourceforge.net
# (C) Frank-Rene Schaefer; FREE OF CHARGE--ABSOLUTELY NO WARRANTY.
#_______________________________________________________________________________
.PHONY: clean
.SECONDARY:

COMPILER := g++ -ggdb -pedantic -Wall -Werror 
LD       := $(COMPILER) -I./ $(ADD_FLAGS) 
# HINTS: -DQUEX_OPTION_ASSERTS_DISABLED_EXT
#        -DQUEX_OPTION_ASSERTS_WARNING_MESSAGE_DISABLED_EXT 
#        -DQUEX_OPTION_DEBUG_SHOW_EXT

all: parser

parser: main.cpp lexical_analysis/Calc_lexer.cpp Calc_parser.tab.cpp
	$(LD) -o $@ $^ -lm -Wno-sign-conversion -Wno-conversion

lexical_analysis/Calc_lexer.cpp: Calc_lexer.qx Calc_parser.tab.hpp
	quex -i $< -o Calc_lexer --token-id-prefix TKN_ \
          --foreign-token-id-file Calc_token-ids.h  \
		  --odir lexical_analysis --suppress 0      

Calc_parser.tab.hpp \
Calc_parser.tab.cpp:  Calc_parser.ypp
	bison $<

clean:	
	rm -rf parser lexical_analysis/ tmp.* Calc_parser.tab.cpp Calc_parser.tab.hpp *.o build
