%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ml1_semantics.h"

#define YYDEBUG 1

extern int yylex();

extern int yyerror(const char*);

Exp *parsed_exp;
%}
%union {
    Exp *exp;
}
%token <exp> INT BOOL
%token PLUS MINUS TIMES LT LP RP LF QUIT END_OF_FILE
%type <exp> exp int_exp times_exp plus_exp bool_exp lt_exp
%%
line
    : exp LF {
        if (parsed_exp != NULL) {
            free_exp(parsed_exp);
        }
        parsed_exp = $1;
        return 0;
    }
    | END_OF_FILE {
        if (parsed_exp != NULL) {
            free_exp(parsed_exp);
        }
        parsed_exp = NULL;
        return 0;
    }
    ;
exp
    : plus_exp
    | lt_exp
    ;
plus_exp
    : times_exp
    | plus_exp PLUS times_exp {
        $$ = create_plus_op_exp($1, $3);
    }
    | plus_exp MINUS times_exp {
        $$ = create_minus_op_exp($1, $3);
    }
    ;
times_exp
    : int_exp
    | times_exp TIMES int_exp {
        $$ = create_times_op_exp($1, $3);
    }
    ;
int_exp
    : INT
    | MINUS INT {
        $$ = create_int_exp(-$2->int_exp->int_value);
        free_exp($2);
    }
    | LP plus_exp RP {
        $$ = $2;
    }
    ;
lt_exp
    : bool_exp
    | plus_exp LT plus_exp {
        $$ = create_lt_op_exp($1, $3);
    }
    ;
bool_exp
    : BOOL
    | LP lt_exp RP {
        $$ = $2;
    }
    ;
%%
extern char *yytext;

int yyerror(const char *str) {
    fprintf(stderr, "parser error near %s\n", yytext);
    return 0;
}
