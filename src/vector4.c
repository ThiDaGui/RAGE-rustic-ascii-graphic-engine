#include "vector4.h"

#include <err.h>
#include <stdlib.h>

#include "vector3.h"

/* =================== Wrapping =============================== */

const vector4_t VECTOR4_INIT = { 0, 0, 0, 0 };
const vector4_t VECTOR4_H_INIT = { 0, 0, 0, 1 };

vector4_t *vector4_init(void)
{
    vector4_t *vector4 = calloc(1, sizeof(vector4_t));
    return vector4;
}

vector4_t *vector4_h_init(void)
{
    vector4_t *vector4 = calloc(1, sizeof(vector4_t));
    if (vector4 == NULL)
        return NULL;
    vector4->w = 1;
    return vector4;
}

void vector4_free(vector4_t *vector4)
{
    free(vector4);
    vector4 = NULL;
}

void vector4_set(vector4_t *vector4, float x, float y, float z, float w)
{
    if (vector4 == NULL)
        warn("vector4_t \"vector4\" is NULL and cannot be set");
    else
    {
        vector4->x = x;
        vector4->y = y;
        vector4->z = z;
        vector4->w = w;
    }
}

vector4_t *vector4_from_vector3(vector3_t *vector3, vector4_t *result)
{
    vector4_set(result, vector3->x, vector3->y, vector3->z, 1);
    return result;
}

vector3_t *vector3_from_vector4(vector4_t *vector4, vector3_t *result)
{
    float one_over_w = 1 / vector4->w;
    vector3_set(result, vector4->x * one_over_w, vector4->y * one_over_w,
                vector4->z * one_over_w);
    return result;
}

vector4_t *vector4_normalize(vector4_t *vector4)
{
    float one_over_w = 1 / vector4->w;
    vector4->x *= one_over_w;
    vector4->y *= one_over_w;
    vector4->z *= one_over_w;
    vector4->w = 1;
    return vector4;
}

/* =================== Operations ============================= */

void vector4_linear(vector4_t *vector4_a, vector4_t *vector4_b, float lambda,
                    vector4_t *result)
{
    result->x = vector4_a->x + lambda * vector4_b->x;
    result->y = vector4_a->y + lambda * vector4_b->y;
    result->z = vector4_a->z + lambda * vector4_b->z;
    result->w = vector4_a->w + lambda * vector4_b->w;
}

void vector4_LERP(vector4_t *vector4_a, vector4_t *vector4_b, float lambda,
                  vector4_t *result)
{
    result->x = (1 - lambda) * vector4_a->x + lambda * vector4_b->x;
    result->y = (1 - lambda) * vector4_a->y + lambda * vector4_b->y;
    result->z = (1 - lambda) * vector4_a->z + lambda * vector4_b->z;
    result->w = (1 - lambda) * vector4_a->w + lambda * vector4_b->w;
}

void vector4_dot_vector4(vector4_t *vector4_a, vector4_t *vector4_b,
                        float *result)
{
    *result = (vector4_a->x * vector4_b->x + vector4_a->y * vector4_b->y
               + vector4_a->z * vector4_b->z + vector4_a->w * vector4_b->w);
}
