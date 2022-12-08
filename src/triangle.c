#include "triangle.h"

#include <stdlib.h>

#include "vector3.h"

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
