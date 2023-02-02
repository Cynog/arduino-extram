#pragma once

#include <math.h>
#include <stdlib.h>

#include "lib_extram.hpp"
#include "lib_usart.hpp"

// contains a convergence flag, number of iterations, residual
struct output {
    int flag;
    int iter;
    float residual;
};

float f_source(float x, float y);

struct output solve(int N, float (*f_source)(float, float), int maxit, float tol, float* phi);

struct output solve_extram(int N, float (*f_source)(float, float), int maxit, float tol, uint16_t phi_addr);
struct output solve_extram_buffered(int N, float (*f_source)(float, float), int maxit, float tol, uint16_t phi_addr);