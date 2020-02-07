#include <stdio.h>
#include <stdbool.h>
#include "ml1_semantics.h"
#include "y.tab.h"

extern FILE *yyin;

extern int yyparse(void);

extern Exp *exp_to_be_evaluated;

int main(void) {
    printf("> ");
    while (yyparse() == 0) {
        if (exp_to_be_evaluated == NULL) {
            printf("\n");
            return 0;
        }

        Value *value = evaluate(exp_to_be_evaluated);
        switch (value->type) {
            case INT_VALUE: {
                printf("%d\n", value->int_value);
                break;
            }
            case BOOL_VALUE: {
                printf("%s\n", value->bool_value ? "true" : "false");
                break;
            }
            default: {
                free_value(value);
                free_exp(exp_to_be_evaluated);
                return 0;
            }
        }

        free_value(value);
        free_exp(exp_to_be_evaluated);
        exp_to_be_evaluated = NULL;
        printf("> ");
    }

    return 0;
}
