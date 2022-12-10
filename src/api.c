#include "api.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "t_matrix.h"
#include "vector3.h"
#include "vector4.h"

vector3_t *vector3_dot_t_matrix(vector3_t *b, t_matrix_t *a, vector3_t *result)
{
    result->x = (((a->data[0]) * b->x) + ((a->data[4]) * b->y)
                 + ((a->data[8]) * b->z) + ((a->data[12])));
    result->y = (((a->data[1]) * b->x) + ((a->data[5]) * b->y)
                 + ((a->data[9]) * b->z) + ((a->data[13])));
    result->z = (((a->data[2]) * b->x) + ((a->data[6]) * b->y)
                 + ((a->data[10]) * b->z) + ((a->data[14])));
    float tmp = (((a->data[3]) * b->x) + ((a->data[7]) * b->y)
                 + ((a->data[11]) * b->z) + ((a->data[15])));
    if (tmp != 1)
    {
        result->x = result->x / tmp;
        result->y = result->y / tmp;
        result->z = result->z / tmp;
    }
    return result;
}

vector4_t *vector4_dot_t_matrix(vector4_t *v, t_matrix_t *M, vector4_t *result)
{
    result->x = v->x * M->data[0] + v->y * M->data[4] + v->z * M->data[8]
        + v->w * M->data[12];

    result->y = v->x * M->data[1] + v->y * M->data[5] + v->z * M->data[9]
        + v->w * M->data[13];

    result->z = v->x * M->data[2] + v->y * M->data[6] + v->z * M->data[10]
        + v->w * M->data[14];

    result->w = v->x * M->data[3] + v->y * M->data[7] + v->z * M->data[11]
        + v->w * M->data[15];

    return result;
}

float fastisqrt(float number)
{
    float x2;
    const float threehalfs = 1.5F;

    union
    {
        float f;
        uint32_t i;
    } y;

    x2 = number * 0.5F;
    y.f = number;
    y.i = 0x5f3759df - (y.i >> 1); // what the fuck?
    y.f = y.f * (threehalfs - (x2 * y.f * y.f)); // 1st iteration
    return y.f;
}
