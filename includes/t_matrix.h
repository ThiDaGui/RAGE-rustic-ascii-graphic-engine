#ifndef T_MATRIX_H
#define T_MATRIX_H

#define T_MATRIX_SIZE 4
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

typedef struct t_matrix_t
{
    float data[T_MATRIX_SIZE * T_MATRIX_SIZE];
} t_matrix_t;

int t_matrix_init(t_matrix_t *t_matrix);

t_matrix_t *t_matrix_set(t_matrix_t *t_matrix, float src[T_MATRIX_SIZE * T_MATRIX_SIZE]);

int t_matrix_dot_t_matrix(t_matrix_t *matrix_a, t_matrix_t *matrix_b, t_matrix_t *result);

#endif
