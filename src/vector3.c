/**
 * @file vector3.c
 * @brief source file for vector3 type and functions
 * @version 0.1
 * @date 2023-06-19
 *
 *
 */
#include "vector3.h"

#include <stdlib.h>

const vector3_t VECTOR3_INIT = { 0 };

void vector3_set(vector3_t *vector3, float x, float y, float z)
{
    vector3->x = x;
    vector3->y = y;
    vector3->z = z;
}

vector3_t *vector3_init(void)
{
    vector3_t *v = calloc(1, sizeof(vector3_t));
    if (v == NULL)
        return NULL;

    return v;
}

void vector3_free(vector3_t *v)
{
    free(v);
}

void vector3_linear(vector3_t *vector3_a, vector3_t *vector3_b, float lambda,
                    vector3_t *result)
{
    result->x = vector3_a->x + lambda * vector3_b->x;
    result->y = vector3_a->y + lambda * vector3_b->y;
    result->z = vector3_a->z + lambda * vector3_b->z;
}

void vector3_LERP(vector3_t *vector3_a, vector3_t *vector3_b, float lambda,
                  vector3_t *result)
{
    result->x = (1 - lambda) * vector3_a->x + lambda * vector3_b->x;
    result->y = (1 - lambda) * vector3_a->y + lambda * vector3_b->y;
    result->z = (1 - lambda) * vector3_a->z + lambda * vector3_b->z;
}

void vector3_pc_BLERP(vector3_t *vector3_a, float z_a, float lambda_a,
                      vector3_t *vector3_b, float z_b, float lambda_b,
                      vector3_t *vector3_c, float z_c, float lambda_c,
                      vector3_t *result)
{
    float one_over_z =
        lambda_a * 1.0f / z_a + lambda_b * 1.0f / z_b + lambda_c * 1.0f / z_c;
    float z = 1.0f / one_over_z;

    result->x = z
        * (lambda_a * vector3_a->x / z_a + lambda_b * vector3_b->x / z_b
           + lambda_c * vector3_c->x / z_c);
    result->y = z
        * (lambda_a * vector3_a->y / z_a + lambda_b * vector3_b->y / z_b
           + lambda_c * vector3_c->y / z_c);
    result->z = z
        * (lambda_a * vector3_a->z / z_a + lambda_b * vector3_b->z / z_b
           + lambda_c * vector3_c->z / z_c);
}

int v_dot_v(vector3_t *a, vector3_t *b, float *result)
{
    *result = (a->x * b->x + a->y * b->y + a->z * b->z);
    return 0;
}

int v_cross_v(vector3_t *a, vector3_t *b, vector3_t *result)
{
    result->x = (a->y * b->z - a->z * b->y);
    result->y = (a->z * b->x - a->x * b->z);
    result->z = (a->x * b->y - a->y * b->x);
    return 0;
}
