#include <stdio.h>
#include <stdlib.h>

#include "ml1_semantics.h"

Value *create_int_value(const int int_value) {
    Value *value = malloc(sizeof(Value));
    value->type = INT_VALUE;
    value->int_value = int_value;
    return value;
}

Value *create_bool_value(const bool bool_value) {
    Value *value = malloc(sizeof(Value));
    value->type = BOOL_VALUE;
    value->bool_value = bool_value;
    return value;
}

void free_value(Value *value) {
    free(value);
}

Exp *create_int_exp(const int int_value) {
    IntExp *int_exp = malloc(sizeof(IntExp));
    int_exp->int_value = int_value;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = INT_EXP;
    exp->int_exp = int_exp;

    return exp;
}

Exp *create_bool_exp(const bool bool_value) {
    BoolExp *bool_exp = malloc(sizeof(BoolExp));
    bool_exp->bool_value = bool_value;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = BOOL_EXP;
    exp->bool_exp = bool_exp;

    return exp;
}

Exp *create_plus_op_exp(Exp *exp_left, Exp *exp_right) {
    OpExp *op_exp = malloc(sizeof(OpExp));
    op_exp->type = PLUS_OP_EXP;
    op_exp->exp_left = exp_left;
    op_exp->exp_right = exp_right;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = OP_EXP;
    exp->op_exp = op_exp;

    return exp;
}

Exp *create_minus_op_exp(Exp *exp_left, Exp *exp_right) {
    OpExp *op_exp = malloc(sizeof(OpExp));
    op_exp->type = MINUS_OP_EXP;
    op_exp->exp_left = exp_left;
    op_exp->exp_right = exp_right;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = OP_EXP;
    exp->op_exp = op_exp;

    return exp;
}

Exp *create_times_op_exp(Exp *exp_left, Exp *exp_right) {
    OpExp *op_exp = malloc(sizeof(OpExp));
    op_exp->type = TIMES_OP_EXP;
    op_exp->exp_left = exp_left;
    op_exp->exp_right = exp_right;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = OP_EXP;
    exp->op_exp = op_exp;

    return exp;
}

Exp *create_lt_op_exp(Exp *exp_left, Exp *exp_right) {
    OpExp *op_exp = malloc(sizeof(OpExp));
    op_exp->type = LT_OP_EXP;
    op_exp->exp_left = exp_left;
    op_exp->exp_right = exp_right;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = OP_EXP;
    exp->op_exp = op_exp;

    return exp;
}

void free_exp(Exp *exp) {
    if (exp == NULL) {
        return;
    }

    switch (exp->type) {
        case INT_EXP: {
            free(exp->int_exp);
            free(exp);
            return;
        }
        case BOOL_EXP: {
            free(exp->bool_exp);
            free(exp);
            return;
        }
        case OP_EXP: {
            if (exp->op_exp == NULL) {
                free(exp);
                return;
            }

            free_exp(exp->op_exp->exp_left);
            free_exp(exp->op_exp->exp_right);
            free(exp->op_exp);
            free(exp);
            return;
        }
        default: {
            free(exp);
            return;
        }
    }
}

bool evalto(Value *value, const Exp *exp) {
    if (value == NULL || exp == NULL) {
        return false;
    }

    switch (exp->type) {
        case INT_EXP: {
            if (exp->int_exp == NULL) {
                return false;
            }

            value->type = INT_VALUE;
            value->int_value = exp->int_exp->int_value;
            return true;
        }
        case BOOL_EXP: {
            if (exp->bool_exp == NULL) {
                return false;
            }

            value->type = BOOL_VALUE;
            value->bool_value = exp->bool_exp->bool_value;
            return true;
        }
        case OP_EXP: {
            if (exp->op_exp == NULL) {
                return false;
            }

            const Exp *exp_left = exp->op_exp->exp_left;
            if (exp_left == NULL) {
                return false;
            }

            const Exp *exp_right = exp->op_exp->exp_right;
            if (exp_right == NULL) {
                return false;
            }

            Value value_left;
            if (!evalto(&value_left, exp_left)) {
                return false;
            }

            if (value_left.type != INT_VALUE) {
                return false;
            }

            Value value_right;
            if (!evalto(&value_right, exp_right)) {
                return false;
            }

            if (value_right.type != INT_VALUE) {
                return false;
            }

            switch(exp->op_exp->type) {
                case PLUS_OP_EXP: {
                    value->type = INT_VALUE;
                    value->int_value = value_left.int_value + value_right.int_value;
                    return true;
                }
                case MINUS_OP_EXP: {
                    value->type = INT_VALUE;
                    value->int_value = value_left.int_value - value_right.int_value;
                    return true;
                }
                case TIMES_OP_EXP: {
                    value->type = INT_VALUE;
                    value->int_value = value_left.int_value * value_right.int_value;
                    return true;
                }
                case LT_OP_EXP: {
                    value->type = BOOL_VALUE;
                    value->bool_value = value_left.int_value < value_right.int_value;
                    return true;
                }
                default:
                    return false;
            }
        }
        default:
            return false;
    }
}

bool derive(Derivation *derivation, Exp *exp) {
    if (derivation == NULL || exp == NULL) {
        return false;
    }

    switch (exp->type) {
        case INT_EXP: {
            Judgement *conclusion = malloc(sizeof(Judgement));
            conclusion->exp = exp;
            conclusion->value = malloc(sizeof(Value));
            conclusion->value->type = INT_VALUE;
            conclusion->value->int_value = exp->int_exp->int_value;

            derivation->type = INT_DERIVATION;
            derivation->int_derivation = malloc(sizeof(IntDerivation));
            derivation->int_derivation->conclusion = conclusion;

            return true;
        }
        case BOOL_EXP: {
            Judgement *conclusion = malloc(sizeof(Judgement));
            conclusion->exp = exp;
            conclusion->value = malloc(sizeof(Value));
            conclusion->value->type = BOOL_VALUE;
            conclusion->value->bool_value = exp->bool_exp->bool_value;

            derivation->type = BOOL_DERIVATION;
            derivation->bool_derivation = malloc(sizeof(BoolDerivation));
            derivation->bool_derivation->conclusion = conclusion;

            return true;
        }
        case OP_EXP: {
            Exp *exp_left = exp->op_exp->exp_left;
            if (exp_left == NULL) {
                return false;
            }

            Exp *exp_right = exp->op_exp->exp_right;
            if (exp_right == NULL) {
                return false;
            }

            Derivation *premise_left = malloc(sizeof(Derivation));
            if (!derive(premise_left, exp_left)) {
                return false;
            }

            int int_value_left;
            switch (premise_left->type) {
                case INT_DERIVATION: {
                    Judgement *conclusion = premise_left->int_derivation->conclusion;
                    if (conclusion->value->type != INT_VALUE) {
                        return false;
                    }

                    int_value_left = conclusion->value->int_value;
                    break;
                }
                case BOOL_DERIVATION: {
                    Judgement *conclusion = premise_left->bool_derivation->conclusion;
                    if (conclusion->value->type != INT_VALUE) {
                        return false;
                    }

                    int_value_left = conclusion->value->int_value;
                    break;
                }
                case OP_DERIVATION: {
                    Judgement *conclusion = premise_left->op_derivation->conclusion;
                    if (conclusion->value->type != INT_VALUE) {
                        return false;
                    }

                    int_value_left = conclusion->value->int_value;
                    break;
                }
                default:
                    return false;
            }

            Derivation *premise_right = malloc(sizeof(Derivation));
            if (!derive(premise_right, exp_right)) {
                return false;
            }

            int int_value_right;
            switch (premise_right->type) {
                case INT_DERIVATION: {
                    Judgement *conclusion = premise_right->int_derivation->conclusion;
                    if (conclusion->value->type != INT_VALUE) {
                        return false;
                    }

                    int_value_right = conclusion->value->int_value;
                    break;
                }
                case BOOL_DERIVATION: {
                    Judgement *conclusion = premise_right->bool_derivation->conclusion;
                    if (conclusion->value->type != INT_VALUE) {
                        return false;
                    }

                    int_value_right = conclusion->value->int_value;
                    break;
                }
                case OP_DERIVATION: {
                    Judgement *conclusion = premise_right->op_derivation->conclusion;
                    if (conclusion->value->type != INT_VALUE) {
                        return false;
                    }

                    int_value_right = conclusion->value->int_value;
                    break;
                }
                default:
                    return false;
            }

            switch(exp->op_exp->type) {
                case PLUS_OP_EXP: {
                    Judgement *conclusion = malloc(sizeof(Judgement));
                    conclusion->exp = exp;
                    conclusion->value = malloc(sizeof(Value));
                    conclusion->value->type = INT_VALUE;
                    conclusion->value->int_value = int_value_left + int_value_right;

                    derivation->type = OP_DERIVATION;
                    derivation->op_derivation = malloc(sizeof(OpDerivation));
                    derivation->op_derivation->type = PLUS_OP_DERIVATION;
                    derivation->op_derivation->conclusion = conclusion;
                    derivation->op_derivation->premise_left = premise_left;
                    derivation->op_derivation->premise_right = premise_right;

                    return true;
                }
                case MINUS_OP_EXP: {
                    Judgement *conclusion = malloc(sizeof(Judgement));
                    conclusion->exp = exp;
                    conclusion->value = malloc(sizeof(Value));
                    conclusion->value->type = INT_VALUE;
                    conclusion->value->int_value = int_value_left - int_value_right;

                    derivation->type = OP_DERIVATION;
                    derivation->op_derivation = malloc(sizeof(OpDerivation));
                    derivation->op_derivation->type = MINUS_OP_DERIVATION;
                    derivation->op_derivation->conclusion = conclusion;
                    derivation->op_derivation->premise_left = premise_left;
                    derivation->op_derivation->premise_right = premise_right;

                    return true;
                }
                case TIMES_OP_EXP: {
                    Judgement *conclusion = malloc(sizeof(Judgement));
                    conclusion->exp = exp;
                    conclusion->value = malloc(sizeof(Value));
                    conclusion->value->type = INT_VALUE;
                    conclusion->value->int_value = int_value_left * int_value_right;

                    derivation->type = OP_DERIVATION;
                    derivation->op_derivation = malloc(sizeof(OpDerivation));
                    derivation->op_derivation->type = TIMES_OP_DERIVATION;
                    derivation->op_derivation->conclusion = conclusion;
                    derivation->op_derivation->premise_left = premise_left;
                    derivation->op_derivation->premise_right = premise_right;

                    return true;
                }
                case LT_OP_EXP: {
                    Judgement *conclusion = malloc(sizeof(Judgement));
                    conclusion->exp = exp;
                    conclusion->value = malloc(sizeof(Value));
                    conclusion->value->type = BOOL_VALUE;
                    conclusion->value->bool_value = int_value_left < int_value_right;

                    derivation->type = OP_DERIVATION;
                    derivation->op_derivation = malloc(sizeof(OpDerivation));
                    derivation->op_derivation->type = LT_OP_DERIVATION;
                    derivation->op_derivation->conclusion = conclusion;
                    derivation->op_derivation->premise_left = premise_left;
                    derivation->op_derivation->premise_right = premise_right;

                    return true;
                }
                default: {
                    return false;
                }
            }
        }
        default:
            return false;
    }
}

void free_derivation(Derivation *derivation) {
    if (derivation == NULL) {
        return;
    }

    switch (derivation->type) {
        case INT_DERIVATION:
            if (derivation->int_derivation == NULL) {
                free(derivation);
                return;
            }

            if (derivation->int_derivation->conclusion != NULL) {
                free_value(derivation->int_derivation->conclusion->value);
                free(derivation->int_derivation->conclusion);
            }
            free(derivation->int_derivation);
            free(derivation);

            return;
        case BOOL_DERIVATION:
            if (derivation->bool_derivation == NULL) {
                free(derivation);
                return;
            }

            if (derivation->int_derivation->conclusion != NULL) {
                free_value(derivation->bool_derivation->conclusion->value);
                free(derivation->bool_derivation->conclusion);
            }
            free(derivation->bool_derivation);
            free(derivation);

            return;
        case OP_DERIVATION:
            if (derivation->op_derivation == NULL) {
                free(derivation);
                return;
            }

            if (derivation->int_derivation->conclusion != NULL) {
                free_value(derivation->op_derivation->conclusion->value);
                free(derivation->op_derivation->conclusion);
            }
            free_derivation(derivation->op_derivation->premise_left);
            free_derivation(derivation->op_derivation->premise_right);
            free(derivation->op_derivation);
            free(derivation);

            return;
        default: {
            free(derivation);
            return;
        }
    }
}

bool fprint_exp(FILE *fp, const Exp *exp) {
    switch (exp->type) {
        case INT_EXP: {
            fprintf(fp, "%d", exp->int_exp->int_value);
            return true;
        }
        case BOOL_EXP: {
            fprintf(fp, "%s", exp->bool_exp->bool_value ? "true" : "false");
            return true;
        }
        case OP_EXP: {
            const Exp *exp_left = exp->op_exp->exp_left;
            const Exp *exp_right = exp->op_exp->exp_right;
            fprintf(fp, "(");
            if (!fprint_exp(fp, exp_left)) {
                return false;
            }
            switch(exp->op_exp->type) {
                case PLUS_OP_EXP: {
                    fprintf(fp, " + ");
                    break;
                }
                case MINUS_OP_EXP: {
                    fprintf(fp, " - ");
                    break;
                }
                case TIMES_OP_EXP: {
                    fprintf(fp, " * ");
                    break;
                }
                case LT_OP_EXP: {
                    fprintf(fp, " < ");
                    break;
                }
                default: {
                    return false;
                }
            }
            if (!fprint_exp(fp, exp_right)) {
                return false;
            }
            fprintf(fp, ")");
            return true;
        }
        default:
            return false;
    }
    return true;
}

void fprint_indent(FILE *fp, const int level) {
    for (int i = 0; i < level; i++) {
        fprintf(fp, "  ");
    }
}

bool fprint_derivation_impl(FILE *fp, const Derivation *derivation, const int level) {
    fprint_indent(fp, level);
    switch (derivation->type) {
        case INT_DERIVATION: {
            const Judgement *conclusion = derivation->int_derivation->conclusion;
            fprint_exp(fp, conclusion->exp);
            fprintf(fp, " evalto %d by E-Int {}", conclusion->value->int_value);
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case BOOL_DERIVATION: {
            const Judgement *conclusion = derivation->bool_derivation->conclusion;
            fprint_exp(fp, conclusion->exp);
            fprintf(fp, " evalto %d by E-Bool {}", conclusion->value->bool_value);
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case OP_DERIVATION: {
            const Judgement *conclusion = derivation->op_derivation->conclusion;
            fprint_exp(fp, conclusion->exp);

            const Derivation *premise_left = derivation->op_derivation->premise_left;
            const Derivation *premise_right = derivation->op_derivation->premise_right;

            int int_value_left;
            switch (premise_left->type) {
                case INT_DERIVATION: {
                    Judgement *conclusion = premise_left->int_derivation->conclusion;
                    if (conclusion->value->type != INT_VALUE) {
                        return false;
                    }

                    int_value_left = conclusion->value->int_value;
                    break;
                }
                case BOOL_DERIVATION: {
                    Judgement *conclusion = premise_left->bool_derivation->conclusion;
                    if (conclusion->value->type != INT_VALUE) {
                        return false;
                    }

                    int_value_left = conclusion->value->int_value;
                    break;
                }
                case OP_DERIVATION: {
                    Judgement *conclusion = premise_left->op_derivation->conclusion;
                    if (conclusion->value->type != INT_VALUE) {
                        return false;
                    }

                    int_value_left = conclusion->value->int_value;
                    break;
                }
                default:
                    return false;
            }

            int int_value_right;
            switch (premise_right->type) {
                case INT_DERIVATION: {
                    Judgement *conclusion = premise_right->int_derivation->conclusion;
                    if (conclusion->value->type != INT_VALUE) {
                        return false;
                    }

                    int_value_right = conclusion->value->int_value;
                    break;
                }
                case BOOL_DERIVATION: {
                    Judgement *conclusion = premise_right->bool_derivation->conclusion;
                    if (conclusion->value->type != INT_VALUE) {
                        return false;
                    }

                    int_value_right = conclusion->value->int_value;
                    break;
                }
                case OP_DERIVATION: {
                    Judgement *conclusion = premise_right->op_derivation->conclusion;
                    if (conclusion->value->type != INT_VALUE) {
                        return false;
                    }

                    int_value_right = conclusion->value->int_value;
                    break;
                }
                default:
                    return false;
            }

            switch (derivation->op_derivation->type) {
                case PLUS_OP_DERIVATION: {
                    fprintf(fp, " evalto %d by E-Plus {\n", conclusion->value->int_value);
                    if (!fprint_derivation_impl(fp, premise_left, level + 1)) {
                        return false;
                    }
                    fprintf(fp, ";\n");
                    if (!fprint_derivation_impl(fp, premise_right, level + 1)) {
                        return false;
                    }
                    fprintf(fp, ";\n");
                    fprint_indent(fp, level + 1);
                    fprintf(fp,
                            "%d plus %d is %d by B-Plus {}\n",
                            int_value_left,
                            int_value_right,
                            conclusion->value->int_value);
                    fprint_indent(fp, level);
                    fprintf(fp, "}");
                    if (level == 0) {
                        fprintf(fp, "\n");
                    }
                    return true;
                }
                case MINUS_OP_DERIVATION: {
                    fprintf(fp, " evalto %d by E-Minus {\n", conclusion->value->int_value);
                    if (!fprint_derivation_impl(fp, premise_left, level + 1)) {
                        return false;
                    }
                    fprintf(fp, ";\n");
                    if (!fprint_derivation_impl(fp, premise_right, level + 1)) {
                        return false;
                    }
                    fprintf(fp, ";\n");
                    fprint_indent(fp, level + 1);
                    fprintf(fp,
                            "%d minus %d is %d by B-Minus {}\n",
                            int_value_left,
                            int_value_right,
                            conclusion->value->int_value);
                    fprint_indent(fp, level);
                    fprintf(fp, "}");
                    if (level == 0) {
                        fprintf(fp, "\n");
                    }
                    return true;
                }
                case TIMES_OP_DERIVATION: {
                    fprintf(fp, " evalto %d by E-Times {\n", conclusion->value->int_value);
                    if (!fprint_derivation_impl(fp, premise_left, level + 1)) {
                        return false;
                    }
                    fprintf(fp, ";\n");
                    if (!fprint_derivation_impl(fp, premise_right, level + 1)) {
                        return false;
                    }
                    fprintf(fp, ";\n");
                    fprint_indent(fp, level + 1);
                    fprintf(fp,
                            "%d times %d is %d by B-Times {}\n",
                            int_value_left,
                            int_value_right,
                            conclusion->value->int_value);
                    fprint_indent(fp, level);
                    fprintf(fp, "}");
                    if (level == 0) {
                        fprintf(fp, "\n");
                    }
                    return true;
                }
                case LT_OP_DERIVATION: {
                    fprintf(fp,
                            " evalto %s by E-Lt {\n",
                            conclusion->value->bool_value ? "true" : "false");
                    if (!fprint_derivation_impl(fp, premise_left, level + 1)) {
                        return false;
                    }
                    fprintf(fp, ";\n");
                    if (!fprint_derivation_impl(fp, premise_right, level + 1)) {
                        return false;
                    }
                    fprintf(fp, ";\n");
                    fprint_indent(fp, level + 1);
                    fprintf(fp,
                            "%d less than %d is %s by B-Lt {}\n",
                            int_value_left,
                            int_value_right,
                            conclusion->value->bool_value ? "true" : "false");
                    fprint_indent(fp, level);
                    fprintf(fp, "}");
                    if (level == 0) {
                        fprintf(fp, "\n");
                    }
                    return true;
                }
                default:
                    return false;
            }
            return true;
        }
        default:
            return false;
    }
}

bool fprint_derivation(FILE *fp, const Derivation *derivation) {
    return fprint_derivation_impl(fp, derivation, 0);
}

int main(void) {
    Value value1;
    Exp *exp1 = create_lt_op_exp(
        create_int_exp(2),
        create_times_op_exp(
            create_plus_op_exp(
                create_int_exp(3),
                create_minus_op_exp(
                    create_int_exp(4),
                    create_int_exp(5)
                )
            ),
            create_int_exp(6)
        )
    );
    evalto(&value1, exp1);
    printf("%s\n", value1.bool_value ? "true" : "false");

    Derivation *derivation1 = malloc(sizeof(Derivation));
    derive(derivation1, exp1);
    fprint_derivation(stdout, derivation1);

    free_derivation(derivation1);
    free_exp(exp1);

    return 0;
}
