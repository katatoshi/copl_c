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
    Exp *exp;
    Value *value;
} Judgement;

typedef struct {
    Judgement *conclusion;
} IntDerivation;

typedef struct {
    Judgement *conclusion;
} BoolDerivation;

typedef struct OpDerivationTag OpDerivation;

typedef enum {
    INT_DERIVATION,
    BOOL_DERIVATION,
    OP_DERIVATION
} DerivationType;

typedef struct {
    DerivationType type;
    union {
        IntDerivation *int_derivation;
        BoolDerivation *bool_derivation;
        OpDerivation *op_derivation;
    };
} Derivation;

typedef enum {
    PLUS_OP_DERIVATION,
    MINUS_OP_DERIVATION,
    TIMES_OP_DERIVATION,
    LT_OP_DERIVATION,
} OpDerivationType;

struct OpDerivationTag {
    OpDerivationType type;
    Judgement *conclusion;
    Derivation *premise_left;
    Derivation *premise_right;
};

void free_value(Value *value);

bool evalto(Value *value, const Exp *exp);

bool derive(Derivation *derivation, Exp *exp);

void free_derivation(Derivation *derivation);

bool fprint_exp(FILE *fp, const Exp *exp);

void fprint_indent(FILE *fp, const int level);

bool fprint_derivation_impl(FILE *fp, const Derivation *derivation, const int level);

bool fprint_derivation(FILE *fp, const Derivation *derivation);

#endif // ML1_SEMANTICS_H
