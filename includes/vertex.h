/**
 * @file vertex.h
 * @brief vertex_t and h_vertex_t definition and functions
 * @version 0.1
 * @date 2023-06-19
 *
 *
 */
#ifndef VERTEX_H
#define VERTEX_H

#include "vector3.h"
#include "vector4.h"
/**
 * @struct vertex_t
 * @brief a vertex_t is a point in 3D space with a normal direction
 * @var vertex_t::position
 * the position of the vertex
 * @var vertex_t::normale
 * the normal direction at the vertex surface
 */
typedef struct vertex_t
{
    vector3_t position;
    vector3_t normale;
} vertex_t;

/**
 * @struct h_vertex_t
 * @brief same as a `vertex_t` but for Homogeneous coordinates
 * @details here the position is a vector4_t because it is in Homogeneous
 * coordinates
 * @var h_vertex_t::position
 * the position of the vertex
 * @var h_vertex_t::normale
 * the normal direction at the vertex surface
 */
typedef struct h_vertex_t
{
    vector4_t position;
    vector3_t normale;
} h_vertex_t;

extern const vertex_t VERTEX_INIT;

extern const h_vertex_t H_VERTEX_INIT;
/**
 * @brief initialize a vertex_t struct
 * @see vertex_free
 * @return a pointer to the vertex_t struct
 */
vertex_t *vertex_init(void);
/**
 * @brief initialize a h_vertex_t struct
 * @see h_vertex_free
 * @return a pointer to the h_vertex_t struct
 */
h_vertex_t *h_vertex_init(void);
/**
 * @brief free the vertex_t struct passed as argument
 * @see vertex_init
 * @param vertex the `vertex_t` to free
 */
void vertex_free(vertex_t *vertex);
/**
 * @brief free the h_vertex_t struct passed as argument
 * @see h_vertex_init
 * @param h_vertex the `h_vertex_t` to free
 */
void h_vertex_free(h_vertex_t *h_vertex);

/**
 * @brief UNDECLARED FUNCTION. DO NOT USE
 * @details linear interpolation for vertex_t
 * @param vertex_a
 * @param vertex_b
 * @param lambda
 * @param result
 */
void vertex_LERP(vertex_t *vertex_a, vertex_t *vertex_b, float lambda,
                 vertex_t *result);
/**
 * @brief perform a linear interpolation for h_vertex_t
 * @details use the vector4_LERP on the position and then vector3_LERP on the
 * normal and store the result in result
 * @param h_vertex_a first h_vertex_t
 * @param h_vertex_b second h_vertex_t
 * @param lambda the lambda for the linear interpolation
 * @param result the result of the linear interpolation
 */
void h_vertex_LERP(h_vertex_t *h_vertex_a, h_vertex_t *h_vertex_b, float lambda,
                   h_vertex_t *result);
/**
 * @brief UNDECLARED FUNCTION. DO NOT USE
 * @details depth correct linear interpolation for vertex_t
 * @param vertex_a
 * @param depth_a
 * @param vertex_b
 * @param depth_b
 * @param lambda
 * @param result
 */
void vertex_depth_correct_LERP(vertex_t *vertex_a, float depth_a,
                               vertex_t *vertex_b, float depth_b, float lambda,
                               vertex_t *result);
/**
 * @brief UNDECLARED FUNCTION. DO NOT USE
 * @details depth correct linear interpolation for h_vertex_t
 * @param h_vertex_a
 * @param depth_a
 * @param h_vertex_b
 * @param depth_b
 * @param lambda
 * @param result
 */
void h_vertex_depth_correct_LERP(h_vertex_t *h_vertex_a, float depth_a,
                                 h_vertex_t *h_vertex_b, float depth_b,
                                 float lambda, h_vertex_t *result);
#endif // VERTEX_H
