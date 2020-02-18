%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ml3_semantics.h"

#define YYDEBUG 1

extern int yylex();

extern int yyerror(const char*);

Exp *parsed_exp;
%}
%union {
    Var *var;
    Exp *exp;
}
%token <var> VAR
%token <exp> INT BOOL
%token PLUS MINUS TIMES LT IF THEN ELSE LET EQ IN FUN TO LP RP END_OF_EXP END_OF_FILE
%type <exp> exp exp_lt exp_plus exp_times exp_app exp_primary
%%
line
    : exp END_OF_EXP {
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
    : exp_lt
    | IF exp THEN exp ELSE exp {
        $$ = create_if_exp($2, $4, $6);
    }
    | exp_lt LT IF exp THEN exp ELSE exp {
        $$ = create_lt_op_exp($1, create_if_exp($4, $6, $8));
    }
    | exp_plus PLUS IF exp THEN exp ELSE exp {
        $$ = create_plus_op_exp($1, create_if_exp($4, $6, $8));
    }
    | exp_plus MINUS IF exp THEN exp ELSE exp {
        $$ = create_minus_op_exp($1, create_if_exp($4, $6, $8));
    }
    | exp_times TIMES IF exp THEN exp ELSE exp {
        $$ = create_times_op_exp($1, create_if_exp($4, $6, $8));
    }
    | LET VAR EQ exp IN exp {
        $$ = create_let_exp($2, $4, $6);
    }
    | exp_lt LT LET VAR EQ exp IN exp {
        $$ = create_lt_op_exp($1, create_let_exp($4, $6, $8));
    }
    | exp_plus PLUS LET VAR EQ exp IN exp {
        $$ = create_plus_op_exp($1, create_let_exp($4, $6, $8));
    }
    | exp_plus MINUS LET VAR EQ exp IN exp {
        $$ = create_minus_op_exp($1, create_let_exp($4, $6, $8));
    }
    | exp_times TIMES LET VAR EQ exp IN exp {
        $$ = create_times_op_exp($1, create_let_exp($4, $6, $8));
    }
    | FUN VAR TO exp {
        $$ = create_fun_exp($2, $4);
    }
    | exp_lt LT FUN VAR TO exp {
        $$ = create_lt_op_exp($1, create_fun_exp($4, $6));
    }
    | exp_plus PLUS FUN VAR TO exp {
        $$ = create_plus_op_exp($1, create_fun_exp($4, $6));
    }
    | exp_plus MINUS FUN VAR TO exp {
        $$ = create_minus_op_exp($1, create_fun_exp($4, $6));
    }
    | exp_times TIMES FUN VAR TO exp {
        $$ = create_times_op_exp($1, create_fun_exp($4, $6));
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
    : exp_app
    | exp_times TIMES exp_app {
        $$ = create_times_op_exp($1, $3);
    }
    ;
exp_app
    : exp_primary
    | exp_primary INT {
        $$ = create_app_exp($1, $2);
    }
    | exp_primary BOOL {
        $$ = create_app_exp($1, $2);
    }
    | exp_primary VAR {
        $$ = create_app_exp($1, create_var_exp($2));
    }
    | exp_primary LP exp RP {
        $$ = create_app_exp($1, $3);
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
        $$ = create_var_exp($1);
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
