#ifndef VERTEX_H
#define VERTEX_H

#include "vector3.h"
#include "vector4.h"

typedef struct
{
    vector3_t position;
    vector3_t normale;
} vertex_t;

typedef struct
{
    vector4_t position;
    vector3_t normale;
} h_vertex_t;

const extern vertex_t VERTEX_INIT;

const extern h_vertex_t H_VERTEX_INIT;

vertex_t *vertex_init(void);

h_vertex_t *h_vertex_init(void);

void vertex_free(vertex_t *vertex);

void h_vertex_free(h_vertex_t *h_vertex);

void vertex_LERP(vertex_t *vertex_a, vertex_t *vertex_b, float lambda,
                 vertex_t *result);

void h_vertex_LERP(h_vertex_t *h_vertex_a, h_vertex_t *h_vertex_b, float lambda,
                   h_vertex_t *result);

void vertex_depth_correct_LERP(vertex_t *vertex_a, float depth_a,
                               vertex_t *vertex_b, float depth_b, float lambda,
                               vertex_t *result);

void h_vertex_depth_correct_LERP(h_vertex_t *h_vertex_a, float depth_a,
                                 h_vertex_t *h_vertex_b, float depth_b,
                                 float lambda, h_vertex_t *result);
#endif // VERTEX_H
