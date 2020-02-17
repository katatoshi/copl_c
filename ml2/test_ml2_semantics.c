#include <stdio.h>
#include <stdlib.h>

#include "ml2_semantics.h"

void test1(void) {
    Exp *exp1 = create_lt_op_exp(
        create_int_exp(2),
        create_times_op_exp(
            create_plus_op_exp(
                create_int_exp(3),
                create_minus_op_exp(
                    create_int_exp(4),
                    create_int_exp(5)
                )
            ),
            create_int_exp(6)
        )
    );

    VarBinding *var_binding_1 = malloc(sizeof(VarBinding));
    var_binding_1->var = create_var("x");
    var_binding_1->value = create_int_value(2);
    var_binding_1->next = NULL;

    VarBinding *var_binding_2 = malloc(sizeof(VarBinding));
    var_binding_2->var = create_var("hoge");
    var_binding_2->value = create_bool_value(true);
    var_binding_2->next = var_binding_1;

    Env *env = malloc(sizeof(Env));
    env->var_binding = var_binding_2;

    Value *value1 = evaluate_impl(env, exp1);
    printf("%s\n", value1->bool_value ? "true" : "false");
    free_value(value1);

    Derivation *derivation1 = derive_impl(env, exp1);
    fprint_derivation(stdout, derivation1);
    free_derivation(derivation1);
    free_env(env);
    free_exp(exp1);
}

void test2(void) {
    Exp *exp1 = create_var_exp(create_var("x"));
    Var *var1 = create_var("x");
    Value *value1 = create_int_value(3);
    Var *var2 = create_var("y");
    Value *value2 = create_int_value(2);
    VarBinding var_binding1 = { .var = var1, .value = value1, .next = NULL };
    VarBinding var_binding2 = { .var = var2, .value = value2, .next = &var_binding1 };
    Env env = { .var_binding = &var_binding2 };
    Value *value3 = evaluate_impl(&env, exp1);
    printf("%d\n", value3->int_value);
    free_value(value3);
    free_var(var2);
    free_value(value2);
    free_var(var1);
    free_value(value1);
    free_exp(exp1);
}

void test3(void) {
    Exp *exp1 = create_let_exp(
        create_var("x"),
        create_plus_op_exp(
            create_int_exp(1),
            create_int_exp(2)
        ),
        create_times_op_exp(
            create_var_exp(create_var("x")),
            create_int_exp(4)
        )
    );
    Env env = { .var_binding = NULL };
    Value *value1 = evaluate_impl(&env, exp1);
    printf("%d\n", value1->int_value);
    free_value(value1);
    free_exp(exp1);
}

void test4(void) {
    Exp *exp1 = create_let_exp(
        create_var("x"),
        create_times_op_exp(
            create_int_exp(3),
            create_int_exp(3)
        ),
        create_let_exp(
            create_var("y"),
            create_times_op_exp(
                create_int_exp(4),
                create_var_exp(create_var("x"))
            ),
            create_plus_op_exp(
                create_var_exp(create_var("x")),
                create_var_exp(create_var("y"))
            )
        )
    );
    Env env = { .var_binding = NULL };
    Value *value1 = evaluate_impl(&env, exp1);
    printf("%d\n", value1->int_value);
    free_value(value1);
    free_exp(exp1);
}

void test5(void) {
    Exp *exp1 = create_let_exp(
        create_var("x"),
        create_bool_exp(true),
        create_let_exp(
            create_var("y"),
            create_int_exp(4),
            create_if_exp(
                create_var_exp(create_var("x")),
                create_times_op_exp(
                    create_var_exp(create_var("y")),
                    create_int_exp(2)
                ),
                create_var_exp(create_var("y"))
            )
        )
    );
    Value *value1 = evaluate(exp1);
    printf("%d\n", value1->int_value);
    free_value(value1);
    free_exp(exp1);

    Exp *exp2 = create_let_exp(
        create_var("x"),
        create_bool_exp(true),
        create_let_exp(
            create_var("y"),
            create_int_exp(4),
            create_if_exp(
                create_var_exp(create_var("x")),
                create_plus_op_exp(
                    create_var_exp(create_var("y")),
                    create_int_exp(2)
                ),
                create_var_exp(create_var("y"))
            )
        )
    );
    Value *value2 = evaluate(exp2);
    printf("%d\n", value2->int_value);
    free_value(value2);
    free_exp(exp2);

    Exp *exp3 = create_let_exp(
        create_var("x"),
        create_bool_exp(true),
        create_let_exp(
            create_var("y"),
            create_int_exp(4),
            create_if_exp(
                create_var_exp(create_var("x")),
                create_times_op_exp(
                    create_var_exp(create_var("y")),
                    create_int_exp(2)
                ),
                create_var_exp(create_var("y"))
            )
        )
    );
    Value *value3 = evaluate(exp3);
    printf("%d\n", value3->int_value);
    free_value(value3);
    free_exp(exp3);
}

int main(void) {
    test1();
    test2();
    test3();
    test4();
    test5();

    return 0;
}
