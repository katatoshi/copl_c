%{
#include <stdio.h>
#include <stdbool.h>
#include "y.tab.h"

int yywrap(void) {
    return 1;
}
%}
%%
"+" return ADD;
"-" return SUB;
"*" return MUL;
[0-9]+ {
    int value;
    sscanf(yytext, "%d", &value);
    yylval.int_value = value;
    return INT;
}
[\t ] ;
"\n" return LF;
<<EOF>> return 0;
%%
