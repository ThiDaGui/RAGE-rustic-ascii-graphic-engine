#ifndef CLIPPING_H
#define CLIPPING_H

#include <stdlib.h>

#include "h_triangle.h"
#include "triangle.h"
#include "vector3.h"
#include "vector4.h"

float vector4_against_plane(vector4_t *vector4, vector4_t *plane)
{
    float res;
    return vector4_dot_vector4(plane, vector4, &res);
}

vector4_t *clip_vector4(vector4_t *vertex_a, vector4_t *vertex_b,
                        vector4_t *plane, vector4_t *result)
{
    vector3_t vertex3_a;
    vector3_t vertex3_b;
    vector3_t plane_normale;

    vector3_from_vector4(vertex_a, &vertex3_a);
    vector3_from_vector4(vertex_b, &vertex3_b);
    vector3_from_vector4(plane, &plane_normale);

    vector4_t b_minus_a;
    vector4_linear(vertex_a, vertex_b, -1, &b_minus_a);

    vector3_t vector3_b_minus_a;

    vector3_linear(&vertex3_b, &vertex3_a, -1.0f, &vector3_b_minus_a);

    float vertex_a_dot_plane_normale;
    float b_minus_a_dot_plane_normale;

    v_dot_v(&vertex3_a, &plane_normale, &vertex_a_dot_plane_normale);
    v_dot_v(&vertex3_b, &plane_normale, &b_minus_a_dot_plane_normale);

    float t =
        (-plane->w - vertex_a_dot_plane_normale) / b_minus_a_dot_plane_normale;

    vector4_linear(vertex_a, vertex_b, t, result);
    return result;
}
/**
 * clip a segment against a plain
 *
 * @param vertex_a `vector4_t*` the first vertex of the segment
 * @param vertex_b `vector4_t*` the secong vertex of the segment
 * @param plane `vector4_t` the plane against which the segment is clipped
 * @return `int`
 *
 * 0 if the segment is in front of the plane
 * -1 if the segment is behind the plane
 * 1 if the segment has been clipped: if it is the case the clipped segment is
 * in place
 */
int clip_segment(vector4_t *vertex_a, vector4_t *vertex_b, vector4_t *plane)
{
    float clipped_vector_a = vector4_against_plane(vertex_a, plane);
    float clipped_vector_b = vector4_against_plane(vertex_b, plane);
    if (clipped_vector_a > 0)
    {
        if (clipped_vector_b >= 0)
        {
            return 0;
        }
        else
        {
            clip_vector4(vertex_a, vertex_b, plane, vertex_a);
            return 1;
        }
    }

    else if (clipped_vector_a == 0)
    {
        if (clipped_vector_b >= 0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }

    else
    {
        if (clipped_vector_a > 0)
        {
            clip_vector4(vertex_b, vertex_a, plane, vertex_b);
            return 1;
        }
        else
        {
            return -1;
        }
    }
}

size_t clip_triangle(h_triangle_t *h_triangle, vector4_t *plane,
                     h_triangle_t *result)
{
    result = calloc(2, sizeof(h_triangle_t));

    // TODO: implement queue struct
    vector4_t *queue = calloc(4, sizeof(vector4_t));
    size_t nb_triangle = 0;
    size_t nb_vector = 0;

    vector4_t *vertex_1;
    vector4_t *vertex_2;
    for (size_t iter = 0; iter < 2; iter++)
    {
        vertex_1 = h_triangle[iter];
        vertex_2 = h_triangle[iter + 1];
        int clipped_result = clip_segment(vertex_1, vertex_2, plane);
        if (clipped_result == 0)
        {
            if (iter == nb_vector)
                queue[nb_vector++] = *vertex_1;
            queue[nb_vector++] = *vertex_2;
        }
        else if (clipped_result > 0)
        {}
        else
        {}
    }

    return size;
}

#endif // CLIPPING_H
