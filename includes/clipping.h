/**
 * @file clipping.h
 * @brief clipping header file
 * does the clipping of the triangles against the near and far clipping planes
 * @version 0.1
 * @date 2023-06-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CLIPPING_H
#define CLIPPING_H

#include <stddef.h>

#include "h_triangle.h"
#include "vector4.h"
#include "vertex.h"

/**
 * @brief check if the vector4 is in front or behind the plane
 *
 * @param vector4 the vector4 to check
 * @param plane the plane to check against
 * @return float signed distance between the vector4 and the plane
 */
float vector4_against_plane(vector4_t *vector4, vector4_t *plane);

/**
 * @brief calculate the intersection between a segment and a plane and store it
 * in result
 *
 * @param vertex_a the first vertex of the segment
 * @param vertex_b the second vertex of the segment
 * @param plane the plane against which the segment is clipped
 * @param result the result of the intersection
 * @return h_vertex_t*
 */
h_vertex_t *clip_vector4(h_vertex_t *vertex_a, h_vertex_t *vertex_b,
                         vector4_t *plane, h_vertex_t *result);

/**
 * @brief clip a segment against a plain
 *
 * @param vertex_a  the first vertex of the segment
 * @param vertex_b  the secong vertex of the segment
 * @param plane  the plane against which the segment is clipped
 * @return
 *
 * 0 if the segment is in front of the plane
 * -1 if the segment is behind the plane
 * 1 if the segment has been clipped: if it is the case the clipped segment is
 * in place
 */
int clip_segment(h_vertex_t *vertex_a, h_vertex_t *vertex_b, vector4_t *plane);

/**
 * @brief clip a triangle against a plane
 *
 * @param h_triangle the triangle to clip
 * @param plane the plane against which the triangle is to be clipped
 * @param result the result of the clipping
 * @return size_t
 */
size_t clip_triangle(h_triangle_t *h_triangle, vector4_t *plane,
                     h_triangle_t *result);

#endif // CLIPPING_H
