#ifndef H_TRIANGLE_H
#define H_TRIANGLE_H

#include "vector4.h"

typedef vector4_t h_triangle_t[3];

extern const h_triangle_t H_TRIANGLE_INIT;

h_triangle_t *h_triangle_init(void);

void h_triangle_free(h_triangle_t *h_triangle);

#endif // H_TRIANGLE_H
