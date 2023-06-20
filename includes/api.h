/**
 * @file api.h
 * @brief api header file
 * @version 0.1
 * @date 2023-06-16
 *
 * @copyright Copyright (c) 2023
 *
 * @note this api use the following conventions:
 * - matrices are stored in row-major order
 * - row vectors
 * - left-to-right multiplication
 */
#ifndef API_H
#define API_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"
#include "t_matrix.h"
#include "vector3.h"
#include "vector4.h"
/**
 * @brief vector3_t product with a transformation matrix, result is stored in
 * the vector3_t result
 *
 * @param v vector3_t
 * @param M t_matrix_t a transformation matrix
 * @param result vector3_t the result of the product
 * @return vector3_t*
 */
vector3_t *vector3_dot_t_matrix(vector3_t *v, t_matrix_t *M, vector3_t *result);

/**
 * @brief vector4_t product with a transformation matrix, result is stored in
 * the vector4_t result
 *
 * @param v vector4_t
 * @param M t_matrix_t a transformation matrix
 * @param result store the result of the product
 * @return vector4_t*
 */
vector4_t *vector4_dot_t_matrix(vector4_t *v, t_matrix_t *M, vector4_t *result);

/**
 * @brief fast inverse square roots. The legendary one
 * @see https://en.wikipedia.org/wiki/Fast_inverse_square_root
 *
 * @param number
 * @return float
 */
float fastisqrt(float number);

#endif // API_H
