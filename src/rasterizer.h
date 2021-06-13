#ifndef RASTERIZER_H
#define RASTERIZER_H
#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "vector3.h"
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

void plotLineLow(int x0,int y0,int x1,int y1, int image[], size_t width, size_t n);
void plotLineHigh(int x0,int y0,int x1,int y1, int image[], size_t width, size_t n);
void plotLine(int x0,int y0,int x1,int y1, int image[], size_t width, size_t n);
float edgeFunction(vector3_t *v1, vector3_t *v2, vector3_t *v3);
void build_triangle(vector3_t *v1, vector3_t *v2, vector3_t *v3, int color,
                    int *image, float *z_buffer, size_t width, size_t height);


#endif
