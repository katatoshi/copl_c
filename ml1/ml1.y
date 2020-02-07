%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ml1_semantics.h"

#define YYDEBUG 1

extern int yylex();
extern int yyerror(const char*);
%}
%union {
    Exp *exp;
}
%token <exp> INT BOOL
%token ADD SUB MUL LT LP RP LF
%type <exp> exp_int exp_int_mul exp_int_prim val_int exp_bool exp_bool_prim val_bool
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
        Value *value = evaluate($1);
        if (value == NULL || value->type != INT_VALUE) {
            printf("error\n");
        }

        printf("%d\n", value->int_value);
        free_value(value);
        free_exp($1);
    }
    | exp_bool {
        Value *value = evaluate($1);
        if (value == NULL || value->type != BOOL_VALUE) {
            printf("error\n");
        }

        printf("%s\n", value->bool_value ? "true" : "false");
        free_value(value);
        free_exp($1);
    }
    ;
exp_int
    : exp_int_mul
    | exp_int ADD exp_int_mul {
        $$ = create_plus_op_exp($1, $3);
    }
    | exp_int SUB exp_int_mul {
        $$ = create_minus_op_exp($1, $3);
    }
    ;
exp_int_mul
    : exp_int_prim
    | exp_int_mul MUL exp_int_prim {
        $$ = create_times_op_exp($1, $3);
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
        $$ = create_int_exp(-$2->int_exp->int_value);
        free_exp($2);
    }
    ;
exp_bool
    : exp_bool_prim
    | exp_int LT exp_int {
        $$ = create_lt_op_exp($1, $3);
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
#include "ml1_semantics.h"
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
