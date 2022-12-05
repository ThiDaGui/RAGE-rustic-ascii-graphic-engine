#include "t_matrix.h"

#include <stddef.h>
#include <string.h>

int t_matrix_init(t_matrix_t *t_matrix)
{
    if (t_matrix == NULL)
        return 1;
    memset(t_matrix->data, 0, T_MATRIX_SIZE * T_MATRIX_SIZE * sizeof(float));
    return 0;
}

t_matrix_t *t_matrix_set(t_matrix_t *t_matrix, float src[T_MATRIX_SIZE * T_MATRIX_SIZE])
{
    return memcpy(t_matrix->data, src, T_MATRIX_SIZE * T_MATRIX_SIZE * sizeof(float));
}

int t_matrix_dot_t_matrix(t_matrix_t *matrix_a, t_matrix_t *matrix_b, t_matrix_t *result)
{
    for (size_t i = 0; i < T_MATRIX_SIZE; i++)
    {
        for (size_t j = 0; j < T_MATRIX_SIZE; j++)
        {
            result->data[T_MATRIX_SIZE * i + j] = 0;
            for (size_t k = 0; k < T_MATRIX_SIZE; k++)
            {
                result->data[T_MATRIX_SIZE * i + j] +=
                    matrix_a->data[T_MATRIX_SIZE * i + k]
                    * matrix_b->data[T_MATRIX_SIZE * k + j];
            }
        }
    }
    return 0;
}
