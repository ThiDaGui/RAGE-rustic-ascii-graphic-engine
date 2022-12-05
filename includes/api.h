#ifndef API_H
#define API_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"
#include "t_matrix.h"
#include "vector3.h"

int v_dot_m(vector3_t *, t_matrix_t *, vector3_t *);
float fastisqrt(float number);
#endif
