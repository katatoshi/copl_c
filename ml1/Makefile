ml1 : y.tab.c lex.yy.c
	gcc -o ml1 $^

y.tab.c : ml1.y
	yacc -dv -o $@ $^

lex.yy.c : ml1.l
	lex -o $@ $^

clean :
	rm -f ./lex.yy.c

.PHONY : clean
