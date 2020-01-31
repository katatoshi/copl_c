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
%token <bool_value> BOOL
%token ADD SUB MUL LT LP RP LF
%type <int_value> exp_int exp_int_mul exp_int_prim val_int
%type <bool_value> exp_bool exp_bool_prim val_bool
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
    | exp_bool {
        printf("%s\n", $1 ? "true" : "false");
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
exp_bool
    : exp_bool_prim
    | exp_int LT exp_int {
        $$ = $1 < $3;
        printf("%d < %d evalto %s\n", $1, $3, $$ ? "true" : "false");
    }
    ;
exp_bool_prim
    : val_bool
    | LP exp_bool RP {
        $$ = $2;
    }
    ;
val_bool
    : BOOL
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
