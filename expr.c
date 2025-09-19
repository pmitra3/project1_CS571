/* Collaborators: None*/
#include "expr.h"
#include "stdlib.h"
#include "stdio.h"


struct Expr *mk_plus(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = PLUS;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_minus(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = MINUS;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_times(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret =  malloc(sizeof(struct Expr));
    ret->type = TIMES;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_div(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = DIV;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_float(float f) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = FLOAT;
    ret->literal = f;

    return ret;
}

/* This function should create the expr (2 + (5 * 3))
 * using the above constructors.
 */
struct Expr *mk_expr1() {
    struct Expr *five = mk_float(5.0);
    struct Expr *three = mk_float(3.0);
    struct Expr *two = mk_float(2.0);

    struct Expr *five_times_three = mk_times(five, three);
    struct Expr *expr = mk_plus(two, five_times_three);
    return expr;
}

/* This function should create the expr (3 + (1 / 8))
 * using the above constructors.
 */
struct Expr *mk_expr2() {
    struct Expr *three = mk_float(3.0);
    struct Expr *one = mk_float(1.0);
    struct Expr *eight = mk_float(8.0);

    struct Expr *one_div_eight = mk_div(one, eight);
    struct Expr *expr = mk_plus(three, one_div_eight);
    return expr;
}

/* This function should create the expr ((4 / 3) - (4 / (2 + 3)))
 * using the above constructors.
 */
struct Expr *mk_expr3() {
    /* Use distinct nodes; don't reuse the same pointer in two places. */
    struct Expr *four_a  = mk_float(4.0);
    struct Expr *three_a = mk_float(3.0);

    struct Expr *two     = mk_float(2.0);
    struct Expr *three_b = mk_float(3.0);

    struct Expr *four_b  = mk_float(4.0);

    struct Expr *four_div_three = mk_div(four_a, three_a);
    struct Expr *two_plus_three = mk_plus(two, three_b);
    struct Expr *four_div_sum   = mk_div(four_b, two_plus_three);
    struct Expr *expr = mk_minus(four_div_three, four_div_sum);
    return expr;
}


/*
 * This function should free all memory associated 
 * with the given AST.
*/
void free_expr(struct Expr* e) {
    if (!e) return;

    if (e->type == PLUS || e->type == MINUS || e->type == TIMES || e->type == DIV) {
        free_expr(e->subexprs.e1);
        free_expr(e->subexprs.e2);
    }
    free(e);
}

/*
 * This function should evaluate the given AST and
 * return the floating-point result.
*/
float eval(struct Expr* e) {
    if (!e) return 0.0;

    switch (e->type) {
        case PLUS:
            return eval(e->subexprs.e1) + eval(e->subexprs.e2);
        case MINUS:
            return eval(e->subexprs.e1) - eval(e->subexprs.e2);
        case TIMES:
            return eval(e->subexprs.e1) * eval(e->subexprs.e2);
        case DIV:
            return eval(e->subexprs.e1) / eval(e->subexprs.e2);
        case FLOAT:
            return e->literal;
        default:
            return 0.0; // Should not happen
    }
}