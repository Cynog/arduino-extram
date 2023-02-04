#pragma once

#include <math.h>
#include <stdlib.h>

#include "lib_extram.hpp"
#include "lib_usart.hpp"

/**
 * @brief Contains a convergence flag, number of iterations, residual
 *
 */
struct output {
    int flag;
    int iter;
    float residual;
};

/**
 * @brief Source function for the 2d Poisson Equation
 *
 * @param x
 * @param y
 * @return float
 */
float f_source(float x, float y);

/**
 * @brief Solve 2d Poisson Equation laplace(phi) = f on the unit square with dirichlet boundary conditions on internal RAM
 *
 * @param N grid size without border
 * @param f_source source function
 * @param maxit maximum number of iterations
 * @param tol desired convergence tolerance
 * @param phi returns solution of size (N+2)*(N+2)
 * @return struct output convergence info
 */
struct output solve(int N, float (*f_source)(float, float), int maxit, float tol, float* phi);

/**
 * @brief Solve 2d Poisson Equation laplace(phi) = f on the unit square with dirichlet boundary conditions on external RAM
 *
 * @param N grid size without border
 * @param f_source source function
 * @param maxit maximum number of iterations
 * @param tol desired convergence tolerance
 * @param phi_addr EXTRAM address to return solution of size (N+2)*(N+2)
 * @return struct output convergence info
 */
struct output solve_extram(int N, float (*f_source)(float, float), int maxit, float tol, uint16_t phi_addr);

/**
 * @brief Solve 2d Poisson Equation laplace(phi) = f on the unit square with dirichlet boundary conditions on external RAM with high buffering to reduce number of EXTRAM accesses
 *
 * @param N grid size without border
 * @param f_source source function
 * @param maxit maximum number of iterations
 * @param tol desired convergence tolerance
 * @param phi_addr EXTRAM address to return solution of size (N+2)*(N+2)
 * @return struct output convergence info
 */
struct output solve_extram_buffered(int N, float (*f_source)(float, float), int maxit, float tol, uint16_t phi_addr);