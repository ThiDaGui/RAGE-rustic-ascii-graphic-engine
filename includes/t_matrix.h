/**
 * @file t_matrix.h
 * @brief header file of the t_matrix module
 * @details 4x4 matrix for 3D transformations and projections, use float and are
 * row-major
 * @version 0.1
 * @date 2023-06-19
 */
#ifndef T_MATRIX_H
#define T_MATRIX_H

#define T_MATRIX_SIZE 4
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

/**
 * @struct t_matrix_t
 * @brief t_matrix_t is a 4x4 matrix for 3D transformations and projections
 * @details use float and are row-major
 * @var t_matrix_t::data
 * The data of the matrix
 */
typedef struct t_matrix_t
{
    float data[T_MATRIX_SIZE * T_MATRIX_SIZE];
} t_matrix_t;

/**
 * @brief initialize the t_matrix_t t_matrix passed as parameter with 0
 * @param t_matrix the t_matrix_t to initialize
 * @retval 1 if the t_matrix_t is NULL
 * @retval 0 for success
 */
int t_matrix_init(t_matrix_t *t_matrix);

/**
 * @brief set the t_matrix_t t_matrix passed as parameter with the data passed
 * as parameter using memcpy
 * @param t_matrix the t_matrix_t to set
 * @param src the data to set the t_matrix_t with
 * @return the t_matrix_t t_matrix passed as parameter
 */
t_matrix_t *t_matrix_set(t_matrix_t *t_matrix,
                         float src[T_MATRIX_SIZE * T_MATRIX_SIZE]);

/**
 * @brief dot product between two t_matrix_t matrix_a and matrix_b, result is
 * stored in the t_matrix_t result
 * @param matrix_a the first t_matrix_t
 * @param matrix_b the second t_matrix_t
 * @param result the t_matrix_t to store the result
 * @return int 0 for success
 */
int t_matrix_dot_t_matrix(t_matrix_t *matrix_a, t_matrix_t *matrix_b,
                          t_matrix_t *result);

#endif
