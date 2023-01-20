#ifndef CLIPPING_H
#define CLIPPING_H

#include <stdlib.h>

#include "h_triangle.h"
#include "triangle.h"
#include "vector4.h"

float clip_vector4(vector4_t *vector4, vector4_t *plane)
{
    float res;
    return vector4_dot_vector4(plane, vector4, &res);
}

int clip_segment(vector4_t *vertex_a, vector4_t *vertex_b, vector4_t *plane)
{
    float clipped_vector_a = clip_vector4(vertex_a, vector4_t * plane);
    return 1;
}

size_t clip_triangle(h_triangle_t *h_triangle, vector4_t *plane,
                     h_triangle_t *result)
{
    result = calloc(1, sizeof(triangle_t));

    vector4_t vertex_1, vertex_2;
    for (size_t iter = 0; iter < 2; iter++)
    {
        for (size_t jter = iter; jter < 3; jter++)
        {
            vertex_1 = h_triangle[iter];
            vertex_2 = h_triangle[jter];
            int clipped_result = clip_segment(&vertex_1, &vertex_2, plane);
            if (clipped_result < 0)
            {}
            else if (clipped_result > 0)
            {}
            else
            {}
        }
    }

    return 1;
}

#endif // CLIPPING_H
