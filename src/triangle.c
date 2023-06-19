/**
 * @file triangle.c
 * @brief Triangle type and functions
 * @version 0.1
 * @date 2023-06-19
 */
#include "triangle.h"

#include <stdlib.h>

#include "vector3.h"

const triangle_t TRIANGLE_INIT = { 0 };

triangle_t *triangle_init(void)
{
    triangle_t *triangle = calloc(1, sizeof(triangle_t));
    return triangle;
}

void triangle_free(triangle_t *triangle)
{
    free(triangle);
    triangle = NULL;
}
