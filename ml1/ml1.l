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
"<" return LT;
[0-9]+ {
    int value;
    sscanf(yytext, "%d", &value);
    yylval.int_value = value;
    return INT;
}
"false" {
    yylval.bool_value = false;
    return BOOL;
}
"true" {
    yylval.bool_value = true;
    return BOOL;
}
"(" return LP;
")" return RP;
[\t ] ;
"\n" return LF;
<<EOF>> return 0;
%%
