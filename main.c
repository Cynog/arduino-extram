#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// #include "poisson_arduino.h"
#include "usart.h"

// contains a convergence flag, number of iterations, residual
struct output {
    int flag;
    int iter;
    float residual;
};

// source function
float f_source(float x, float y) {
    // preparations
    float a = x - 0.5;
    float b = y - 0.5;
    float r = sqrt(a * a + b * b);

    // evaluate
    if ((0.3 < r && r < 0.4) || r < 0.04)
        return 10.0;
    else if (0.12 < r && r < 0.2)
        return -10.0;
    else
        return 0.0;
}

// float f_source(float x, float y) {
//     return 2.0 * (x + y);
// }

// serial jacobi solver for the 2d poisson equation laplace(phi) = f on the unit square with dirichlet boundary conditions
struct output solve_serial(int N, float (*f_source)(float, float), int maxit, float tol, float *phi) {
    // prepare return values
    struct output retval;
    retval.flag = 1;
    retval.iter = maxit;
    retval.residual = 20.0F;

    // allocate memory
    float *phi_old = (float *)calloc((N + 2) * (N + 2), sizeof(float));
    if (phi_old == NULL)
        serprint("PHI_OLD MEMORY ALLOCATION FAILED\n\r");
    float *f_vals = (float *)calloc((N + 2) * (N + 2), sizeof(float));
    if (f_vals == NULL)
        serprint("F_VALS MEMORY ALLOCATION FAILED\n\r");
    // float phi_old[(N + 2) * (N + 2)];
    serprinthex(phi_old);
    serprint("\n\r");
    // float f_vals[(N + 2) * (N + 2)];
    serprinthex(f_vals);
    serprint("\n\r");
    // for (int i = 0; i < (N + 2) * (N + 2); i++) {
    //     phi[i] = 0.0;
    //     phi_old[i] = 0.0;
    //     f_vals[i] = 0.0;
    // }
    //  evaluate source function
    for (int i = 1; i < N + 1; i++) {
        float x = (float)(i) / (float)(N + 1);
        for (int j = 1; j < N + 1; j++) {
            float y = (float)(j) / (float)(N + 1);
            f_vals[(N + 2) * i + j] = f_source(x, y);
        }
    }

    // scale evaluated source function because of discretization
    float square_Np2 = (float)((N + 2) * (N + 2));
    for (int i = 0; i < N + 2; i++) {
        for (int j = 0; j < N + 2; j++) {
            f_vals[(N + 2) * i + j] /= square_Np2;
        }
    }

    // serprintmat(f_vals, N + 2);
    // serprint("\n\r");

    ////////////////* JACOBI MAIN LOOP *////////////////
    for (int k = 1; k <= maxit; k++) {
        serprint("k = ");
        serprintint(k);
        serprint("\n\r");

        // save old phi
        // float *buf;
        // buf = phi_old;
        // phi_old = phi;
        // phi = buf;
        for (int i = 0; i < N + 2; i++) {
            for (int j = 0; j < N + 2; j++) {
                phi_old[(N + 2) * i + j] = phi[(N + 2) * i + j];
            }
        }

        // serprintmat(phi, N + 2);
        // serprint("\n\r");
        // serprintmat(phi_old, N + 2);
        // serprint("\n\r");

        // update phi
        for (int i = 1; i < N + 1; i++) {
            // serprint("i = ");
            // serprintint(i);
            // serprint("\n\r");
            for (int j = 1; j < N + 1; j++) {
                // serprint("j = ");
                // serprintint(j);
                // serprint("\n\r");
                phi[(N + 2) * i + j] = 0.25 * (phi_old[(N + 2) * (i + 1) + j] + phi_old[(N + 2) * (i - 1) + j] + phi_old[(N + 2) * i + (j + 1)] + phi_old[(N + 2) * i + (j - 1)] - f_vals[(N + 2) * i + j]);
                // serprintmat(phi, N + 2);
                // serprint("\n\r");
                // serprintmat(phi_old, N + 2);
                // serprint("\n\r");

                // serprintfloat(phi_old[(N + 2) * (i + 1) + j], 14, 4);
                // serprintchar(' ');
                // serprintfloat(phi_old[(N + 2) * (i - 1) + j], 14, 4);
                // serprintchar(' ');
                // serprintfloat(phi_old[(N + 2) * i + (j + 1)], 14, 4);
                // serprintchar(' ');
                // serprintfloat(phi_old[(N + 2) * i + (j - 1)], 14, 4);
                // serprintchar(' ');
                // serprintfloat(f_vals[(N + 2) * i + j], 14, 4);
                // serprintchar(' ');
                // serprintfloat(phi[(N + 2) * i + j], 14, 4);
                // serprint("\n\r");
            }
        }

        // serprintmat(phi, N + 2);
        // serprint("\n\r");
        // serprintmat(phi_old, N + 2);
        // serprint("\n\r");

        // calculate change
        float scp = 0.0;
        for (int i = 1; i < N + 1; i++) {
            for (int j = 1; j < N + 1; j++) {
                float diff = phi[(N + 2) * i + j] - phi_old[(N + 2) * i + j];
                scp += diff * diff;
            }
        }
        retval.residual = sqrt(scp);
        serprint("residual = ");
        serprintfloat(retval.residual, 12, 6);
        serprint("\n\r");

        // check for convergence
        if (retval.residual < tol) {
            // free
            free(phi_old);
            free(f_vals);

            // return info about convergence
            retval.flag = 0;
            retval.iter = k;
            return retval;
        }
    }

    // free
    free(phi_old);
    free(f_vals);

    // desired tolerance not reached
    return retval;
}

int main(void) {
    // initialize usart
    setup_usart();

    // test
    int N = 10;

    // allocate phi
    float *phi = (float *)calloc((N+2) * (N+2), sizeof(float));
    if (phi == NULL)
        serprint("PHI MEMORY ALLOCATION FAILED\n\r");
    // float phi[(N + 2) * (N + 2)];

    // solve poisson equation
    int maxit = 1000;
    float tol = 1e-2F;

    serprinthex(phi);
    serprint("\n\r");

    struct output retval = solve_serial(N, f_source, maxit, tol, phi);

    serprint("flag = ");
    serprintint(retval.flag);
    serprint("\n\riter = ");
    serprintint(retval.iter);
    serprint("\n\rresidual = ");
    serprintfloat(retval.residual, 0, 6);
    serprint("\n\r");

    // free
    free(phi);

    // endless loop
    while (1) {
    };
}
