# PURPOSE: Linking Lexical Analysis with Bison generated Parser.
#
# License: MIT; Project http://quex.sourceforge.net
# (C) Frank-Rene Schaefer; FREE OF CHARGE--ABSOLUTELY NO WARRANTY.
#_______________________________________________________________________________
.PHONY: clean
.SECONDARY:

COMPILER := gcc -ggdb -pedantic -Wall -Werror 
LD       := $(COMPILER) -I./ $(ADD_FLAGS) 
# HINTS: -DQUEX_OPTION_ASSERTS_DISABLED_EXT
#        -DQUEX_OPTION_ASSERTS_WARNING_MESSAGE_DISABLED_EXT 
#        -DQUEX_OPTION_DEBUG_SHOW_EXT

all: parser

parser: main.c lexical_analysis/Calc_lexer.c Calc_parser.tab.c
	$(LD) -o $@ $^ -lm -Wno-sign-conversion -Wno-conversion

lexical_analysis/Calc_lexer.c: Calc_lexer.qx Calc_parser.tab.h
	quex -i $< -o Calc_lexer --token-id-prefix TKN_ \
          --foreign-token-id-file Calc_token-ids.h  \
		  --odir lexical_analysis --suppress 0 --language C         

Calc_parser.tab.h \
Calc_parser.tab.c:  Calc_parser.y
	bison $<

clean:	
	rm -rf parser lexical_analysis/ tmp.* Calc_parser.tab.c Calc_parser.tab.h *.o build
