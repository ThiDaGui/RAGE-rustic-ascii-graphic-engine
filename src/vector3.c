#include "vector3.h"

#include <stdlib.h>

const vector3_t VECTOR3_INIT = { 0 };

void vector3_set(vector3_t *v, float x, float y, float z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

vector3_t *vector3_init(void)
{
    vector3_t *v = (vector3_t *)malloc(sizeof(vector3_t));
    if (v == NULL)
        return NULL;

    v->x = 0;
    v->y = 0;
    v->z = 0;

    return v;
}

void vector3_free(vector3_t *v)
{
    free(v);
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
