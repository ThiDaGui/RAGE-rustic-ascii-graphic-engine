#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector3.h"

typedef vector3_t triangle_t[3];

extern const triangle_t TRIANGLE_INIT;

triangle_t *triangle_init(void);

void triangle_free(triangle_t *triangle);

#endif // TRIANGLE_H
