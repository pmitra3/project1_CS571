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
    // Create (5 * 3) first
    struct Expr *five_times_three = mk_times(mk_float(5.0), mk_float(3.0));
    
    // Then create (2 + (5 * 3))
    return mk_plus(mk_float(2.0), five_times_three);
}

/* This function should create the expr (3 + (1 / 8))
 * using the above constructors.
 */
struct Expr *mk_expr2() {
    // Create (1 / 8) first
    struct Expr *one_div_eight = mk_div(mk_float(1.0), mk_float(8.0));
    
    // Then create (3 + (1 / 8))
    return mk_plus(mk_float(3.0), one_div_eight);
}

/* This function should create the expr ((4 / 3) - (4 / (2 + 3)))
 * using the above constructors.
 */
struct Expr *mk_expr3() {
    // Create (4 / 3)
    struct Expr *four_div_three = mk_div(mk_float(4.0), mk_float(3.0));
    
    // Create (2 + 3)
    struct Expr *two_plus_three = mk_plus(mk_float(2.0), mk_float(3.0));
    
    // Create (4 / (2 + 3))
    struct Expr *four_div_sum = mk_div(mk_float(4.0), two_plus_three);
    
    // Finally create ((4 / 3) - (4 / (2 + 3)))
    return mk_minus(four_div_three, four_div_sum);
}

/*
 * This function should free all memory associated 
 * with the given AST.
*/
void free_expr(struct Expr* e) {
    if (e == NULL) {
        return;
    }
    
    // If this is not a leaf node (FLOAT), recursively free children
    if (e->type != FLOAT) {
        free_expr(e->subexprs.e1);
        free_expr(e->subexprs.e2);
    }
    
    // Free the current node
    free(e);
}

/*
 * This function should evaluate the given AST and
 * return the floating-point result.
*/
float eval(struct Expr* e) {
    if (e == NULL) {
        return 0.0;  // Should not happen in well-formed expressions
    }
    
    switch (e->type) {
        case FLOAT:
            return e->literal;
            
        case PLUS:
            return eval(e->subexprs.e1) + eval(e->subexprs.e2);
            
        case MINUS:
            return eval(e->subexprs.e1) - eval(e->subexprs.e2);
            
        case TIMES:
            return eval(e->subexprs.e1) * eval(e->subexprs.e2);
            
        case DIV:
            return eval(e->subexprs.e1) / eval(e->subexprs.e2);
            
        default:
            // Should not happen
            return 0.0;
    }
}