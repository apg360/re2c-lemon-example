CFLAGS := $(CFLAGS) -std=c99

test: test_tokenizer test_isadate
	./test_tokenizer.sh
	./test_isadate.sh

test_tokenizer: ../dateparser.c tokentos.c test_tokenizer.c ../dategrammar.c ../dategrammar.h
	cat ../dateparser.c tokentos.c test_tokenizer.c > t.c
	${CC} -I.. -o $@ t.c
	rm t.c

test_isadate: ../dateparser.c test_isadate.c ../dategrammar.c ../dategrammar.h
	cat ../dateparser.c test_isadate.c > t.c
	${CC} -I.. -o $@ t.c
	rm t.c

tokentos.c: ../dategrammar.h tokentos.awk
	cat ../dategrammar.h | awk -f tokentos.awk > t.c
	mv t.c $@

clean:
	rm -f *.o
	rm -f test_tokenizer
	rm -f y.tab.c
	rm -f tokentos.c
	rm -f t.c
	rm -f test_isadate