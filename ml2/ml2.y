%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ml2_semantics.h"

#define YYDEBUG 1

extern int yylex();

extern int yyerror(const char*);

Exp *parsed_exp;

bool is_eof;
%}
%union {
    Var *var;
    Exp *exp;
}
%token <var> VAR
%token <exp> INT BOOL
%token PLUS MINUS TIMES LT IF THEN ELSE LET EQ IN LP RP LF QUIT END_OF_FILE
%type <exp> exp exp_lt exp_plus exp_times exp_primary
%%
line
    : exp LF {
        is_eof = false;
        if (parsed_exp != NULL) {
            free_exp(parsed_exp);
        }
        parsed_exp = $1;
        return 0;
    }
    | LF {
        is_eof = false;
        if (parsed_exp != NULL) {
            free_exp(parsed_exp);
        }
        parsed_exp = NULL;
        return 0;
    }
    | END_OF_FILE {
        is_eof = true;
        if (parsed_exp != NULL) {
            free_exp(parsed_exp);
        }
        parsed_exp = NULL;
        return 0;
    }
    ;
exp
    : exp_lt
    | IF exp THEN exp ELSE exp {
        $$ = create_if_exp($2, $4, $6);
    }
    | LET VAR EQ exp IN exp {
        $$ = create_let_exp($2, $4, $6);
    }
    ;
exp_lt
    : exp_plus
    | exp_lt LT exp_plus {
        $$ = create_lt_op_exp($1, $3);
    }
    ;
exp_plus
    : exp_times
    | exp_plus PLUS exp_times {
        $$ = create_plus_op_exp($1, $3);
    }
    | exp_plus MINUS exp_times {
        $$ = create_minus_op_exp($1, $3);
    }
    ;
exp_times
    : exp_primary
    | exp_times TIMES exp_primary {
        $$ = create_times_op_exp($1, $3);
    }
    ;
exp_primary
    : INT
    | MINUS INT {
        $$ = create_int_exp(-$2->int_exp->int_value);
        free_exp($2);
    }
    | BOOL
    | VAR {
        $$ = create_var_exp($1->name);
        free_var($1);
    }
    | LP exp RP {
        $$ = $2;
    }
    ;
%%
extern char *yytext;

int yyerror(const char *str) {
    fprintf(stderr, "parser error near %s\n", yytext);
    return 0;
}
