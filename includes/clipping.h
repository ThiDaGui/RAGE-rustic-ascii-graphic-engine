#ifndef CLIPPING_H
#define CLIPPING_H

#include <stddef.h>

#include "h_triangle.h"
#include "vector4.h"

float vector4_against_plane(vector4_t *vector4, vector4_t *plane);

vector4_t *clip_vector4(vector4_t *vertex_a, vector4_t *vertex_b,
                        vector4_t *plane, vector4_t *result);

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
int clip_segment(vector4_t *vertex_a, vector4_t *vertex_b, vector4_t *plane);

size_t clip_triangle(h_triangle_t *h_triangle, vector4_t *plane,
                     h_triangle_t *result);

#endif // CLIPPING_H
