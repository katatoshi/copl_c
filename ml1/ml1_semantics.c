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

Value *evaluate(const Exp *exp) {
    if (exp == NULL) {
        return NULL;
    }

    switch (exp->type) {
        case INT_EXP: {
            if (exp->int_exp == NULL) {
                return NULL;
            }

            Value *value = malloc(sizeof(Value));
            value->type = INT_VALUE;
            value->int_value = exp->int_exp->int_value;
            return value;
        }
        case BOOL_EXP: {
            if (exp->bool_exp == NULL) {
                return NULL;
            }

            Value *value = malloc(sizeof(Value));
            value->type = BOOL_VALUE;
            value->bool_value = exp->bool_exp->bool_value;
            return value;
        }
        case OP_EXP: {
            if (exp->op_exp == NULL) {
                return NULL;
            }

            const Exp *exp_left = exp->op_exp->exp_left;
            if (exp_left == NULL) {
                return NULL;
            }

            const Exp *exp_right = exp->op_exp->exp_right;
            if (exp_right == NULL) {
                return NULL;
            }

            Value *value_left = evaluate(exp_left);
            if (value_left == NULL) {
                return NULL;
            }

            if (value_left->type != INT_VALUE) {
                return NULL;
            }

            Value *value_right = evaluate(exp_right);
            if (value_right == NULL) {
                return NULL;
            }

            if (value_right->type != INT_VALUE) {
                return NULL;
            }

            switch(exp->op_exp->type) {
                case PLUS_OP_EXP: {
                    Value *value = malloc(sizeof(Value));
                    value->type = INT_VALUE;
                    value->int_value = value_left->int_value + value_right->int_value;
                    free_value(value_left);
                    free_value(value_right);
                    return value;
                }
                case MINUS_OP_EXP: {
                    Value *value = malloc(sizeof(Value));
                    value->type = INT_VALUE;
                    value->int_value = value_left->int_value - value_right->int_value;
                    free_value(value_left);
                    free_value(value_right);
                    return value;
                }
                case TIMES_OP_EXP: {
                    Value *value = malloc(sizeof(Value));
                    value->type = INT_VALUE;
                    value->int_value = value_left->int_value * value_right->int_value;
                    free_value(value_left);
                    free_value(value_right);
                    return value;
                }
                case LT_OP_EXP: {
                    Value *value = malloc(sizeof(Value));
                    value->type = BOOL_VALUE;
                    value->bool_value = value_left->int_value < value_right->int_value;
                    free_value(value_left);
                    free_value(value_right);
                    return value;
                }
                default:
                    return NULL;
            }
        }
        default:
            return NULL;
    }
}

bool try_get_int_value_from_derivation(Derivation *derivation, int *int_value) {
    if (derivation == NULL) {
        return false;
    }

    switch (derivation->type) {
        case INT_DERIVATION: {
            if (derivation->int_derivation == NULL) {
                return false;
            }

            *int_value = derivation->int_derivation->int_value;
            return true;
        }
        case PLUS_OP_DERIVATION: {
            if (derivation->plus_op_derivation == NULL) {
                return false;
            }

            *int_value = derivation->plus_op_derivation->int_value;
            return true;
        }
        case MINUS_OP_DERIVATION: {
            if (derivation->plus_op_derivation == NULL) {
                return false;
            }

            *int_value = derivation->plus_op_derivation->int_value;
            return true;
        }
        case TIMES_OP_DERIVATION: {
            if (derivation->plus_op_derivation == NULL) {
                return false;
            }

            *int_value = derivation->plus_op_derivation->int_value;
            return true;
        }
        default:
            return false;
    }
}

Derivation *derive(Exp *exp) {
    if (exp == NULL) {
        return NULL;
    }

    switch (exp->type) {
        case INT_EXP: {
            if (exp->int_exp == NULL) {
                return NULL;
            }

            IntDerivation *int_derivation = malloc(sizeof(IntDerivation));
            int_derivation->int_exp = exp->int_exp;
            int_derivation->int_value = exp->int_exp->int_value;

            Derivation *derivation = malloc(sizeof(Derivation));
            derivation->type = INT_DERIVATION;
            derivation->int_derivation = int_derivation;
            return derivation;
        }
        case BOOL_EXP: {
            if (exp->bool_exp == NULL) {
                return NULL;
            }

            BoolDerivation *bool_derivation = malloc(sizeof(BoolDerivation));
            bool_derivation->bool_exp = exp->bool_exp;
            bool_derivation->bool_value = exp->bool_exp->bool_value;

            Derivation *derivation = malloc(sizeof(Derivation));
            derivation->type = BOOL_DERIVATION;
            derivation->bool_derivation = bool_derivation;
            return derivation;
        }
        case OP_EXP: {
            if (exp->op_exp == NULL) {
                return NULL;
            }

            Exp *exp_left = exp->op_exp->exp_left;
            if (exp_left == NULL) {
                return NULL;
            }

            Exp *exp_right = exp->op_exp->exp_right;
            if (exp_right == NULL) {
                return NULL;
            }

            Derivation *premise_left = derive(exp_left);
            if (premise_left == NULL) {
                return NULL;
            }

            int int_value_left;
            if (!try_get_int_value_from_derivation(premise_left, &int_value_left)) {
                return NULL;
            }

            Derivation *premise_right = derive(exp_right);
            if (premise_right == NULL) {
                return NULL;
            }

            int int_value_right;
            if (!try_get_int_value_from_derivation(premise_right, &int_value_right)) {
                return NULL;
            }

            switch(exp->op_exp->type) {
                case PLUS_OP_EXP: {
                    PlusOpDerivation *plus_op_derivation = malloc(sizeof(PlusOpDerivation));
                    plus_op_derivation->premise_left = premise_left;
                    plus_op_derivation->premise_right = premise_right;
                    plus_op_derivation->op_exp = exp->op_exp;
                    plus_op_derivation->int_value = int_value_left + int_value_right;

                    Derivation *derivation = malloc(sizeof(Derivation));
                    derivation->type = PLUS_OP_DERIVATION;
                    derivation->plus_op_derivation = plus_op_derivation;
                    return derivation;
                }
                case MINUS_OP_EXP: {
                    MinusOpDerivation *minus_op_derivation = malloc(sizeof(MinusOpDerivation));
                    minus_op_derivation->premise_left = premise_left;
                    minus_op_derivation->premise_right = premise_right;
                    minus_op_derivation->op_exp = exp->op_exp;
                    minus_op_derivation->int_value = int_value_left - int_value_right;

                    Derivation *derivation = malloc(sizeof(Derivation));
                    derivation->type = MINUS_OP_DERIVATION;
                    derivation->minus_op_derivation = minus_op_derivation;
                    return derivation;
                }
                case TIMES_OP_EXP: {
                    TimesOpDerivation *times_op_derivation = malloc(sizeof(TimesOpDerivation));
                    times_op_derivation->premise_left = premise_left;
                    times_op_derivation->premise_right = premise_right;
                    times_op_derivation->op_exp = exp->op_exp;
                    times_op_derivation->int_value = int_value_left * int_value_right;

                    Derivation *derivation = malloc(sizeof(Derivation));
                    derivation->type = TIMES_OP_DERIVATION;
                    derivation->times_op_derivation = times_op_derivation;
                    return derivation;
                }
                case LT_OP_EXP: {
                    LtOpDerivation *lt_op_derivation = malloc(sizeof(LtOpDerivation));
                    lt_op_derivation->premise_left = premise_left;
                    lt_op_derivation->premise_right = premise_right;
                    lt_op_derivation->op_exp = exp->op_exp;
                    lt_op_derivation->bool_value = int_value_left < int_value_right;

                    Derivation *derivation = malloc(sizeof(Derivation));
                    derivation->type = LT_OP_DERIVATION;
                    derivation->lt_op_derivation = lt_op_derivation;
                    return derivation;
                }
                default: {
                    return NULL;
                }
            }
        }
        default:
            return NULL;
    }
}

void free_derivation(Derivation *derivation) {
    if (derivation == NULL) {
        return;
    }

    switch (derivation->type) {
        case INT_DERIVATION: {
            free(derivation->int_derivation);
            free(derivation);
            return;
        }
        case BOOL_DERIVATION: {
            free(derivation->int_derivation);
            free(derivation);
            return;
        }
        case PLUS_OP_DERIVATION: {
            if (derivation->plus_op_derivation == NULL) {
                free(derivation);
                return;
            }

            free_derivation(derivation->plus_op_derivation->premise_left);
            free_derivation(derivation->plus_op_derivation->premise_right);
            free(derivation->plus_op_derivation);
            free(derivation);
            return;
        }
        case MINUS_OP_DERIVATION: {
            if (derivation->minus_op_derivation == NULL) {
                free(derivation);
                return;
            }

            free_derivation(derivation->minus_op_derivation->premise_left);
            free_derivation(derivation->minus_op_derivation->premise_right);
            free(derivation->minus_op_derivation);
            free(derivation);
            return;
        }
        case TIMES_OP_DERIVATION: {
            if (derivation->times_op_derivation == NULL) {
                free(derivation);
                return;
            }

            free_derivation(derivation->times_op_derivation->premise_left);
            free_derivation(derivation->times_op_derivation->premise_right);
            free(derivation->times_op_derivation);
            free(derivation);
            return;
        }
        case LT_OP_DERIVATION: {
            if (derivation->lt_op_derivation == NULL) {
                free(derivation);
                return;
            }

            free_derivation(derivation->lt_op_derivation->premise_left);
            free_derivation(derivation->lt_op_derivation->premise_right);
            free(derivation->lt_op_derivation);
            free(derivation);
            return;
        }
        default: {
            free(derivation);
            return;
        }
    }
}

bool fprint_exp(FILE *fp, Exp *exp) {
    if (fp == NULL || exp == NULL) {
        return false;
    }

    switch (exp->type) {
        case INT_EXP: {
            if (exp->int_exp == NULL) {
                return false;
            }

            fprintf(fp, "%d", exp->int_exp->int_value);
            return true;
        }
        case BOOL_EXP: {
            if (exp->bool_exp == NULL) {
                return false;
            }

            fprintf(fp, "%s", exp->bool_exp->bool_value ? "true" : "false");
            return true;
        }
        case OP_EXP: {
            if (exp->op_exp == NULL) {
                return false;
            }

            Exp *exp_left = exp->op_exp->exp_left;
            Exp *exp_right = exp->op_exp->exp_right;

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

bool fprint_int_exp(FILE *fp, IntExp *int_exp) {
    if (fp == NULL || int_exp == NULL) {
        return false;
    }

    Exp exp;
    exp.type = INT_EXP;
    exp.int_exp = int_exp;
    return fprint_exp(fp, &exp);
}

bool fprint_bool_exp(FILE *fp, BoolExp *bool_exp) {
    if (fp == NULL || bool_exp == NULL) {
        return false;
    }

    Exp exp;
    exp.type = BOOL_EXP;
    exp.bool_exp = bool_exp;
    return fprint_exp(fp, &exp);
}

bool fprint_op_exp(FILE *fp, OpExp *op_exp) {
    if (fp == NULL || op_exp == NULL) {
        return false;
    }

    Exp exp;
    exp.type = OP_EXP;
    exp.op_exp = op_exp;
    return fprint_exp(fp, &exp);
}

void fprint_indent(FILE *fp, const int level) {
    for (int i = 0; i < level; i++) {
        fprintf(fp, "  ");
    }
}

bool fprint_derivation_impl(FILE *fp, const Derivation *derivation, const int level) {
    if (fp == NULL || derivation == NULL) {
        return false;
    }

    fprint_indent(fp, level);
    switch (derivation->type) {
        case INT_DERIVATION: {
            if (derivation->int_derivation == NULL) {
                return false;
            }

            if (!fprint_int_exp(fp, derivation->int_derivation->int_exp)) {
                return false;
            }

            fprintf(fp, " evalto %d by E-Int {}", derivation->int_derivation->int_value);
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case BOOL_DERIVATION: {
            if (derivation->bool_derivation == NULL) {
                return false;
            }

            if (!fprint_bool_exp(fp, derivation->bool_derivation->bool_exp)) {
                return false;
            }

            fprintf(fp, " evalto %d by E-Bool {}", derivation->bool_derivation->bool_value);
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case PLUS_OP_DERIVATION: {
            if (derivation->plus_op_derivation == NULL) {
                return false;
            }

            if (!fprint_op_exp(fp, derivation->plus_op_derivation->op_exp)) {
                return false;
            }

            Derivation *premise_left = derivation->plus_op_derivation->premise_left;

            int int_value_left;
            if (!try_get_int_value_from_derivation(premise_left, &int_value_left)) {
                return false;
            }

            Derivation *premise_right = derivation->plus_op_derivation->premise_right;

            int int_value_right;
            if (!try_get_int_value_from_derivation(premise_right, &int_value_right)) {
                return false;
            }

            fprintf(fp, " evalto %d by E-Plus {\n", derivation->plus_op_derivation->int_value);
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
                    derivation->plus_op_derivation->int_value);
            fprint_indent(fp, level);
            fprintf(fp, "}");
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case MINUS_OP_DERIVATION: {
            if (derivation->minus_op_derivation == NULL) {
                return false;
            }

            if (!fprint_op_exp(fp, derivation->minus_op_derivation->op_exp)) {
                return false;
            }

            Derivation *premise_left = derivation->minus_op_derivation->premise_left;

            int int_value_left;
            if (!try_get_int_value_from_derivation(premise_left, &int_value_left)) {
                return false;
            }

            Derivation *premise_right = derivation->minus_op_derivation->premise_right;

            int int_value_right;
            if (!try_get_int_value_from_derivation(premise_right, &int_value_right)) {
                return false;
            }

            fprintf(fp, " evalto %d by E-Minus {\n", derivation->minus_op_derivation->int_value);
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
                    derivation->minus_op_derivation->int_value);
            fprint_indent(fp, level);
            fprintf(fp, "}");
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case TIMES_OP_DERIVATION: {
            if (derivation->times_op_derivation == NULL) {
                return false;
            }

            if (!fprint_op_exp(fp, derivation->times_op_derivation->op_exp)) {
                return false;
            }

            Derivation *premise_left = derivation->times_op_derivation->premise_left;

            int int_value_left;
            if (!try_get_int_value_from_derivation(premise_left, &int_value_left)) {
                return false;
            }

            Derivation *premise_right = derivation->times_op_derivation->premise_right;

            int int_value_right;
            if (!try_get_int_value_from_derivation(premise_right, &int_value_right)) {
                return false;
            }

            fprintf(fp, " evalto %d by E-Times {\n", derivation->times_op_derivation->int_value);
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
                    derivation->times_op_derivation->int_value);
            fprint_indent(fp, level);
            fprintf(fp, "}");
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case LT_OP_DERIVATION: {
            if (derivation->lt_op_derivation == NULL) {
                return false;
            }

            if (!fprint_op_exp(fp, derivation->lt_op_derivation->op_exp)) {
                return false;
            }

            Derivation *premise_left = derivation->lt_op_derivation->premise_left;

            int int_value_left;
            if (!try_get_int_value_from_derivation(premise_left, &int_value_left)) {
                return false;
            }

            Derivation *premise_right = derivation->lt_op_derivation->premise_right;

            int int_value_right;
            if (!try_get_int_value_from_derivation(premise_right, &int_value_right)) {
                return false;
            }

            fprintf(fp, " evalto %s by E-Lt {\n", derivation->lt_op_derivation->bool_value ? "true" : "false");
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
                    derivation->lt_op_derivation->bool_value ? "true" : "false");
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
}

bool fprint_derivation(FILE *fp, const Derivation *derivation) {
    return fprint_derivation_impl(fp, derivation, 0);
}
