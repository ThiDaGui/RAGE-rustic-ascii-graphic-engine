#include "projection.h"

#include <err.h>
#include <math.h>

#include "api.h"
#include "parser.h"
#include "rasterizer.h"
#include "vector3.h"

int projection(obj_t *object, camera_t *camera, vector3_t *light, int *image)
{
    vector3_t *triangle[3];
    vector3_t projTriangle[3];
    face_t *face;
    float norm;
    /*
     * vectors used to calculate each tri normal
     */
    vector3_t view = VECTOR3_INIT;
    vector3_t AB = VECTOR3_INIT;
    vector3_t AC = VECTOR3_INIT;
    vector3_t N = VECTOR3_INIT;

    /*
     * vectors used to express the matrix world_to_view
     */
    vector3_t uz = VECTOR3_INIT;
    vector3_set(&uz, 0.0f, 0.0f, 1.0f);

    vector3_t camera_ux = VECTOR3_INIT;
    vector3_t camera_uy = VECTOR3_INIT;
    vector3_t camera_uz = *(camera->look_at);

    /*
     * floats used to express world_to_view
     */
    float pos_dot_ux;
    float pos_dot_uy;
    float pos_dot_uz;

    float color;

    float z_buffer[camera->height
                   * camera->width]; // need a more efficient way of doing this
                                     // (maybe memcpy ?)
    for (size_t i = 0; i < camera->width * camera->height; i++)
        z_buffer[i] = 1.0f;

    for (size_t i = 0; i < 3; i++)
        projTriangle[i] = VECTOR3_INIT;

    tmatrix_t *view_to_clip = malloc(sizeof(struct tmatrix_t));
    if (view_to_clip == NULL)
        err(EXIT_FAILURE,
            "Error while allocating memory for view_to_clip matrix");
    tmatrix_init(view_to_clip);

    tmatrix_t *world_to_view = malloc(sizeof(struct tmatrix_t));
    if (world_to_view == NULL)
        err(EXIT_FAILURE,
            "Error while allocating memory for world_to_view matrix");
    tmatrix_init(world_to_view);

    tmatrix_t *projMatrix = malloc(sizeof(struct tmatrix_t));
    if (projMatrix == NULL)
        err(EXIT_FAILURE,
            "Error while allocating memory for projMatrix matrix");
    tmatrix_init(projMatrix);

    float aspectRatio = (float)camera->height / (float)camera->width;
    float zNear = 0.1f;
    float zFar = 1000.0f;
    float fovRad = 1.0f / tanf(camera->fov * 0.5f / 180.0f * M_PI);

    view_to_clip->data[0] = aspectRatio * fovRad;
    view_to_clip->data[5] = fovRad;
    view_to_clip->data[10] = zFar / (zFar - zNear);
    view_to_clip->data[11] = 1.0f;
    view_to_clip->data[14] = (-zFar * zNear) / (zFar - zNear);

    /*
     * Calculate the other vectors of the camera base (right/ux and down/uy)
     * Algo not adapted to vertical camera : need some clamping
     */
    v_cross_v(&camera_uz, &uz, &camera_ux);
    norm = fastisqrt(camera_ux.x * camera_ux.x + camera_ux.y * camera_ux.y
                     + camera_ux.z * camera_ux.z);
    camera_ux.x = camera_ux.x * norm;
    camera_ux.y = camera_ux.y * norm;
    camera_ux.z = camera_ux.z * norm;

    /*
     * camera_look_at and camera_right are already normalized, no need to do it
     * to camera_down
     */
    v_cross_v(&camera_uz, &camera_ux, &camera_uy);

    /*
     * calculating the values for the last row
     */
    v_dot_v(camera->position, &camera_ux, &pos_dot_ux);
    v_dot_v(camera->position, &camera_uy, &pos_dot_uy);
    v_dot_v(camera->position, &camera_uz, &pos_dot_uz);

    world_to_view->data[0] = camera_ux.x;
    world_to_view->data[1] = camera_uy.x;
    world_to_view->data[2] = camera_uz.x;
    world_to_view->data[4] = camera_ux.y;
    world_to_view->data[5] = camera_uy.y;
    world_to_view->data[6] = camera_uz.y;
    world_to_view->data[8] = camera_ux.z;
    world_to_view->data[9] = camera_uy.z;
    world_to_view->data[10] = camera_uz.z;
    world_to_view->data[12] = -pos_dot_ux;
    world_to_view->data[13] = -pos_dot_uy;
    world_to_view->data[14] = -pos_dot_uz;
    world_to_view->data[15] = 1;

    tm_dot_tm(world_to_view, view_to_clip, projMatrix);

    for (size_t face_i = 0; face_i < object->face_count; face_i++)
    {
        face = object->faces[face_i];
        if (face->vertex_count != 3)
            err(EXIT_FAILURE, "The objet is not composed of triangles");

        for (size_t i = 0; i < 3; i++)
        {
            triangle[i] = object->vertices[face->v_indices[i] - 1];
        }
        /*
         * calculate the triangle normal for the backface culling
         * AB dot AC then normalize
         */

        // calculate the normal
        vector3_set(&AB, triangle[1]->x - triangle[0]->x,
                    triangle[1]->y - triangle[0]->y,
                    triangle[1]->z - triangle[0]->z);
        vector3_set(&AC, triangle[2]->x - triangle[0]->x,
                    triangle[2]->y - triangle[0]->y,
                    triangle[2]->z - triangle[0]->z);
        v_cross_v(&AB, &AC, &N);

        // normalize
        norm = fastisqrt(N.x * N.x + N.y * N.y + N.z * N.z);
        N.x = N.x * norm;
        N.y = N.y * norm;
        N.z = N.z * norm;

        // backface culling
        float culling;
        vector3_set(&view, triangle[0]->x - camera->position->x,
                    triangle[0]->y - camera->position->y,
                    triangle[0]->z - camera->position->z);
        v_dot_v(&view, &N, &culling);

        if (culling > 0)
            continue;

        // projection View -> Clipping space
        v_dot_m(triangle[0], projMatrix, projTriangle + 0);
        v_dot_m(triangle[1], projMatrix, projTriangle + 1);
        v_dot_m(triangle[2], projMatrix, projTriangle + 2);

        // Clipping space -> Screen space
        for (size_t i = 0; i < 3; i++)
        {
            projTriangle[i].x = 0.5f * (projTriangle[i].x + 1) * camera->width;
            projTriangle[i].y = 0.5f * (projTriangle[i].y + 1) * camera->height;
        }

        // Proto coloration
        v_dot_v(light, &N, &color);
        color = min(color, 255);
        color = max(1, color);

        // Raster stage
        build_triangle(projTriangle, projTriangle + 1, projTriangle + 2,
                       (int)color, image, z_buffer, camera->width,
                       camera->height);
    }

    free(view_to_clip);
    free(world_to_view);
    free(projMatrix);
    return 0;
}
