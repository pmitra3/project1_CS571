/* Collaborators: None*/
#include "expr.h"
#include "stdio.h"

int main() {
    struct Expr *e1 = mk_expr1();

    // After finishing part 1, the following should output:
    // "Expr 1: (2.000000 + (5.000000 * 3.000000))"
    printf("Expr 1: ");
    print_expr(e1);
   //printf("\n");

    // After finishing part 3, the following should output:
    // "evals to 17.000000"

    printf("evals to %f\n", eval(e1)); 

    free_expr(e1);

    struct Expr *e2 = mk_expr2();

    // After finishing part 1, the following should output:
    // "Expr 2: (3.000000 + (1.000000 / 8.000000))"
    printf("Expr 2: ");
    print_expr(e2);
   // printf("\n");

    // After finishing part 3, the following should output:
    // "evals to 3.125000"
    printf("evals to %f\n", eval(e2)); 

    free_expr(e2);

    struct Expr *e3 = mk_expr3();

    // After finishing part 1, the following should output:
    // "Expr 3: ((4.000000 / 3.000000) - (4.000000 / (2.000000 + 3.000000)))"
    printf("Expr 3: ");
    print_expr(e3);
   // printf("\n");

    // After finishing part 3, the following should output:
    // "evals to  0.533333"
    printf("evals to %f\n", eval(e3)); 

    free_expr(e3);

    //Free memory to avoid leaks



    return 0;
}
