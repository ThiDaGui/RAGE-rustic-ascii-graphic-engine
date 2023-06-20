/**
 * @file obj.h
 * @brief header file of the obj module.
 * @details this module is used to represent a 3D object and store its vertices,
 * texture coordinates, normals and faces.
 * @see https://en.wikipedia.org/wiki/Wavefront_.obj_file
 * @version 0.1
 * @date 2023-06-17
 */
#ifndef OBJ_H
#define OBJ_H

#include <stddef.h>

#include "vector3.h"

#define OBJ_TRUE (1)
#define OBJ_FALSE (0)

#define OBJ_SUCCESS (0)
#define OBJ_ERROR (-1)
#define OBJ_ERROR_NULL (-2)

/**
 * @struct face_t
 * @brief the implementation of a face from the wavefront .obj file format.
 * @details a face is a collection of vertices, texture coordinates and normals.
 * TLDR its a triangle.
 * @see https://en.wikipedia.org/wiki/Wavefront_.obj_file#Face_elements
 * @var face_t::v_indices
 * The indices of the geometric vertices.
 * @var face_t::vt_indices
 * The indices of the texture vertices.
 * @var face_t::vn_indices
 * The indices of the normal vertices.
 */
typedef struct face_t
{
    size_t *v_indices;
    size_t *vt_indices;
    size_t *vn_indices;

    size_t vertex_count;
} face_t;

/**
 * @struct obj_t
 * @brief struct used to represent a 3D object from the wavefront .obj file
 * format.
 * @details an object is a collection of vertices, texture coordinates, normals
 * and faces.
 * @see https://en.wikipedia.org/wiki/Wavefront_.obj_file#File_format
 * @var obj_t::vertices
 * The geometric vertices.
 * @var obj_t::texture_coords
 * The texture coordinates.
 * @var obj_t::normals
 * The normals.
 * @var obj_t::faces
 * The faces.
 * @var obj_t::v_count
 * The number of geometric vertices.
 * @var obj_t::vt_count
 * The number of texture coordinates.
 * @var obj_t::vn_count
 * The number of normals.
 * @var obj_t::face_count
 * The number of faces.
 */
typedef struct obj_t
{
    vector3_t **vertices;
    vector3_t **texture_coords;
    vector3_t **normals;
    face_t **faces;

    size_t v_count;
    size_t vt_count;
    size_t vn_count;
    size_t face_count;
} obj_t;

/**
 * Allocate and initializes a `face_t`.
 * @details the `face_t` is initialized with all its pointers set to NULL and
 * its vertex count set to 0.
 * @see face_free()
 * @see face_add_vertex()
 * @see obj_add_face()
 * @return The initialized `face_t`.
 * @retval NULL if the allocation failed
 */
face_t *face_init(void);

/**
 * Frees an initialized `face_t`.
 * @param face The `face_t` to free.
 */
void face_free(face_t *face);

/**
 * Add a vertex reference index to a face.
 * @param face The `face_t` to which to add the vertex references.
 * @param v The geometric vertex index.
 * @param vt The texture coordinates vertex index.
 * @param vn The normal vertex index.
 * @retval OBJ_SUCCESS if the operation was successful
 * @retval OBJ_ERROR if the face is NULL or if any operation failed
 */
int face_add_vertex(face_t *face, size_t v, size_t vt, size_t vn);

/**
 * Allocate and initializes a `obj_t`.
 * @details The `obj_t` is initialized with 0 vertices, 0 texture coordinates, 0
 * normals and 0 faces. all the pointers are initialized to NULL.
 * @see obj_free()
 * @see obj_add_vertex()
 * @see obj_add_texture_coordinate()
 * @see obj_add_normal()
 * @see obj_add_face()
 * @see obj_is_valid()
 * @retval NULL if the allocation failed
 * @return The initialized `obj_t`.
 *
 */
obj_t *obj_init(void);

/**
 * Frees an initialized `obj_t`.
 * @see obj_init()
 * @param obj The `obj_t` to free.
 */
void obj_free(obj_t *obj);

/**
 * Verify if an `obj_t` is valid.
 * @details An `obj_t` is invalid if any of its faces has a vertex index greater
 * than the number of vertices, texture coordinates or normals.
 * @param obj The `obj_t` to verify if is valid.
 * @retval OBJ_TRUE if the `obj_t` is valid
 * @retval OBJ_FALSE if the `obj_t` is not valid
 * @retval OBJ_ERROR_NULL if the `obj_t` is NULL
 *
 */
int obj_is_valid(obj_t *obj);

/**
 * Add a geometric vertex to an `obj_t`.
 * @param obj The `obj_t` to which to add the vertex.
 * @param v The geometric vertex to be added.
 * @see vector3_t
 * @retval OBJ_SUCCESS if the operation was successful
 * @retval OBJ_ERROR if the `obj_t` or the `vector3_t` are NULL
 * @retval OBJ_ERROR if the allocation failed
 * @return 0 if the operation was successful, a negative value otherwise.
 */
int obj_add_vertex(obj_t *obj, vector3_t *v);

/**
 * Add a texture coordinate vertex to an `obj_t`.
 * @param obj The `obj_t` to which to add the vertex.
 * @param vt The texture coordinate vertex to be added.
 * @see vector3_t
 * @retval OBJ_SUCCESS if the operation was successful
 * @retval OBJ_ERROR if the `obj_t` or the `vector3_t` are NULL or if the
 * allocation failed
 * @return 0 if the operation was successful, a negative value otherwise.
 */
int obj_add_texture_coordinate(obj_t *obj, vector3_t *vt);

/**
 * Add a normal vertex to an `obj_t`; normals might not be unit vectors.
 * @param obj The `obj_t` to which to add the vertex.
 * @param vn The normal vertex to be added.
 * @see vector3_t
 * @retval OBJ_SUCCESS if the operation was successful
 * @retval OBJ_ERROR if the `obj_t` or the `vector3_t` are NULL or if the
 * allocation failed
 * @return 0 if the operation was successful, a negative value otherwise.
 */
int obj_add_normal(obj_t *obj, vector3_t *vn);

/**
 * Add a face to an `obj_t`.
 * @param obj The `obj_t` to which to add the face.
 * @param face The `face_t` to be added.
 * @retval OBJ_SUCCESS if the operation was successful
 * @retval OBJ_ERROR if the `obj_t` or the `face_t` are NULL or if the
 * allocation failed
 * @return 0 if the operation was successful, a negative value otherwise.
 */
int obj_add_face(obj_t *obj, face_t *face);

#endif
