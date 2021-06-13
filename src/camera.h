#ifndef PROJECTION_H
#define PROJECTION_H

#include "vector3.h"

typedef struct {
    vector3_t *ux;
    vector3_t *uy;
    vector3_t *uz;
    vector3_t *pos;
    float fov;
    int height;
    int width;
} camera_t;

/*
 * project the object object on the buffer image according to the camera camera
 * vector3_t light is a vector representing a direction light
 * return 0 if no error and the buffer image is now the new image

int projection(obj_t*, camera_t*, vector3_t*, int*);
 */

#endif
