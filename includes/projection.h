/**
 * @file projection.h
 * @brief header file of the projection module
 * @version 0.1
 * @date 2023-06-19
 */
#ifndef PROJECTION_H
#define PROJECTION_H

#include "camera.h"
#include "obj.h"
#include "vector3.h"

/**
 * project the object `object` on the buffer `image` according to the camera
 * `camera`
 * @param object the `obj_t` to be projected
 * @param camera the `camera_t` used to project
 * @param light is a `vector3_t` representing a direction light
 * @return 0 if no error and the buffer image is now the new image
 */
int projection(obj_t *, camera_t *, vector3_t *, int *);

#endif
