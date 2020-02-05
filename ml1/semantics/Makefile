ml1_semantics: ml1_semantics.o
	gcc -o $@ $^

.c.o:
	gcc -c $<

ml1_semantics.o: ml1_semantics.h

clean :
	rm -f ./ml1_semantics
	rm -f ./ml1_semantics.o

.PHONY : clean
