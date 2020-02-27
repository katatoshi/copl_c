#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ml4_semantics.h"
#include "y.tab.h"

extern FILE *yyin;

extern int yyparse(void);

extern Exp *parsed_exp;

typedef enum {
    OUTPUT_VALUE,
    OUTPUT_DERIVATION
} OutputType;

const char *options[] = {
    "--derivation"
};

int main(int argc, char *argv[]) {
    if (2 < argc) {
        printf("usage: ml4 [--derivation]\n");
        return 1;
    }

    OutputType output_type = OUTPUT_VALUE;

    if (argc == 2) {
        if (strlen(options[0]) != strlen(argv[1])) {
            printf("unknown option: %s\n", argv[1]);
            printf("usage: ml4 [--derivation]\n");
            return 1;
        }

        if (strncmp(options[0], argv[1], strlen(options[0])) != 0) {
            printf("unknown option: %s\n", argv[1]);
            printf("usage: ml4 [--derivation]\n");
            return 1;
        }

        output_type = OUTPUT_DERIVATION;
    }

    printf("# ");
    while (yyparse() == 0) {
        if (parsed_exp == NULL) {
            printf("\n");
            return 0;
        }

        switch (output_type) {
            case OUTPUT_VALUE: {
                Value *value = evaluate(parsed_exp);
                if (value == NULL) {
                    printf("evaluation failed\n");
                    break;
                }

                fprint_value(stdout, value);
                printf("\n");

                free_value(value);
                break;
            }
            case OUTPUT_DERIVATION: {
                Derivation *derivation = derive(parsed_exp);
                if (derivation == NULL) {
                    printf("derivation failed\n");
                    break;
                }

                fprint_derivation(stdout, derivation);
                printf("\n");

                free_derivation(derivation);
                break;
            }
            default: {
                break;
            }
        }

        free_exp(parsed_exp);
        parsed_exp = NULL;
        printf("# ");
    }

    return 0;
}
