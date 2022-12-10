#ifndef API_H
#define API_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"
#include "t_matrix.h"
#include "vector3.h"
#include "vector4.h"

vector3_t *vector3_dot_t_matrix(vector3_t *v, t_matrix_t *M, vector3_t *result);

vector4_t *vector4_dot_t_matrix(vector4_t *v, t_matrix_t *M, vector4_t *result);

float fastisqrt(float number);

#endif // API_H
