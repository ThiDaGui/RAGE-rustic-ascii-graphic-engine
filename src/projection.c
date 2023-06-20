/**
 * @file projection.c
 * @brief source file of the projection module
 * @details contain many function who are not exposed and used only here
 * @version 0.1
 * @date 2023-06-17
 */
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
#include "vertex.h"

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

void vertex_shader(t_matrix_t *proj_matrix, triangle_t triangle,
                   h_triangle_t proj_h_triangle)
{
    vector4_t h_triangle[3] = { VECTOR4_H_INIT, VECTOR4_H_INIT,
                                VECTOR4_H_INIT };

    vector4_from_vector3(&triangle[0].position, &h_triangle[0]);
    vector4_dot_t_matrix(&h_triangle[0], proj_matrix,
                         &proj_h_triangle[0].position);
    proj_h_triangle[0].normale = triangle[0].normale;

    vector4_from_vector3(&triangle[1].position, &h_triangle[1]);
    vector4_dot_t_matrix(&h_triangle[1], proj_matrix,
                         &proj_h_triangle[1].position);
    proj_h_triangle[1].normale = triangle[1].normale;

    vector4_from_vector3(&triangle[2].position, &h_triangle[2]);
    vector4_dot_t_matrix(&h_triangle[2], proj_matrix,
                         &proj_h_triangle[2].position);
    proj_h_triangle[2].normale = triangle[2].normale;
}

void screen_mapping_shader(h_triangle_t clipped_h_triangle, camera_t *camera,
                           triangle_t clipped_triangle)
{
    vector3_from_vector4(&clipped_h_triangle[0].position,
                         &clipped_triangle[0].position);
    clipped_triangle[0].normale = clipped_h_triangle[0].normale;
    vector3_from_vector4(&clipped_h_triangle[1].position,
                         &clipped_triangle[1].position);
    clipped_triangle[1].normale = clipped_h_triangle[1].normale;
    vector3_from_vector4(&clipped_h_triangle[2].position,
                         &clipped_triangle[2].position);
    clipped_triangle[2].normale = clipped_h_triangle[2].normale;

    // Homogenous Clip space -> Screen space
    for (size_t i = 0; i < 3; i++)
    {
        clipped_triangle[i].position.x =
            0.5f * (clipped_triangle[i].position.x + 1) * (float)camera->width;
        clipped_triangle[i].position.y =
            0.5f * (clipped_triangle[i].position.y + 1) * (float)camera->height;
    }
}

void pixel_shader(triangle_t clipped_triangle, const float ws[3],
                  const size_t pixel_position[2], vector3_t *light,
                  camera_t *camera, int *image, float *z_buffer)
{
    vector3_t p = { pixel_position[0] + 0.5f, pixel_position[1] + 0.5f,
                    camera->z_near };

    float area = edgeFunction(&clipped_triangle[0].position,
                              &clipped_triangle[1].position,
                              &clipped_triangle[2].position);
    float lambdas[3] = {
        edgeFunction(&clipped_triangle[1].position,
                     &clipped_triangle[2].position, &p),
        edgeFunction(&clipped_triangle[2].position,
                     &clipped_triangle[0].position, &p),
        edgeFunction(&clipped_triangle[0].position,
                     &clipped_triangle[1].position, &p),
    };

    if (((lambdas[0] == 0
          && (((clipped_triangle[2].position.y - clipped_triangle[1].position.y)
                   == 0
               && (clipped_triangle[2].position.x
                   - clipped_triangle[1].position.x)
                   < 0)
              || (clipped_triangle[2].position.y
                  - clipped_triangle[1].position.y)
                  > 0))
         || lambdas[0] > 0)
        && ((lambdas[1] == 0
             && (((clipped_triangle[0].position.y
                   - clipped_triangle[2].position.y)
                      == 0
                  && (clipped_triangle[0].position.x
                      - clipped_triangle[2].position.x)
                      < 0)
                 || (clipped_triangle[0].position.y
                     - clipped_triangle[2].position.y)
                     > 0))
            || lambdas[1] > 0)
        && ((lambdas[2] == 0
             && (((clipped_triangle[1].position.y
                   - clipped_triangle[0].position.y)
                      == 0
                  && (clipped_triangle[1].position.x
                      - clipped_triangle[0].position.x)
                      < 0)
                 || (clipped_triangle[1].position.y
                     - clipped_triangle[0].position.y)
                     > 0))
            || lambdas[2] > 0))
    {
        lambdas[0] /= area;
        lambdas[1] /= area;
        lambdas[2] /= area;
        float z = (lambdas[0] * (clipped_triangle[0].position.z))
            + (lambdas[1] * (clipped_triangle[1].position.z))
            + (lambdas[2] * (clipped_triangle[2].position.z));

        vector3_t normal = VECTOR3_INIT;

        vector3_pc_BLERP(&clipped_triangle[0].normale, ws[0], lambdas[0],
                         &clipped_triangle[1].normale, ws[1], lambdas[1],
                         &clipped_triangle[2].normale, ws[2], lambdas[2],
                         &normal);

        float f_color;
        v_dot_v(light, &normal, &f_color);
        f_color = min(f_color, 255);
        f_color = max(1, f_color);
        int color = f_color;

        if (z < z_buffer[pixel_position[1] * camera->width + pixel_position[0]])
        {
            z_buffer[pixel_position[1] * camera->width + pixel_position[0]] = z;
            image[pixel_position[1] * camera->width + pixel_position[0]] =
                color;
        }
    }
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
    triangle_t triangle = {
        VERTEX_INIT,
        VERTEX_INIT,
        VERTEX_INIT,
    };

    h_triangle_t proj_h_triangle = {
        H_VERTEX_INIT,
        H_VERTEX_INIT,
        H_VERTEX_INIT,
    };
    h_triangle_t clipped_h_triangles[2] = {
        { H_VERTEX_INIT, H_VERTEX_INIT, H_VERTEX_INIT },
        { H_VERTEX_INIT, H_VERTEX_INIT, H_VERTEX_INIT },
    };

    triangle_t clipped_triangle = {
        VERTEX_INIT,
        VERTEX_INIT,
        VERTEX_INIT,
    };

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
            triangle[i].position = *(object->vertices[face->v_indices[i] - 1]);
        }

        /*
         * calculate the triangle normal for the backface culling
         * v_side_1 dot v_side_2 then normalize
         */

        // calculate the normal
        vector3_set(&v_side_1, triangle[1].position.x - triangle[0].position.x,
                    triangle[1].position.y - triangle[0].position.y,
                    triangle[1].position.z - triangle[0].position.z);
        vector3_set(&v_side_2, triangle[2].position.x - triangle[0].position.x,
                    triangle[2].position.y - triangle[0].position.y,
                    triangle[2].position.z - triangle[0].position.z);
        v_cross_v(&v_side_1, &v_side_2, &v_normal);

        // normalize
        float norm = fastisqrt(v_normal.x * v_normal.x + v_normal.y * v_normal.y
                               + v_normal.z * v_normal.z);
        v_normal.x *= norm;
        v_normal.y *= norm;
        v_normal.z *= norm;

        bool is_full_back = true;
        vector3_t origin = VECTOR3_INIT;
        vector3_t view_origin = VECTOR3_INIT;
        float dot_product;

        for (size_t iter = 0; iter < 3 && is_full_back; iter++)
        {
            origin = triangle[iter].position;
            vector3_linear(&origin, camera->position, -1, &view_origin);
            v_dot_v(&view_origin, camera->look_at, &dot_product);
            if (dot_product > 0)
                is_full_back = false;
        }

        if (is_full_back)
            continue;

        v_dot_v(&v_normal, &view_origin, &dot_product);
        if (dot_product > 0)
            continue;

        for (size_t i = 0; i < 3; i++)
        {
            size_t normale_i = face->vn_indices[i] - 1;
            if (normale_i < object->vn_count)
                triangle[i].normale = *(object->normals[normale_i]);
            else
                triangle[i].normale = v_normal;
        }

        /*
         * Projection and Clipping stages
         */

        // World space -> Homogenous Clip space
        vertex_shader(proj_matrix, triangle, proj_h_triangle);

        // Clipping stage
        vector4_t near_plane = { 0, 0, 1, 0 };

        size_t nb_triangle =
            clip_triangle(&proj_h_triangle, &near_plane, clipped_h_triangles);

        for (size_t iter = 0; iter < nb_triangle; iter++)
        {
            // Homogenise vector4 coordinates
            screen_mapping_shader(clipped_h_triangles[iter], camera,
                                  clipped_triangle);

            // Proto coloration
            float color;
            float ws[3] = {
                clipped_h_triangles[iter][0].position.w,
                clipped_h_triangles[iter][1].position.w,
                clipped_h_triangles[iter][2].position.w,
            };

            v_dot_v(light, &v_normal, &color);
            color = min(color, 255);
            color = max(1, color);

            /*
             * Raster stage
             */

            int x_max = min(floorf(max(max(clipped_triangle[0].position.x,
                                           clipped_triangle[1].position.x),
                                       clipped_triangle[2].position.x)),
                            camera->width - 1);
            int y_max = min(floorf(max(max(clipped_triangle[0].position.y,
                                           clipped_triangle[1].position.y),
                                       clipped_triangle[2].position.y)),
                            camera->height - 1);
            int x_min = max(floorf(min(min(clipped_triangle[0].position.x,
                                           clipped_triangle[1].position.x),
                                       clipped_triangle[2].position.x)),
                            0);
            int y_min = max(floorf(min(min(clipped_triangle[0].position.y,
                                           clipped_triangle[1].position.y),
                                       clipped_triangle[2].position.y)),
                            0);

            size_t p[2];
            for (int y = y_min; y <= y_max; y++)
            {
                for (int x = x_min; x <= x_max; x++)
                {
                    p[0] = x;
                    p[1] = y;

                    pixel_shader(clipped_triangle, ws, p, light, camera, image,
                                 z_buffer);
                }
            }
        }
    }

    free(z_buffer);
    return 0;
}
