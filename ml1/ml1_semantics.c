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

Exp *create_if_exp(Exp *exp_cond, Exp *exp_true, Exp *exp_false) {
    IfExp *if_exp = malloc(sizeof(IfExp));
    if_exp->exp_cond = exp_cond;
    if_exp->exp_true = exp_true;
    if_exp->exp_false = exp_false;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = IF_EXP;
    exp->if_exp = if_exp;

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
        case IF_EXP: {
            if (exp->if_exp == NULL) {
                free(exp);
                return;
            }

            free_exp(exp->if_exp->exp_cond);
            free_exp(exp->if_exp->exp_true);
            free_exp(exp->if_exp->exp_false);
            free(exp->if_exp);
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
                free_value(value_left);
                return NULL;
            }

            Value *value_right = evaluate(exp_right);
            if (value_right == NULL) {
                free_value(value_left);
                return NULL;
            }

            if (value_right->type != INT_VALUE) {
                free_value(value_left);
                free_value(value_right);
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
        case IF_EXP: {
            if (exp->if_exp == NULL) {
                return NULL;
            }

            const Exp *exp_cond = exp->if_exp->exp_cond;
            if (exp_cond == NULL) {
                return NULL;
            }

            Value *value_cond = evaluate(exp_cond);
            if (value_cond == NULL) {
                return NULL;
            }

            if (value_cond->type != BOOL_VALUE) {
                free_value(value_cond);
                return NULL;
            }

            if (value_cond->bool_value) {
                const Exp *exp_true = exp->if_exp->exp_true;
                if (exp_true == NULL) {
                    free_value(value_cond);
                    return NULL;
                }

                Value *value_true = evaluate(exp_true);
                if (value_true == NULL) {
                    free_value(value_cond);
                    return NULL;
                }

                free_value(value_cond);
                return value_true;
            } else {
                const Exp *exp_false = exp->if_exp->exp_false;
                if (exp_false == NULL) {
                    free_value(value_cond);
                    return NULL;
                }

                Value *value_false = evaluate(exp_false);
                if (value_false == NULL) {
                    free_value(value_cond);
                    return NULL;
                }

                free_value(value_cond);
                return value_false;
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
        case PLUS_DERIVATION: {
            if (derivation->plus_derivation == NULL) {
                return false;
            }

            *int_value = derivation->plus_derivation->int_value;
            return true;
        }
        case MINUS_DERIVATION: {
            if (derivation->minus_derivation == NULL) {
                return false;
            }

            *int_value = derivation->minus_derivation->int_value;
            return true;
        }
        case TIMES_DERIVATION: {
            if (derivation->times_derivation == NULL) {
                return false;
            }

            *int_value = derivation->times_derivation->int_value;
            return true;
        }
        case IF_TRUE_DERIVATION: {
            if (derivation->if_true_derivation == NULL) {
                return false;
            }

            Value *value = derivation->if_true_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != INT_VALUE) {
                return false;
            }

            *int_value = value->int_value;
            return true;
        }
        case IF_FALSE_DERIVATION: {
            if (derivation->if_false_derivation == NULL) {
                return false;
            }

            Value *value = derivation->if_false_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != INT_VALUE) {
                return false;
            }

            *int_value = value->int_value;
            return true;
        }
        default:
            return false;
    }
}

bool try_get_bool_value_from_derivation(Derivation *derivation, bool *bool_value) {
    if (derivation == NULL) {
        return false;
    }

    switch (derivation->type) {
        case BOOL_DERIVATION: {
            if (derivation->bool_derivation == NULL) {
                return false;
            }

            *bool_value = derivation->bool_derivation->bool_value;
            return true;
        }
        case LT_DERIVATION: {
            if (derivation->lt_derivation == NULL) {
                return false;
            }

            *bool_value = derivation->lt_derivation->bool_value;
            return true;
        }
        case IF_TRUE_DERIVATION: {
            if (derivation->if_true_derivation == NULL) {
                return false;
            }

            Value *value = derivation->if_true_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != BOOL_VALUE) {
                return false;
            }

            *bool_value = value->bool_value;
            return true;
        }
        case IF_FALSE_DERIVATION: {
            if (derivation->if_false_derivation == NULL) {
                return false;
            }

            Value *value = derivation->if_false_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != BOOL_VALUE) {
                return false;
            }

            *bool_value = value->bool_value;
            return true;
        }
        default:
            return false;
    }
}

Value *create_value_from_derivation(Derivation *derivation) {
    if (derivation == NULL) {
        return NULL;
    }

    switch (derivation->type) {
        case INT_DERIVATION: {
            if (derivation->int_derivation == NULL) {
                return NULL;
            }

            Value *value = malloc(sizeof(Value));
            value->type = INT_VALUE;
            value->int_value = derivation->int_derivation->int_value;
            return value;
        }
        case BOOL_DERIVATION: {
            if (derivation->bool_derivation == NULL) {
                return NULL;
            }

            Value *value = malloc(sizeof(Value));
            value->type = BOOL_VALUE;
            value->bool_value = derivation->bool_derivation->bool_value;
            return value;
        }
        case PLUS_DERIVATION: {
            if (derivation->plus_derivation == NULL) {
                return NULL;
            }

            Value *value = malloc(sizeof(Value));
            value->type = INT_VALUE;
            value->int_value = derivation->plus_derivation->int_value;
            return value;
        }
        case MINUS_DERIVATION: {
            if (derivation->minus_derivation == NULL) {
                return NULL;
            }

            Value *value = malloc(sizeof(Value));
            value->type = INT_VALUE;
            value->int_value = derivation->minus_derivation->int_value;
            return value;
        }
        case TIMES_DERIVATION: {
            if (derivation->times_derivation == NULL) {
                return NULL;
            }

            Value *value = malloc(sizeof(Value));
            value->type = INT_VALUE;
            value->int_value = derivation->times_derivation->int_value;
            return value;
        }
        case IF_TRUE_DERIVATION: {
            if (derivation->if_true_derivation == NULL) {
                return false;
            }

            Value *value_src = derivation->if_true_derivation->value;
            if (value_src == NULL) {
                return false;
            }

            Value *value = malloc(sizeof(Value));
            value->type = value_src->type;
            switch (value_src->type) {
                case INT_VALUE: {
                    value->int_value = value_src->int_value;
                    break;
                }
                case BOOL_VALUE: {
                    value->bool_value = value_src->bool_value;
                    break;
                }
                default:
                    return NULL;
            }
            return value;
        }
        case IF_FALSE_DERIVATION: {
            if (derivation->if_false_derivation == NULL) {
                return false;
            }

            Value *value_src = derivation->if_false_derivation->value;
            if (value_src == NULL) {
                return false;
            }

            Value *value = malloc(sizeof(Value));
            value->type = value_src->type;
            switch (value_src->type) {
                case INT_VALUE: {
                    value->int_value = value_src->int_value;
                    break;
                }
                case BOOL_VALUE: {
                    value->bool_value = value_src->bool_value;
                    break;
                }
                default:
                    return NULL;
            }
            return value;
        }
        default:
            return NULL;
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
                free_derivation(premise_left);
                return NULL;
            }

            Derivation *premise_right = derive(exp_right);
            if (premise_right == NULL) {
                free_derivation(premise_left);
                return NULL;
            }

            int int_value_right;
            if (!try_get_int_value_from_derivation(premise_right, &int_value_right)) {
                free_derivation(premise_left);
                free_derivation(premise_right);
                return NULL;
            }

            switch(exp->op_exp->type) {
                case PLUS_OP_EXP: {
                    PlusDerivation *plus_derivation = malloc(sizeof(PlusDerivation));
                    plus_derivation->premise_left = premise_left;
                    plus_derivation->premise_right = premise_right;
                    plus_derivation->op_exp = exp->op_exp;
                    plus_derivation->int_value = int_value_left + int_value_right;

                    Derivation *derivation = malloc(sizeof(Derivation));
                    derivation->type = PLUS_DERIVATION;
                    derivation->plus_derivation = plus_derivation;
                    return derivation;
                }
                case MINUS_OP_EXP: {
                    MinusDerivation *minus_derivation = malloc(sizeof(MinusDerivation));
                    minus_derivation->premise_left = premise_left;
                    minus_derivation->premise_right = premise_right;
                    minus_derivation->op_exp = exp->op_exp;
                    minus_derivation->int_value = int_value_left - int_value_right;

                    Derivation *derivation = malloc(sizeof(Derivation));
                    derivation->type = MINUS_DERIVATION;
                    derivation->minus_derivation = minus_derivation;
                    return derivation;
                }
                case TIMES_OP_EXP: {
                    TimesDerivation *times_derivation = malloc(sizeof(TimesDerivation));
                    times_derivation->premise_left = premise_left;
                    times_derivation->premise_right = premise_right;
                    times_derivation->op_exp = exp->op_exp;
                    times_derivation->int_value = int_value_left * int_value_right;

                    Derivation *derivation = malloc(sizeof(Derivation));
                    derivation->type = TIMES_DERIVATION;
                    derivation->times_derivation = times_derivation;
                    return derivation;
                }
                case LT_OP_EXP: {
                    LtDerivation *lt_derivation = malloc(sizeof(LtDerivation));
                    lt_derivation->premise_left = premise_left;
                    lt_derivation->premise_right = premise_right;
                    lt_derivation->op_exp = exp->op_exp;
                    lt_derivation->bool_value = int_value_left < int_value_right;

                    Derivation *derivation = malloc(sizeof(Derivation));
                    derivation->type = LT_DERIVATION;
                    derivation->lt_derivation = lt_derivation;
                    return derivation;
                }
                default: {
                    return NULL;
                }
            }
        }
        case IF_EXP: {
            if (exp->if_exp == NULL) {
                return NULL;
            }

            Exp *exp_cond = exp->if_exp->exp_cond;
            if (exp_cond == NULL) {
                return NULL;
            }

            Derivation *premise_cond = derive(exp_cond);
            if (premise_cond == NULL) {
                return NULL;
            }

            bool bool_value_cond;
            if (!try_get_bool_value_from_derivation(premise_cond, &bool_value_cond)) {
                free_derivation(premise_cond);
                return NULL;
            }

            if (bool_value_cond) {
                Exp *exp_true = exp->if_exp->exp_true;
                if (exp_true == NULL) {
                    free_derivation(premise_cond);
                    return NULL;
                }

                Derivation *premise_true = derive(exp_true);
                if (premise_true == NULL) {
                    free_derivation(premise_cond);
                    return NULL;
                }

                Value *value_true = create_value_from_derivation(premise_true);
                if (value_true == NULL) {
                    free_derivation(premise_cond);
                    free_derivation(premise_true);
                    return NULL;
                }

                IfTrueDerivation *if_true_derivation = malloc(sizeof(IfTrueDerivation));
                if_true_derivation->premise_cond = premise_cond;
                if_true_derivation->premise_true = premise_true;
                if_true_derivation->if_exp = exp->if_exp;
                if_true_derivation->value = value_true;

                Derivation *derivation = malloc(sizeof(Derivation));
                derivation->type = IF_TRUE_DERIVATION;
                derivation->if_true_derivation = if_true_derivation;
                return derivation;
            } else {
                Exp *exp_false = exp->if_exp->exp_false;
                if (exp_false == NULL) {
                    free_derivation(premise_cond);
                    return NULL;
                }

                Derivation *premise_false = derive(exp_false);
                if (premise_false == NULL) {
                    free_derivation(premise_cond);
                    return NULL;
                }

                Value *value_false = create_value_from_derivation(premise_false);
                if (value_false == NULL) {
                    free_derivation(premise_cond);
                    free_derivation(premise_false);
                    return NULL;
                }

                IfFalseDerivation *if_false_derivation = malloc(sizeof(IfFalseDerivation));
                if_false_derivation->premise_cond = premise_cond;
                if_false_derivation->premise_false = premise_false;
                if_false_derivation->if_exp = exp->if_exp;
                if_false_derivation->value = value_false;

                Derivation *derivation = malloc(sizeof(Derivation));
                derivation->type = IF_FALSE_DERIVATION;
                derivation->if_false_derivation = if_false_derivation;
                return derivation;
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
        case PLUS_DERIVATION: {
            if (derivation->plus_derivation == NULL) {
                free(derivation);
                return;
            }

            free_derivation(derivation->plus_derivation->premise_left);
            free_derivation(derivation->plus_derivation->premise_right);
            free(derivation->plus_derivation);
            free(derivation);
            return;
        }
        case MINUS_DERIVATION: {
            if (derivation->minus_derivation == NULL) {
                free(derivation);
                return;
            }

            free_derivation(derivation->minus_derivation->premise_left);
            free_derivation(derivation->minus_derivation->premise_right);
            free(derivation->minus_derivation);
            free(derivation);
            return;
        }
        case TIMES_DERIVATION: {
            if (derivation->times_derivation == NULL) {
                free(derivation);
                return;
            }

            free_derivation(derivation->times_derivation->premise_left);
            free_derivation(derivation->times_derivation->premise_right);
            free(derivation->times_derivation);
            free(derivation);
            return;
        }
        case LT_DERIVATION: {
            if (derivation->lt_derivation == NULL) {
                free(derivation);
                return;
            }

            free_derivation(derivation->lt_derivation->premise_left);
            free_derivation(derivation->lt_derivation->premise_right);
            free(derivation->lt_derivation);
            free(derivation);
            return;
        }
        case IF_TRUE_DERIVATION: {
            if (derivation->if_true_derivation == NULL) {
                free(derivation);
                return;
            }

            free_derivation(derivation->if_true_derivation->premise_cond);
            free_derivation(derivation->if_true_derivation->premise_true);
            free_value(derivation->if_true_derivation->value);
            free(derivation->if_true_derivation);
            free(derivation);
            return;
        }
        case IF_FALSE_DERIVATION: {
            if (derivation->if_false_derivation == NULL) {
                free(derivation);
                return;
            }

            free_derivation(derivation->if_false_derivation->premise_cond);
            free_derivation(derivation->if_false_derivation->premise_false);
            free_value(derivation->if_false_derivation->value);
            free(derivation->if_false_derivation);
            free(derivation);
            return;
        }
        default: {
            free(derivation);
            return;
        }
    }
}

bool fprint_value(FILE *fp, Value *value) {
    if (fp == NULL || value == NULL) {
        return false;
    }

    switch (value->type) {
        case INT_VALUE: {
            fprintf(fp, "%d", value->int_value);
            return true;
        }
        case BOOL_VALUE: {
            fprintf(fp, "%s", value->bool_value ? "true" : "false");
            return true;
        }
        default:
            return false;
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
        case IF_EXP: {
            if (exp->if_exp == NULL) {
                return false;
            }

            Exp *exp_cond = exp->if_exp->exp_cond;
            Exp *exp_true = exp->if_exp->exp_true;
            Exp *exp_false = exp->if_exp->exp_false;

            fprintf(fp, "(if ");
            if (!fprint_exp(fp, exp_cond)) {
                return false;
            }
            fprintf(fp, " then ");
            if (!fprint_exp(fp, exp_true)) {
                return false;
            }
            fprintf(fp, " else ");
            if (!fprint_exp(fp, exp_false)) {
                return false;
            }
            fprintf(fp, ")");
            return true;
        }
        default:
            return false;
    }
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

bool fprint_if_exp(FILE *fp, IfExp *if_exp) {
    if (fp == NULL || if_exp == NULL) {
        return false;
    }

    Exp exp;
    exp.type = IF_EXP;
    exp.if_exp = if_exp;
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

            fprintf(fp, " evalto %s by E-Bool {}", derivation->bool_derivation->bool_value ? "true" : "false");
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case PLUS_DERIVATION: {
            if (derivation->plus_derivation == NULL) {
                return false;
            }

            if (!fprint_op_exp(fp, derivation->plus_derivation->op_exp)) {
                return false;
            }

            Derivation *premise_left = derivation->plus_derivation->premise_left;

            int int_value_left;
            if (!try_get_int_value_from_derivation(premise_left, &int_value_left)) {
                return false;
            }

            Derivation *premise_right = derivation->plus_derivation->premise_right;

            int int_value_right;
            if (!try_get_int_value_from_derivation(premise_right, &int_value_right)) {
                return false;
            }

            fprintf(fp, " evalto %d by E-Plus {\n", derivation->plus_derivation->int_value);
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
                    derivation->plus_derivation->int_value);
            fprint_indent(fp, level);
            fprintf(fp, "}");
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case MINUS_DERIVATION: {
            if (derivation->minus_derivation == NULL) {
                return false;
            }

            if (!fprint_op_exp(fp, derivation->minus_derivation->op_exp)) {
                return false;
            }

            Derivation *premise_left = derivation->minus_derivation->premise_left;

            int int_value_left;
            if (!try_get_int_value_from_derivation(premise_left, &int_value_left)) {
                return false;
            }

            Derivation *premise_right = derivation->minus_derivation->premise_right;

            int int_value_right;
            if (!try_get_int_value_from_derivation(premise_right, &int_value_right)) {
                return false;
            }

            fprintf(fp, " evalto %d by E-Minus {\n", derivation->minus_derivation->int_value);
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
                    derivation->minus_derivation->int_value);
            fprint_indent(fp, level);
            fprintf(fp, "}");
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case TIMES_DERIVATION: {
            if (derivation->times_derivation == NULL) {
                return false;
            }

            if (!fprint_op_exp(fp, derivation->times_derivation->op_exp)) {
                return false;
            }

            Derivation *premise_left = derivation->times_derivation->premise_left;

            int int_value_left;
            if (!try_get_int_value_from_derivation(premise_left, &int_value_left)) {
                return false;
            }

            Derivation *premise_right = derivation->times_derivation->premise_right;

            int int_value_right;
            if (!try_get_int_value_from_derivation(premise_right, &int_value_right)) {
                return false;
            }

            fprintf(fp, " evalto %d by E-Times {\n", derivation->times_derivation->int_value);
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
                    derivation->times_derivation->int_value);
            fprint_indent(fp, level);
            fprintf(fp, "}");
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case LT_DERIVATION: {
            if (derivation->lt_derivation == NULL) {
                return false;
            }

            if (!fprint_op_exp(fp, derivation->lt_derivation->op_exp)) {
                return false;
            }

            Derivation *premise_left = derivation->lt_derivation->premise_left;

            int int_value_left;
            if (!try_get_int_value_from_derivation(premise_left, &int_value_left)) {
                return false;
            }

            Derivation *premise_right = derivation->lt_derivation->premise_right;

            int int_value_right;
            if (!try_get_int_value_from_derivation(premise_right, &int_value_right)) {
                return false;
            }

            fprintf(fp, " evalto %s by E-Lt {\n", derivation->lt_derivation->bool_value ? "true" : "false");
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
                    derivation->lt_derivation->bool_value ? "true" : "false");
            fprint_indent(fp, level);
            fprintf(fp, "}");
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case IF_TRUE_DERIVATION: {
            IfTrueDerivation *if_true_derivation = derivation->if_true_derivation;
            if (if_true_derivation == NULL) {
                return false;
            }

            if (!fprint_if_exp(fp, if_true_derivation->if_exp)) {
                return false;
            }

            Value *value = if_true_derivation->value;
            if (value == NULL) {
                return false;
            }

            fprintf(fp, " evalto ");
            fprint_value(fp, value);
            fprintf(fp, " by E-IfT {\n");
            if (!fprint_derivation_impl(fp, if_true_derivation->premise_cond, level + 1)) {
                return false;
            }
            fprintf(fp, ";\n");
            if (!fprint_derivation_impl(fp, if_true_derivation->premise_true, level + 1)) {
                return false;
            }
            fprintf(fp, "\n");
            fprint_indent(fp, level);
            fprintf(fp, "}");
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case IF_FALSE_DERIVATION: {
            IfFalseDerivation *if_false_derivation = derivation->if_false_derivation;
            if (if_false_derivation == NULL) {
                return false;
            }

            if (!fprint_if_exp(fp, if_false_derivation->if_exp)) {
                return false;
            }

            Value *value = if_false_derivation->value;
            if (value == NULL) {
                return false;
            }

            fprintf(fp, " evalto ");
            fprint_value(fp, value);
            fprintf(fp, " by E-IfF {\n");
            if (!fprint_derivation_impl(fp, if_false_derivation->premise_cond, level + 1)) {
                return false;
            }
            fprintf(fp, ";\n");
            if (!fprint_derivation_impl(fp, if_false_derivation->premise_false, level + 1)) {
                return false;
            }
            fprintf(fp, "\n");
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
