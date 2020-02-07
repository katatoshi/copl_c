ml1 :ml1_semantics.o y.tab.o lex.yy.o main.o
	gcc -o $@ $^

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

y.tab.o : ml1_semantics.h

lex.yy.o : ml1_semantics.h y.tab.h

main.o : ml1_semantics.h y.tab.h

clean :
	rm -f ./ml1
	rm -f ./lex.yy.c y.tab.c y.tab.h y.output
	rm -f ./test_ml1_semantics
	rm -f ./*.o

.PHONY : clean
