# PURPOSE: Engines with Encodings different from Unicode
#
# License: MIT; Project http://quex.sourceforge.net
# (C) Frank-Rene Schaefer; FREE OF CHARGE--ABSOLUTELY NO WARRANTY.
#_______________________________________________________________________________
.PHONY: clean
.SECONDARY:

COMPILER := g++ -ggdb -pedantic -Wconversion -Wall -Werror -W
LD       := $(COMPILER) -I./ $(ADD_FLAGS) 
# HINTS: -DQUEX_OPTION_ASSERTS_DISABLED_EXT
#        -DQUEX_OPTION_ASSERTS_WARNING_MESSAGE_DISABLED_EXT 
#        -DQUEX_OPTION_DEBUG_SHOW_EXT

APPS := iso8859-7-lexer \
	    utf8-lexer      \
		utf16-lexer     \
		utf16-lexer-other

all: $(APPS)

iso8859-7-lexer: iso8859-7-lexer.cpp greek.qx
	quex -i                greek.qx  \
		 --encoding        iso8859_7 \
		 --token-id-prefix TKN_      \
		 -o                ISO8859_7_Lex --odir iso8859-7 
	$(LD) -D__QUEX_TEST_OPTION_ISO8859_7 $< iso8859-7/ISO8859_7_Lex.cpp -o $@

utf8-lexer: utf8-lexer.cpp greek.qx
	quex -i greek.qx            \
		 --encoding utf8        \
		 --token-id-prefix TKN_ \
		 -o UTF8Lex             --odir utf8 
	$(LD) $< utf8/UTF8Lex.cpp -o $@
	
utf16-lexer: utf16-lexer.cpp greek.qx
	quex -i                greek.qx  \
		 --encoding        utf16     \
		 --token-id-prefix TKN_      \
	     -b                2         \
		 -o                UTF16Lex  --odir utf16 
	$(LD) -D__QUEX_TEST_OPTION_UTF16BE $< utf16/UTF16Lex.cpp -o $@

utf16-lexer-other: utf16-lexer-other.cpp greek-other.qx
	quex -i                greek-other.qx  \
		 --encoding        utf16           \
		 --token-id-prefix TKN_            \
	     -b                2               \
		 -o                UTF16Lex --odir utf16-other 
	$(LD) -D__QUEX_TEST_OPTION_UTF16BE $< utf16-other/UTF16Lex.cpp -o $@

clean:
	rm -rf iso8859-7/ utf8/ utf16/ *.o tmp.* $(APPS) utf16-other build

