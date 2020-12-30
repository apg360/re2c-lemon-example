# PURPOSE: Example for Include-stack Handling
#
# License: MIT; Project http://quex.sourceforge.net
# (C) Frank-Rene Schaefer; FREE OF CHARGE--ABSOLUTELY NO WARRANTY.
#_______________________________________________________________________________
.PHONY: clean
.SECONDARY:

COMPILER := g++ -pedantic -Wconversion -Wall -Werror -W -ggdb
LD       := $(COMPILER) -I./ $(ADD_FLAGS) 
# HINTS: -DQUEX_OPTION_ASSERTS_DISABLED_EXT
#        -DQUEX_OPTION_ASSERTS_WARNING_MESSAGE_DISABLED_EXT 
#        -DQUEX_OPTION_DEBUG_SHOW_EXT
#
all: lexer-1 lexer-2

lexer-1:        approach-1.cpp approach-1/Easy.cpp
	$(LD) -o $@ approach-1.cpp approach-1/Easy.cpp
          
lexer-2:        approach-2.cpp approach-2/Easy.cpp
	$(LD) -o $@ approach-2.cpp approach-2/Easy.cpp
          
approach-1/Easy.cpp: approach-1.qx 
	quex -i approach-1.qx -o Easy --odir approach-1

approach-2/Easy.cpp: approach-2.qx 
	quex -i approach-2.qx -o Easy --odir approach-2

clean: clean_lexer-1 clean_lexer-2
	rm -rf tmp.* *.o build
clean_lexer-1:
	rm -rf lexer-1 approach-1
clean_lexer-2:
	rm -rf lexer-2 approach-2 
