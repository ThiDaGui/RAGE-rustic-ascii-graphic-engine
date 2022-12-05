#include "projection.h"

#include <err.h>
#include <math.h>

#include "api.h"
#include "rasterizer.h"
#include "vector3.h"

float *z_buffer_init(size_t height, size_t width)
{
    static float *z_buffer = NULL;
    if (z_buffer == NULL)
    {
        z_buffer = malloc(height * width * sizeof(float));
        for (size_t i = 0; i < width * height; i++)
        {
            z_buffer[i] = 1.0f;
        }
    }

    float *dest = malloc(height * width * sizeof(float));
    return memcpy(dest, z_buffer, height * width * sizeof(float));
}

tmatrix_t *world_to_view_init(camera_t *camera)
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
    vector3_t uz = VECTOR3_INIT;
    vector3_set(&uz, 0.0f, 0.0f, 1.0f);

    vector3_t camera_ux = VECTOR3_INIT;
    vector3_t camera_uy = VECTOR3_INIT;
    vector3_t camera_uz = *(camera->look_at);

    tmatrix_t *world_to_view = malloc(sizeof(struct tmatrix_t));
    if (world_to_view == NULL)
        err(EXIT_FAILURE,
            "Error while allocating memory for world_to_view matrix");
    tmatrix_init(world_to_view);

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

    return world_to_view;
}

tmatrix_t *view_to_clip_init(camera_t *camera)
{
    tmatrix_t *view_to_clip = malloc(sizeof(struct tmatrix_t));
    if (view_to_clip == NULL)
        err(EXIT_FAILURE,
            "Error while allocating memory for view_to_clip matrix");
    tmatrix_init(view_to_clip);

    float aspectRatio = (float)camera->height / (float)camera->width;
    float zNear = 0.1f;
    float zFar = 1000.0f;
    float fovRad = 1.0f / tanf(camera->fov * 0.5f / 180.0f * M_PI);

    view_to_clip->data[0] = aspectRatio * fovRad;
    view_to_clip->data[5] = fovRad;
    view_to_clip->data[10] = zFar / (zFar - zNear);
    view_to_clip->data[11] = 1.0f;
    view_to_clip->data[14] = (-zFar * zNear) / (zFar - zNear);

    return view_to_clip;
}

int projection(obj_t *object, camera_t *camera, vector3_t *light, int *image)
{
    //**************************************************************************
    // Start initialisation
    //**************************************************************************

    /*============================= z_buffer =================================*/

    float *z_buffer = z_buffer_init(camera->height, camera->width);

    /*========================== object_to_world =============================*/
    /*=========================== world_to_view ==============================*/

    tmatrix_t *world_to_view = world_to_view_init(camera);

    /*=========================== view_to_clip ===============================*/

    tmatrix_t *view_to_clip = view_to_clip_init(camera);

    /*============================ proj_matrix ===============================*/

    tmatrix_t *proj_matrix = malloc(sizeof(struct tmatrix_t));
    if (proj_matrix == NULL)
        err(EXIT_FAILURE,
            "Error while allocating memory for proj_matrix matrix");
    tmatrix_init(proj_matrix);

    tm_dot_tm(world_to_view, view_to_clip, proj_matrix);

    /*=============================== other ==================================*/

    face_t *face;
    vector3_t *triangle[3];
    vector3_t proj_triangle[3] = { VECTOR3_INIT, VECTOR3_INIT, VECTOR3_INIT };

    /*
     * vectors used to calculate each tri normal
     */
    vector3_t view = VECTOR3_INIT;
    vector3_t v_side_1 = VECTOR3_INIT;
    vector3_t v_side_2 = VECTOR3_INIT;
    vector3_t v_normal = VECTOR3_INIT;

    //**************************************************************************
    // End initialisation
    //**************************************************************************

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
         * v_side_1 dot v_side_2 then normalize
         */

        // calculate the normal
        vector3_set(&v_side_1, triangle[1]->x - triangle[0]->x,
                    triangle[1]->y - triangle[0]->y,
                    triangle[1]->z - triangle[0]->z);
        vector3_set(&v_side_2, triangle[2]->x - triangle[0]->x,
                    triangle[2]->y - triangle[0]->y,
                    triangle[2]->z - triangle[0]->z);
        v_cross_v(&v_side_1, &v_side_2, &v_normal);

        // normalize
        float norm = fastisqrt(v_normal.x * v_normal.x + v_normal.y * v_normal.y
                               + v_normal.z * v_normal.z);
        v_normal.x = v_normal.x * norm;
        v_normal.y = v_normal.y * norm;
        v_normal.z = v_normal.z * norm;

        // backface culling
        float culling;
        vector3_set(&view, triangle[0]->x - camera->position->x,
                    triangle[0]->y - camera->position->y,
                    triangle[0]->z - camera->position->z);
        v_dot_v(&view, &v_normal, &culling);

        if (culling > 0)
            continue;

        // projection View -> Clipping space
        v_dot_m(triangle[0], proj_matrix, proj_triangle + 0);
        v_dot_m(triangle[1], proj_matrix, proj_triangle + 1);
        v_dot_m(triangle[2], proj_matrix, proj_triangle + 2);

        // Clipping space -> Screen space
        for (size_t i = 0; i < 3; i++)
        {
            proj_triangle[i].x =
                0.5f * (proj_triangle[i].x + 1) * (float)camera->width;
            proj_triangle[i].y =
                0.5f * (proj_triangle[i].y + 1) * (float)camera->height;
        }

        // Proto coloration
        float color;
        v_dot_v(light, &v_normal, &color);
        color = min(color, 255);
        color = max(1, color);

        // Raster stage
        build_triangle(proj_triangle, proj_triangle + 1, proj_triangle + 2,
                       (int)color, image, z_buffer, camera->width,
                       camera->height);
    }

    free(view_to_clip);
    free(world_to_view);
    free(proj_matrix);
    free(z_buffer);
    return 0;
}
