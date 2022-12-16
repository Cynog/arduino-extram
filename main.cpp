#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "poisson.hpp"
#include "usart.hpp"

int main(void) {
    // initialize usart
    setup_usart();

    // test
    int N = 13;

    // allocate phi
    float *phi = (float *)calloc((N + 2) * (N + 2), sizeof(float));
    if (phi == NULL)
        serprint("PHI MEMORY ALLOCATION FAILED\n\r");

    // solve poisson equation
    int maxit = 1000;
    float tol = 1e-6F;

    struct output retval = solve_serial(N, f_source, maxit, tol, phi);

    serprint("flag = ");
    serprintint(retval.flag);
    serprint("\n\riter = ");
    serprintint(retval.iter);
    serprint("\n\rresidual = ");
    serprintfloat(retval.residual, 0, 8);
    serprint("\n\r");

    // free
    free(phi);

    // endless loop
    while (1) {
    };
}
