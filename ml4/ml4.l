%{
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ml4_semantics.h"
#include "y.tab.h"

extern bool is_interactive;

extern void start_string_literal();

extern void add_char_to_string_literal(char);

extern char *get_string_literal();

int yywrap(void) {
    return 1;
}
%}
%start STRING_LITERAL_STATE
%%
<INITIAL>"+" return PLUS;
<INITIAL>"-" return MINUS;
<INITIAL>"*" return TIMES;
<INITIAL>"<" return LT;
<INITIAL>"if" return IF;
<INITIAL>"then" return THEN;
<INITIAL>"else" return ELSE;
<INITIAL>"let" return LET;
<INITIAL>"=" return EQ;
<INITIAL>"in" return IN;
<INITIAL>"fun" return FUN;
<INITIAL>"->" return TO;
<INITIAL>"rec" return REC;
<INITIAL>"[]" return NIL;
<INITIAL>"::" return CONS;
<INITIAL>"match" return MATCH;
<INITIAL>"with" return WITH;
<INITIAL>"|" return OR;
<INITIAL>"#use" return USE;
<INITIAL>[0-9]+ {
    int value;
    sscanf(yytext, "%d", &value);
    yylval.exp = create_int_exp(value);
    return INT;
}
<INITIAL>"false" {
    yylval.exp = create_bool_exp(false);
    return BOOL;
}
<INITIAL>"true" {
    yylval.exp = create_bool_exp(true);
    return BOOL;
}
<INITIAL>([a-z][a-zA-Z0-9_']*|_[a-zA-Z0-9_']+) {
    if (VAR_NAME_LEN_MAX < strlen(yytext)) {
        return 1;
    }

    yylval.var = create_var(yytext);
    return VAR;
}
<INITIAL>\" {
    start_string_literal();
    BEGIN STRING_LITERAL_STATE;
}
<INITIAL>"(" return LP;
<INITIAL>")" return RP;
<INITIAL>";;\n" return END_OF_EXP;
<INITIAL>"\n" {
    if (is_interactive) {
        printf("  ");
    }
}
<INITIAL>[\t ] ;
<INITIAL><<EOF>> return END_OF_FILE;
<INITIAL>. return yytext[0];
<STRING_LITERAL_STATE>\" {
    yylval.string_literal = get_string_literal();
    BEGIN INITIAL;
    return STRING_LITERAL;
}
<STRING_LITERAL_STATE>\n {
    add_char_to_string_literal('\n');
}
<STRING_LITERAL_STATE>\\\" {
    add_char_to_string_literal('"');
}
<STRING_LITERAL_STATE>\\n {
    add_char_to_string_literal('\n');
}
<STRING_LITERAL_STATE>\\t {
    add_char_to_string_literal('\t');
}
<STRING_LITERAL_STATE>\\\\ {
    add_char_to_string_literal('\\');
}
<STRING_LITERAL_STATE>. {
    add_char_to_string_literal(yytext[0]);
}
%%
