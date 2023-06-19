/**
 * @file matrix.h
 * @brief header file of the matrix module
 * this module is used to represent a matrix of height x width size and store float
 * it use the row-major order
 * @version 0.1
 * @date 2023-06-16
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
/**
 * @brief set the height and width of the matrix_t m and fill it with zero
 * 
 * @param m a pointer to a matrix_t
 * @param height 
 * @param width 
 * @return int 
 * @retval 0 if the matrix is initialized
 * @retval 1 if it failled
 */
int init_null_mat(matrix_t *m, size_t height, size_t width);
/**
 * @brief set the height and width of the matrix_t m and fill it with the data array
 * 
 * @param m a pointer to a matrix_t
 * @param height 
 * @param width
 * @param data a pointer to a float array of size height * width
 * @return int
 */
int init_mat(matrix_t *m, size_t height, size_t width, float *data);

/**
 * @brief store the result of the dot product between A and B in result. A.width must be equal to B.height
 * 
 * @details the result matrix must be initialized before calling this function.
 * 
 * 
 * @param A a pointer to a matrix_t
 * @param B a pointer to a matrix_t
 * @param result a pointer to a matrix_t where the result will be stored 
 * @return int
 * @retval 0 if the dot product is done
 * @retval 1 if it failled
 */
int m_dot_m(matrix_t *A, matrix_t *B, matrix_t *result);

#endif // RAGE_RUSTIC_ASCII_GRAPHIC_ENGINE_MATRIX_H
