#include "projection.h"

#include <err.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "api.h"
#include "camera.h"
#include "clipping.h"
#include "h_triangle.h"
#include "rasterizer.h"
#include "t_matrix.h"
#include "triangle.h"
#include "vector3.h"
#include "vector4.h"

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

int projection(obj_t *object, camera_t *camera, vector3_t *light, int *image)
{
    //**************************************************************************
    // Start initialisation
    //**************************************************************************

    /*============================= z_buffer =================================*/

    float *z_buffer = z_buffer_init(camera->height, camera->width);

    /*========================== object_to_world =============================*/

    /*
     * nothing here at the moment, the object is immobile at the center
     */

    /*============================ proj_matrix ===============================*/

    t_matrix_t *proj_matrix = camera->projection;

    /*=============================== other ==================================*/

    face_t *face;
    triangle_t triangle = { VECTOR3_INIT, VECTOR3_INIT, VECTOR3_INIT };
    vector4_t h_triangle[3] = { VECTOR4_H_INIT, VECTOR4_H_INIT,
                                VECTOR4_H_INIT };

    h_triangle_t proj_h_triangle = { VECTOR4_H_INIT, VECTOR4_H_INIT,
                                     VECTOR4_H_INIT };
    h_triangle_t clipped_h_triangles[2] = { 0 };
    triangle_t clipped_triangle = { 0 };

    /*
     * vectors used to calculate each triangle normal
     */
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
            errx(EXIT_FAILURE, "The objet is not composed of triangles\n");

        for (size_t i = 0; i < 3; i++)
        {
            triangle[i] = *(object->vertices[face->v_indices[i] - 1]);
        }

        /*
         * calculate the triangle normal for the backface culling
         * v_side_1 dot v_side_2 then normalize
         */

        // calculate the normal
        vector3_set(&v_side_1, triangle[1].x - triangle[0].x,
                    triangle[1].y - triangle[0].y,
                    triangle[1].z - triangle[0].z);
        vector3_set(&v_side_2, triangle[2].x - triangle[0].x,
                    triangle[2].y - triangle[0].y,
                    triangle[2].z - triangle[0].z);
        v_cross_v(&v_side_1, &v_side_2, &v_normal);

        // normalize
        float norm = fastisqrt(v_normal.x * v_normal.x + v_normal.y * v_normal.y
                               + v_normal.z * v_normal.z);
        v_normal.x *= norm;
        v_normal.y *= norm;
        v_normal.z *= norm;

        /*
         * Projection and Clipping stages
         */

        // World space -> Homogenous Clip space
        vector4_from_vector3(&triangle[0], &h_triangle[0]);
        vector4_dot_t_matrix(&h_triangle[0], proj_matrix, &proj_h_triangle[0]);

        vector4_from_vector3(&triangle[1], &h_triangle[1]);
        vector4_dot_t_matrix(&h_triangle[1], proj_matrix, &proj_h_triangle[1]);

        vector4_from_vector3(&triangle[2], &h_triangle[2]);
        vector4_dot_t_matrix(&h_triangle[2], proj_matrix, &proj_h_triangle[2]);

        // Clipping stage
        vector4_t near_plane = { 0, 0, 1, 0 };

        size_t nb_triangle =
            clip_triangle(&proj_h_triangle, &near_plane, clipped_h_triangles);

        for (size_t iter = 0; iter < nb_triangle; iter++)
        {
            // Homogenise vector4 coordinates
            vector3_from_vector4(&clipped_h_triangles[iter][0],
                                 &clipped_triangle[0]);
            vector3_from_vector4(&clipped_h_triangles[iter][1],
                                 &clipped_triangle[1]);
            vector3_from_vector4(&clipped_h_triangles[iter][2],
                                 &clipped_triangle[2]);

            // Homogenous Clip space -> Screen space
            for (size_t i = 0; i < 3; i++)
            {
                clipped_triangle[i].x =
                    0.5f * (clipped_triangle[i].x + 1) * (float)camera->width;
                clipped_triangle[i].y =
                    0.5f * (clipped_triangle[i].y + 1) * (float)camera->height;
            }

            // Proto coloration
            float color;
            v_dot_v(light, &v_normal, &color);
            color = min(color, 255);
            color = max(1, color);

            /*
             * Raster stage
             */

            build_triangle(clipped_triangle, clipped_triangle + 1,
                           clipped_triangle + 2, color, image, z_buffer,
                           camera->width, camera->height);
        }
    }

    free(z_buffer);
    return 0;
}
