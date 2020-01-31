%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define YYDEBUG 1

extern int yylex();
extern int yyerror(const char*);
%}
%union {
    int int_value;
    bool bool_value;
}
%token <int_value> INT
%token ADD SUB MUL LF
%type <int_value> exp_int_2 exp_int_1 val_int
%%
lines
    : line {
        printf("> ");
    }
    | lines line {
        printf("> ");
    }
    ;
line
    : exp LF
    ;
exp
    : exp_int_1 {
        printf("%d\n", $1);
    }
    ;
exp_int_1
    : exp_int_2
    | exp_int_1 ADD exp_int_2 {
        $$ = $1 + $3;
        printf("%d + %d evalto %d\n", $1, $3, $$);
    }
    | exp_int_1 SUB exp_int_2 {
        $$ = $1 - $3;
        printf("%d - %d evalto %d\n", $1, $3, $$);
    }
    ;
exp_int_2
    : val_int
    | exp_int_2 MUL val_int {
        $$ = $1 * $3;
        printf("%d * %d evalto %d\n", $1, $3, $$);
    }
    ;
val_int
    : INT
    | SUB INT {
        $$ = -$2;
    }
    ;
%%
extern char *yytext;
extern FILE *yyin;

extern int yyparse(void);

int yyerror(const char *str) {
    fprintf(stderr, "parser error near %s", yytext);
    return 0;
}

int main(void)
{
    yyin = stdin;
    printf("> ");
    if (yyparse()) {
        fprintf(stderr, "error\n");
        return 1;
    }

    printf("\n");
    return 0;
}
