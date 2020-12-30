# PURPOSE: Manual Buffer Filling via Feeder and Gavager
#
# License: MIT; Project http://quex.sourceforge.net
# (C) Frank-Rene Schaefer; FREE OF CHARGE--ABSOLUTELY NO WARRANTY.
#_______________________________________________________________________________
.PHONY: clean
.SECONDARY:

COMPILER := g++ -ggdb -pedantic -Wconversion -Wall -Werror -W
LD       := $(COMPILER) -I./ $(ADD_FLAGS) 
LD_PLAIN     := $(LD) -DQUEX_SETTING_BUFFER_SIZE_EXT=13 
LD_CONVERTER := $(LD) -DQUEX_SETTING_BUFFER_LEXATOM_LOADER_CONVERTER_BUFFER_SIZE_EXT=6 \
	                  -DQUEX_SETTING_BUFFER_SIZE_EXT=16            \
			          -DQUEX_TYPE_LEXATOM_EXT=wchar_t              \
			          -DQUEX_DEMO_WITH_CONVERTER                   \
			          -DQUEX_DEMO_OPTION_CONVERTER_ICONV
# HINTS: -DQUEX_OPTION_ASSERTS_DISABLED_EXT
#        -DQUEX_OPTION_ASSERTS_WARNING_MESSAGE_DISABLED_EXT 
#        -DQUEX_OPTION_DEBUG_SHOW_EXT

FILES := feeder-plain.exe  feeder-converter.exe  \
	     gavager-plain.exe gavager-converter.exe \
         point-plain.exe

all: $(FILES)

feeder-plain.exe:       lexer-feeder.cpp receiver.cpp  plain/Lexer.cpp
	$(LD_PLAIN)     -o $@ $^ 
          
gavager-plain.exe:      lexer-gavager.cpp receiver.cpp plain/Lexer.cpp
	$(LD_PLAIN)     -o $@ $^ 
          
point-plain.exe:        lexer-point.cpp                plain/Lexer.cpp
	$(LD_PLAIN)     -o $@ $^

feeder-converter.exe:   lexer-feeder.cpp receiver.cpp  converter/Lexer.cpp
	$(LD_CONVERTER) -o $@ $^ 

gavager-converter.exe:  lexer-gavager.cpp receiver.cpp converter/Lexer.cpp
	$(LD_CONVERTER) -o $@ $^ 

plain/Lexer.cpp: lexPlain.qx 
	quex --cbm --fallback-mandatory \
		 -i lexPlain.qx -o Lexer --odir plain 

converter/Lexer.cpp: lexConverter.qx 
	quex --cbm --fallback-mandatory \
		 -i lexConverter.qx -o Lexer --odir converter \
		 --buffer-element-type wchar_t 

clean:	
	rm -rf plain/ converter/ *.o $(FILES) tmp.* build
