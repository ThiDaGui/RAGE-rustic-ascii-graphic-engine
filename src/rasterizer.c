#include "rasterizer.h"

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include "vector3.h"

void plotLineLow(int x0, int y0, int x1, int y1, int image[], size_t width,
                 size_t n)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }
    int D = (2 * dy) - dx;
    int y = y0;

    for (int x = x0; x <= x1; x++)
    {
        image[x * ((int)width) + y] = 1;
        n += 1;
        if (D > 0)
        {
            y = y + yi;
            D = D + (2 * (dy - dx));
        }
        else
            D = D + 2 * dy;
    }
}
void plotLineHigh(int x0, int y0, int x1, int y1, int image[], size_t width,
                  size_t n)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }
    int D = (2 * dx) - dy;
    int x = x0;
    for (int y = y0; y <= y1; y++)
    {
        image[x * ((int)width) + y] = 1;
        n += 1;
        if (D > 0)
        {
            x = x + xi;
            D = D + (2 * (dx - dy));
        }
        else
            D = D + 2 * dx;
    }
}
void plotLine(int x0, int y0, int x1, int y1, int image[], size_t width,
              size_t n)
{
    if (abs(y1 - y0) < abs(x1 - x0))
        if (x0 > x1)
            plotLineLow(x1, y1, x0, y0, image, width, n);
        else
            plotLineLow(x0, y0, x1, y1, image, width, n);
    else if (y0 > y1)
        plotLineHigh(x1, y1, x0, y0, image, width, n);
    else
        plotLineHigh(x0, y0, x1, y1, image, width, n);
}

float edgeFunction(vector3_t *v1, vector3_t *v2, vector3_t *v3)
{
    return ((v3->x - v1->x) * (v2->y - v1->y)
            - (v3->y - v1->y) * (v2->x - v1->x));
}

void build_triangle(vector3_t *v1, vector3_t *v2, vector3_t *v3, int color,
                    int *image, float *z_buffer, size_t width, size_t height)
{
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    // convert the vertices of the current triangle to raster space
    x_max = min(floorf(max(max(v1->x, v2->x), v3->x)), width - 1);
    y_max = min(floorf(max(max(v1->y, v2->y), v3->y)), height - 1);
    x_min = max(floorf(min(min(v1->x, v2->x), v3->x)), 0);
    y_min = max(floorf(min(min(v1->y, v2->y), v3->y)), 0);

    float area = edgeFunction(v1, v2, v3);

    vector3_t p = VECTOR3_INIT;
    for (int y = y_min; y <= y_max; y++)
    {
        for (int x = x_min; x <= x_max; x++)
        {
            p.x = x + 0.5;
            p.y = y + 0.5;
            p.z = 0;
            float w1 = edgeFunction(v2, v3, &p);
            float w2 = edgeFunction(v3, v1, &p);
            float w3 = edgeFunction(v1, v2, &p);
            if (((w1 == 0
                  && (((v3->y - v2->y) == 0 && (v3->x - v2->x) < 0)
                      || (v3->y - v2->y) > 0))
                 || w1 > 0)
                && ((w2 == 0
                     && (((v1->y - v3->y) == 0 && (v1->x - v3->x) < 0)
                         || (v1->y - v3->y) > 0))
                    || w2 > 0)
                && ((w3 == 0
                     && (((v2->y - v1->y) == 0 && (v2->x - v1->x) < 0)
                         || (v2->y - v1->y) > 0))
                    || w3 > 0))
            {
                {
                    w1 /= area;
                    w2 /= area;
                    w3 /= area;
                    float z = (w1 * (v1->z)) + (w2 * (v2->z)) + (w3 * (v3->z));
                    // float z = oneOverZ;

                    // printf("%f \n",oneOverZ);
                    // printf("%f \n",z);
                    if (z < z_buffer[(size_t)y * width + (size_t)x])
                    {
                        // printf("%lu,%lu \n",x,y);
                        z_buffer[(size_t)y * width + (size_t)x] = z;
                        image[(size_t)y * width + (size_t)x] = color;
                    }
                }
            }
        }
    }
}
