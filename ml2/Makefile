ml2 : ml2_semantics.o y.tab.o lex.yy.o main.o
	gcc -o $@ $^

run : ml2
	./ml2

y.tab.c : ml2.y
	yacc -dv -o $@ $^

lex.yy.c : ml2.l
	lex -o $@ $^

test : test_ml2_semantics.o ml2_semantics.o
	gcc -o $@ $^

run_test : test
	./test

.c.o :
	gcc -c $<

ml2_semantics.o : ml2_semantics.h

y.tab.o : ml2_semantics.h

lex.yy.o : ml2_semantics.h y.tab.h

main.o : ml2_semantics.h y.tab.h

test_ml2_semantics.o : ml2_semantics.h

clean :
	rm -f ./ml2
	rm -f ./test
	rm -f ./lex.yy.c y.tab.c y.tab.h y.output
	rm -f ./test_ml2_semantics
	rm -f ./*.o

.PHONY : clean
