ml1 : y.tab.c lex.yy.c
	gcc -o ml1 $^

run_ml1 : ml1
	./ml1

y.tab.c : ml1.y
	yacc -dv -o $@ $^

lex.yy.c : ml1.l
	lex -o $@ $^

test_ml1_semantics : test_ml1_semantics.o ml1_semantics.o
	gcc -o $@ $^

run_test_ml1_semantics : test_ml1_semantics
	./test_ml1_semantics

.c.o :
	gcc -c $<

ml1_semantics.o : ml1_semantics.h

clean :
	rm -f ./ml1
	rm -f ./lex.yy.c y.tab.c y.tab.h y.output
	rm -f ./test_ml1_semantics
	rm -f ./*.o

.PHONY : clean
