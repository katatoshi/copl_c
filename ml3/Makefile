ml3 : ml3_semantics.o y.tab.o lex.yy.o main.o
	gcc -o $@ $^

run : ml3
	./ml3

y.tab.c : ml3.y
	yacc -dv -o $@ $^

lex.yy.c : ml3.l
	lex -o $@ $^

test : test_ml3_semantics.o ml3_semantics.o
	gcc -o $@ $^

run_test : test
	./test

.c.o :
	gcc -c $<

ml3_semantics.o : ml3_semantics.h

y.tab.o : ml3_semantics.h

lex.yy.o : ml3_semantics.h y.tab.h

main.o : ml3_semantics.h y.tab.h

test_ml3_semantics.o : ml3_semantics.h

clean :
	rm -f ./ml3
	rm -f ./test
	rm -f ./lex.yy.c y.tab.c y.tab.h y.output
	rm -f ./test_ml3_semantics
	rm -f ./*.o

.PHONY : clean
