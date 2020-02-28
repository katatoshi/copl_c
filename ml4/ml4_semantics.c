#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml4_semantics.h"

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

Var *create_copied_var(const Var* var) {
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

Closure *create_closure(const Env *env, const Var *var, const Exp *exp) {
    if (env == NULL || var == NULL || exp == NULL) {
        return NULL;
    }

    Closure *closure = malloc(sizeof(Closure));
    closure->env = create_copied_env(env);
    closure->var = create_copied_var(var);
    closure->exp = create_copied_exp(exp);
    return closure;
}

Closure *create_copied_closure(const Closure *closure) {
    if (closure == NULL) {
        return NULL;
    }

    return create_closure(closure->env, closure->var, closure->exp);
}

bool copy_closure(Closure *closure_dst, const Closure *closure_src) {
    if (closure_dst == NULL || closure_src == NULL) {
        return false;
    }

    closure_dst->env = create_copied_env(closure_src->env);
    closure_dst->var = create_copied_var(closure_src->var);
    closure_dst->exp = create_copied_exp(closure_src->exp);
    return true;
}

Value *create_closure_value(Closure *closure_value) {
    if (closure_value == NULL) {
        return NULL;
    }

    Value *value = malloc(sizeof(Value));
    value->type = CLOSURE_VALUE;
    value->closure_value = closure_value;
    return value;
}

void free_closure(Closure *closure) {
    if (closure == NULL) {
        return;
    }

    free_env(closure->env);
    free_var(closure->var);
//    free_exp(closure->exp); // FIXME コメントを外すと導出の結果がおかしい（やたら解放してる）
    free(closure);
}

RecClosure *create_rec_closure(const Env *env,
                               const Var *var_rec,
                               const Var *var,
                               const Exp *exp) {
    if (env == NULL || var_rec == NULL || var == NULL || exp == NULL) {
        return NULL;
    }

    RecClosure *rec_closure = malloc(sizeof(RecClosure));
    rec_closure->env = create_copied_env(env);
    rec_closure->var_rec = create_copied_var(var_rec);
    rec_closure->var = create_copied_var(var);
    rec_closure->exp = create_copied_exp(exp);
    return rec_closure;
}

RecClosure *create_copied_rec_closure(const RecClosure *rec_closure) {
    if (rec_closure == NULL) {
        return NULL;
    }

    return create_rec_closure(
        rec_closure->env,
        rec_closure->var_rec,
        rec_closure->var,
        rec_closure->exp
    );
}

bool copy_rec_closure(RecClosure *rec_closure_dst, const RecClosure *rec_closure_src) {
    if (rec_closure_dst == NULL || rec_closure_src == NULL) {
        return false;
    }

    rec_closure_dst->env = create_copied_env(rec_closure_src->env);
    rec_closure_dst->var_rec = create_copied_var(rec_closure_src->var_rec);
    rec_closure_dst->var = create_copied_var(rec_closure_src->var);
    rec_closure_dst->exp = create_copied_exp(rec_closure_src->exp);
    return true;
}

Value *create_rec_closure_value(RecClosure *rec_closure_value) {
    if (rec_closure_value == NULL) {
        return NULL;
    }

    Value *value = malloc(sizeof(Value));
    value->type = REC_CLOSURE_VALUE;
    value->rec_closure_value = rec_closure_value;
    return value;
}

void free_rec_closure(RecClosure *rec_closure) {
    if (rec_closure == NULL) {
        return;
    }

    free_env(rec_closure->env);
    free_var(rec_closure->var_rec);
    free_var(rec_closure->var);
//    free_exp(rec_closure->exp); // FIXME コメントを外すと導出の結果がおかしい（やたら解放してる）
    free(rec_closure);
}

Value *create_nil_value() {
    Value *value = malloc(sizeof(Value));
    value->type = NIL_VALUE;
    return value;
}

Cons *create_cons(const Value *value_elem, const Value *value_list) {
    if (value_elem == NULL || value_list == NULL) {
        return NULL;
    }

    Cons *cons = malloc(sizeof(Cons));
    cons->value_elem = create_copied_value(value_elem);
    cons->value_list = create_copied_value(value_list);
    return cons;
}

Cons *create_copied_cons(const Cons *cons) {
    if (cons == NULL) {
        return NULL;
    }

    return create_cons(cons->value_elem, cons->value_list);
}

bool copy_cons(Cons *cons_dst, const Cons *cons_src) {
    if (cons_dst == NULL || cons_src == NULL) {
        return false;
    }

    cons_dst->value_elem = cons_src->value_elem;
    cons_dst->value_list = cons_src->value_list;
    return true;
}

Value *create_cons_value(Cons *cons_value) {
    if (cons_value == NULL) {
        return NULL;
    }

    Value *value = malloc(sizeof(Value));
    value->type = CONS_VALUE;
    value->cons_value = cons_value;
    return value;
}

void free_cons(Cons *cons) {
    free(cons);
}

Value *create_copied_value(const Value *value) {
    if (value == NULL) {
        return NULL;
    }

    switch (value->type) {
        case INT_VALUE:
            return create_int_value(value->int_value);
        case BOOL_VALUE:
            return create_bool_value(value->bool_value);
        case CLOSURE_VALUE: {
            if (value->closure_value == NULL) {
                return NULL;
            }

            return create_closure_value(create_copied_closure(value->closure_value));
        }
        case REC_CLOSURE_VALUE: {
            if (value->rec_closure_value == NULL) {
                return NULL;
            }

            return create_rec_closure_value(
                create_copied_rec_closure(value->rec_closure_value)
            );
        }
        case NIL_VALUE: {
            return create_nil_value();
        }
        case CONS_VALUE: {
            if (value->cons_value == NULL) {
                return NULL;
            }

            return create_cons_value(create_copied_cons(value->cons_value));
        }
        default: {
            return NULL;
        }
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
            if (value->closure_value == NULL) {
                free(value);
                return;
            }

            free_closure(value->closure_value);
            free(value);
            break;
        }
        case REC_CLOSURE_VALUE: {
            if (value->rec_closure_value == NULL) {
                free(value);
                return;
            }

            free_rec_closure(value->rec_closure_value);
            free(value);
            break;
        }
        case NIL_VALUE: {
            free(value);
            break;
        }
        case CONS_VALUE: {
            if (value->cons_value == NULL) {
                free(value);
                return;
            }

            free_cons(value->cons_value);
            free(value);
            break;
        }
        default: {
            free(value);
        }
    }
}

Env *create_copied_env(const Env *env) {
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
        var_binding_new->var = create_copied_var(var_binding->var);
        var_binding_new->value = create_copied_value(var_binding->value);
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

    Env *env_new = create_copied_env(env);
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

    Env *env_new = create_copied_env(env);

    VarBinding *var_binding = malloc(sizeof(VarBinding));
    var_binding->var = create_copied_var(var);
    var_binding->value = create_copied_value(value);
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
    if (exp_left == NULL || exp_right == NULL) {
        return NULL;
    }

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
    if (exp_left == NULL || exp_right == NULL) {
        return NULL;
    }

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
    if (exp_left == NULL || exp_right == NULL) {
        return NULL;
    }

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
    if (exp_left == NULL || exp_right == NULL) {
        return NULL;
    }

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
    if (exp_cond == NULL || exp_true == NULL || exp_false == NULL) {
        return NULL;
    }

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
    if (var == NULL || exp_1 == NULL || exp_2 == NULL) {
        return NULL;
    }

    LetExp *let_exp = malloc(sizeof(LetExp));
    let_exp->var = var;
    let_exp->exp_1 = exp_1;
    let_exp->exp_2 = exp_2;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = LET_EXP;
    exp->let_exp = let_exp;

    return exp;
}

Exp *create_fun_exp(Var *var, Exp *exp) {
    if (var == NULL || exp == NULL) {
        return NULL;
    }

    FunExp *fun_exp = malloc(sizeof(FunExp));
    fun_exp->var = var;
    fun_exp->exp = exp;

    Exp *exp_new = malloc(sizeof(Exp));
    exp_new->type = FUN_EXP;
    exp_new->fun_exp = fun_exp;

    return exp_new;
}

Exp *create_app_exp(Exp *exp_1, Exp *exp_2) {
    if (exp_1 == NULL || exp_2 == NULL) {
        return NULL;
    }

    AppExp *app_exp = malloc(sizeof(AppExp));
    app_exp->exp_1 = exp_1;
    app_exp->exp_2 = exp_2;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = APP_EXP;
    exp->app_exp = app_exp;

    return exp;
}

Exp *create_let_rec_exp(Var *var_rec, Var *var, Exp *exp_1, Exp *exp_2) {
    if (var_rec == NULL || exp_1 == NULL || exp_2 == NULL) {
        return NULL;
    }

    LetRecExp *let_rec_exp = malloc(sizeof(LetRecExp));
    let_rec_exp->var_rec = var_rec;
    let_rec_exp->var = var;
    let_rec_exp->exp_1 = exp_1;
    let_rec_exp->exp_2 = exp_2;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = LET_REC_EXP;
    exp->let_rec_exp = let_rec_exp;

    return exp;
}

Exp *create_nil_exp() {
    Exp *exp = malloc(sizeof(Exp));
    exp->type = NIL_EXP;

    return exp;
}

Exp *create_cons_exp(Exp *exp_elem, Exp *exp_list) {
    if (exp_elem == NULL || exp_list == NULL) {
        return NULL;
    }

    ConsExp *cons_exp = malloc(sizeof(ConsExp));
    cons_exp->exp_elem = exp_elem;
    cons_exp->exp_list = exp_list;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = CONS_EXP;
    exp->cons_exp = cons_exp;

    return exp;
}

Exp *create_match_exp(Exp *exp_list,
                      Exp *exp_match_nil,
                      Var *var_elem,
                      Var *var_list,
                      Exp *exp_match_cons) {
    if (exp_list == NULL
        || exp_match_nil == NULL
        || var_elem == NULL
        || var_list == NULL
        || exp_match_cons == NULL) {
        return NULL;
    }

    if (is_same_var(var_elem, var_list)) {
        return NULL;
    }

    MatchExp *match_exp = malloc(sizeof(MatchExp));
    match_exp->exp_list = exp_list;
    match_exp->exp_match_nil = exp_match_nil;
    match_exp->var_elem = var_elem;
    match_exp->var_list = var_list;
    match_exp->exp_match_cons = exp_match_cons;

    Exp *exp = malloc(sizeof(Exp));
    exp->type = MATCH_EXP;
    exp->match_exp = match_exp;

    return exp;
}

Exp *create_copied_exp(const Exp *exp) {
    if (exp == NULL) {
        return NULL;
    }

    switch (exp->type) {
        case INT_EXP: {
            if (exp->int_exp == NULL) {
                return NULL;
            }

            return create_int_exp(exp->int_exp->int_value);
        }
        case BOOL_EXP: {
            if (exp->bool_exp == NULL) {
                return NULL;
            }

            return create_bool_exp(exp->bool_exp->bool_value);
        }
        case VAR_EXP: {
            if (exp->var_exp == NULL) {
                return NULL;
            }

            return create_var_exp(create_copied_var(exp->var_exp->var));
        }
        case OP_EXP: {
            if (exp->op_exp == NULL) {
                return NULL;
            }

            Exp *exp_left = create_copied_exp(exp->op_exp->exp_left);
            if (exp_left == NULL) {
                return NULL;
            }

            Exp *exp_right = create_copied_exp(exp->op_exp->exp_right);
            if (exp_right == NULL) {
                free_exp(exp_left);
                return NULL;
            }

            switch (exp->op_exp->type) {
                case PLUS_OP_EXP: {
                    return create_plus_op_exp(exp_left, exp_right);
                }
                case MINUS_OP_EXP: {
                    return create_minus_op_exp(exp_left, exp_right);
                }
                case TIMES_OP_EXP: {
                    return create_times_op_exp(exp_left, exp_right);
                }
                case LT_OP_EXP: {
                    return create_lt_op_exp(exp_left, exp_right);
                }
                default: {
                    free_exp(exp_right);
                    free_exp(exp_left);
                    return NULL;
                }
            }
        }
        case IF_EXP: {
            if (exp->if_exp == NULL) {
                return NULL;
            }

            Exp *exp_cond = create_copied_exp(exp->if_exp->exp_cond);
            if (exp_cond == NULL) {
                return NULL;
            }

            Exp *exp_true = create_copied_exp(exp->if_exp->exp_true);
            if (exp_true == NULL) {
                free_exp(exp_cond);
                return NULL;
            }

            Exp *exp_false = create_copied_exp(exp->if_exp->exp_false);
            if (exp_false == NULL) {
                free_exp(exp_true);
                free_exp(exp_cond);
                return NULL;
            }

            return create_if_exp(exp_cond, exp_true, exp_false);
        }
        case LET_EXP: {
            if (exp->let_exp == NULL) {
                return NULL;
            }

            Var *var = create_copied_var(exp->let_exp->var);
            if (var == NULL) {
                return NULL;
            }

            Exp *exp_1 = create_copied_exp(exp->let_exp->exp_1);
            if (exp_1 == NULL) {
                free_var(var);
                return NULL;
            }

            Exp *exp_2 = create_copied_exp(exp->let_exp->exp_2);
            if (exp_2 == NULL) {
                free_exp(exp_1);
                free_var(var);
                return NULL;
            }

            return create_let_exp(var, exp_1, exp_2);
        }
        case FUN_EXP: {
            if (exp->fun_exp == NULL) {
                return NULL;
            }

            Var *var = create_copied_var(exp->fun_exp->var);
            if (var == NULL) {
                return NULL;
            }

            Exp *exp_body = create_copied_exp(exp->fun_exp->exp);
            if (exp_body == NULL) {
                free_var(var);
                return NULL;
            }

            return create_fun_exp(var, exp_body);
        }
        case APP_EXP: {
            if (exp->app_exp == NULL) {
                return NULL;
            }

            Exp *exp_1 = create_copied_exp(exp->app_exp->exp_1);
            if (exp_1 == NULL) {
                return NULL;
            }

            Exp *exp_2 = create_copied_exp(exp->app_exp->exp_2);
            if (exp_2 == NULL) {
                free_exp(exp_1);
                return NULL;
            }

            return create_app_exp(exp_1, exp_2);
        }
        case LET_REC_EXP: {
            if (exp->let_rec_exp == NULL) {
                return NULL;
            }

            Var *var_rec = create_copied_var(exp->let_rec_exp->var_rec);
            if (var_rec == NULL) {
                return NULL;
            }

            Var *var = create_copied_var(exp->let_rec_exp->var);
            if (var == NULL) {
                free_var(var_rec);
                return NULL;
            }

            Exp *exp_1 = create_copied_exp(exp->let_rec_exp->exp_1);
            if (exp_1 == NULL) {
                free_var(var);
                free_var(var_rec);
                return NULL;
            }

            Exp *exp_2 = create_copied_exp(exp->let_rec_exp->exp_2);
            if (exp_2 == NULL) {
                free_exp(exp_1);
                free_var(var);
                free_var(var_rec);
                return NULL;
            }
        }
        case NIL_EXP: {
            return create_nil_exp();
        }
        case CONS_EXP: {
            if (exp->cons_exp == NULL) {
                return NULL;
            }

            Exp *exp_elem = create_copied_exp(exp->cons_exp->exp_elem);
            if (exp_elem == NULL) {
                return NULL;
            }

            Exp *exp_list = create_copied_exp(exp->cons_exp->exp_list);
            if (exp_list == NULL) {
                free_exp(exp_elem);
                return NULL;
            }

            return create_cons_exp(exp_elem, exp_list);
        }
        case MATCH_EXP: {
            if (exp->match_exp == NULL) {
                return NULL;
            }

            Exp *exp_list = create_copied_exp(exp->match_exp->exp_list);
            if (exp_list == NULL) {
                return NULL;
            }

            Exp *exp_match_nil = create_copied_exp(exp->match_exp->exp_match_nil);
            if (exp_match_nil == NULL) {
                free_exp(exp_list);
                return NULL;
            }

            Var *var_elem = create_copied_var(exp->match_exp->var_elem);
            if (var_elem == NULL) {
                free_exp(exp_match_nil);
                free_exp(exp_list);
                return NULL;
            }

            Var *var_list = create_copied_var(exp->match_exp->var_list);
            if (var_list == NULL) {
                free_var(var_elem);
                free_exp(exp_match_nil);
                free_exp(exp_list);
                return NULL;
            }

            Exp *exp_match_cons = create_copied_exp(exp->match_exp->exp_match_cons);
            if (exp_match_cons == NULL) {
                free_var(var_list);
                free_var(var_elem);
                free_exp(exp_match_nil);
                free_exp(exp_list);
                return NULL;
            }

            return create_match_exp(exp_list,
                                    exp_match_nil,
                                    var_elem,
                                    var_list,
                                    exp_match_cons);
        }
        default: {
            return NULL;
        }
    }
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
            free_exp(exp->fun_exp->exp);
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
        case LET_REC_EXP: {
            if (exp->let_rec_exp == NULL) {
                free(exp);
                return;
            }

            free_var(exp->let_rec_exp->var_rec);
            free_var(exp->let_rec_exp->var);
            free_exp(exp->let_rec_exp->exp_1);
            free_exp(exp->let_rec_exp->exp_2);
            free(exp->let_rec_exp);
            free(exp);
            return;
        }
        case NIL_EXP: {
            free(exp);
            return;
        }
        case CONS_EXP: {
            if (exp->cons_exp == NULL) {
                free(exp);
                return;
            }

            free_exp(exp->cons_exp->exp_elem);
            free_exp(exp->cons_exp->exp_list);
            free(exp);
            return;
        }
        case MATCH_EXP: {
            if (exp->match_exp == NULL) {
                free(exp);
                return;
            }

            free_exp(exp->match_exp->exp_list);
            free_exp(exp->match_exp->exp_match_nil);
            free_var(exp->match_exp->var_elem);
            free_var(exp->match_exp->var_list);
            free_exp(exp->match_exp->exp_match_cons);
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
                    return create_copied_value(var_binding->value);
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
                default: {
                    return NULL;
                }
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

            if (exp->fun_exp->exp == NULL) {
                return NULL;
            }

            return create_closure_value(
                create_closure(env, exp->fun_exp->var, exp->fun_exp->exp)
            );
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

            switch (value_1->type) {
                case CLOSURE_VALUE: {
                    Closure *closure_value = value_1->closure_value;
                    if (closure_value == NULL) {
                        free_value(value_1);
                        return NULL;
                    }

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

                    Value *value_3 = evaluate_impl(env_new, closure_value->exp);

                    free_env(env_new);
                    free_value(value_2);
                    free_value(value_1);

                    return value_3;
                }
                case REC_CLOSURE_VALUE: {
                    RecClosure *rec_closure_value = value_1->rec_closure_value;
                    if (rec_closure_value == NULL) {
                        free_value(value_1);
                        return NULL;
                    }

                    Value *value_2 = evaluate_impl(env, exp->app_exp->exp_2);
                    if (value_2 == NULL) {
                        free_value(value_1);
                        return NULL;
                    }

                    Env *env_temp = create_appended_env(
                        rec_closure_value->env,
                        rec_closure_value->var_rec,
                        value_1
                    );
                    if (env_temp == NULL) {
                        free_value(value_2);
                        free_value(value_1);
                        return NULL;
                    }

                    Env *env_new = create_appended_env(
                        env_temp,
                        rec_closure_value->var,
                        value_2
                    );
                    free_env(env_temp);
                    if (env_new == NULL) {
                        free_value(value_2);
                        free_value(value_1);
                        return NULL;
                    }

                    Value *value_3 = evaluate_impl(env_new, rec_closure_value->exp);

                    free_env(env_new);
                    free_value(value_2);
                    free_value(value_1);

                    return value_3;
                }
                default: {
                    free_value(value_1);
                    return NULL;
                }
            }
        }
        case LET_REC_EXP: {
            if (exp->let_rec_exp == NULL) {
                return NULL;
            }

            if (exp->let_rec_exp->var_rec == NULL) {
                return NULL;
            }

            if (exp->let_rec_exp->var == NULL) {
                return NULL;
            }

            if (exp->let_rec_exp->exp_1 == NULL) {
                return NULL;
            }

            if (exp->let_rec_exp->exp_2 == NULL) {
                return NULL;
            }

            Value *rec_closure_value = create_rec_closure_value(
                create_rec_closure(
                    env,
                    exp->let_rec_exp->var_rec,
                    exp->let_rec_exp->var,
                    exp->let_rec_exp->exp_1
                )
            );
            if (rec_closure_value == NULL) {
                return NULL;
            }

            Env *env_new = create_appended_env(
                env,
                exp->let_rec_exp->var_rec,
                rec_closure_value
            );
            if (env_new == NULL) {
                free_value(rec_closure_value);
                return NULL;
            }

            Value *value = evaluate_impl(env_new, exp->let_rec_exp->exp_2);

            free_env(env_new);
            free_value(rec_closure_value);

            return value;
        }
        case NIL_EXP: {
            Value *value = malloc(sizeof(Value));
            value->type = NIL_VALUE;
            return value;
        }
        case CONS_EXP: {
            if (exp->cons_exp == NULL) {
                return NULL;
            }

            const Exp *exp_elem = exp->cons_exp->exp_elem;
            if (exp_elem == NULL) {
                return NULL;
            }

            const Exp *exp_list = exp->cons_exp->exp_list;
            if (exp_list == NULL) {
                return NULL;
            }

            Value *value_elem = evaluate_impl(env, exp_elem);
            if (value_elem == NULL) {
                return NULL;
            }

            Value *value_list = evaluate_impl(env, exp_list);
            if (value_list == NULL) {
                free_value(value_elem);
                return NULL;
            }

            Value *value = malloc(sizeof(Value));
            value->type = CONS_VALUE;
            value->cons_value = create_cons(value_elem, value_list);
            free_value(value_elem);
            free_value(value_list);
            return value;
        }
        case MATCH_EXP: {
            if (exp->match_exp == NULL) {
                return NULL;
            }

            const Exp *exp_list = exp->match_exp->exp_list;
            if (exp_list == NULL) {
                return NULL;
            }

            Value *value_list = evaluate_impl(env, exp_list);
            if (value_list == NULL) {
                return NULL;
            }

            switch (value_list->type) {
                case NIL_VALUE: {
                    const Exp *exp_match_nil = exp->match_exp->exp_match_nil;
                    if (exp_match_nil == NULL) {
                        free_value(value_list);
                        return NULL;
                    }

                    Value *value_nil = evaluate_impl(env, exp_match_nil);
                    if (value_nil == NULL) {
                        free_value(value_list);
                        return NULL;
                    }

                    free_value(value_list);
                    return value_nil;
                }
                case CONS_VALUE: {
                    Cons *cons_value = value_list->cons_value;
                    if (cons_value == NULL) {
                        free_value(value_list);
                        return NULL;
                    }

                    Value *value_elem = create_copied_value(cons_value->value_elem);
                    if (value_elem == NULL) {
                        free_value(value_list);
                        return NULL;
                    }

                    Value *value_subsequent_list = create_copied_value(cons_value->value_list);
                    if (value_list == NULL) {
                        free_value(value_elem);
                        free_value(value_list);
                        return NULL;
                    }

                    const Exp *exp_match_cons = exp->match_exp->exp_match_cons;
                    if (exp_match_cons == NULL) {
                        free_value(value_subsequent_list);
                        free_value(value_elem);
                        free_value(value_list);
                        return NULL;
                    }

                    Env *env_temp = create_appended_env(
                        env,
                        exp->match_exp->var_elem,
                        value_elem
                    );
                    if (env_temp == NULL) {
                        free_value(value_subsequent_list);
                        free_value(value_elem);
                        free_value(value_list);
                    }

                    Env *env_new = create_appended_env(
                        env_temp,
                        exp->match_exp->var_list,
                        value_subsequent_list
                    );
                    free_env(env_temp);
                    if (env_new == NULL) {
                        free_value(value_subsequent_list);
                        free_value(value_elem);
                        free_value(value_list);
                    }

                    Value *value_cons = evaluate_impl(env_new, exp_match_cons);
                    if (value_cons == NULL) {
                        free_value(value_subsequent_list);
                        free_value(value_elem);
                        free_value(value_list);
                        return NULL;
                    }

                    free_env(env_new);
                    free_value(value_subsequent_list);
                    free_value(value_elem);
                    free_value(value_list);
                    return value_cons;
                }
                default: {
                    free_value(value_list);
                    return NULL;
                }
            }
        }
        default: {
            return NULL;
        }
    }
}

Def *create_let_def(Var *var, Exp *exp_1) {
    if (var == NULL || exp_1 == NULL) {
        return NULL;
    }

    LetDef *let_def = malloc(sizeof(LetDef));
    let_def->var = var;
    let_def->exp_1 = exp_1;

    Def *def = malloc(sizeof(Def));
    def->type = LET_DEF;
    def->let_def = let_def;
    return def;
}

Def *create_let_rec_def(Var *var_rec, Var *var, Exp *exp_1) {
    if (var_rec == NULL || var == NULL || exp_1 == NULL) {
        return NULL;
    }

    LetRecDef *let_rec_def = malloc(sizeof(LetRecDef));
    let_rec_def->var_rec = var_rec;
    let_rec_def->var = var;
    let_rec_def->exp_1 = exp_1;

    Def *def = malloc(sizeof(Def));
    def->type = LET_REC_DEF;
    def->let_rec_def = let_rec_def;
    return def;
}

void free_def(Def *def) {
    if (def == NULL) {
        return;
    }

    switch (def->type) {
        case LET_DEF: {
            if (def->let_def == NULL) {
                free(def);
                return;
            }

            free_var(def->let_def->var);
            free_exp(def->let_def->exp_1);
            free(def->let_def);
            free(def);
            break;
        }
        case LET_REC_DEF: {
            if (def->let_rec_def == NULL) {
                free(def);
                return;
            }

            free_var(def->let_rec_def->var_rec);
            free_var(def->let_rec_def->var);
            free_exp(def->let_rec_def->exp_1);
            free(def->let_rec_def);
            free(def);
            break;
        }
        default: {
            free(def);
            return;
        }
    }
}

bool add_def_to_env(Env *env, const Def *def) {
    if (env == NULL || def == NULL) {
        return false;
    }

    switch (def->type) {
        case LET_DEF: {
            if (def->let_def == NULL) {
                return false;
            }

            Value *value_1 = evaluate_impl(env, def->let_def->exp_1);
            if (value_1 == NULL) {
                return false;
            }

            VarBinding *var_binding = malloc(sizeof(VarBinding));
            var_binding->var = create_copied_var(def->let_def->var);
            var_binding->value = value_1;
            var_binding->next = env->var_binding;
            env->var_binding = var_binding;
            return true;
        }
        case LET_REC_DEF: {
            if (def->let_rec_def == NULL) {
                return false;
            }

            Value *rec_closure_value = create_rec_closure_value(
                create_rec_closure(
                    env,
                    def->let_rec_def->var_rec,
                    def->let_rec_def->var,
                    def->let_rec_def->exp_1
                )
            );
            if (rec_closure_value == NULL) {
                return false;
            }

            VarBinding *var_binding = malloc(sizeof(VarBinding));
            var_binding->var = create_copied_var(def->let_rec_def->var_rec);
            var_binding->value = rec_closure_value;
            var_binding->next = env->var_binding;
            env->var_binding = var_binding;
            return true;
        }
        default: {
            return false;
        }
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

bool fprint_closure(FILE *fp, const Closure *closure) {
    if (closure == NULL) {
        return false;
    }

    fprintf(fp, "(");
    if (!fprint_env(fp, closure->env)) {
        return false;
    }
    fprintf(fp, ")[fun ");
    if (!fprint_var(fp, closure->var)) {
        return false;
    }
    fprintf(fp, " -> ");
    if (!fprint_exp(fp, closure->exp)) {
        return false;
    }
    fprintf(fp, "]");
    return true;
}

bool fprint_rec_closure(FILE *fp, const RecClosure *rec_closure) {
    if (rec_closure == NULL) {
        return false;
    }

    fprintf(fp, "(");
    if (!fprint_env(fp, rec_closure->env)) {
        return false;
    }
    fprintf(fp, ")[rec ");
    if (!fprint_var(fp, rec_closure->var_rec)) {
        return false;
    }
    fprintf(fp, " = fun ");
    if (!fprint_var(fp, rec_closure->var)) {
        return false;
    }
    fprintf(fp, " -> ");
    if (!fprint_exp(fp, rec_closure->exp)) {
        return false;
    }
    fprintf(fp, "]");
    return true;
}

bool fprint_cons(FILE *fp, const Cons *cons) {
    if (cons == NULL) {
        return false;
    }

    fprintf(fp, "(");
    if (!fprint_value(fp, cons->value_elem)) {
        return false;
    }
    fprintf(fp, " :: ");
    if (!fprint_value(fp, cons->value_list)) {
        return false;
    }
    fprintf(fp, ")");
    return true;
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

            return fprint_closure(fp, value->closure_value);
        }
        case REC_CLOSURE_VALUE: {
            if (value->rec_closure_value == NULL) {
                return false;
            }

            return fprint_rec_closure(fp, value->rec_closure_value);
        }
        case NIL_VALUE: {
            fprintf(fp, "[]");
            return true;
        }
        case CONS_VALUE: {
            if (value->cons_value == NULL) {
                return false;
            }

            return fprint_cons(fp, value->cons_value);
        }
        default: {
            return false;
        }
    }
}

bool fprint_env(FILE *fp, const Env *env) {
    if (fp == NULL || env == NULL) {
        return false;
    }

    Env *env_reverse = create_copied_env(env);
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
            Exp *exp_body = exp->fun_exp->exp;

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
        case LET_REC_EXP: {
            if (exp->let_rec_exp == NULL) {
                return false;
            }

            Var *var_rec = exp->let_rec_exp->var_rec;
            Var *var = exp->let_rec_exp->var;
            Exp *exp_1 = exp->let_rec_exp->exp_1;
            Exp *exp_2 = exp->let_rec_exp->exp_2;

            fprintf(fp, "(let rec ");
            if (!fprint_var(fp, var_rec)) {
                return false;
            }
            fprintf(fp, " = fun ");
            if (!fprint_var(fp, var)) {
                return false;
            }
            fprintf(fp, " -> ");
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
        case NIL_EXP: {
            fprintf(fp, "[]");
            return true;
        }
        case CONS_EXP: {
            if (exp->cons_exp == NULL) {
                return false;
            }

            Exp *exp_elem = exp->cons_exp->exp_elem;
            Exp *exp_list = exp->cons_exp->exp_list;

            fprintf(fp, "(");
            if (!fprint_exp(fp, exp_elem)) {
                return false;
            }
            fprintf(fp, " :: ");
            if (!fprint_exp(fp, exp_list)) {
                return false;
            }
            fprintf(fp, ")");
            return true;
        }
        case MATCH_EXP: {
            if (exp->match_exp == NULL) {
                return false;
            }

            Exp *exp_list = exp->match_exp->exp_list;
            Exp *exp_match_nil = exp->match_exp->exp_match_nil;
            Var *var_elem = exp->match_exp->var_elem;
            Var *var_list = exp->match_exp->var_list;
            Exp *exp_match_cons = exp->match_exp->exp_match_cons;

            fprintf(fp, "(match ");
            if (!fprint_exp(fp, exp_list)) {
                return false;
            }
            fprintf(fp, " with [] -> ");
            if (!fprint_exp(fp, exp_match_nil)) {
                return false;
            }
            fprintf(fp, " | ");
            if (!fprint_var(fp, var_elem)) {
                return false;
            }
            fprintf(fp, " :: ");
            if (!fprint_var(fp, var_list)) {
                return false;
            }
            fprintf(fp, " -> ");
            if (!fprint_exp(fp, exp_match_cons)) {
                return false;
            }
            fprintf(fp, ")");
            return true;
        }
        default: {
            return false;
        }
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

bool fprint_fun_exp(FILE *fp, FunExp *fun_exp) {
    if (fp == NULL || fun_exp == NULL) {
        return false;
    }

    Exp exp;
    exp.type = FUN_EXP;
    exp.fun_exp = fun_exp;
    return fprint_exp(fp, &exp);
}

bool fprint_app_exp(FILE *fp, AppExp *app_exp) {
    if (fp == NULL || app_exp == NULL) {
        return false;
    }

    Exp exp;
    exp.type = APP_EXP;
    exp.app_exp = app_exp;
    return fprint_exp(fp, &exp);
}

bool fprint_let_rec_exp(FILE *fp, LetRecExp *let_rec_exp) {
    if (fp == NULL || let_rec_exp == NULL) {
        return false;
    }

    Exp exp;
    exp.type = LET_REC_EXP;
    exp.let_rec_exp = let_rec_exp;
    return fprint_exp(fp, &exp);
}

bool fprint_cons_exp(FILE *fp, ConsExp *cons_exp) {
    if (fp == NULL || cons_exp == NULL) {
        return false;
    }

    Exp exp;
    exp.type = CONS_EXP;
    exp.cons_exp = cons_exp;
    return fprint_exp(fp, &exp);
}

bool fprint_match_exp(FILE *fp, MatchExp *match_exp) {
    if (fp == NULL || match_exp == NULL) {
        return false;
    }

    Exp exp;
    exp.type = MATCH_EXP;
    exp.match_exp = match_exp;
    return fprint_exp(fp, &exp);
}
