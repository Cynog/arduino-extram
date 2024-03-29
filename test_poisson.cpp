/**
 * @file test_poisson.cpp
 * @author Cynog (github.com/Cynog)
 * @brief Main program to measure time of the different Jacobi-solvers for the 2d Poisson equation showing the performance improvements using caching.
 * 
 */

#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib_poisson.hpp"
#include "lib_timer.hpp"
#include "lib_usart.hpp"

int main(void) {
    // initialize usart
    usart_setup();

    // initialize extram
    extram_setup();

    // initialize timer
    timer_setup();
    uint32_t t;

    // testing parameters
    uint8_t N = 10;
    uint16_t maxit = 1000;
    float tol = 1e-6F;

    // return value
    struct output retval;

    // endless main loop
    while (1) {
        // print info
        serprint("SOLVING POISSON EQUATION LAPLACE(phi) = f WITH DIRICHLET BOUNDARY CONDITION ON UNIT SQUARE\n\r");
        serprint("number of intervals in each direction: ");
        serprintuint8(N);
        serprint("\n\r");

        ////////////////* INTERNAL RAM *////////////////
        serprint("\n\rINTERNAL RAM\n\r");

        // allocate phi
        float *phi = (float *)calloc((N + 2) * (N + 2), sizeof(float));
        if (phi == NULL)
            serprint("PHI MEMORY ALLOCATION FAILED\n\r");

        // solve poisson equation in internal RAM
        timer_reset();
        retval = solve(N, f_source, maxit, tol, phi);
        t = timer_getms();
        serprint("flag = ");
        serprintint(retval.flag);
        serprint("\n\riter = ");
        serprintint(retval.iter);
        serprint("\n\rresidual = ");
        serprintfloat(retval.residual, 0, 10);
        serprint("\n\relapsed time = ");
        serprintuint32(t);
        serprint(" ms\n\r");

        ////////////////* EXTERNAL RAM *////////////////
        // external SRAM starting address for phi
        uint16_t phi_addr = 0;

        // solve poisson equation on external RAM with external buffer
        serprint("\n\rEXTERNAL RAM\n\r");
        timer_reset();
        retval = solve_extram(N, f_source, maxit, tol, phi_addr);
        t = timer_getms();
        serprint("flag = ");
        serprintint(retval.flag);
        serprint("\n\riter = ");
        serprintint(retval.iter);
        serprint("\n\rresidual = ");
        serprintfloat(retval.residual, 0, 10);
        serprint("\n\relapsed time = ");
        serprintuint32(t);
        serprint(" ms\n\r");

        // solve poisson equation on external RAM with internal buffer
        serprint("\n\rEXTERNAL RAM INTERNAL BUFFER\n\r");
        timer_reset();
        retval = solve_extram_buffered(N, f_source, maxit, tol, phi_addr);
        t = timer_getms();
        serprint("flag = ");
        serprintint(retval.flag);
        serprint("\n\riter = ");
        serprintint(retval.iter);
        serprint("\n\rresidual = ");
        serprintfloat(retval.residual, 0, 10);
        serprint("\n\relapsed time = ");
        serprintuint32(t);
        serprint(" ms\n\r");

        // solve buffered poisson equation on external RAM with double internal buffer
        serprint("\n\rEXTERNAL RAM DOUBLE INTERNAL BUFFER\n\r");
        timer_reset();
        retval = solve_extram_doublebuffered(N, f_source, maxit, tol, phi_addr);
        t = timer_getms();
        serprint("flag = ");
        serprintint(retval.flag);
        serprint("\n\riter = ");
        serprintint(retval.iter);
        serprint("\n\rresidual = ");
        serprintfloat(retval.residual, 0, 10);
        serprint("\n\relapsed time = ");
        serprintuint32(t);
        serprint(" ms\n\r");

        // free
        free(phi);

        // wait for user to run test again
        serprint("\n\r\n\r\n\r");
        wait_key_remind("TEST FINISHED. PRESS ANY KEY TO RUN IT AGAIN.\n\r", 5000);
        serprint("\n\r");
    }
}
