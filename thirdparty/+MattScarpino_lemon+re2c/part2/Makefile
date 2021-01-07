PROJ=simple_c

CC=gcc
LEXER=re2c
PARSER=lemon
GRAMMAR=$(PROJ)_grammar

$(PROJ): $(PROJ).re $(GRAMMAR).c
	$(LEXER) -o $(PROJ).c $(PROJ).re
	$(CC) -O3 $(CFLAGS) -o $@ $(PROJ).c $(GRAMMAR).c

$(GRAMMAR).c: $(GRAMMAR).y
	$(PARSER) $(GRAMMAR).y

.PHONY: clean

clean:
	rm $(PROJ) $(GRAMMAR).h $(GRAMMAR).c $(GRAMMAR).out $(PROJ).c
