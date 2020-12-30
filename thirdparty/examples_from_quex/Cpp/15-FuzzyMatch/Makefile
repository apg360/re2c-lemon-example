all: vowel_tolerance dna_statistics spelling # measure_edit_distance

CC := g++ -Wall -Werror

vowel_tolerance: vowel_tolerance.cpp vowel_tolerance.qx
	quex -i vowel_tolerance.qx --encoding utf8 -o TolerantLex 
	$(CC) -I. $< TolerantLex/TolerantLex.cpp -o $@
	
dna_statistics: dna.cpp dna.qx
	quex -i dna.qx -o DnaLex 
	$(CC) -I. $< DnaLex/DnaLex.cpp -o $@ -ggdb

spelling: spelling.cpp spelling.qx
	quex -i spelling.qx -o SpellLex 
	$(CC) -I. $< SpellLex/SpellLex.cpp -o $@ -ggdb

measure_edit_distance: measure_edit_distance.cpp measure_edit_distance.qx
	# quex -i measure_edit_distance.qx -o EdLex 
	$(CC)  -I. $< EdLex/EdLex.cpp -o $@ -ggdb
	
clean:
	rm -rf vowel_tolerance TolerantLex dna_statistics DnaLex spelling SpellLex build EdLex measure_edit_distance
