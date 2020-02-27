ml4 : ml4_semantics.o ml4_derivation.o y.tab.o lex.yy.o main.o
	gcc -o $@ $^

run : ml4
	./ml4

y.tab.c : ml4.y
	yacc -dv -o $@ $^

lex.yy.c : ml4.l
	lex -o $@ $^

test : test_ml4_semantics.o ml4_semantics.o ml4_derivation.o
	gcc -o $@ $^

run_test : test
	./test

.c.o :
	gcc -c $<

ml4_semantics.o : ml4_semantics.h

ml4_derivation.o : ml4_derivation.h

y.tab.o : ml4_semantics.h ml4_derivation.h

lex.yy.o : ml4_semantics.h ml4_derivation.h y.tab.h

main.o : ml4_semantics.h ml4_derivation.h y.tab.h

test_ml4_semantics.o : ml4_semantics.h ml4_derivation.h

clean :
	rm -f ./ml4
	rm -f ./test
	rm -f ./lex.yy.c y.tab.c y.tab.h y.output
	rm -f ./test_ml4_semantics
	rm -f ./*.o

.PHONY : clean
