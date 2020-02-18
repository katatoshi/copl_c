%{
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ml3_semantics.h"
#include "y.tab.h"

int yywrap(void) {
    return 1;
}
%}
%%
"+" return PLUS;
"-" return MINUS;
"*" return TIMES;
"<" return LT;
"if" return IF;
"then" return THEN;
"else" return ELSE;
"let" return LET;
"=" return EQ;
"in" return IN;
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
([a-z][a-zA-Z0-9_']*|_[a-zA-Z0-9_']+) {
    if (VAR_NAME_LEN_MAX < strlen(yytext)) {
        return 1;
    }

    yylval.var = create_var(yytext);
    return VAR;
}
"(" return LP;
")" return RP;
";;\n" return END_OF_EXP;
"\n" {
    printf("# ");
}
[\t ] ;
<<EOF>> return END_OF_FILE;
. return yytext[0];
%%
