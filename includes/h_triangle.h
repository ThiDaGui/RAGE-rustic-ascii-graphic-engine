/**
 * @file h_triangle.h
 * @brief header file of the h_triangle module
 * this module is used to represent a triangle in homogeneous coordinates
 * @see https://en.wikipedia.org/wiki/Homogeneous_coordinates
 * @version 0.1
 * @date 2023-06-16
 * 
 * 
 */
#ifndef H_TRIANGLE_H
#define H_TRIANGLE_H

#include "vertex.h"
/**
 * @brief a h_triangle is composed of 3 `h_vertex_t` 
 * 
 */
typedef h_vertex_t h_triangle_t[3];

/**
 * @brief a h_triangle_t struct initialized with 0
 * 
 */
extern const h_triangle_t H_TRIANGLE_INIT;

/**
 * @brief initialize a h_triangle_t struct
 * @return a pointer to the h_triangle_t struct created
 */
h_triangle_t *h_triangle_init(void);
/**
 * @brief free the h_triangle_t struct passed as argument
 * 
 * @param h_triangle the h_triangle_t to free
 */
void h_triangle_free(h_triangle_t *h_triangle);

#endif // H_TRIANGLE_H
