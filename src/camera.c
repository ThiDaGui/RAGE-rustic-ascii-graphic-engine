#include "camera.h"

#include "api.h"
#include "parser.h"
#include "rasterizer.h"
#include "t_matrix.h"
#include "vector3.h"

void camera_init(camera_t *camera, float fov, size_t width, size_t height)
{
    camera->position = vector3_init();
    camera->look_at = vector3_init();
    camera->fov = fov;
    camera->tan_fov = 1.0f / tanf(camera->fov / 360.0f * M_PI);
    camera->height = height;
    camera->width = width;
    camera->aspect_ratio = (float)camera->height / camera->width;
    camera->z_far = DEFAULT_Z_FAR;
    camera->z_near = DEFAULT_Z_NEAR;
    camera->world_to_view = calloc(1, sizeof(t_matrix_t));
    camera->view_to_clip = calloc(1, sizeof(t_matrix_t));
    camera->projection = calloc(1, sizeof(t_matrix_t));
}

void camera_free(camera_t *camera)
{
    vector3_free(camera->position);
    vector3_free(camera->look_at);
    free(camera->world_to_view);
    free(camera->view_to_clip);
    free(camera->projection);
}

void update_world_to_view_matrix(camera_t *camera)
{
    /*
     * floats used to express world_to_view
     */
    float pos_dot_ux;
    float pos_dot_uy;
    float pos_dot_uz;

    /*
     * vectors used to express the matrix world_to_view
     */
    vector3_t uz = { 0.0f, 0.0f, 1.0f };

    vector3_t camera_ux = VECTOR3_INIT;
    vector3_t camera_uy = VECTOR3_INIT;
    vector3_t camera_uz = *(camera->look_at);

    /*
     * Calculate the other vectors of the camera base (right/ux and down/uy)
     * Algo not adapted to vertical camera : need some clamping
     */
    v_cross_v(&camera_uz, &uz, &camera_ux);
    float norm = fastisqrt(camera_ux.x * camera_ux.x + camera_ux.y * camera_ux.y
                           + camera_ux.z * camera_ux.z);
    camera_ux.x = camera_ux.x * norm;
    camera_ux.y = camera_ux.y * norm;
    camera_ux.z = camera_ux.z * norm;

    /*
     * camera_look_at and camera_right are already normalized, no need to do
     * it to camera_down
     */
    v_cross_v(&camera_uz, &camera_ux, &camera_uy);

    /*
     * calculating the values for the last row
     */
    v_dot_v(camera->position, &camera_ux, &pos_dot_ux);
    v_dot_v(camera->position, &camera_uy, &pos_dot_uy);
    v_dot_v(camera->position, &camera_uz, &pos_dot_uz);

    float data[T_MATRIX_SIZE * T_MATRIX_SIZE] = {
        camera_ux.x, camera_uy.x, camera_uz.x, 0,
        camera_ux.y, camera_uy.y, camera_uz.y, 0,
        camera_ux.z, camera_uy.z, camera_uz.z, 0,
        -pos_dot_ux, -pos_dot_uy, -pos_dot_uz, 1
    };

    t_matrix_set(camera->world_to_view, data);
}

void update_view_to_clip_matrix(camera_t *camera)
{
    camera->view_to_clip->data[0] = camera->aspect_ratio * camera->tan_fov;
    camera->view_to_clip->data[5] = camera->tan_fov;
    camera->view_to_clip->data[10] =
        camera->z_far / (camera->z_far - camera->z_near);
    camera->view_to_clip->data[11] = 1.0f;
    camera->view_to_clip->data[14] =
        (-camera->z_far * camera->z_near) / (camera->z_far - camera->z_near);
}

void update_projection_matrix(camera_t *camera)
{
    update_world_to_view_matrix(camera);
    update_view_to_clip_matrix(camera);
    t_matrix_dot_t_matrix(camera->world_to_view, camera->view_to_clip,
                          camera->projection);
}
