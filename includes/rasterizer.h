/**
 * @file rasterizer.h
 * @brief header file of the rasterizer module
 * @details UNUSED FOR NOW
 * @version 0.1
 * @date 2023-06-17
 */
#ifndef RASTERIZER_H
#define RASTERIZER_H
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector3.h"

/**
 * @def max(a, b) ((a) >= (b) ? (a) : (b))
 * @brief return the maximum between two numbers
 */
#define max(a, b) ((a) >= (b) ? (a) : (b))
/**
 * @def min(a, b) ((a) <= (b) ? (a) : (b))
 * @brief return the minimum between two numbers
 */
#define min(a, b) ((a) <= (b) ? (a) : (b))

/**
 * @brief plot a line between two points
 * 
 * @param x0 
 * @param y0 
 * @param x1 
 * @param y1 
 * @param image 
 * @param width 
 */
void plotLineLow(int x0, int y0, int x1, int y1, int image[], size_t width);
void plotLineHigh(int x0, int y0, int x1, int y1, int image[], size_t width);
void plotLine(int x0, int y0, int x1, int y1, int image[], size_t width);
float edgeFunction(vector3_t *v1, vector3_t *v2, vector3_t *v3);
void build_triangle(vector3_t *v1, vector3_t *v2, vector3_t *v3, int color,
                    int *image, float *z_buffer, size_t width, size_t height);

#endif
