#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml3_semantics.h"

Var *create_var(const char *src_name) {
    if (src_name == NULL) {
        return NULL;
    }

    size_t name_len = strlen(src_name);
    if (name_len < 1 || VAR_NAME_LEN_MAX < name_len) {
        return NULL;
    }

    char *dst_name = malloc(name_len + 1);
    snprintf(dst_name, VAR_NAME_LEN_MAX, "%s", src_name);

    Var *var = malloc(sizeof(Var));
    var->name = dst_name;
    var->name_len = name_len;
    return var;
}

Var *copy_var(const Var* var) {
    if (var == NULL) {
        return NULL;
    }

    return create_var(var->name);
}

bool is_same_var(const Var *var_1, const Var *var_2) {
    if (var_1 == NULL || var_2 == NULL) {
        return false;
    }

    if (var_1->name == NULL || var_2->name == NULL) {
        return false;
    }

    if (var_1->name_len != var_2->name_len) {
        return false;
    }

    return strncmp(var_1->name, var_2->name, var_1->name_len) == 0;
}

void free_var(Var *var) {
    if (var == NULL) {
        return;
    }

    free(var->name);
    free(var);
}

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

Value *create_closure_value(const Env *env, const Var *var, Exp *exp_body) {
    if (env == NULL || var == NULL || exp_body == NULL) {
        return NULL;
    }

    ClosureValue *closure_value = malloc(sizeof(ClosureValue));
    closure_value->env = copy_env(env);
    closure_value->var = copy_var(var);
    closure_value->exp_body = exp_body;

    Value *value = malloc(sizeof(Value));
    value->type = CLOSURE_VALUE;
    value->closure_value = closure_value;
    return value;
}

Value *copy_value(const Value *value) {
    if (value == NULL) {
        return NULL;
    }

    switch (value->type) {
        case INT_VALUE:
            return create_int_value(value->int_value);
        case BOOL_VALUE:
            return create_bool_value(value->bool_value);
        case CLOSURE_VALUE: {
            ClosureValue *closure_value = value->closure_value;
            if (closure_value == NULL) {
                return NULL;
            }

            return create_closure_value(
                closure_value->env,
                closure_value->var,
                closure_value->exp_body
            );
        }
        default:
            return NULL;
    }
}

void free_value(Value *value) {
    if (value == NULL) {
        return;
    }

    switch (value->type) {
        case INT_VALUE: {
            free(value);
            break;
        }
        case BOOL_VALUE: {
            free(value);
            break;
        }
        case CLOSURE_VALUE: {
            ClosureValue *closure_value = value->closure_value;
            if (closure_value == NULL) {
                free(value);
                return;
            }

            free_var(closure_value->var);
            free_env(closure_value->env);
            free(closure_value);
            free(value);
            break;
        }
        default:
            free(value);
    }
}

Env *copy_env(const Env *env) {
    if (env == NULL) {
        return NULL;
    }

    Env *env_new = malloc(sizeof(Env));
    if (env->var_binding == NULL) {
        env_new->var_binding = NULL;
        return env_new;
    }

    VarBinding *var_binding_new_prev = NULL;
    VarBinding *var_binding = env->var_binding;
    while (var_binding != NULL) {
        if (var_binding->var == NULL || var_binding->value == NULL) {
            free_env(env_new);
            return NULL;
        }

        VarBinding *var_binding_new = malloc(sizeof(VarBinding));
        var_binding_new->var = copy_var(var_binding->var);
        var_binding_new->value = copy_value(var_binding->value);
        var_binding_new->next = NULL;

        if (var_binding_new_prev == NULL) {
            env_new->var_binding = var_binding_new;
        } else {
            var_binding_new_prev->next = var_binding_new;
        }

        var_binding_new_prev = var_binding_new;
        var_binding = var_binding->next;
    }

    return env_new;
}

Env *create_poped_env(const Env *env) {
    if (env == NULL) {
        return NULL;
    }

    if (env->var_binding == NULL) {
        return NULL;
    }

    Env *env_new = copy_env(env);
    VarBinding *var_binding_temp = env_new->var_binding;
    env_new->var_binding = var_binding_temp->next;

    free_var(var_binding_temp->var);
    free_value(var_binding_temp->value);
    free(var_binding_temp);

    return env_new;
}

Env *create_appended_env(const Env *env, const Var *var, const Value *value) {
    if (env == NULL || var == NULL || value == NULL) {
        return NULL;
    }

    Env *env_new = copy_env(env);

    VarBinding *var_binding = malloc(sizeof(VarBinding));
    var_binding->var = copy_var(var);
    var_binding->value = copy_value(value);
    var_binding->next = env_new->var_binding;

    env_new->var_binding = var_binding;

    return env_new;
}

void free_env(Env *env) {
    if (env == NULL) {
        return;
    }

    VarBinding *var_binding = env->var_binding;
    while (var_binding != NULL) {
        VarBinding *var_binding_next = var_binding->next;

        free_var(var_binding->var);
        free_value(var_binding->value);
        free(var_binding);

        var_binding = var_binding_next;
    }
    free(env);
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

Exp *create_var_exp(Var *var) {
    if (var == NULL) {
        return NULL;
    }

    VarExp *var_exp = malloc(sizeof(VarExp));
    var_exp->var = var;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = VAR_EXP;
    exp->var_exp = var_exp;

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

Exp *create_let_exp(Var *var, Exp *exp_1, Exp *exp_2) {
    LetExp *let_exp = malloc(sizeof(LetExp));
    let_exp->var = var;
    let_exp->exp_1 = exp_1;
    let_exp->exp_2 = exp_2;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = LET_EXP;
    exp->let_exp = let_exp;

    return exp;
}

Exp *create_fun_exp(Var *var, Exp *exp_body) {
    FunExp *fun_exp = malloc(sizeof(FunExp));
    fun_exp->var = var;
    fun_exp->exp_body = exp_body;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = FUN_EXP;
    exp->fun_exp = fun_exp;

    return exp;
}

Exp *create_app_exp(Exp *exp_1, Exp *exp_2) {
    AppExp *app_exp = malloc(sizeof(AppExp));
    app_exp->exp_1 = exp_1;
    app_exp->exp_2 = exp_2;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = APP_EXP;
    exp->app_exp = app_exp;

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
        case VAR_EXP: {
            if (exp->var_exp == NULL) {
                free(exp);
                return;
            }

            free_var(exp->var_exp->var);
            free(exp->var_exp);
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
        case LET_EXP: {
            if (exp->let_exp == NULL) {
                free(exp);
                return;
            }

            free_var(exp->let_exp->var);
            free_exp(exp->let_exp->exp_1);
            free_exp(exp->let_exp->exp_2);
            free(exp->let_exp);
            free(exp);
            return;
        }
        case FUN_EXP: {
            if (exp->fun_exp == NULL) {
                free(exp);
                return;
            }

            free_var(exp->fun_exp->var);
            free_exp(exp->fun_exp->exp_body);
            free(exp->fun_exp);
            free(exp);
            return;
        }
        case APP_EXP: {
            if (exp->app_exp == NULL) {
                free(exp);
                return;
            }

            free_exp(exp->app_exp->exp_1);
            free_exp(exp->app_exp->exp_2);
            free(exp->app_exp);
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

    Env env = { .var_binding = NULL };
    return evaluate_impl(&env, exp);
}

Value *evaluate_impl(const Env *env, const Exp *exp) {
    if (env == NULL) {
        return NULL;
    }

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
        case VAR_EXP: {
            if (exp->var_exp == NULL) {
                return NULL;
            }

            VarBinding *var_binding = env->var_binding;
            while (var_binding != NULL) {
                if (is_same_var(var_binding->var, exp->var_exp->var)) {
                    return copy_value(var_binding->value);
                }

                var_binding = var_binding->next;
            }

            return NULL;
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

            Value *value_left = evaluate_impl(env, exp_left);
            if (value_left == NULL) {
                return NULL;
            }

            if (value_left->type != INT_VALUE) {
                free_value(value_left);
                return NULL;
            }

            Value *value_right = evaluate_impl(env, exp_right);
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

            Value *value_cond = evaluate_impl(env, exp_cond);
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

                Value *value_true = evaluate_impl(env, exp_true);
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

                Value *value_false = evaluate_impl(env, exp_false);
                if (value_false == NULL) {
                    free_value(value_cond);
                    return NULL;
                }

                free_value(value_cond);
                return value_false;
            }
        }
        case LET_EXP: {
            if (exp->let_exp == NULL) {
                return NULL;
            }

            if (exp->let_exp->var == NULL) {
                return NULL;
            }

            if (exp->let_exp->exp_1 == NULL) {
                return NULL;
            }

            if (exp->let_exp->exp_2 == NULL) {
                return NULL;
            }

            Value *value_1 = evaluate_impl(env, exp->let_exp->exp_1);
            if (value_1 == NULL) {
                return NULL;
            }

            Env *env_new = create_appended_env(env, exp->let_exp->var, value_1);
            if (env_new == NULL) {
                free_value(value_1);
                return NULL;
            }

            Value *value_2 = evaluate_impl(env_new, exp->let_exp->exp_2);

            free_env(env_new);
            free_value(value_1);

            return value_2;
        }
        case FUN_EXP: {
            if (exp->fun_exp == NULL) {
                return NULL;
            }

            if (exp->fun_exp->var == NULL) {
                return NULL;
            }

            if (exp->fun_exp->exp_body == NULL) {
                return NULL;
            }

            return create_closure_value(env, exp->fun_exp->var, exp->fun_exp->exp_body);
        }
        case APP_EXP: {
            if (exp->app_exp == NULL) {
                return NULL;
            }

            if (exp->app_exp->exp_1 == NULL) {
                return NULL;
            }

            if (exp->app_exp->exp_2 == NULL) {
                return NULL;
            }

            Value *value_1 = evaluate_impl(env, exp->app_exp->exp_1);
            if (value_1 == NULL) {
                return NULL;
            }

            if (value_1->type != CLOSURE_VALUE) {
                free_value(value_1);
                return NULL;
            }

            ClosureValue *closure_value = value_1->closure_value;

            Value *value_2 = evaluate_impl(env, exp->app_exp->exp_2);
            if (value_2 == NULL) {
                free_value(value_1);
                return NULL;
            }

            Env *env_new = create_appended_env(
                closure_value->env,
                closure_value->var,
                value_2
            );
            if (env_new == NULL) {
                free_value(value_2);
                free_value(value_1);
                return NULL;
            }

            Value *value_3 = evaluate_impl(env_new, closure_value->exp_body);

            free_env(env_new);
            free_value(value_2);
            free_value(value_1);

            return value_3;
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
        case VAR_1_DERIVATION: {
            if (derivation->var_1_derivation == NULL) {
                return false;
            }

            Value *value = derivation->var_1_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != INT_VALUE) {
                return false;
            }

            *int_value = value->int_value;
            return true;
        }
        case VAR_2_DERIVATION: {
            if (derivation->var_2_derivation == NULL) {
                return false;
            }

            Value *value = derivation->var_2_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != INT_VALUE) {
                return false;
            }

            *int_value = value->int_value;
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
        case LET_DERIVATION: {
            if (derivation->let_derivation == NULL) {
                return false;
            }

            Value *value = derivation->let_derivation->value;
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
        case VAR_1_DERIVATION: {
            if (derivation->var_1_derivation == NULL) {
                return false;
            }

            Value *value = derivation->var_1_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != BOOL_VALUE) {
                return false;
            }

            *bool_value = value->bool_value;
            return true;
        }
        case VAR_2_DERIVATION: {
            if (derivation->var_2_derivation == NULL) {
                return false;
            }

            Value *value = derivation->var_2_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != BOOL_VALUE) {
                return false;
            }

            *bool_value = value->bool_value;
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
        case LET_DERIVATION: {
            if (derivation->let_derivation == NULL) {
                return false;
            }

            Value *value = derivation->let_derivation->value;
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

            return create_int_value(derivation->int_derivation->int_value);
        }
        case BOOL_DERIVATION: {
            if (derivation->bool_derivation == NULL) {
                return NULL;
            }

            return create_bool_value(derivation->bool_derivation->bool_value);
        }
        case VAR_1_DERIVATION: {
            if (derivation->var_1_derivation == NULL) {
                return NULL;
            }

            return copy_value(derivation->var_1_derivation->value);
        }
        case VAR_2_DERIVATION: {
            if (derivation->var_2_derivation == NULL) {
                return NULL;
            }

            return copy_value(derivation->var_2_derivation->value);
        }
        case PLUS_DERIVATION: {
            if (derivation->plus_derivation == NULL) {
                return NULL;
            }

            return create_int_value(derivation->plus_derivation->int_value);
        }
        case MINUS_DERIVATION: {
            if (derivation->minus_derivation == NULL) {
                return NULL;
            }

            return create_int_value(derivation->minus_derivation->int_value);
        }
        case TIMES_DERIVATION: {
            if (derivation->times_derivation == NULL) {
                return NULL;
            }

            return create_int_value(derivation->times_derivation->int_value);
        }
        case LT_DERIVATION: {
            if (derivation->lt_derivation == NULL) {
                return NULL;
            }

            return create_bool_value(derivation->lt_derivation->bool_value);
        }
        case IF_TRUE_DERIVATION: {
            if (derivation->if_true_derivation == NULL) {
                return NULL;
            }

            return copy_value(derivation->if_true_derivation->value);
        }
        case IF_FALSE_DERIVATION: {
            if (derivation->if_false_derivation == NULL) {
                return NULL;
            }

            return copy_value(derivation->if_false_derivation->value);
        }
        case LET_DERIVATION: {
            if (derivation->let_derivation == NULL) {
                return NULL;
            }

            return copy_value(derivation->let_derivation->value);
        }
        default:
            return NULL;
    }
}

Derivation *derive(Exp *exp) {
    if (exp == NULL) {
        return NULL;
    }

    Env env = { .var_binding = NULL };
    return derive_impl(&env, exp);
}

Derivation *derive_impl(const Env *env, Exp *exp) {
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
            derivation->env = copy_env(env);
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
            derivation->env = copy_env(env);
            derivation->bool_derivation = bool_derivation;
            return derivation;
        }
        case VAR_EXP: {
            if (exp->var_exp == NULL) {
                return NULL;
            }

            if (env->var_binding == NULL) {
                return NULL;
            }

            if (is_same_var(env->var_binding->var, exp->var_exp->var)) {
                Var1Derivation *var_1_derivation = malloc(sizeof(Var1Derivation));
                var_1_derivation->var_exp = exp->var_exp;
                var_1_derivation->value = copy_value(env->var_binding->value);

                Derivation *derivation = malloc(sizeof(Derivation));
                derivation->type = VAR_1_DERIVATION;
                derivation->env = copy_env(env);
                derivation->var_1_derivation = var_1_derivation;
                return derivation;
            } else {
                Env *env_poped = create_poped_env(env);
                if (env_poped == NULL) {
                    return NULL;
                }

                Derivation *premise = derive_impl(env_poped, exp);
                if (premise == NULL) {
                    free_env(env_poped);
                    return NULL;
                }

                Value *value = create_value_from_derivation(premise);
                if (value == NULL) {
                    free_derivation(premise);
                    free_env(env_poped);
                    return NULL;
                }

                free_env(env_poped);

                Var2Derivation *var_2_derivation = malloc(sizeof(Var2Derivation));
                var_2_derivation->premise = premise;
                var_2_derivation->var_exp = exp->var_exp;
                var_2_derivation->value = value;

                Derivation *derivation = malloc(sizeof(Derivation));
                derivation->type = VAR_2_DERIVATION;
                derivation->env = copy_env(env);
                derivation->var_2_derivation = var_2_derivation;
                return derivation;
            }
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

            Derivation *premise_left = derive_impl(env, exp_left);
            if (premise_left == NULL) {
                return NULL;
            }

            int int_value_left;
            if (!try_get_int_value_from_derivation(premise_left, &int_value_left)) {
                free_derivation(premise_left);
                return NULL;
            }

            Derivation *premise_right = derive_impl(env, exp_right);
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
                    derivation->env = copy_env(env);
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
                    derivation->env = copy_env(env);
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
                    derivation->env = copy_env(env);
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
                    derivation->env = copy_env(env);
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

            Derivation *premise_cond = derive_impl(env, exp_cond);
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

                Derivation *premise_true = derive_impl(env, exp_true);
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
                derivation->env = copy_env(env);
                derivation->if_true_derivation = if_true_derivation;
                return derivation;
            } else {
                Exp *exp_false = exp->if_exp->exp_false;
                if (exp_false == NULL) {
                    free_derivation(premise_cond);
                    return NULL;
                }

                Derivation *premise_false = derive_impl(env, exp_false);
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
                derivation->env = copy_env(env);
                derivation->if_false_derivation = if_false_derivation;
                return derivation;
            }
        }
        case LET_EXP: {
            if (exp->let_exp == NULL) {
                return NULL;
            }

            if (exp->let_exp->var == NULL) {
                return NULL;
            }

            if (exp->let_exp->exp_1 == NULL) {
                return NULL;
            }

            if (exp->let_exp->exp_2 == NULL) {
                return NULL;
            }

            Derivation *premise_1 = derive_impl(env, exp->let_exp->exp_1);
            if (premise_1 == NULL) {
                return NULL;
            }

            Value *value_1 = create_value_from_derivation(premise_1);
            if (value_1 == NULL) {
                free_derivation(premise_1);
                return NULL;
            }

            Env *env_new = create_appended_env(env, exp->let_exp->var, value_1);
            if (env_new == NULL) {
                free_value(value_1);
                free_derivation(premise_1);
                return NULL;
            }

            Derivation *premise_2 = derive_impl(env_new, exp->let_exp->exp_2);
            if (premise_2 == NULL) {
                free_env(env_new);
                free_value(value_1);
                free_derivation(premise_1);
                return NULL;
            }

            Value *value_2 = create_value_from_derivation(premise_2);
            if (value_2 == NULL) {
                free_derivation(premise_2);
                free_env(env_new);
                free_value(value_1);
                free_derivation(premise_1);
                return NULL;
            }

            LetDerivation *let_derivation = malloc(sizeof(LetDerivation));
            let_derivation->premise_1 = premise_1;
            let_derivation->premise_2 = premise_2;
            let_derivation->let_exp = exp->let_exp;
            let_derivation->value = value_2;

            Derivation *derivation = malloc(sizeof(Derivation));
            derivation->type = LET_DERIVATION;
            derivation->env = copy_env(env);
            derivation->let_derivation = let_derivation;

            free_env(env_new);
            free_value(value_1);

            return derivation;
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
            free_env(derivation->env);
            free(derivation->int_derivation);
            free(derivation);
            return;
        }
        case BOOL_DERIVATION: {
            free_env(derivation->env);
            free(derivation->int_derivation);
            free(derivation);
            return;
        }
        case PLUS_DERIVATION: {
            if (derivation->plus_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            free_derivation(derivation->plus_derivation->premise_left);
            free_derivation(derivation->plus_derivation->premise_right);
            free(derivation->plus_derivation);
            free_env(derivation->env);
            free(derivation);
            return;
        }
        case MINUS_DERIVATION: {
            if (derivation->minus_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            free_derivation(derivation->minus_derivation->premise_left);
            free_derivation(derivation->minus_derivation->premise_right);
            free(derivation->minus_derivation);
            free_env(derivation->env);
            free(derivation);
            return;
        }
        case TIMES_DERIVATION: {
            if (derivation->times_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            free_derivation(derivation->times_derivation->premise_left);
            free_derivation(derivation->times_derivation->premise_right);
            free(derivation->times_derivation);
            free_env(derivation->env);
            free(derivation);
            return;
        }
        case LT_DERIVATION: {
            if (derivation->lt_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            free_derivation(derivation->lt_derivation->premise_left);
            free_derivation(derivation->lt_derivation->premise_right);
            free(derivation->lt_derivation);
            free_env(derivation->env);
            free(derivation);
            return;
        }
        case IF_TRUE_DERIVATION: {
            if (derivation->if_true_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            free_derivation(derivation->if_true_derivation->premise_cond);
            free_derivation(derivation->if_true_derivation->premise_true);
            free_value(derivation->if_true_derivation->value);
            free(derivation->if_true_derivation);
            free_env(derivation->env);
            free(derivation);
            return;
        }
        case IF_FALSE_DERIVATION: {
            if (derivation->if_false_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            free_derivation(derivation->if_false_derivation->premise_cond);
            free_derivation(derivation->if_false_derivation->premise_false);
            free_value(derivation->if_false_derivation->value);
            free(derivation->if_false_derivation);
            free_env(derivation->env);
            free(derivation);
            return;
        }
        default: {
            free(derivation);
            return;
        }
    }
}

bool fprint_value(FILE *fp, const Value *value) {
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
        case CLOSURE_VALUE: {
            if (value->closure_value == NULL) {
                return false;
            }

            fprintf(fp, "(");
            if (!fprint_env(fp, value->closure_value->env)) {
                return false;
            }
            fprintf(fp, ")[fun ");
            if (!fprint_var(fp, value->closure_value->var)) {
                return false;
            }
            fprintf(fp, " -> ");
            if (!fprint_exp(fp, value->closure_value->exp_body)) {
                return false;
            }
            fprintf(fp, "]");
            return true;
        }
        default:
            return false;
    }
}

bool fprint_var(FILE *fp, const Var *var) {
    if (fp == NULL || var == NULL) {
        return false;
    }

    if (var->name == NULL) {
        return false;
    }

    fprintf(fp, "%s", var->name);
    return true;
}

bool fprint_env(FILE *fp, const Env *env) {
    if (fp == NULL || env == NULL) {
        return false;
    }

    Env *env_reverse = copy_env(env);
    VarBinding *var_binding_prev = NULL;
    VarBinding *var_binding_current = env_reverse->var_binding;
    while (var_binding_current != NULL) {
        VarBinding *var_binding_next = var_binding_current->next;

        var_binding_current->next = var_binding_prev;

        var_binding_prev = var_binding_current;
        var_binding_current = var_binding_next;
    }
    env_reverse->var_binding = var_binding_prev;

    VarBinding *var_binding = env_reverse->var_binding;
    while (var_binding != NULL) {
        if (var_binding->var == NULL || var_binding->value == NULL) {
            free_env(env_reverse);
            return false;
        }

        if (!fprint_var(fp, var_binding->var)) {
            free_env(env_reverse);
            return false;
        }
        fprintf(fp, " = ");
        if (!fprint_value(fp, var_binding->value)) {
            free_env(env_reverse);
            return false;
        }
        if (var_binding->next != NULL) {
            fprintf(fp, ", ");
        }
        var_binding = var_binding->next;
    }

    free_env(env_reverse);

    return true;
}

bool fprint_exp(FILE *fp, const Exp *exp) {
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
        case VAR_EXP: {
            if (exp->var_exp == NULL) {
                return false;
            }

            fprint_var(fp, exp->var_exp->var);
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
        case LET_EXP: {
            if (exp->let_exp == NULL) {
                return false;
            }

            Var *var = exp->let_exp->var;
            Exp *exp_1 = exp->let_exp->exp_1;
            Exp *exp_2 = exp->let_exp->exp_2;

            fprintf(fp, "(let ");
            if (!fprint_var(fp, var)) {
                return false;
            }
            fprintf(fp, " = ");
            if (!fprint_exp(fp, exp_1)) {
                return false;
            }
            fprintf(fp, " in ");
            if (!fprint_exp(fp, exp_2)) {
                return false;
            }
            fprintf(fp, ")");
            return true;
        }
        case FUN_EXP: {
            if (exp->fun_exp == NULL) {
                return false;
            }

            Var *var = exp->fun_exp->var;
            Exp *exp_body = exp->fun_exp->exp_body;

            fprintf(fp, "(fun ");
            if (!fprint_var(fp, var)) {
                return false;
            }
            fprintf(fp, " -> ");
            if (!fprint_exp(fp, exp_body)) {
                return false;
            }
            fprintf(fp, ")");
            return true;
        }
        case APP_EXP: {
            if (exp->app_exp == NULL) {
                return false;
            }

            Exp *exp_1 = exp->app_exp->exp_1;
            Exp *exp_2 = exp->app_exp->exp_2;

            fprintf(fp, "(");
            if (!fprint_exp(fp, exp_1)) {
                return false;
            }
            fprintf(fp, " ");
            if (!fprint_exp(fp, exp_2)) {
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

bool fprint_var_exp(FILE *fp, VarExp *var_exp) {
    if (fp == NULL || var_exp == NULL) {
        return false;
    }

    Exp exp;
    exp.type = VAR_EXP;
    exp.var_exp = var_exp;
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

bool fprint_let_exp(FILE *fp, LetExp *let_exp) {
    if (fp == NULL || let_exp == NULL) {
        return false;
    }

    Exp exp;
    exp.type = LET_EXP;
    exp.let_exp = let_exp;
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

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

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

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

            if (!fprint_bool_exp(fp, derivation->bool_derivation->bool_exp)) {
                return false;
            }

            fprintf(fp, " evalto %s by E-Bool {}", derivation->bool_derivation->bool_value ? "true" : "false");
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case VAR_1_DERIVATION: {
            if (derivation->var_1_derivation == NULL) {
                return false;
            }

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

            if (!fprint_var_exp(fp, derivation->var_1_derivation->var_exp)) {
                return false;
            }

            Value *value = derivation->var_1_derivation->value;
            if (value == NULL) {
                return false;
            }

            fprintf(fp, " evalto ");
            if (!fprint_value(fp, value)) {
                return false;
            }
            fprintf(fp, " by E-Var1 {}");
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case VAR_2_DERIVATION: {
            if (derivation->var_2_derivation == NULL) {
                return false;
            }

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

            if (!fprint_var_exp(fp, derivation->var_2_derivation->var_exp)) {
                return false;
            }

            Value *value = derivation->var_2_derivation->value;
            if (value == NULL) {
                return false;
            }

            fprintf(fp, " evalto ");
            if (!fprint_value(fp, value)) {
                return false;
            }
            fprintf(fp, " by E-Var2 {\n");
            Derivation *premise = derivation->var_2_derivation->premise;
            if (premise == NULL) {
                return false;
            }
            if (!fprint_derivation_impl(fp, premise, level + 1)) {
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
        case PLUS_DERIVATION: {
            if (derivation->plus_derivation == NULL) {
                return false;
            }

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

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

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

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

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

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

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

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

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

            if (!fprint_if_exp(fp, if_true_derivation->if_exp)) {
                return false;
            }

            Value *value = if_true_derivation->value;
            if (value == NULL) {
                return false;
            }

            fprintf(fp, " evalto ");
            if (!fprint_value(fp, value)) {
                return false;
            }
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

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

            if (!fprint_if_exp(fp, if_false_derivation->if_exp)) {
                return false;
            }

            Value *value = if_false_derivation->value;
            if (value == NULL) {
                return false;
            }

            fprintf(fp, " evalto ");
            if (!fprint_value(fp, value)) {
                return false;
            }
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
        case LET_DERIVATION: {
            LetDerivation *let_derivation = derivation->let_derivation;
            if (let_derivation == NULL) {
                return false;
            }

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

            if (!fprint_let_exp(fp, let_derivation->let_exp)) {
                return false;
            }

            Value *value = let_derivation->value;
            if (value == NULL) {
                return false;
            }

            fprintf(fp, " evalto ");
            if (!fprint_value(fp, value)) {
                return false;
            }
            fprintf(fp, " by E-Let {\n");
            if (!fprint_derivation_impl(fp, let_derivation->premise_1, level + 1)) {
                return false;
            }
            fprintf(fp, ";\n");
            if (!fprint_derivation_impl(fp, let_derivation->premise_2, level + 1)) {
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
