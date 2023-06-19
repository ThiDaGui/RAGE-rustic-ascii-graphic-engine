/**
 * @file camera.h
 * @brief camera header file. 
 * contains the camera struct and the functions to manipulate it.
 * @version 0.1
 * @date 2023-06-16
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <stddef.h>

#include "t_matrix.h"
#include "vector3.h"
/**
 * @brief The default near clipping plane of the camera
 * @def DEFAULT_Z_NEAR
 */
#define DEFAULT_Z_NEAR 0.1f

/**
 * @brief The default far clipping plane of the camera
 * @def DEFAULT_Z_FAR
 */
#define DEFAULT_Z_FAR 100.0f


/**
 * @struct camera_t
 * @brief camera_t is a struct that contains the data of a camera
 * @details Initialize the camera with the camera_init function and free it with the camera_free function
 * @var camera_t::position
 * The position of the camera
 * @var camera_t::look_at
 * The point the camera is looking at
 * @var camera_t::fov
 * The field of view of the camera
 * @var camera_t::tan_fov
 * The tangent of the field of view of the camera
 * @var camera_t::height
 * The height of the camera in pixels
 * @var camera_t::width
 * The width of the camera in pixels
 * @var camera_t::aspect_ratio
 * The aspect ratio of the camera
 * @var camera_t::z_near
 * The near clipping plane of the camera
 * @var camera_t::z_far
 * The far clipping plane of the camera
 * @var camera_t::world_to_view
 * The world to view matrix of the camera
 * @var camera_t::view_to_clip
 * The view to clip matrix of the camera
 * @var camera_t::projection
 * The projection matrix of the camera
 */
typedef struct camera_t
{
    vector3_t *position; /** The position of the camera */
    vector3_t *look_at; /** The point the camera is looking at */
    float fov; /** The field of view of the camera */
    float tan_fov; /** The tangent of the field of view of the camera */
    size_t height; /** The height of the camera in pixels */
    size_t width; /** The width of the camera in pixels */
    float aspect_ratio; /** The aspect ratio of the camera */
    float z_near; /**  The near clipping plane of the camera */
    float z_far; /** The far clipping plane of the camera */
    t_matrix_t *world_to_view; /** The world to view matrix of the camera */
    t_matrix_t *view_to_clip; /** The view to clip matrix of the camera */
    t_matrix_t *projection; /** The projection matrix of the camera */
} camera_t;

/**
 * @brief Initialize the camera
 * 
 * @param camera the pointer to the camera to initialize
 * @param fov field of view of the camera in degrees to set
 * @param width width of the camera in pixels
 * @param height height of the camera in pixels
 */
void camera_init(camera_t *camera, float fov, size_t width, size_t height);
/**
 * @brief Free the camera
 * 
 * @param camera the pointer to the camera to free
 */
void camera_free(camera_t *camera);
/**
 * @brief Update the world to view matrix of the camera
 * 
 * @param camera 
 */
void update_world_to_view_matrix(camera_t *camera);
/**
 * @brief Update the view to clip matrix of the camera
 * 
 * @param camera 
 */
void update_view_to_clip_matrix(camera_t *camera);
/**
 * @brief Update the projection matrix of the camera
 * 
 * @param camera  
 */
void update_projection_matrix(camera_t *camera);

#endif // CAMERA_H
