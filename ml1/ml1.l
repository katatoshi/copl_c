%{
#include <stdio.h>
#include <stdbool.h>
#include "ml1_semantics.h"
#include "y.tab.h"

int yywrap(void) {
    return 1;
}
%}
%%
"+" return ADD;
"-" return SUB;
"*" return MUL;
"<" return LT;
[0-9]+ {
    int value;
    sscanf(yytext, "%d", &value);
    yylval.exp = create_int_exp(value);
    return INT;
}
"false" {
    yylval.exp = create_bool_exp(false);
    return BOOL;
}
"true" {
    yylval.exp = create_bool_exp(true);
    return BOOL;
}
"(" return LP;
")" return RP;
[\t ] ;
"\n" return LF;
<<EOF>> return 0;
%%
