/**
 * @file lib_poisson.hpp
 * @author Cynog (github.com/Cynog)
 * @brief Jacobi-solvers of the 2d Poisson Equation on internal and external RAM for comparison.
 *
 */

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
 * @brief Solve 2d Poisson Equation laplace(phi) = f on the unit square with dirichlet boundary conditions on external RAM.
 * Solver uses the (N+2)*(N+2) + N*N + N+1 addresses starting from phi_addr on external RAM.
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
 * @brief Solve 2d Poisson Equation laplace(phi) = f on the unit square with dirichlet boundary conditions on external RAM where the small buffer is stored on internal RAM.
 * Solver uses the (N+2)*(N+2) + N*N addresses starting from phi_addr on external RAM.
 * 
 * @param N grid size without border
 * @param f_source source function
 * @param maxit maximum number of iterations
 * @param tol desired convergence tolerance
 * @param phi_addr EXTRAM address to return solution of size (N+2)*(N+2)
 * @return struct output convergence info
 */
struct output solve_extram_buffered(int N, float (*f_source)(float, float), int maxit, float tol, uint16_t phi_addr);

/**
 * @brief Solve 2d Poisson Equation laplace(phi) = f on the unit square with dirichlet boundary conditions on external RAM where the small buffer is stored on internal RAM and yet another buffer is used to minimize external RAM accesses.
 * Solver uses the (N+2)*(N+2) + N*N addresses starting from phi_addr on external RAM.
 *
 * @param N grid size without border
 * @param f_source source function
 * @param maxit maximum number of iterations
 * @param tol desired convergence tolerance
 * @param phi_addr EXTRAM address to return solution of size (N+2)*(N+2)
 * @return struct output convergence info
 */
struct output solve_extram_doublebuffered(int N, float (*f_source)(float, float), int maxit, float tol, uint16_t phi_addr);