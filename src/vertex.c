#include "vertex.h"

#include <stdlib.h>

#include "vector3.h"

const vertex_t VERTEX_INIT = { 0 };

const h_vertex_t H_VERTEX_INIT = { 0 };

vertex_t *vertex_init(void)
{
    vertex_t *vertex = calloc(1, sizeof(vertex_t));
    return vertex;
}

h_vertex_t *h_vertex_init(void)
{
    h_vertex_t *h_vertex = calloc(1, sizeof(h_vertex_t));
    return h_vertex;
}

void vertex_free(vertex_t *vertex)
{
    free(vertex);
    vertex = NULL;
}

void h_vertex_free(h_vertex_t *h_vertex)
{
    free(h_vertex);
    h_vertex = NULL;
}

void h_vertex_LERP(h_vertex_t *h_vertex_a, h_vertex_t *h_vertex_b, float lambda,
                   h_vertex_t *result)
{
    vector4_LERP(&h_vertex_a->position, &h_vertex_b->position, lambda,
                 &result->position);
    vector3_LERP(&h_vertex_a->normale, &h_vertex_b->normale, lambda,
                 &result->normale);
}
