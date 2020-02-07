#include <stdio.h>
#include <stdlib.h>

#include "ml1_semantics.h"

int main(void) {
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
    Value *value1 = evaluate(exp1);
    printf("%s\n", value1->bool_value ? "true" : "false");
    free_value(value1);

    Derivation *derivation1 = derive(exp1);
    fprint_derivation(stdout, derivation1);
    free_derivation(derivation1);
    free_exp(exp1);

    return 0;
}
