#ifndef PROJECTION_H
#define PROJECTION_H
#include "obj.h"
#include "vector3.h"

typedef struct
{
    vector3_t *position;
    vector3_t *look_at;
    float fov;
    size_t height;
    size_t width;
} camera_t;

/**
 * project the object `object` on the buffer `image` according to the camera `camera`
 * @param object the `obj_t` to be projected
 * @param camera the `camera_t` used to project
 * @param light is a `vector3_t` representing a direction light
 * @return 0 if no error and the buffer image is now the new image
 */
int projection(obj_t *, camera_t *, vector3_t *, int *);

#endif
