#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml4_semantics.h"
#include "ml4_derivation.h"

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
        case VAR_DERIVATION: {
            if (derivation->var_derivation == NULL) {
                return false;
            }

            Value *value = derivation->var_derivation->value;
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
        case APP_DERIVATION: {
            if (derivation->app_derivation == NULL) {
                return false;
            }

            Value *value = derivation->app_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != INT_VALUE) {
                return false;
            }

            *int_value = value->int_value;
            return true;
        }
        case LET_REC_DERIVATION: {
            if (derivation->let_rec_derivation == NULL) {
                return false;
            }

            Value *value = derivation->let_rec_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != INT_VALUE) {
                return false;
            }

            *int_value = value->int_value;
            return true;
        }
        case APP_REC_DERIVATION: {
            if (derivation->app_rec_derivation == NULL) {
                return false;
            }

            Value *value = derivation->app_rec_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != INT_VALUE) {
                return false;
            }

            *int_value = value->int_value;
            return true;
        }
        case MATCH_NIL_DERIVATION: {
            if (derivation->match_nil_derivation == NULL) {
                return false;
            }

            Value *value = derivation->match_nil_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != INT_VALUE) {
                return false;
            }

            *int_value = value->int_value;
            return true;
        }
        case MATCH_CONS_DERIVATION: {
            if (derivation->match_cons_derivation == NULL) {
                return false;
            }

            Value *value = derivation->match_cons_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != INT_VALUE) {
                return false;
            }

            *int_value = value->int_value;
            return true;
        }
        default: {
            return false;
        }
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
        case VAR_DERIVATION: {
            if (derivation->var_derivation == NULL) {
                return false;
            }

            Value *value = derivation->var_derivation->value;
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
        case APP_DERIVATION: {
            if (derivation->app_derivation == NULL) {
                return false;
            }

            Value *value = derivation->app_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != BOOL_VALUE) {
                return false;
            }

            *bool_value = value->bool_value;
            return true;
        }
        case LET_REC_DERIVATION: {
            if (derivation->let_rec_derivation == NULL) {
                return false;
            }

            Value *value = derivation->let_rec_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != BOOL_VALUE) {
                return false;
            }

            *bool_value = value->bool_value;
            return true;
        }
        case APP_REC_DERIVATION: {
            if (derivation->app_rec_derivation == NULL) {
                return false;
            }

            Value *value = derivation->app_rec_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != BOOL_VALUE) {
                return false;
            }

            *bool_value = value->bool_value;
            return true;
        }
        case MATCH_NIL_DERIVATION: {
            if (derivation->match_nil_derivation == NULL) {
                return false;
            }

            Value *value = derivation->match_nil_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != BOOL_VALUE) {
                return false;
            }

            *bool_value = value->bool_value;
            return true;
        }
        case MATCH_CONS_DERIVATION: {
            if (derivation->match_cons_derivation == NULL) {
                return false;
            }

            Value *value = derivation->match_cons_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != BOOL_VALUE) {
                return false;
            }

            *bool_value = value->bool_value;
            return true;
        }
        default: {
            return false;
        }
    }
}

bool try_get_closure_value_from_derivation(Derivation *derivation, Closure *closure_value) {
    if (derivation == NULL) {
        return false;
    }

    if (closure_value == NULL) {
        return false;
    }

    switch (derivation->type) {
        case VAR_DERIVATION: {
            if (derivation->var_derivation == NULL) {
                return false;
            }

            Value *value = derivation->var_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != CLOSURE_VALUE) {
                return false;
            }

            if (value->closure_value == NULL) {
                return false;
            }

            if (!copy_closure(closure_value, value->closure_value)) {
                return false;
            }

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

            if (value->type != CLOSURE_VALUE) {
                return false;
            }

            if (value->closure_value == NULL) {
                return false;
            }

            if (!copy_closure(closure_value, value->closure_value)) {
                return false;
            }

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

            if (value->type != CLOSURE_VALUE) {
                return false;
            }

            if (value->closure_value == NULL) {
                return false;
            }

            if (!copy_closure(closure_value, value->closure_value)) {
                return false;
            }

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

            if (value->type != CLOSURE_VALUE) {
                return false;
            }

            if (value->closure_value == NULL) {
                return false;
            }

            if (!copy_closure(closure_value, value->closure_value)) {
                return false;
            }

            return true;
        }
        case FUN_DERIVATION: {
            if (derivation->fun_derivation == NULL) {
                return false;
            }

            Closure *closure = derivation->fun_derivation->closure_value;
            if (closure == NULL) {
                return false;
            }

            if (!copy_closure(closure_value, closure)) {
                return false;
            }

            return true;
        }
        case APP_DERIVATION: {
            if (derivation->app_derivation == NULL) {
                return false;
            }

            Value *value = derivation->app_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != CLOSURE_VALUE) {
                return false;
            }

            if (value->closure_value == NULL) {
                return false;
            }

            if (!copy_closure(closure_value, value->closure_value)) {
                return false;
            }

            return true;
        }
        case LET_REC_DERIVATION: {
            if (derivation->let_rec_derivation == NULL) {
                return false;
            }

            Value *value = derivation->let_rec_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != CLOSURE_VALUE) {
                return false;
            }

            if (value->closure_value == NULL) {
                return false;
            }

            if (!copy_closure(closure_value, value->closure_value)) {
                return false;
            }

            return true;
        }
        case APP_REC_DERIVATION: {
            if (derivation->app_rec_derivation == NULL) {
                return false;
            }

            Value *value = derivation->app_rec_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != CLOSURE_VALUE) {
                return false;
            }

            if (value->closure_value == NULL) {
                return false;
            }

            if (!copy_closure(closure_value, value->closure_value)) {
                return false;
            }

            return true;
        }
        case MATCH_NIL_DERIVATION: {
            if (derivation->match_nil_derivation == NULL) {
                return false;
            }

            Value *value = derivation->match_nil_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != CLOSURE_VALUE) {
                return false;
            }

            if (value->closure_value == NULL) {
                return false;
            }

            if (!copy_closure(closure_value, value->closure_value)) {
                return false;
            }

            return true;
        }
        case MATCH_CONS_DERIVATION: {
            if (derivation->match_cons_derivation == NULL) {
                return false;
            }

            Value *value = derivation->match_cons_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != CLOSURE_VALUE) {
                return false;
            }

            if (value->closure_value == NULL) {
                return false;
            }

            if (!copy_closure(closure_value, value->closure_value)) {
                return false;
            }

            return true;
        }
        default: {
            return false;
        }
    }
}

bool try_get_rec_closure_value_from_derivation(Derivation *derivation,
                                               RecClosure *rec_closure_value) {
    if (derivation == NULL) {
        return false;
    }

    if (rec_closure_value == NULL) {
        return false;
    }

    switch (derivation->type) {
        case VAR_DERIVATION: {
            if (derivation->var_derivation == NULL) {
                return false;
            }

            Value *value = derivation->var_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != REC_CLOSURE_VALUE) {
                return false;
            }

            if (value->rec_closure_value == NULL) {
                return false;
            }

            if (!copy_rec_closure(rec_closure_value, value->rec_closure_value)) {
                return false;
            }

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

            if (value->type != REC_CLOSURE_VALUE) {
                return false;
            }

            if (value->rec_closure_value == NULL) {
                return false;
            }

            if (!copy_rec_closure(rec_closure_value, value->rec_closure_value)) {
                return false;
            }

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

            if (value->type != REC_CLOSURE_VALUE) {
                return false;
            }

            if (value->rec_closure_value == NULL) {
                return false;
            }

            if (!copy_rec_closure(rec_closure_value, value->rec_closure_value)) {
                return false;
            }

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

            if (value->type != REC_CLOSURE_VALUE) {
                return false;
            }

            if (value->rec_closure_value == NULL) {
                return false;
            }

            if (!copy_rec_closure(rec_closure_value, value->rec_closure_value)) {
                return false;
            }

            return true;
        }
        case APP_DERIVATION: {
            if (derivation->app_derivation == NULL) {
                return false;
            }

            Value *value = derivation->app_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != REC_CLOSURE_VALUE) {
                return false;
            }

            if (value->rec_closure_value == NULL) {
                return false;
            }

            if (!copy_rec_closure(rec_closure_value, value->rec_closure_value)) {
                return false;
            }

            return true;
        }
        case LET_REC_DERIVATION: {
            if (derivation->let_rec_derivation == NULL) {
                return false;
            }

            Value *value = derivation->let_rec_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != REC_CLOSURE_VALUE) {
                return false;
            }

            if (value->rec_closure_value == NULL) {
                return false;
            }

            if (!copy_rec_closure(rec_closure_value, value->rec_closure_value)) {
                return false;
            }

            return true;
        }
        case APP_REC_DERIVATION: {
            if (derivation->app_rec_derivation == NULL) {
                return false;
            }

            Value *value = derivation->app_rec_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != REC_CLOSURE_VALUE) {
                return false;
            }

            if (value->rec_closure_value == NULL) {
                return false;
            }

            if (!copy_rec_closure(rec_closure_value, value->rec_closure_value)) {
                return false;
            }

            return true;
        }
        case MATCH_NIL_DERIVATION: {
            if (derivation->match_nil_derivation == NULL) {
                return false;
            }

            Value *value = derivation->match_nil_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != REC_CLOSURE_VALUE) {
                return false;
            }

            if (value->rec_closure_value == NULL) {
                return false;
            }

            if (!copy_rec_closure(rec_closure_value, value->rec_closure_value)) {
                return false;
            }

            return true;
        }
        case MATCH_CONS_DERIVATION: {
            if (derivation->match_cons_derivation == NULL) {
                return false;
            }

            Value *value = derivation->match_cons_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != REC_CLOSURE_VALUE) {
                return false;
            }

            if (value->rec_closure_value == NULL) {
                return false;
            }

            if (!copy_rec_closure(rec_closure_value, value->rec_closure_value)) {
                return false;
            }

            return true;
        }
        default: {
            return false;
        }
    }
}

bool try_get_cons_value_from_derivation(Derivation *derivation, Cons *cons_value) {
    if (derivation == NULL) {
        return false;
    }

    if (cons_value == NULL) {
        return false;
    }

    switch (derivation->type) {
        case VAR_DERIVATION: {
            if (derivation->var_derivation == NULL) {
                return false;
            }

            Value *value = derivation->var_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != CONS_VALUE) {
                return false;
            }

            if (value->cons_value == NULL) {
                return false;
            }

            if (!copy_cons(cons_value, value->cons_value)) {
                return false;
            }

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

            if (value->type != CONS_VALUE) {
                return false;
            }

            if (value->cons_value == NULL) {
                return false;
            }

            if (!copy_cons(cons_value, value->cons_value)) {
                return false;
            }

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

            if (value->type != CONS_VALUE) {
                return false;
            }

            if (value->cons_value == NULL) {
                return false;
            }

            if (!copy_cons(cons_value, value->cons_value)) {
                return false;
            }

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

            if (value->type != CONS_VALUE) {
                return false;
            }

            if (value->cons_value == NULL) {
                return false;
            }

            if (!copy_cons(cons_value, value->cons_value)) {
                return false;
            }

            return true;
        }
        case APP_DERIVATION: {
            if (derivation->app_derivation == NULL) {
                return false;
            }

            Value *value = derivation->app_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != CONS_VALUE) {
                return false;
            }

            if (value->cons_value == NULL) {
                return false;
            }

            if (!copy_cons(cons_value, value->cons_value)) {
                return false;
            }

            return true;
        }
        case LET_REC_DERIVATION: {
            if (derivation->let_rec_derivation == NULL) {
                return false;
            }

            Value *value = derivation->let_rec_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != CONS_VALUE) {
                return false;
            }

            if (value->cons_value == NULL) {
                return false;
            }

            if (!copy_cons(cons_value, value->cons_value)) {
                return false;
            }

            return true;
        }
        case APP_REC_DERIVATION: {
            if (derivation->app_rec_derivation == NULL) {
                return false;
            }

            Value *value = derivation->app_rec_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != CONS_VALUE) {
                return false;
            }

            if (value->cons_value == NULL) {
                return false;
            }

            if (!copy_cons(cons_value, value->cons_value)) {
                return false;
            }

            return true;
        }
        case CONS_DERIVATION: {
            if (derivation->cons_derivation == NULL) {
                return false;
            }

            Cons *cons = derivation->cons_derivation->cons_value;
            if (cons == NULL) {
                return false;
            }

            if (!copy_cons(cons_value, cons)) {
                return false;
            }

            return true;
        }
        case MATCH_NIL_DERIVATION: {
            if (derivation->match_nil_derivation == NULL) {
                return false;
            }

            Value *value = derivation->match_nil_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != CONS_VALUE) {
                return false;
            }

            if (value->cons_value == NULL) {
                return false;
            }

            if (!copy_cons(cons_value, value->cons_value)) {
                return false;
            }

            return true;
        }
        case MATCH_CONS_DERIVATION: {
            if (derivation->match_cons_derivation == NULL) {
                return false;
            }

            Value *value = derivation->match_cons_derivation->value;
            if (value == NULL) {
                return false;
            }

            if (value->type != CONS_VALUE) {
                return false;
            }

            if (value->cons_value == NULL) {
                return false;
            }

            if (!copy_cons(cons_value, value->cons_value)) {
                return false;
            }

            return true;
        }
        default: {
            return false;
        }
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
        case VAR_DERIVATION: {
            if (derivation->var_derivation == NULL) {
                return NULL;
            }

            return create_copied_value(derivation->var_derivation->value);
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

            return create_copied_value(derivation->if_true_derivation->value);
        }
        case IF_FALSE_DERIVATION: {
            if (derivation->if_false_derivation == NULL) {
                return NULL;
            }

            return create_copied_value(derivation->if_false_derivation->value);
        }
        case LET_DERIVATION: {
            if (derivation->let_derivation == NULL) {
                return NULL;
            }

            return create_copied_value(derivation->let_derivation->value);
        }
        case FUN_DERIVATION: {
            if (derivation->fun_derivation == NULL) {
                return NULL;
            }

            Closure *closure_value = create_copied_closure(
                derivation->fun_derivation->closure_value
            );
            if (closure_value == NULL) {
                return NULL;
            }

            return create_closure_value(closure_value);
        }
        case APP_DERIVATION: {
            if (derivation->app_derivation == NULL) {
                return NULL;
            }

            return create_copied_value(derivation->app_derivation->value);
        }
        case LET_REC_DERIVATION: {
            if (derivation->let_rec_derivation == NULL) {
                return NULL;
            }

            return create_copied_value(derivation->let_rec_derivation->value);
        }
        case APP_REC_DERIVATION: {
            if (derivation->app_rec_derivation == NULL) {
                return NULL;
            }

            return create_copied_value(derivation->app_rec_derivation->value);
        }
        case NIL_DERIVATION: {
            return create_nil_value();
        }
        case CONS_DERIVATION: {
            if (derivation->cons_derivation == NULL) {
                return NULL;
            }

            return create_cons_value(
                create_copied_cons(derivation->cons_derivation->cons_value)
            );
        }
        case MATCH_NIL_DERIVATION: {
            if (derivation->match_nil_derivation == NULL) {
                return NULL;
            }

            return create_copied_value(derivation->match_nil_derivation->value);
        }
        case MATCH_CONS_DERIVATION: {
            if (derivation->match_cons_derivation == NULL) {
                return NULL;
            }

            return create_copied_value(derivation->match_cons_derivation->value);
        }
        default: {
            return NULL;
        }
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
            derivation->env = create_copied_env(env);
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
            derivation->env = create_copied_env(env);
            derivation->bool_derivation = bool_derivation;
            return derivation;
        }
        case VAR_EXP: {
            if (exp->var_exp == NULL) {
                return NULL;
            }

            VarBinding *var_binding = env->var_binding;
            while (var_binding != NULL) {
                if (is_same_var(var_binding->var, exp->var_exp->var)) {
                    VarDerivation *var_derivation = malloc(sizeof(VarDerivation));
                    var_derivation->var_exp = exp->var_exp;
                    var_derivation->value = create_copied_value(var_binding->value);

                    Derivation *derivation = malloc(sizeof(Derivation));
                    derivation->type = VAR_DERIVATION;
                    derivation->env = create_copied_env(env);
                    derivation->var_derivation = var_derivation;
                    return derivation;
                }

                var_binding = var_binding->next;
            }

            return NULL;
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
                    derivation->env = create_copied_env(env);
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
                    derivation->env = create_copied_env(env);
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
                    derivation->env = create_copied_env(env);
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
                    derivation->env = create_copied_env(env);
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
                derivation->env = create_copied_env(env);
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
                derivation->env = create_copied_env(env);
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
            derivation->env = create_copied_env(env);
            derivation->let_derivation = let_derivation;

            free_env(env_new);
            free_value(value_1);

            return derivation;
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

            Closure *closure_value = create_closure(env, exp->fun_exp->var, exp->fun_exp->exp);
            if (closure_value == NULL) {
                return NULL;
            }

            FunDerivation *fun_derivation = malloc(sizeof(FunDerivation));
            fun_derivation->fun_exp = exp->fun_exp;
            fun_derivation->closure_value = closure_value;

            Derivation *derivation = malloc(sizeof(Derivation));
            derivation->type = FUN_DERIVATION;
            derivation->env = create_copied_env(env);
            derivation->fun_derivation = fun_derivation;
            return derivation;
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

            Derivation *premise_1 = derive_impl(env, exp->app_exp->exp_1);
            if (premise_1 == NULL) {
                return NULL;
            }

            Value *value_1 = create_value_from_derivation(premise_1);
            if (value_1 == NULL) {
                free_derivation(premise_1);
                return NULL;
            }

            switch (value_1->type) {
                case CLOSURE_VALUE: {
                    Closure *closure_value = value_1->closure_value;
                    if (closure_value == NULL) {
                        free_value(value_1);
                        free_derivation(premise_1);
                        return NULL;
                    }

                    Derivation *premise_2 = derive_impl(env, exp->app_exp->exp_2);
                    if (premise_2 == NULL) {
                        free_value(value_1);
                        free_derivation(premise_1);
                        return NULL;
                    }

                    Value *value_2 = create_value_from_derivation(premise_2);
                    if (value_2 == NULL) {
                        free_derivation(premise_2);
                        free_value(value_1);
                        free_derivation(premise_1);
                        return NULL;
                    }

                    Env *env_new = create_appended_env(
                        closure_value->env,
                        closure_value->var,
                        value_2
                    );
                    if (env_new == NULL) {
                        free_value(value_2);
                        free_derivation(premise_2);
                        free_value(value_1);
                        free_derivation(premise_1);
                        return NULL;
                    }

                    Derivation *premise_3 = derive_impl(env_new, closure_value->exp);
                    if (premise_3 == NULL) {
                        free_env(env_new);
                        free_value(value_2);
                        free_derivation(premise_2);
                        free_value(value_1);
                        free_derivation(premise_1);
                        return NULL;
                    }

                    Value *value_3 = create_value_from_derivation(premise_3);
                    if (value_3 == NULL) {
                        free_env(env_new);
                        free_value(value_2);
                        free_derivation(premise_2);
                        free_value(value_1);
                        free_derivation(premise_1);
                        return NULL;
                    }

                    AppDerivation *app_derivation = malloc(sizeof(AppDerivation));
                    app_derivation->premise_1 = premise_1;
                    app_derivation->premise_2 = premise_2;
                    app_derivation->premise_3 = premise_3;
                    app_derivation->app_exp = exp->app_exp;
                    app_derivation->value = value_3;

                    Derivation *derivation = malloc(sizeof(Derivation));
                    derivation->type = APP_DERIVATION;
                    derivation->env = create_copied_env(env);
                    derivation->app_derivation = app_derivation;

                    free_env(env_new);
                    free_value(value_2);
                    free_value(value_1);

                    return derivation;
                }
                case REC_CLOSURE_VALUE: {
                    RecClosure *rec_closure_value = value_1->rec_closure_value;
                    if (rec_closure_value == NULL) {
                        free_value(value_1);
                        free_derivation(premise_1);
                        return NULL;
                    }

                    Derivation *premise_2 = derive_impl(env, exp->app_exp->exp_2);
                    if (premise_2 == NULL) {
                        free_value(value_1);
                        free_derivation(premise_1);
                        return NULL;
                    }

                    Value *value_2 = create_value_from_derivation(premise_2);
                    if (value_2 == NULL) {
                        free_derivation(premise_2);
                        free_value(value_1);
                        free_derivation(premise_1);
                        return NULL;
                    }

                    Env *env_temp = create_appended_env(
                        rec_closure_value->env,
                        rec_closure_value->var_rec,
                        value_1
                    );
                    if (env_temp == NULL) {
                        free_value(value_2);
                        free_derivation(premise_2);
                        free_value(value_1);
                        free_derivation(premise_1);
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
                        free_derivation(premise_2);
                        free_value(value_1);
                        free_derivation(premise_1);
                        return NULL;
                    }

                    Derivation *premise_3 = derive_impl(env_new, rec_closure_value->exp);
                    if (premise_3 == NULL) {
                        free_env(env_new);
                        free_value(value_2);
                        free_derivation(premise_2);
                        free_value(value_1);
                        free_derivation(premise_1);
                    }

                    Value *value_3 = create_value_from_derivation(premise_3);
                    if (value_3 == NULL) {
                        free_derivation(premise_3);
                        free_env(env_new);
                        free_value(value_2);
                        free_derivation(premise_2);
                        free_value(value_1);
                        free_derivation(premise_1);
                    }

                    AppRecDerivation *app_rec_derivation = malloc(sizeof(AppRecDerivation));
                    app_rec_derivation->premise_1 = premise_1;
                    app_rec_derivation->premise_2 = premise_2;
                    app_rec_derivation->premise_3 = premise_3;
                    app_rec_derivation->app_exp = exp->app_exp;
                    app_rec_derivation->value = value_3;

                    Derivation *derivation = malloc(sizeof(Derivation));
                    derivation->type = APP_REC_DERIVATION;
                    derivation->env = create_copied_env(env);
                    derivation->app_rec_derivation = app_rec_derivation;

                    free_env(env_new);
                    free_value(value_2);
                    free_value(value_1);

                    return derivation;
                }
                default: {
                    free_value(value_1);
                    free_derivation(premise_1);
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

            Derivation *premise = derive_impl(env_new, exp->let_rec_exp->exp_2);
            if (premise == NULL) {
                free_env(env_new);
                free_value(rec_closure_value);
                return NULL;
            }

            Value *value = create_value_from_derivation(premise);
            if (value == NULL) {
                free_derivation(premise);
                free_env(env_new);
                free_value(rec_closure_value);
            }

            LetRecDerivation *let_rec_derivation = malloc(sizeof(LetRecDerivation));
            let_rec_derivation->premise = premise;
            let_rec_derivation->let_rec_exp = exp->let_rec_exp;
            let_rec_derivation->value = value;

            Derivation *derivation = malloc(sizeof(Derivation));
            derivation->type = LET_REC_DERIVATION;
            derivation->env = create_copied_env(env);
            derivation->let_rec_derivation = let_rec_derivation;

            free_env(env_new);
            free_value(rec_closure_value);

            return derivation;
        }
        case NIL_EXP: {
            Derivation *derivation = malloc(sizeof(Derivation));
            derivation->type = NIL_DERIVATION;
            derivation->env = create_copied_env(env);
            return derivation;
        }
        case CONS_EXP: {
            if (exp->cons_exp == NULL) {
                return NULL;
            }

            Exp *exp_elem = exp->cons_exp->exp_elem;
            if (exp_elem == NULL) {
                return NULL;
            }

            Exp *exp_list = exp->cons_exp->exp_list;
            if (exp_list == NULL) {
                return NULL;
            }

            Derivation *premise_elem = derive_impl(env, exp_elem);
            if (premise_elem == NULL) {
                return NULL;
            }

            Value *value_elem = create_value_from_derivation(premise_elem);
            if (value_elem == NULL) {
                free_derivation(premise_elem);
                return NULL;
            }

            Derivation *premise_list = derive_impl(env, exp_list);
            if (premise_list == NULL) {
                free_value(value_elem);
                free_derivation(premise_elem);
                return NULL;
            }

            Value *value_list = create_value_from_derivation(premise_list);
            if (value_list == NULL) {
                free_derivation(premise_list);
                free_value(value_elem);
                free_derivation(premise_elem);
                return NULL;
            }

            ConsDerivation *cons_derivation = malloc(sizeof(ConsDerivation));
            cons_derivation->premise_elem = premise_elem;
            cons_derivation->premise_list = premise_list;
            cons_derivation->cons_exp = exp->cons_exp;
            cons_derivation->cons_value = create_cons(value_elem, value_list);

            Derivation *derivation = malloc(sizeof(Derivation));
            derivation->type = CONS_DERIVATION;
            derivation->env = create_copied_env(env);
            derivation->cons_derivation = cons_derivation;

            free_value(value_list);
            free_value(value_elem);

            return derivation;
        }
        case MATCH_EXP: {
            if (exp->match_exp == NULL) {
                return NULL;
            }

            Exp *exp_list = exp->match_exp->exp_list;
            if (exp_list == NULL) {
                return NULL;
            }

            Derivation *premise_list = derive_impl(env, exp_list);
            if (premise_list == NULL) {
                return NULL;
            }

            Value *value_list = create_value_from_derivation(premise_list);
            if (value_list == NULL) {
                free_derivation(premise_list);
                return NULL;
            }

            switch (value_list->type) {
                case NIL_VALUE: {
                    Exp *exp_match_nil = exp->match_exp->exp_match_nil;
                    if (exp_match_nil == NULL) {
                        free_derivation(premise_list);
                        return NULL;
                    }

                    Derivation *premise_match_nil = derive_impl(env, exp_match_nil);
                    if (premise_match_nil == NULL) {
                        free_derivation(premise_list);
                        return NULL;
                    }

                    Value *value_match_nil = create_value_from_derivation(premise_match_nil);
                    if (value_match_nil == NULL) {
                        free_derivation(premise_match_nil);
                        free_derivation(premise_list);
                        return NULL;
                    }

                    MatchNilDerivation *match_nil_derivation = malloc(sizeof(MatchNilDerivation));
                    match_nil_derivation->premise_list = premise_list;
                    match_nil_derivation->premise_match_nil = premise_match_nil;
                    match_nil_derivation->match_exp = exp->match_exp;
                    match_nil_derivation->value = value_match_nil;

                    Derivation *derivation = malloc(sizeof(Derivation));
                    derivation->type = MATCH_NIL_DERIVATION;
                    derivation->env = create_copied_env(env);
                    derivation->match_nil_derivation = match_nil_derivation;
                    return derivation;
                }
                case CONS_VALUE: {
                    Cons *cons_value = value_list->cons_value;
                    if (cons_value == NULL) {
                        free_value(value_list);
                        free_derivation(premise_list);
                        return NULL;
                    }

                    Value *value_elem = create_copied_value(cons_value->value_elem);
                    if (value_elem == NULL) {
                        free_value(value_list);
                        free_derivation(premise_list);
                        return NULL;
                    }

                    Value *value_subsequent_list = create_copied_value(cons_value->value_list);
                    if (value_list == NULL) {
                        free_value(value_elem);
                        free_value(value_list);
                        free_derivation(premise_list);
                        return NULL;
                    }

                    Exp *exp_match_cons = exp->match_exp->exp_match_cons;
                    if (exp_match_cons == NULL) {
                        free_value(value_subsequent_list);
                        free_value(value_elem);
                        free_value(value_list);
                        free_derivation(premise_list);
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
                        free_derivation(premise_list);
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
                        free_derivation(premise_list);
                    }

                    Derivation *premise_match_cons = derive_impl(env_new, exp_match_cons);
                    if (premise_match_cons == NULL) {
                        free_env(env_new);
                        free_value(value_subsequent_list);
                        free_value(value_elem);
                        free_value(value_list);
                        free_derivation(premise_list);
                        return NULL;
                    }

                    Value *value_cons = create_value_from_derivation(premise_match_cons);
                    if (value_cons == NULL) {
                        free_derivation(premise_match_cons);
                        free_env(env_new);
                        free_value(value_subsequent_list);
                        free_value(value_elem);
                        free_value(value_list);
                        free_derivation(premise_list);
                        return NULL;
                    }

                    MatchConsDerivation *match_cons_derivation = malloc(
                        sizeof(MatchConsDerivation)
                    );
                    match_cons_derivation->premise_list = premise_list;
                    match_cons_derivation->premise_match_cons = premise_match_cons;
                    match_cons_derivation->match_exp = exp->match_exp;
                    match_cons_derivation->value = value_cons;

                    Derivation *derivation = malloc(sizeof(Derivation));
                    derivation->type = MATCH_CONS_DERIVATION;
                    derivation->env = create_copied_env(env);
                    derivation->match_cons_derivation = match_cons_derivation;

                    free_env(env_new);
                    free_value(value_subsequent_list);
                    free_value(value_elem);
                    free_value(value_list);

                    return derivation;
                }
                default: {
                    free_derivation(premise_list);
                    return NULL;
                }
            }
        }
        default: {
            return NULL;
        }
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
        case VAR_DERIVATION: {
            if (derivation->var_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            free_value(derivation->var_derivation->value);
            free(derivation->var_derivation);
            free_env(derivation->env);
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
        case LET_DERIVATION: {
            if (derivation->let_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            free_derivation(derivation->let_derivation->premise_1);
            free_derivation(derivation->let_derivation->premise_2);
            free_value(derivation->let_derivation->value);
            free(derivation->let_derivation);
            free_env(derivation->env);
            free(derivation);
            return;
        }
        case FUN_DERIVATION: {
            if (derivation->fun_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            if (derivation->fun_derivation->closure_value != NULL) {
                free_env(derivation->fun_derivation->closure_value->env);
                free_var(derivation->fun_derivation->closure_value->var);
                free(derivation->fun_derivation->closure_value);
            }
            free(derivation->fun_derivation);
            free_env(derivation->env);
            free(derivation);
            return;
        }
        case APP_DERIVATION: {
            if (derivation->app_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            free_derivation(derivation->app_derivation->premise_1);
            free_derivation(derivation->app_derivation->premise_2);
            free_derivation(derivation->app_derivation->premise_3);
            free_value(derivation->app_derivation->value);
            free(derivation->app_derivation);
            free_env(derivation->env);
            free(derivation);
            return;
        }
        case LET_REC_DERIVATION: {
            if (derivation->let_rec_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            free_derivation(derivation->let_rec_derivation->premise);
            free_value(derivation->let_rec_derivation->value);
            free(derivation->let_rec_derivation);
            free_env(derivation->env);
            free(derivation);
            return;
        }
        case APP_REC_DERIVATION: {
            if (derivation->app_rec_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            free_derivation(derivation->app_rec_derivation->premise_1);
            free_derivation(derivation->app_rec_derivation->premise_2);
            free_derivation(derivation->app_rec_derivation->premise_3);
            free_value(derivation->app_rec_derivation->value);
            free(derivation->app_rec_derivation);
            free_env(derivation->env);
            free(derivation);
            return;
        }
        case CONS_DERIVATION: {
            if (derivation->cons_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            free_derivation(derivation->cons_derivation->premise_elem);
            free_derivation(derivation->cons_derivation->premise_list);
            free_cons(derivation->cons_derivation->cons_value);
            free_env(derivation->env);
            free(derivation);
            return;
        }
        case MATCH_NIL_DERIVATION: {
            if (derivation->match_nil_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            free_derivation(derivation->match_nil_derivation->premise_list);
            free_derivation(derivation->match_nil_derivation->premise_match_nil);
            free_value(derivation->match_nil_derivation->value);
            free_env(derivation->env);
            free(derivation);
            return;
        }
        case MATCH_CONS_DERIVATION: {
            if (derivation->match_cons_derivation == NULL) {
                free_env(derivation->env);
                free(derivation);
                return;
            }

            free_derivation(derivation->match_cons_derivation->premise_list);
            free_derivation(derivation->match_cons_derivation->premise_match_cons);
            free_value(derivation->match_cons_derivation->value);
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

void fprint_indent(FILE *fp, const int level) {
    for (int i = 0; i < level; i++) {
        fprintf(fp, "  ");
    }
}

bool fprint_derivation(FILE *fp, const Derivation *derivation) {
    return fprint_derivation_impl(fp, derivation, 0);
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

            fprintf(fp,
                    " evalto %s by E-Bool {}",
                    derivation->bool_derivation->bool_value ? "true" : "false");
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case VAR_DERIVATION: {
            if (derivation->var_derivation == NULL) {
                return false;
            }

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

            if (!fprint_var_exp(fp, derivation->var_derivation->var_exp)) {
                return false;
            }

            Value *value = derivation->var_derivation->value;
            if (value == NULL) {
                return false;
            }

            fprintf(fp, " evalto ");
            if (!fprint_value(fp, value)) {
                return false;
            }
            fprintf(fp, " by E-Var {}");
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

            fprintf(fp,
                    " evalto %s by E-Lt {\n",
                    derivation->lt_derivation->bool_value ? "true" : "false");
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
        case FUN_DERIVATION: {
            FunDerivation *fun_derivation = derivation->fun_derivation;
            if (fun_derivation == NULL) {
                return false;
            }

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

            if (!fprint_fun_exp(fp, fun_derivation->fun_exp)) {
                return false;
            }

            if (fun_derivation->closure_value == NULL) {
                return false;
            }

            fprintf(fp, " evalto ");
            if (!fprint_closure(fp, fun_derivation->closure_value)) {
                return false;
            }
            fprintf(fp, " by E-Fun {}");
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case APP_DERIVATION: {
            AppDerivation *app_derivation = derivation->app_derivation;
            if (app_derivation == NULL) {
                return false;
            }

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

            if (!fprint_app_exp(fp, app_derivation->app_exp)) {
                return false;
            }

            Value *value = app_derivation->value;
            if (value == NULL) {
                return false;
            }

            fprintf(fp, " evalto ");
            if (!fprint_value(fp, value)) {
                return false;
            }
            fprintf(fp, " by E-App {\n");
            if (!fprint_derivation_impl(fp, app_derivation->premise_1, level + 1)) {
                return false;
            }
            fprintf(fp, ";\n");
            if (!fprint_derivation_impl(fp, app_derivation->premise_2, level + 1)) {
                return false;
            }
            fprintf(fp, ";\n");
            if (!fprint_derivation_impl(fp, app_derivation->premise_3, level + 1)) {
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
        case LET_REC_DERIVATION: {
            LetRecDerivation *let_rec_derivation = derivation->let_rec_derivation;
            if (let_rec_derivation == NULL) {
                return false;
            }

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

            if (!fprint_let_rec_exp(fp, let_rec_derivation->let_rec_exp)) {
                return false;
            }

            Value *value = let_rec_derivation->value;
            if (value == NULL) {
                return false;
            }

            fprintf(fp, " evalto ");
            if (!fprint_value(fp, value)) {
                return false;
            }
            fprintf(fp, " by E-LetRec {\n");
            if (!fprint_derivation_impl(fp, let_rec_derivation->premise, level + 1)) {
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
        case APP_REC_DERIVATION: {
            AppRecDerivation *app_rec_derivation = derivation->app_rec_derivation;
            if (app_rec_derivation == NULL) {
                return false;
            }

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

            if (!fprint_app_exp(fp, app_rec_derivation->app_exp)) {
                return false;
            }

            Value *value = app_rec_derivation->value;
            if (value == NULL) {
                return false;
            }

            fprintf(fp, " evalto ");
            if (!fprint_value(fp, value)) {
                return false;
            }
            fprintf(fp, " by E-AppRec {\n");
            if (!fprint_derivation_impl(fp, app_rec_derivation->premise_1, level + 1)) {
                return false;
            }
            fprintf(fp, ";\n");
            if (!fprint_derivation_impl(fp, app_rec_derivation->premise_2, level + 1)) {
                return false;
            }
            fprintf(fp, ";\n");
            if (!fprint_derivation_impl(fp, app_rec_derivation->premise_3, level + 1)) {
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
        case NIL_DERIVATION: {
            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- [] evalto [] by E-Nil {}");
            if (level == 0) {
                fprintf(fp, "\n");
            }
            return true;
        }
        case CONS_DERIVATION: {
            if (derivation->cons_derivation == NULL) {
                return false;
            }

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

            if (!fprint_cons_exp(fp, derivation->cons_derivation->cons_exp)) {
                return false;
            }

            Derivation *premise_elem = derivation->cons_derivation->premise_elem;

            Value *value_elem = create_value_from_derivation(premise_elem);
            if (value_elem == NULL) {
                return false;
            }

            Derivation *premise_list = derivation->cons_derivation->premise_list;

            Value *value_list = create_value_from_derivation(premise_list);
            if (value_list == NULL) {
                free_value(value_elem);
                return false;
            }

            fprintf(fp, " evalto ");
            if (!fprint_cons(fp, derivation->cons_derivation->cons_value)) {
                return false;
            }
            fprintf(fp, " by E-Cons {\n");
            if (!fprint_derivation_impl(fp, premise_elem, level + 1)) {
                return false;
            }
            fprintf(fp, ";\n");
            if (!fprint_derivation_impl(fp, premise_list, level + 1)) {
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
        case MATCH_NIL_DERIVATION: {
            MatchNilDerivation *match_nil_derivation = derivation->match_nil_derivation;
            if (match_nil_derivation == NULL) {
                return false;
            }

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

            if (!fprint_match_exp(fp, match_nil_derivation->match_exp)) {
                return false;
            }

            Value *value = match_nil_derivation->value;
            if (value == NULL) {
                return false;
            }

            fprintf(fp, " evalto ");
            if (!fprint_value(fp, value)) {
                return false;
            }
            fprintf(fp, " by E-MatchNil {\n");
            if (!fprint_derivation_impl(fp, match_nil_derivation->premise_list, level + 1)) {
                return false;
            }
            fprintf(fp, ";\n");
            if (!fprint_derivation_impl(fp,
                                        match_nil_derivation->premise_match_nil,
                                        level + 1)) {
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
        case MATCH_CONS_DERIVATION: {
            MatchConsDerivation *match_cons_derivation = derivation->match_cons_derivation;
            if (match_cons_derivation == NULL) {
                return false;
            }

            if (!fprint_env(fp, derivation->env)) {
                return false;
            }
            if (derivation->env->var_binding != NULL) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|- ");

            if (!fprint_match_exp(fp, match_cons_derivation->match_exp)) {
                return false;
            }

            Value *value = match_cons_derivation->value;
            if (value == NULL) {
                return false;
            }

            fprintf(fp, " evalto ");
            if (!fprint_value(fp, value)) {
                return false;
            }
            fprintf(fp, " by E-MatchCons {\n");
            if (!fprint_derivation_impl(fp, match_cons_derivation->premise_list, level + 1)) {
                return false;
            }
            fprintf(fp, ";\n");
            if (!fprint_derivation_impl(fp,
                                        match_cons_derivation->premise_match_cons,
                                        level + 1)) {
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
        default: {
            return false;
        }
    }
}
