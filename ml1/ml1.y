%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ml1_semantics.h"

#define YYDEBUG 1

extern int yylex();

extern int yyerror(const char*);

Exp *parsed_exp;

bool is_eof;
%}
%union {
    Exp *exp;
}
%token <exp> INT BOOL
%token PLUS MINUS TIMES LT IF THEN ELSE LP RP LF QUIT END_OF_FILE
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
    | IF exp THEN exp ELSE exp
    {
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
    | BOOL
    | MINUS INT {
        $$ = create_int_exp(-$2->int_exp->int_value);
        free_exp($2);
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
