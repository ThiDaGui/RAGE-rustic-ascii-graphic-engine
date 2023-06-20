/**
 * @file clipping.c
 * @brief source file of the clipping module
 * @version 0.1
 * @date 2023-06-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "clipping.h"

#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "h_triangle.h"
#include "triangle.h"
#include "vector3.h"
#include "vector4.h"
#include "vertex.h"

float vector4_against_plane(vector4_t *vector4, vector4_t *plane)
{
    float res;
    vector4_dot_vector4(plane, vector4, &res);
    return res;
}

h_vertex_t *clip_vector4(h_vertex_t *vertex_a, h_vertex_t *vertex_b,
                         vector4_t *plane, h_vertex_t *result)
{
    vector3_t vertex3_a;
    vector3_t vertex3_b;
    vector3_t plane_normale;

    vector3_set(&vertex3_a, vertex_a->position.x, vertex_a->position.y,
                vertex_a->position.z);
    vector3_set(&vertex3_b, vertex_b->position.x, vertex_b->position.y,
                vertex_b->position.z);
    vector3_set(&plane_normale, plane->x, plane->y, plane->z);

    vector4_t b_minus_a;
    vector4_linear(&vertex_b->position, &vertex_a->position, -1.0f, &b_minus_a);

    vector3_t vector3_b_minus_a;
    vector3_linear(&vertex3_b, &vertex3_a, -1.0f, &vector3_b_minus_a);

    float vertex_a_dot_plane_normale;
    float b_minus_a_dot_plane_normale;

    v_dot_v(&vertex3_a, &plane_normale, &vertex_a_dot_plane_normale);
    v_dot_v(&vector3_b_minus_a, &plane_normale, &b_minus_a_dot_plane_normale);

    float t =
        (-plane->w - vertex_a_dot_plane_normale) / b_minus_a_dot_plane_normale;

    h_vertex_LERP(vertex_a, vertex_b, t, result);
    return result;
}

int clip_segment(h_vertex_t *vertex_a, h_vertex_t *vertex_b, vector4_t *plane)
{
    float clipped_vector_a = vector4_against_plane(&vertex_a->position, plane);
    float clipped_vector_b = vector4_against_plane(&vertex_b->position, plane);
    if (clipped_vector_a > 0)
    {
        if (clipped_vector_b >= 0)
        {
            return 0;
        }
        else
        {
            clip_vector4(vertex_b, vertex_a, plane, vertex_b);
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
        if (clipped_vector_b > 0)
        {
            clip_vector4(vertex_a, vertex_b, plane, vertex_a);
            return 1;
        }
        else
        {
            return -1;
        }
    }
}

void clip_triange_case_one(h_triangle_t *h_triangle, size_t *before_queue,
                           size_t *behind_queue, vector4_t *plane,
                           h_triangle_t *result)
{
    h_vertex_t buf[2] = { H_VERTEX_INIT, H_VERTEX_INIT };
    clip_vector4(&(*h_triangle)[behind_queue[0]],
                 &(*h_triangle)[before_queue[0]], plane, buf);
    clip_vector4(&(*h_triangle)[behind_queue[1]],
                 &(*h_triangle)[before_queue[0]], plane, buf + 1);

    switch (before_queue[0])
    {
    case 0:
    case 2:
        (*result)[0] = (*h_triangle)[before_queue[0]];
        (*result)[1] = buf[0];
        (*result)[2] = buf[1];
        break;
    case 1:
        (*result)[0] = (*h_triangle)[before_queue[0]];
        (*result)[1] = buf[1];
        (*result)[2] = buf[0];
        break;
    default:
        errx(EXIT_FAILURE,
             "Something when wrong during clipping: vertex index is %lu\n",
             before_queue[0]);
    }
}

void clip_triange_case_two(h_triangle_t *h_triangle, size_t *before_queue,
                           size_t *behind_queue, vector4_t *plane,
                           h_triangle_t *result)
{
    h_vertex_t pivot = (*h_triangle)[behind_queue[0]];

    h_vertex_t buf[2] = { H_VERTEX_INIT, H_VERTEX_INIT };

    clip_vector4(&(*h_triangle)[before_queue[0]], &pivot, plane, buf);
    clip_vector4(&(*h_triangle)[before_queue[1]], &pivot, plane, buf + 1);

    switch (behind_queue[0])
    {
    case 0:
    case 2:
        result[0][0] = (*h_triangle)[before_queue[0]];
        result[0][1] = (*h_triangle)[before_queue[1]];
        result[0][2] = buf[1];

        result[1][0] = (*h_triangle)[before_queue[0]];
        result[1][1] = buf[1];
        result[1][2] = buf[0];
        break;
    case 1:
        result[0][0] = (*h_triangle)[before_queue[1]];
        result[0][1] = (*h_triangle)[before_queue[0]];
        result[0][2] = buf[0];

        result[1][0] = (*h_triangle)[before_queue[1]];
        result[1][1] = buf[0];
        result[1][2] = buf[1];
        break;
    default:
        errx(EXIT_FAILURE,
             "Something when wrong during clipping: vertex index is %lu\n",
             before_queue[0]);
    }
}

size_t clip_triangle(h_triangle_t *h_triangle, vector4_t *plane,
                     h_triangle_t *result)
{
    size_t before_queue[3] = { 0 };
    size_t size_before = 0;
    size_t behind_queue[3] = { 0 };
    size_t size_behind = 0;

    size_t nb_triangle = 0;

    for (size_t iter = 0; iter < 3; iter++)
    {
        h_vertex_t current_vertex = (*h_triangle)[iter];
        float dist = vector4_against_plane(&current_vertex.position, plane);

        if (dist > 0)
            before_queue[size_before++] = iter;
        else
            behind_queue[size_behind++] = iter;
    }

    switch (size_before)
    {
    case 0:
        nb_triangle = 0;
        break;
    case 1:
        nb_triangle = 1;
        clip_triange_case_one(h_triangle, before_queue, behind_queue, plane,
                              result);
        break;
    case 2:
        nb_triangle = 2;
        clip_triange_case_two(h_triangle, before_queue, behind_queue, plane,
                              result);
        break;
    case 3:
        nb_triangle = 1;
        memcpy(result, h_triangle, sizeof(h_triangle_t));
        break;
    default:
        errx(EXIT_FAILURE,
             "Something went wrong during clipping, got %lu vertex in front "
             "of the plane\n",
             size_before);
    }

    return nb_triangle;
}
