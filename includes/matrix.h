/**
 * @file matrix.h
 * @brief header file of the matrix module
 * this module is used to represent a matrix of height x width size and store float
 * it use the row-major order
 * @version 0.1
 * @date 2023-06-16
 * 
 * 
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

#define MATRIX_INIT { 0, 0, (float *)NULL };
/**
 * @struct matrix_t
 * @brief a matrix is composed of a height, a width and a pointer to a float array
 * 
 * @var matrix_t::height
 * the height of the matrix
 * @var matrix_t::width
 * the width of the matrix
 * @var matrix_t::data
 * a pointer to a float array of size height * width
 * 
 * @note the matrix is stored in row-major order
 * @see https://en.wikipedia.org/wiki/Row-_and_column-major_order
 * 
 */
typedef struct matrix_t
{
    size_t height;
    size_t width;
    float *data;
} matrix_t;

int init_null_mat(matrix_t *, size_t, size_t);
int init_mat(matrix_t *, size_t, size_t, float *);
int m_dot_m(matrix_t *, matrix_t *, matrix_t *);

#endif // RAGE_RUSTIC_ASCII_GRAPHIC_ENGINE_MATRIX_H
