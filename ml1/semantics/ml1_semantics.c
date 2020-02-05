#include <stdio.h>

#include "ml1_semantics.h"

bool evalto(Value *value, const Exp *exp) {
    if (value == NULL || exp == NULL) {
        return false;
    }

    switch (exp->type) {
        case INT_EXP: {
            value->type = INT_VALUE;
            value->int_value = exp->int_exp->int_value;
            return true;
        }
        case BOOL_EXP: {
            value->type = BOOL_VALUE;
            value->bool_value = exp->bool_exp->bool_value;
            return true;
        }
        case OP_EXP: {
            const Exp *exp_left = exp->op_exp->exp_left;
            if (exp_left == NULL) {
                return false;
            }

            const Exp *exp_right = exp->op_exp->exp_right;
            if (exp_right == NULL) {
                return false;
            }

            Value value_left;
            if (!evalto(&value_left, exp_left)) {
                return false;
            }

            if (value_left.type != INT_VALUE) {
                return false;
            }

            Value value_right;
            if (!evalto(&value_right, exp_right)) {
                return false;
            }

            if (value_right.type != INT_VALUE) {
                return false;
            }

            switch(exp->op_exp->type) {
                case PLUS_OP_EXP: {
                    value->type = INT_VALUE;
                    value->int_value = value_left.int_value + value_right.int_value;
                    return true;
                }
                case MINUS_OP_EXP: {
                    value->type = INT_VALUE;
                    value->int_value = value_left.int_value - value_right.int_value;
                    return true;
                }
                case TIMES_OP_EXP: {
                    value->type = INT_VALUE;
                    value->int_value = value_left.int_value * value_right.int_value;
                    return true;
                }
                case LT_OP_EXP: {
                    value->type = BOOL_VALUE;
                    value->bool_value = value_left.int_value < value_right.int_value;
                    return true;
                }
                default:
                    return false;
            }
        }
        default:
            return false;
    }
}

int main(void) {
    Value value1;
    IntExp int_exp1 = { 2 };
    Exp exp1;
    exp1.type = INT_EXP;
    exp1.int_exp = &int_exp1;
    evalto(&value1, &exp1);
    printf("%d\n", value1.int_value);

    Value value2;
    BoolExp bool_exp2 = { true };
    Exp exp2;
    exp2.type = BOOL_EXP;
    exp2.bool_exp = &bool_exp2;
    evalto(&value2, &exp2);
    printf("%s\n", value2.bool_value ? "true" : "false");

    Value value3;
    IntExp int_exp3 = { 3 };
    Exp exp3;
    exp3.type = INT_EXP;
    exp3.int_exp = &int_exp3;
    evalto(&value3, &exp3);
    printf("%d\n", value3.int_value);

    Value value4;
    OpExp op_exp4;
    op_exp4.type = PLUS_OP_EXP;
    op_exp4.exp_left = &exp1;
    op_exp4.exp_right = &exp3;
    Exp exp4;
    exp4.type = OP_EXP;
    exp4.op_exp = &op_exp4;
    evalto(&value4, &exp4);
    printf("%d\n", value4.int_value);

    Value value5;
    IntExp int_exp5 = { 5 };
    Exp exp5;
    exp5.type = INT_EXP;
    exp5.int_exp = &int_exp5;
    evalto(&value5, &exp5);
    printf("%d\n", value5.int_value);

    Value value6;
    OpExp op_exp6;
    op_exp6.type = TIMES_OP_EXP;
    op_exp6.exp_left = &exp4;
    op_exp6.exp_right = &exp5;
    Exp exp6;
    exp6.type = OP_EXP;
    exp6.op_exp = &op_exp6;
    evalto(&value6, &exp6);
    printf("%d\n", value6.int_value);

    Value value7;
    IntExp int_exp7 = { -2 };
    Exp exp7;
    exp7.type = INT_EXP;
    exp7.int_exp = &int_exp7;
    evalto(&value7, &exp7);
    printf("%d\n", value7.int_value);

    return 0;
}
