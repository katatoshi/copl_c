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
    BOOL_VALUE
} ValueType;

typedef struct {
    ValueType type;
    union {
        int int_value;
        bool bool_value;
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

typedef enum {
    INT_EXP,
    BOOL_EXP,
    VAR_EXP,
    OP_EXP,
    IF_EXP,
    LET_EXP
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
    };
} Exp;

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

typedef struct {
    IntExp *int_exp;
    int int_value;
} IntDerivation;

typedef struct {
    BoolExp *bool_exp;
    bool bool_value;
} BoolDerivation;

typedef struct PlusDerivationTag PlusDerivation;

typedef struct MinusDerivationTag MinusDerivation;

typedef struct TimesDerivationTag TimesDerivation;

typedef struct LtDerivationTag LtDerivation;

typedef struct IfTrueDerivationTag IfTrueDerivation;

typedef struct IfFalseDerivationTag IfFalseDerivation;

typedef enum {
    INT_DERIVATION,
    BOOL_DERIVATION,
    PLUS_DERIVATION,
    MINUS_DERIVATION,
    TIMES_DERIVATION,
    LT_DERIVATION,
    IF_TRUE_DERIVATION,
    IF_FALSE_DERIVATION
} DerivationType;

typedef struct {
    DerivationType type;
    union {
        IntDerivation *int_derivation;
        BoolDerivation *bool_derivation;
        PlusDerivation *plus_derivation;
        MinusDerivation *minus_derivation;
        TimesDerivation *times_derivation;
        LtDerivation *lt_derivation;
        IfTrueDerivation *if_true_derivation;
        IfFalseDerivation *if_false_derivation;
    };
} Derivation;

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

Var *create_var(const char *src_name);

Var *copy_var(const Var *var);

bool is_same_var(const Var *var_1, const Var *var_2);

void free_var(Var *var);

Value *create_int_value(const int int_value);

Value *create_bool_value(const bool bool_value);

Value *copy_value(const Value *value);

void free_value(Value *value);

Env *copy_env(const Env *env);

Env *create_appended_env(const Env *env, const Var *var, const Value *value);

void free_env(Env *env);

Exp *create_int_exp(const int int_value);

Exp *create_bool_exp(const bool bool_value);

Exp *create_var_exp(const char *src_name);

Exp *create_plus_op_exp(Exp *exp_left, Exp *exp_right);

Exp *create_minus_op_exp(Exp *exp_left, Exp *exp_right);

Exp *create_times_op_exp(Exp *exp_left, Exp *exp_right);

Exp *create_lt_op_exp(Exp *exp_left, Exp *exp_right);

Exp *create_if_exp(Exp *exp_cond, Exp *exp_true, Exp *exp_false);

Exp *create_let_exp(Var *var, Exp *exp_1, Exp *exp_2);

void free_exp(Exp *exp);

Value *evaluate(Env *env, const Exp *exp);

bool try_get_int_value_from_derivation(Derivation *derivation, int *int_value);

bool try_get_bool_value_from_derivation(Derivation *derivation, bool *bool_value);

Value *create_value_from_derivation(Derivation *derivation);

Derivation *derive(Exp *exp);

void free_derivation(Derivation *derivation);

bool fprint_value(FILE *fp, Value *value);

bool fprint_var(FILE *fp, Var *var);

bool fprint_env(FILE *fp, Env *exp);

bool fprint_exp(FILE *fp, Exp *exp);

bool fprint_int_exp(FILE *fp, IntExp *exp);

bool fprint_bool_exp(FILE *fp, BoolExp *exp);

bool fprint_op_exp(FILE *fp, OpExp *exp);

bool fprint_if_exp(FILE *fp, IfExp *exp);

void fprint_indent(FILE *fp, const int level);

bool fprint_derivation_impl(FILE *fp, const Derivation *derivation, const int level);

bool fprint_derivation(FILE *fp, const Derivation *derivation);

#endif // ML2_SEMANTICS_H
