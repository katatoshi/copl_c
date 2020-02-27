#ifndef ML4_DERIVATION_H
#define ML4_DERIVATION_H

#include <stdbool.h>
#include <stdio.h>

typedef struct {
    IntExp *int_exp;
    int int_value;
} IntDerivation;

typedef struct {
    BoolExp *bool_exp;
    bool bool_value;
} BoolDerivation;

typedef struct VarDerivationTag VarDerivation;

typedef struct PlusDerivationTag PlusDerivation;

typedef struct MinusDerivationTag MinusDerivation;

typedef struct TimesDerivationTag TimesDerivation;

typedef struct LtDerivationTag LtDerivation;

typedef struct IfTrueDerivationTag IfTrueDerivation;

typedef struct IfFalseDerivationTag IfFalseDerivation;

typedef struct LetDerivationTag LetDerivation;

typedef struct AppDerivationTag AppDerivation;

typedef struct LetRecDerivationTag LetRecDerivation;

typedef struct {
    FunExp *fun_exp;
    Closure *closure_value;
} FunDerivation;

typedef struct AppRecDerivationTag AppRecDerivation;

typedef struct ConsDerivationTag ConsDerivation;

typedef struct MatchNilDerivationTag MatchNilDerivation;

typedef struct MatchConsDerivationTag MatchConsDerivation;

typedef enum {
    INT_DERIVATION,
    BOOL_DERIVATION,
    VAR_DERIVATION,
    PLUS_DERIVATION,
    MINUS_DERIVATION,
    TIMES_DERIVATION,
    LT_DERIVATION,
    IF_TRUE_DERIVATION,
    IF_FALSE_DERIVATION,
    LET_DERIVATION,
    FUN_DERIVATION,
    APP_DERIVATION,
    LET_REC_DERIVATION,
    APP_REC_DERIVATION,
    NIL_DERIVATION,
    CONS_DERIVATION,
    MATCH_NIL_DERIVATION,
    MATCH_CONS_DERIVATION
} DerivationType;

typedef struct {
    DerivationType type;
    Env *env;
    union {
        IntDerivation *int_derivation;
        BoolDerivation *bool_derivation;
        VarDerivation *var_derivation;
        PlusDerivation *plus_derivation;
        MinusDerivation *minus_derivation;
        TimesDerivation *times_derivation;
        LtDerivation *lt_derivation;
        IfTrueDerivation *if_true_derivation;
        IfFalseDerivation *if_false_derivation;
        LetDerivation *let_derivation;
        FunDerivation *fun_derivation;
        AppDerivation *app_derivation;
        LetRecDerivation *let_rec_derivation;
        AppRecDerivation *app_rec_derivation;
        ConsDerivation *cons_derivation;
        MatchNilDerivation *match_nil_derivation;
        MatchConsDerivation *match_cons_derivation;
    };
} Derivation;

struct VarDerivationTag {
    VarExp *var_exp;
    Value *value;
};

struct PlusDerivationTag {
    Derivation *premise_left;
    Derivation *premise_right;
    OpExp *op_exp;
    int int_value;
};

struct MinusDerivationTag {
    Derivation *premise_left;
    Derivation *premise_right;
    OpExp *op_exp;
    int int_value;
};

struct TimesDerivationTag {
    Derivation *premise_left;
    Derivation *premise_right;
    OpExp *op_exp;
    int int_value;
};

struct LtDerivationTag {
    Derivation *premise_left;
    Derivation *premise_right;
    OpExp *op_exp;
    bool bool_value;
};

struct IfTrueDerivationTag {
    Derivation *premise_cond;
    Derivation *premise_true;
    IfExp *if_exp;
    Value *value;
};

struct IfFalseDerivationTag {
    Derivation *premise_cond;
    Derivation *premise_false;
    IfExp *if_exp;
    Value *value;
};

struct LetDerivationTag {
    Derivation *premise_1;
    Derivation *premise_2;
    LetExp *let_exp;
    Value *value;
};

struct AppDerivationTag {
    Derivation *premise_1;
    Derivation *premise_2;
    Derivation *premise_3;
    AppExp *app_exp;
    Value *value;
};

struct LetRecDerivationTag {
    Derivation *premise;
    LetRecExp *let_rec_exp;
    Value *value;
};

struct AppRecDerivationTag {
    Derivation *premise_1;
    Derivation *premise_2;
    Derivation *premise_3;
    AppExp *app_exp;
    Value *value;
};

struct ConsDerivationTag {
    Derivation *premise_elem;
    Derivation *premise_list;
    ConsExp *cons_exp;
    Cons *cons_value;
};

struct MatchNilDerivationTag {
    Derivation *premise_list;
    Derivation *premise_match_nil;
    MatchExp *match_exp;
    Value *value;
};

struct MatchConsDerivationTag {
    Derivation *premise_list;
    Derivation *premise_match_cons;
    MatchExp *match_exp;
    Value *value;
};

bool try_get_int_value_from_derivation(Derivation *derivation, int *int_value);

bool try_get_bool_value_from_derivation(Derivation *derivation, bool *bool_value);

bool try_get_closure_value_from_derivation(Derivation *derivation, Closure *closure_value);

bool try_get_rec_closure_value_from_derivation(Derivation *derivation,
                                               RecClosure *rec_closure_value);

bool try_get_cons_value_from_derivation(Derivation *derivation, Cons *cons_value);

Value *create_value_from_derivation(Derivation *derivation);

Derivation *derive(Exp *exp);

Derivation *derive_impl(const Env *env, Exp *exp);

void free_derivation(Derivation *derivation);

void fprint_indent(FILE *fp, const int level);

bool fprint_derivation(FILE *fp, const Derivation *derivation);

bool fprint_derivation_impl(FILE *fp, const Derivation *derivation, const int level);

#endif // ML4_DERIVATION_H
