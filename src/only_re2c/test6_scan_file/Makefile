PROJ=scan_file

CC=gcc
LEXER=re2c

$(PROJ): $(PROJ).re
	$(LEXER) -o $(PROJ).c $(PROJ).re
	$(CC) -O3 $(CFLAGS) -o $@ $(PROJ).c

.PHONY: clean

clean:
	rm $(PROJ) $(PROJ).c
