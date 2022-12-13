#include "poisson_arduino.h"

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

// serial jacobi solver for the 2d poisson equation laplace(phi) = f on the unit square with dirichlet boundary conditions
struct output solve_serial(int N, float (*f_source)(float, float), int maxit, float tol, float *phi) {
    // prepare return values
    struct output retval;
    retval.flag = 1;
    retval.iter = maxit;
    retval.residual = INFINITY;

    // allocate memory
    float *phi_old = (float *)malloc((N + 1) * sizeof(float));
    if (phi_old == NULL)
        serprint("PHI_OLD MEMORY ALLOCATION FAILED\n\r");
    float *f_vals = (float *)malloc(N * N * sizeof(float));
    if (f_vals == NULL)
        serprint("F_VALS MEMORY ALLOCATION FAILED\n\r");

    //  evaluate source function
    for (int i = 1; i < N + 1; i++) {
        float x = (float)(i) / (float)(N + 1);
        for (int j = 1; j < N + 1; j++) {
            float y = (float)(j) / (float)(N + 1);
            f_vals[N * (i - 1) + (j - 1)] = f_source(x, y);
        }
    }

    // scale evaluated source function because of discretization
    float square_Np2 = (float)((N + 2) * (N + 2));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            f_vals[N * i + j] /= square_Np2;
        }
    }

    ////////////////* JACOBI MAIN LOOP *////////////////
    for (int k = 1; k <= maxit; k++) {
        // initialize phi_old
        for (int j = 1; j < N + 1; j++)
            phi_old[j] = phi[j];

        // update phi and calculate change
        float scp = 0.0;
        for (int i = 1; i < N + 1; i++) {
            phi_old[0] = phi[(N + 2) * i];
            for (int j = 1; j < N + 1; j++) {
                // update phi
                float phi_old_buf = phi[(N + 2) * i + j];
                phi[(N + 2) * i + j] = 0.25 * (phi[(N + 2) * (i + 1) + j] + phi_old[j] + phi[(N + 2) * i + (j + 1)] + phi_old[j - 1] - f_vals[N * (i - 1) + (j - 1)]);
                phi_old[j] = phi_old_buf;

                // calculate change
                float diff = phi[(N + 2) * i + j] - phi_old_buf;
                scp += diff * diff;
            }
        }
        retval.residual = sqrt(scp);

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