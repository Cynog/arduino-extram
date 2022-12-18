#include "poisson.hpp"

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

// jacobi solver for the 2d poisson equation laplace(phi) = f on the unit square with dirichlet boundary conditions using internal RAM
struct output solve(int N, float (*f_source)(float, float), int maxit, float tol, float *phi) {
    // prepare return values
    struct output retval;
    retval.flag = 1;
    retval.iter = maxit;
    retval.residual = INFINITY;

    // allocate memory
    float *phi_old = (float *)malloc((N + 1) * sizeof(float));
    if (phi_old == NULL) {
        serprint("PHI_OLD MEMORY ALLOCATION FAILED\n\r");
        return retval;
    }
    float *f_vals = (float *)malloc(N * N * sizeof(float));
    if (f_vals == NULL) {
        serprint("F_VALS MEMORY ALLOCATION FAILED\n\r");
        return retval;
    }

    //  evaluate source function
    float square_Np2 = (float)((N + 2) * (N + 2));  // scaling factor because of the discretization
    for (int i = 1; i < N + 1; i++) {
        float x = (float)(i) / (float)(N + 1);
        for (int j = 1; j < N + 1; j++) {
            float y = (float)(j) / (float)(N + 1);
            f_vals[N * (i - 1) + (j - 1)] = f_source(x, y) / square_Np2;
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

// jacobi solver for the 2d poisson equation laplace(phi) = f on the unit square with dirichlet boundary conditions using external RAM
struct output solve_extram(int N, float (*f_source)(float, float), int maxit, float tol, uint16_t phi_addr) {
    // prepare return values
    struct output retval;
    retval.flag = 1;
    retval.iter = maxit;
    retval.residual = INFINITY;

    // check for valid N
    if ((phi_addr + (N + 2) * (N + 2) + N * N - 1) * 4 >= EXTRAM_SIZE) {
        serprint("NOT ENOUGH MEMORY ON EXTERNAL RAM\n\r");
        return retval;
    }

    // address for f_vals
    uint16_t f_vals_addr = phi_addr + ((N + 2) * (N + 2)) * 4;

    // allocate memory for phi_old
    float *phi_old = (float *)malloc((N + 1) * sizeof(float));
    if (phi_old == NULL) {
        serprint("PHI_OLD MEMORY ALLOCATION FAILED\n\r");
        return retval;
    }
    // initialize phi to 0
    for (int i = 0; i < N + 2; i++) {
        for (int j = 0; j < N + 2; j++) {
            extram_write_float(phi_addr + ((N + 2) * i + j) * 4, 0.0);
        }
    }

    //  evaluate source function
    float square_Np2 = (float)((N + 2) * (N + 2));  // scaling factor because of the discretization
    for (int i = 1; i < N + 1; i++) {
        float x = (float)(i) / (float)(N + 1);
        for (int j = 1; j < N + 1; j++) {
            float y = (float)(j) / (float)(N + 1);
            extram_write_float(f_vals_addr + (N * (i - 1) + (j - 1)) * 4, f_source(x, y) / square_Np2);
        }
    }

    ////////////////* JACOBI MAIN LOOP *////////////////
    for (int k = 1; k <= maxit; k++) {
        // initialize phi_old
        for (int j = 1; j < N + 1; j++)
            phi_old[j] = extram_read_float(phi_addr + j * 4);

        // update phi and calculate change
        float scp = 0.0;
        for (int i = 1; i < N + 1; i++) {
            phi_old[0] = extram_read_float(phi_addr + ((N + 2) * i) * 4);
            for (int j = 1; j < N + 1; j++) {
                // update phi
                float phi_old_buf = extram_read_float(phi_addr + ((N + 2) * i + j) * 4);
                float phi_new = 0.25 * (extram_read_float(phi_addr + ((N + 2) * (i + 1) + j) * 4) + phi_old[j] + extram_read_float(phi_addr + ((N + 2) * i + (j + 1)) * 4) + phi_old[j - 1] - extram_read_float(f_vals_addr + (N * (i - 1) + (j - 1)) * 4));
                extram_write_float(phi_addr + ((N + 2) * i + j) * 4, phi_new);
                phi_old[j] = phi_old_buf;

                // calculate change
                float diff = phi_new - phi_old_buf;
                scp += diff * diff;
            }
        }
        retval.residual = sqrt(scp);

        // check for convergence
        if (retval.residual < tol) {
            // return info about convergence
            retval.flag = 0;
            retval.iter = k;
            return retval;
        }
    }

    // desired tolerance not reached
    return retval;
}