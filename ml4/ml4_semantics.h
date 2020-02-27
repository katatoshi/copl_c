#ifndef ML4_SEMANTICS_H
#define ML4_SEMANTICS_H

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
    CLOSURE_VALUE,
    REC_CLOSURE_VALUE,
    NIL_VALUE,
    CONS_VALUE
} ValueType;

typedef struct ClosureTag Closure;

typedef struct RecClosureTag RecClosure;

typedef struct ConsTag Cons;

typedef struct {
    ValueType type;
    union {
        int int_value;
        bool bool_value;
        Closure *closure_value;
        RecClosure *rec_closure_value;
        Cons *cons_value;
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

typedef struct LetRecExpTag LetRecExp;

typedef struct ConsExpTag ConsExp;

typedef struct MatchExpTag MatchExp;

typedef enum {
    INT_EXP,
    BOOL_EXP,
    VAR_EXP,
    OP_EXP,
    IF_EXP,
    LET_EXP,
    FUN_EXP,
    APP_EXP,
    LET_REC_EXP,
    NIL_EXP,
    CONS_EXP,
    MATCH_EXP
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
        LetRecExp *let_rec_exp;
        ConsExp *cons_exp;
        MatchExp *match_exp;
    };
} Exp;

struct ClosureTag {
    Env *env;
    Var *var;
    Exp *exp;
};

struct RecClosureTag {
    Env *env;
    Var *var_rec;
    Var *var;
    Exp *exp;
};

struct ConsTag {
    Value *value_elem;
    Value *value_list;
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

struct LetRecExpTag {
    Var *var_rec;
    Var *var;
    Exp *exp_1;
    Exp *exp_2;
};

struct ConsExpTag {
    Exp *exp_elem;
    Exp *exp_list;
};

struct MatchExpTag {
    Exp *exp_list;
    Exp *exp_match_nil;
    Var *var_elem;
    Var *var_list;
    Exp *exp_match_cons;
};

Var *create_var(const char *src_name);

Var *create_copied_var(const Var *var);

bool is_same_var(const Var *var_1, const Var *var_2);

void free_var(Var *var);

Value *create_int_value(const int int_value);

Value *create_bool_value(const bool bool_value);

Closure *create_closure(const Env *env, const Var *var, Exp *exp);

Closure *create_copied_closure(const Closure *closure);

bool copy_closure(Closure *closure_dst, const Closure *closure_src);

void free_closure(Closure *closure);

Value *create_closure_value(Closure *closure);

RecClosure *create_rec_closure(const Env *env, const Var *var_rec, const Var *var, Exp *exp);

RecClosure *create_copied_rec_closure(const RecClosure *rec_closure);

bool copy_rec_closure(RecClosure *rec_closure_dst, const RecClosure *rec_closure_src);

void free_rec_closure(RecClosure *rec_closure);

Value *create_rec_closure_value(RecClosure *rec_closure);

Value *create_nil_value();

Cons *create_cons(const Value *value_elem, const Value *value_list);

Cons *create_copied_cons(const Cons *cons);

bool copy_cons(Cons *cons_dst, const Cons *cons_src);

void free_cons(Cons *cons);

Value *create_cons_value(Cons *cons);

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

Exp *create_let_rec_exp(Var *var_rec, Var *var, Exp *exp_1, Exp *exp_2);

Exp *create_nil_exp();

Exp *create_cons_exp(Exp *exp_elem, Exp *exp_list);

Exp *create_match_exp(Exp *exp_list,
                      Exp *exp_match_nil,
                      Var *var_elem,
                      Var *var_list,
                      Exp *exp_match_cons);

void free_exp(Exp *exp);

Value *evaluate(const Exp *exp);

Value *evaluate_impl(const Env *env, const Exp *exp);

bool fprint_var(FILE *fp, const Var *var);

bool fprint_closure(FILE *fp, const Closure *closure);

bool fprint_rec_closure(FILE *fp, const RecClosure *rec_closure);

bool fprint_cons(FILE *fp, const Cons *cons);

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

bool fprint_let_rec_exp(FILE *fp, LetRecExp *exp);

bool fprint_nil_exp(FILE *fp);

bool fprint_cons_exp(FILE *fp, ConsExp *exp);

bool fprint_match_exp(FILE *fp, MatchExp *exp);

#endif // ML4_SEMANTICS_H
