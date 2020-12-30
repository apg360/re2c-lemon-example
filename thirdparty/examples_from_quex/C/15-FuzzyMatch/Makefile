all: vowel_tolerance dna_statistics spelling # measure_edit_distance

CC := gcc -Wall -Werror

vowel_tolerance: vowel_tolerance.c vowel_tolerance.qx
	quex -i vowel_tolerance.qx --encoding utf8 -o TolerantLex --language C
	$(CC)  -I. $< TolerantLex/TolerantLex.c -o $@
	
dna_statistics: dna.c dna.qx
	quex -i dna.qx -o DnaLex --language C
	$(CC)  -I. $< DnaLex/DnaLex.c -o $@ -ggdb

spelling: spelling.c spelling.qx
	quex -i spelling.qx -o SpellLex --language C
	$(CC)  -I. $< SpellLex/SpellLex.c -o $@ -ggdb

measure_edit_distance: measure_edit_distance.c measure_edit_distance.qx
    # quex -i measure_edit_distance.qx -o EdLex --language C
	$(CC)  -I. $< EdLex/EdLex.c -o $@ -ggdb
	
clean:
	rm -rf vowel_tolerance TolerantLex dna_statistics DnaLex spelling SpellLex build EdLex measure_edit_distance
