/**
 * @file h_triangle.c
 * @brief source file of the h_triangle module
 * @version 0.1
 * @date 2023-06-16
 *
 *
 */
#include "h_triangle.h"

#include <stdlib.h>

const h_triangle_t H_TRIANGLE_INIT = {
    { { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
};

h_triangle_t *h_triangle_init(void)
{
    h_triangle_t *h_triangle = calloc(1, sizeof(h_triangle_t));
    return h_triangle;
}

void h_triangle_free(h_triangle_t *h_triangle)
{
    free(h_triangle);
    h_triangle = NULL;
}
