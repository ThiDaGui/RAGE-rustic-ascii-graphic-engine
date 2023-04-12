#ifndef CAMERA_H
#define CAMERA_H

#include <stddef.h>

#include "t_matrix.h"
#include "vector3.h"

#define DEFAULT_Z_NEAR 0.1f
#define DEFAULT_Z_FAR 100.0f

typedef struct
{
    vector3_t *position;
    vector3_t *look_at;
    float fov;
    float tan_fov;
    size_t height;
    size_t width;
    float aspect_ratio;
    float z_near;
    float z_far;
    t_matrix_t *world_to_view;
    t_matrix_t *view_to_clip;
    t_matrix_t *projection;
} camera_t;

void camera_init(camera_t *camera, float fov, size_t width, size_t height);

void camera_free(camera_t *camera);

void update_world_to_view_matrix(camera_t *camera);

void update_view_to_clip_matrix(camera_t *camera);

void update_projection_matrix(camera_t *camera);

#endif // CAMERA_H
