# PURPOSE: Lexical analyzers based on converters.
# 
#_______________________________________________________________________________
.PHONY: clean
.SECONDARY: # avoid remove of intermediate targets => faster unit testing

COMPILER := gcc -ggdb -pedantic -Wconversion -Wall -Werror -W
LD       := $(COMPILER) 
CC       := $(COMPILER) -c -I./ $(ADD_FLAGS) 
# HINTS: -DQUEX_OPTION_ASSERTS_DISABLED_EXT
#        -DQUEX_OPTION_ASSERTS_WARNING_MESSAGE_DISABLED_EXT 
#        -DQUEX_OPTION_DEBUG_SHOW_EXT

BYTES_PER_CHARACTER = 2 

# Configuration of GNU IConv: some compilers include '-liconv' others do not.
LIBICONV:=#
ifneq (,$(or $(findstring apple, $(shell $(COMPILER) --version)), \
             $(findstring $(COMPILER),icpc cl dmc)))
	LIBICONV:=-liconv
endif

all: lexer lexer-with-bom lexer-icu

lexer:          lexer.o Easy.o
	$(LD) -o $@ lexer.o Easy.o $(LIB_CONV) 
          
lexer-with-bom: lexer-with-bom.o Easy.o
	$(LD) -o $@ lexer-with-bom.o Easy.o $(LIB_CONV) 

lexer-icu:      lexer-icu.o Easy.o
	$(LD) -o $@ lexer-icu.o Easy.o $(LIB_CONV) `icu-config --ldflags`
          
Easy.o: Easy/Easy.c 
	$(CC) $< -o $@ 

lexer.o:          lexer.c Easy/Easy.h
	$(CC) $< -o $@  

lexer-with-bom.o: lexer-with-bom.c Easy/Easy.h
	$(CC) $< -o $@  

lexer-icu.o:      lexer-icu.c Easy/Easy.h
	$(CC) $< -o $@  

Easy/Easy.c \
Easy/Easy.h: definitions.qx end_of_file.qx program.qx 
	quex -i definitions.qx end_of_file.qx program.qx -o Easy \
	     -b $(BYTES_PER_CHARACTER) --language        C                      

# (*) HELPERS __________________________________________________________________
clean: clean_lexer clean_lexer-icu clean_lexer-with-bom
	rm -rf build

clean_lexer:	
	rm -rf lexer Easy/ *.o tmp.*

clean_lexer-with-bom:	
	rm -rf lexer-with-bom Easy/ *.o tmp.*

clean_lexer-icu:	
	rm -rf lexer-icu Easy/ *.o tmp.*
