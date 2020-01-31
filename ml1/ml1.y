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
%token ADD SUB MUL LP RP LF
%type <int_value> exp_int exp_int_mul exp_int_prim val_int
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
    : exp_int {
        printf("%d\n", $1);
    }
    ;
exp_int
    : exp_int_mul
    | exp_int ADD exp_int_mul {
        $$ = $1 + $3;
        printf("%d + %d evalto %d\n", $1, $3, $$);
    }
    | exp_int SUB exp_int_mul {
        $$ = $1 - $3;
        printf("%d - %d evalto %d\n", $1, $3, $$);
    }
    ;
exp_int_mul
    : exp_int_prim
    | exp_int_mul MUL exp_int_prim {
        $$ = $1 * $3;
        printf("%d * %d evalto %d\n", $1, $3, $$);
    }
    ;
exp_int_prim
    : val_int
    | LP exp_int RP {
        $$ = $2;
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
    fprintf(stderr, "parser error near %s\n", yytext);
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
