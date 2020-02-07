#ifndef ML1_SEMANTICS_H
#define ML1_SEMANTICS_H

#include <stdbool.h>
#include <stdio.h>

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

typedef struct {
    int int_value;
} IntExp;

typedef struct {
    bool bool_value;
} BoolExp;

typedef struct OpExpTag OpExp;

typedef enum {
    INT_EXP,
    BOOL_EXP,
    OP_EXP
} ExpType;

typedef struct {
    ExpType type;
    union {
        IntExp *int_exp;
        BoolExp *bool_exp;
        OpExp *op_exp;
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

typedef struct {
    IntExp *int_exp;
    int int_value;
} IntDerivation;

typedef struct {
    BoolExp *bool_exp;
    bool bool_value;
} BoolDerivation;

typedef struct PlusOpDerivationTag PlusOpDerivation;

typedef struct MinusOpDerivationTag MinusOpDerivation;

typedef struct TimesOpDerivationTag TimesOpDerivation;

typedef struct LtOpDerivationTag LtOpDerivation;

typedef enum {
    INT_DERIVATION,
    BOOL_DERIVATION,
    PLUS_OP_DERIVATION,
    MINUS_OP_DERIVATION,
    TIMES_OP_DERIVATION,
    LT_OP_DERIVATION
} DerivationType;

typedef struct {
    DerivationType type;
    union {
        IntDerivation *int_derivation;
        BoolDerivation *bool_derivation;
        PlusOpDerivation *plus_op_derivation;
        MinusOpDerivation *minus_op_derivation;
        TimesOpDerivation *times_op_derivation;
        LtOpDerivation *lt_op_derivation;
    };
} Derivation;

struct PlusOpDerivationTag {
    Derivation *premise_left;
    Derivation *premise_right;
    OpExp *op_exp;
    int int_value;
};

struct MinusOpDerivationTag {
    Derivation *premise_left;
    Derivation *premise_right;
    OpExp *op_exp;
    int int_value;
};

struct TimesOpDerivationTag {
    Derivation *premise_left;
    Derivation *premise_right;
    OpExp *op_exp;
    int int_value;
};

struct LtOpDerivationTag {
    Derivation *premise_left;
    Derivation *premise_right;
    OpExp *op_exp;
    bool bool_value;
};

Value *create_int_value(const int int_value);

Value *create_bool_value(const bool bool_value);

void free_value(Value *value);

Exp *create_int_exp(const int int_value);

Exp *create_bool_exp(const bool bool_value);

Exp *create_plus_op_exp(Exp *exp_left, Exp *exp_right);

bool evalto(Value *value, const Exp *exp);

bool derive(Derivation *derivation, Exp *exp);

void free_derivation(Derivation *derivation);

bool fprint_exp(FILE *fp, Exp *exp);

bool fprint_int_exp(FILE *fp, IntExp *exp);

bool fprint_bool_exp(FILE *fp, BoolExp *exp);

bool fprint_op_exp(FILE *fp, OpExp *exp);

void fprint_indent(FILE *fp, const int level);

bool fprint_derivation_impl(FILE *fp, const Derivation *derivation, const int level);

bool fprint_derivation(FILE *fp, const Derivation *derivation);

#endif // ML1_SEMANTICS_H
