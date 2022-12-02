#ifndef PROJECTION_H
#define PROJECTION_H

#include "vector3.h"

typedef struct
{
    vector3_t *ux;
    vector3_t *uy;
    vector3_t *uz;
    vector3_t *pos;
    float fov;
    int height;
    int width;
} camera_t;

#endif
