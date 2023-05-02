#ifndef VERTEX_H
#define VERTEX_H

#include "vector3.h"
#include "vector4.h"
/**
 * @struct vertex_t
 * 
 * @brief is composed of two `vector3_t` and is used to hold vertex informations
 * 
 * @param position the position of the vertex 
 * @param normale the normal direction at the vertex surface
 */
typedef struct
{
    vector3_t position;
    vector3_t normale;
} vertex_t;

/**
 * @struct h_vertex_t
 * 
 * @brief same as a `vertex_t` but for Homogeneous coordinates
 * 
 * @param position the position of the vertex 
 * @param normale the normal direction at the vertex surface
 */
typedef struct
{
    vector4_t position;
    vector3_t normale;
} h_vertex_t;

extern const vertex_t VERTEX_INIT;

extern const h_vertex_t H_VERTEX_INIT;

vertex_t *vertex_init(void);

h_vertex_t *h_vertex_init(void);
/**
 * @fn void vertex_free(vertex_t *vertex)
 * @brief free the vertex_t struct passed as argument
 * 
 * @param vertex the `vertex_t` to free
 */
void vertex_free(vertex_t *vertex);
/**
 * @fn void h_vertex_free(h_vertex_t *h_vertex)
 * 
 * @brief free the h_vertex_t struct passed as argument
 * 
 * @param h_vertex 
 */
void h_vertex_free(h_vertex_t *h_vertex);

/**
 * @fn void vertex_LERP(vertex_t *vertex_a, vertex_t *vertex_b, float lambda, vertex_t *result)
 * @brief linear interpolation for vertex_t
 * @param vertex_a 
 * @param vertex_b 
 * @param lambda 
 * @param result 
 */
void vertex_LERP(vertex_t *vertex_a, vertex_t *vertex_b, float lambda,
                 vertex_t *result);
/**
 * @fn void vertex_LERP(vertex_t *vertex_a, vertex_t *vertex_b, float lambda, vertex_t *result)
 * @brief linear interpolation for h_vertex_t
 * @param h_vertex_a 
 * @param h_vertex_b 
 * @param lambda 
 * @param result 
 */
void h_vertex_LERP(h_vertex_t *h_vertex_a, h_vertex_t *h_vertex_b, float lambda,
                   h_vertex_t *result);
/**
 * @fn void vertex_depth_correct_LERP(vertex_t *vertex_a, float depth_a, vertex_t *vertex_b, float depth_b, float lambda, vertex_t *result)
 * @brief depth correct linear interpolation for vertex_t
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
 * @fn void h_vertex_depth_correct_LERP(h_vertex_t *h_vertex_a, float depth_a, h_vertex_t *h_vertex_b, float depth_b, float lambda, h_vertex_t *result)
 * @brief depth correct linear interpolation for h_vertex_t
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
