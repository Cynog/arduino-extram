#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "poisson.hpp"
#include "usart.hpp"

int main(void) {
    // initialize usart
    setup_usart();

    // initialize extram
    setup_extram();

    // testing parameters
    int N = 13;
    int maxit = 1000;
    float tol = 1e-6F;

    // return value
    struct output retval;

    ////////////////* INTERNAL RAM *////////////////
    // allocate phi
    float *phi = (float *)calloc((N + 2) * (N + 2), sizeof(float));
    if (phi == NULL)
        serprint("PHI MEMORY ALLOCATION FAILED\n\r");

    // solve poisson equation
    retval = solve(N, f_source, maxit, tol, phi);
    serprint("flag = ");
    serprintint(retval.flag);
    serprint("\n\riter = ");
    serprintint(retval.iter);
    serprint("\n\rresidual = ");
    serprintfloat(retval.residual, 0, 8);
    serprint("\n\r");

    ////////////////* EXTERNAL RAM *////////////////
    // external SRAM starting address for phi
    uint16_t phi_addr = 0;

    // solve poisson equation
    retval = solve_extram(N, f_source, maxit, tol, phi_addr);
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
