#ifndef ML1_SEMANTICS_H
#define ML1_SEMANTICS_H

#include <stdbool.h>

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

bool evalto(Value *value, const Exp *exp);

#endif // ML1_SEMANTICS_H
