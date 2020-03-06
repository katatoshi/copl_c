#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ml4_semantics.h"
#include "ml4_derivation.h"
#include "y.tab.h"

extern FILE *yyin;

extern int yyparse(void);

extern void yyrestart(FILE*);

extern Exp *parsed_exp;

extern Def *parsed_def;

extern char *filename;

extern bool is_interactive;

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

    Env *env_global = malloc(sizeof(Env));
    env_global->var_binding = NULL;

    is_interactive = true;
    printf("# ");
    while (yyparse() == 0) {
        if (parsed_exp != NULL && parsed_def == NULL && filename == NULL) {
            switch (output_type) {
                case OUTPUT_VALUE: {
                    Value *value = evaluate_impl(env_global, parsed_exp);
                    if (value == NULL) {
                        printf("evaluation failed\n");
                        break;
                    }

                    printf("- = ");
                    fprint_value(stdout, value);
                    printf("\n");

                    free_value(value);
                    break;
                }
                case OUTPUT_DERIVATION: {
                    Derivation *derivation = derive_impl(env_global, parsed_exp);
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
        } else if (parsed_exp == NULL && parsed_def != NULL && filename == NULL) {
            if (add_def_to_env(env_global, parsed_def)) {
                VarBinding *var_binding = env_global->var_binding;
                printf("val ");
                fprint_var(stdout, var_binding->var);
                printf(" = ");
                switch (var_binding->value->type) {
                    case CLOSURE_VALUE: {
                        printf("<fun>");
                        break;
                    }
                    case REC_CLOSURE_VALUE: {
                        printf("<fun>");
                        break;
                    }
                    default: {
                        fprint_value(stdout, var_binding->value);
                        break;
                    }
                }
                printf("\n");

                free_def(parsed_def);
                parsed_def = NULL;
            } else {
                printf("definition failed\n");
            }
        } else if (parsed_exp == NULL && parsed_def == NULL && filename != NULL) {
            FILE *fp = fopen(filename, "r");
            if (fp != NULL) {
                yyrestart(fp);
                is_interactive = false;

                while (yyparse() == 0) {
                    if (parsed_exp != NULL && parsed_def == NULL) {
                        switch (output_type) {
                            case OUTPUT_VALUE: {
                                Value *value = evaluate_impl(env_global, parsed_exp);
                                if (value == NULL) {
                                    printf("evaluation failed\n");
                                    break;
                                }

                                printf("- = ");
                                fprint_value(stdout, value);
                                printf("\n");

                                free_value(value);
                                break;
                            }
                            case OUTPUT_DERIVATION: {
                                Derivation *derivation = derive_impl(env_global, parsed_exp);
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
                    } else if (parsed_exp == NULL && parsed_def != NULL) {
                        if (add_def_to_env(env_global, parsed_def)) {
                            VarBinding *var_binding = env_global->var_binding;
                            printf("val ");
                            fprint_var(stdout, var_binding->var);
                            printf(" = ");
                            switch (var_binding->value->type) {
                                case CLOSURE_VALUE: {
                                    printf("<fun>");
                                    break;
                                }
                                case REC_CLOSURE_VALUE: {
                                    printf("<fun>");
                                    break;
                                }
                                default: {
                                    fprint_value(stdout, var_binding->value);
                                    break;
                                }
                            }
                            printf("\n");

                            free_def(parsed_def);
                            parsed_def = NULL;
                        } else {
                            printf("definition failed\n");
                        }
                    } else {
                        break;
                    }
                }

                is_interactive = true;
                yyrestart(stdin);

                fclose(fp);

                free(filename);
                filename = NULL;
            } else {
                printf("file not found\n");
            }
        } else {
            printf("\n");
            free_env(env_global);
            return 0;
        }

        printf("# ");
    }

    free_env(env_global);
    return 0;
}
