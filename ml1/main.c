#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ml1_semantics.h"
#include "y.tab.h"

extern FILE *yyin;

extern int yyparse(void);

extern Exp *parsed_exp;

extern bool is_eof;

typedef enum {
    OUTPUT_VALUE,
    OUTPUT_DERIVATION
} OutputType;

const char *options[] = {
    "--derivation"
};

int main(int argc, char *argv[]) {
    if (2 < argc) {
        printf("usage: ml1 [--derivation]\n");
        return 1;
    }

    OutputType output_type = OUTPUT_VALUE;
    if (argc == 2) {
        if (strncmp(options[0], argv[1], strlen(options[0])) != 0) {
            printf("unknown option: %s\n", argv[1]);
            printf("usage: ml1 [--derivation]\n");
            return 1;
        }

        output_type = OUTPUT_DERIVATION;
    }

    printf("> ");
    while (yyparse() == 0) {
        if (parsed_exp == NULL) {
            if (is_eof) {
                printf("\n");
                return 0;
            }

            printf("> ");
            continue;
        }

        switch (output_type) {
            case OUTPUT_VALUE: {
                Value *value = evaluate(parsed_exp);
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
                        free_exp(parsed_exp);
                        return 0;
                    }
                }
                free_value(value);
                break;
            }
            case OUTPUT_DERIVATION: {
                Derivation *derivation = derive(parsed_exp);
                fprint_derivation(stdout, derivation);
                break;
            }
            default: {
                break;
            }
        }
        free_exp(parsed_exp);
        parsed_exp = NULL;
        printf("> ");
    }

    return 0;
}
