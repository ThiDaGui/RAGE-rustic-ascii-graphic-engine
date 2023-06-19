/**
 * @file triangle.h
 * @brief Triangle type and functions
 * @version 0.1
 * @date 2023-06-19
 */
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vertex.h"
/**
 * @brief Triangle type definition. it is an array of 3 vertices
 */
typedef vertex_t triangle_t[3];

extern const triangle_t TRIANGLE_INIT;
/**
 * @brief Initialize a triangle
 * @see triangle_free
 * @return triangle_t* 
 */
triangle_t *triangle_init(void);
/**
 * @brief Free a triangle
 * @see triangle_init
 * @param triangle the triangle to free
 */
void triangle_free(triangle_t *triangle);

#endif // TRIANGLE_H
