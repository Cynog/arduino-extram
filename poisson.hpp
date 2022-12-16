#ifndef _POISSON_ARDUINO_H_
#define _POISSON_ARDUINO_H_

#include <math.h>
#include <stdlib.h>

#include "usart.hpp"

// contains a convergence flag, number of iterations, residual
struct output {
    int flag;
    int iter;
    float residual;
};

float f_source(float x, float y);

struct output solve_serial(int N, float (*f_source)(float, float), int maxit, float tol, float* phi);

#endif  // _POISSON_ARDUINO_H_