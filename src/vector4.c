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
