#ifndef ML2_SEMANTICS_H
#define ML2_SEMANTICS_H

#include <stdbool.h>
#include <stdio.h>

#define VAR_NAME_LEN_MAX (32)

typedef struct {
    char *name;
    size_t name_len;
} Var;

typedef enum {
    INT_VALUE,
    BOOL_VALUE,
    CLOSURE_VALUE
} ValueType;

typedef struct ClosureTag Closure;

typedef struct {
    ValueType type;
    union {
        int int_value;
        bool bool_value;
        Closure *closure_value;
    };
} Value;

typedef struct VarBindingTag {
    Var *var;
    Value *value;
    struct VarBindingTag *next;
} VarBinding;

typedef struct {
    VarBinding *var_binding;
} Env;

typedef struct {
    int int_value;
} IntExp;

typedef struct {
    bool bool_value;
} BoolExp;

typedef struct {
    Var *var;
} VarExp;

typedef struct OpExpTag OpExp;

typedef struct IfExpTag IfExp;

typedef struct LetExpTag LetExp;

typedef struct FunExpTag FunExp;

typedef struct AppExpTag AppExp;

typedef enum {
    INT_EXP,
    BOOL_EXP,
    VAR_EXP,
    OP_EXP,
    IF_EXP,
    LET_EXP,
    FUN_EXP,
    APP_EXP
} ExpType;

typedef struct {
    ExpType type;
    union {
        IntExp *int_exp;
        BoolExp *bool_exp;
        VarExp *var_exp;
        OpExp *op_exp;
        IfExp *if_exp;
        LetExp *let_exp;
        FunExp *fun_exp;
        AppExp *app_exp;
    };
} Exp;

struct ClosureTag {
    Env *env;
    Var *var;
    Exp *exp;
};

typedef enum {
    PLUS_OP_EXP,
    MINUS_OP_EXP,
    TIMES_OP_EXP,
    LT_OP_EXP
} OpExpType;

struct OpExpTag {
    OpExpType type;
    Exp *exp_left;
    Exp *exp_right;
};

struct IfExpTag {
    Exp *exp_cond;
    Exp *exp_true;
    Exp *exp_false;
};

struct LetExpTag {
    Var *var;
    Exp *exp_1;
    Exp *exp_2;
};

struct FunExpTag {
    Var *var;
    Exp *exp;
};

struct AppExpTag {
    Exp *exp_1;
    Exp *exp_2;
};

typedef struct {
    IntExp *int_exp;
    int int_value;
} IntDerivation;

typedef struct {
    BoolExp *bool_exp;
    bool bool_value;
} BoolDerivation;

typedef struct {
    FunExp *fun_exp;
    Closure *closure_value;
} FunDerivation;

typedef struct Var1DerivationTag Var1Derivation;

typedef struct Var2DerivationTag Var2Derivation;

typedef struct PlusDerivationTag PlusDerivation;

typedef struct MinusDerivationTag MinusDerivation;

typedef struct TimesDerivationTag TimesDerivation;

typedef struct LtDerivationTag LtDerivation;

typedef struct IfTrueDerivationTag IfTrueDerivation;

typedef struct IfFalseDerivationTag IfFalseDerivation;

typedef struct LetDerivationTag LetDerivation;

typedef struct AppDerivationTag AppDerivation;

typedef enum {
    INT_DERIVATION,
    BOOL_DERIVATION,
    VAR_1_DERIVATION,
    VAR_2_DERIVATION,
    PLUS_DERIVATION,
    MINUS_DERIVATION,
    TIMES_DERIVATION,
    LT_DERIVATION,
    IF_TRUE_DERIVATION,
    IF_FALSE_DERIVATION,
    LET_DERIVATION,
    FUN_DERIVATION,
    APP_DERIVATION
} DerivationType;

typedef struct {
    DerivationType type;
    Env *env;
    union {
        IntDerivation *int_derivation;
        BoolDerivation *bool_derivation;
        Var1Derivation *var_1_derivation;
        Var2Derivation *var_2_derivation;
        PlusDerivation *plus_derivation;
        MinusDerivation *minus_derivation;
        TimesDerivation *times_derivation;
        LtDerivation *lt_derivation;
        IfTrueDerivation *if_true_derivation;
        IfFalseDerivation *if_false_derivation;
        LetDerivation *let_derivation;
        FunDerivation *fun_derivation;
        AppDerivation *app_derivation;
    };
} Derivation;

struct Var1DerivationTag {
    VarExp *var_exp;
    Value *value;
};

struct Var2DerivationTag {
    Derivation *premise;
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

Var *create_var(const char *src_name);

Var *create_copied_var(const Var *var);

bool is_same_var(const Var *var_1, const Var *var_2);

void free_var(Var *var);

Value *create_int_value(const int int_value);

Value *create_bool_value(const bool bool_value);

Closure *create_closure(const Env *env, const Var *var, Exp *exp);

Closure *create_copied_closure(const Closure *closure);

void free_closure(Closure *closure);

Value *create_closure_value(Closure *closure);

Value *create_copied_value(const Value *value);

void free_value(Value *value);

Env *create_copied_env(const Env *env);

Env *create_poped_env(const Env *env);

Env *create_appended_env(const Env *env, const Var *var, const Value *value);

void free_env(Env *env);

Exp *create_int_exp(const int int_value);

Exp *create_bool_exp(const bool bool_value);

Exp *create_var_exp(Var *var);

Exp *create_plus_op_exp(Exp *exp_left, Exp *exp_right);

Exp *create_minus_op_exp(Exp *exp_left, Exp *exp_right);

Exp *create_times_op_exp(Exp *exp_left, Exp *exp_right);

Exp *create_lt_op_exp(Exp *exp_left, Exp *exp_right);

Exp *create_if_exp(Exp *exp_cond, Exp *exp_true, Exp *exp_false);

Exp *create_let_exp(Var *var, Exp *exp_1, Exp *exp_2);

Exp *create_fun_exp(Var *var, Exp *exp);

Exp *create_app_exp(Exp *exp_1, Exp *exp_2);

void free_exp(Exp *exp);

Value *evaluate(const Exp *exp);

Value *evaluate_impl(const Env *env, const Exp *exp);

bool try_get_int_value_from_derivation(Derivation *derivation, int *int_value);

bool try_get_bool_value_from_derivation(Derivation *derivation, bool *bool_value);

bool try_get_closure_value_from_derivation(Derivation *derivation, Closure *closure_value);

Value *create_value_from_derivation(Derivation *derivation);

Derivation *derive(Exp *exp);

Derivation *derive_impl(const Env *env, Exp *exp);

void free_derivation(Derivation *derivation);

bool fprint_var(FILE *fp, const Var *var);

bool fprint_closure(FILE *fp, const Closure *closure);

bool fprint_value(FILE *fp, const Value *value);

bool fprint_env(FILE *fp, const Env *exp);

bool fprint_exp(FILE *fp, const Exp *exp);

bool fprint_int_exp(FILE *fp, IntExp *exp);

bool fprint_bool_exp(FILE *fp, BoolExp *exp);

bool fprint_var_exp(FILE *fp, VarExp *exp);

bool fprint_op_exp(FILE *fp, OpExp *exp);

bool fprint_if_exp(FILE *fp, IfExp *exp);

bool fprint_let_exp(FILE *fp, LetExp *exp);

bool fprint_fun_exp(FILE *fp, FunExp *exp);

bool fprint_app_exp(FILE *fp, AppExp *exp);

void fprint_indent(FILE *fp, const int level);

bool fprint_derivation(FILE *fp, const Derivation *derivation);

bool fprint_derivation_impl(FILE *fp, const Derivation *derivation, const int level);

#endif // ML2_SEMANTICS_H
