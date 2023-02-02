#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib_poisson.hpp"
#include "lib_usart.hpp"
#include "lib_time.hpp"

int main(void) {
    // initialize usart
    usart_setup();

    // initialize extram
    extram_setup();

    // initialize timer
    timer_setup();
    uint32_t t;

    // testing parameters
    int N = 10;
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
    timer_reset();
    retval = solve(N, f_source, maxit, tol, phi);
    t = timer_getms();
    serprint("flag = ");
    serprintint(retval.flag);
    serprint("\n\riter = ");
    serprintint(retval.iter);
    serprint("\n\rresidual = ");
    serprintfloat(retval.residual, 0, 8);
    serprint("\n\relapsed time = ");
    serprintuint32(t);
    serprint(" ms\n\r");

    ////////////////* EXTERNAL RAM *////////////////
    // external SRAM starting address for phi
    uint16_t phi_addr = 0;

    // solve poisson equation
    timer_reset();
    retval = solve_extram(N, f_source, maxit, tol, phi_addr);
    t = timer_getms();
    serprint("flag = ");
    serprintint(retval.flag);
    serprint("\n\riter = ");
    serprintint(retval.iter);
    serprint("\n\rresidual = ");
    serprintfloat(retval.residual, 0, 8);
    serprint("\n\relapsed time = ");
    serprintuint32(t);
    serprint(" ms\n\r");

    // solve buffered poisson equation
    timer_reset();
    retval = solve_extram_buffered(N, f_source, maxit, tol, phi_addr);
    t = timer_getms();
    serprint("flag = ");
    serprintint(retval.flag);
    serprint("\n\riter = ");
    serprintint(retval.iter);
    serprint("\n\rresidual = ");
    serprintfloat(retval.residual, 0, 8);
    serprint("\n\relapsed time = ");
    serprintuint32(t);
    serprint(" ms\n\r");

    // free
    free(phi);

    // endless loop
    while (1) {
    };
}
