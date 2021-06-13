#ifndef OBJ_H
#define OBJ_H

#include "vector3.h"
#include <stddef.h>

#define OBJ_TRUE (1)
#define OBJ_FALSE (0)

#define OBJ_SUCCESS         (0)
#define OBJ_ERROR           (-1)
#define OBJ_ERROR_NULL      (-2)

typedef struct {
    size_t      *v_indices;
    size_t      *vt_indices;
    size_t      *vn_indices;

    size_t      vertex_count;
} face_t;

typedef struct {
    vector3_t   **vertices;
    vector3_t   **texture_coords;
    vector3_t   **normals;
    face_t      **faces;

    size_t      v_count;
    size_t      vt_count;
    size_t      vn_count;
    size_t      face_count;
} obj_t;

/**
 * Allocate and initializes a `face_t`.
 * @return The initialized `face_t`.
 */
face_t  *face_init(void);

/**
 * Frees an initialized `face_t`.
 * @param face The `face_t` to free.
 */
void    face_free(face_t *face);

/**
 * Add a vertex reference index to a face.
 * @param face The `face_t` to which to add the vertex references.
 * @param v The geometric vertex index.
 * @param vt The texture coordinates vertex index.
 * @param vn The normal vertex index.
 * @return 0 if the operation was successful, a negative value otherwise.
 */
int     face_add_vertex(face_t *face, size_t v, size_t vt, size_t vn);

/**
 * Allocate and initializes a `obj_t`.
 * @return The initialized `obj_t`.
 */
obj_t   *obj_init(void);

/**
 * Frees an initialized `obj_t`.
 * @param obj The `obj_t` to free.
 */
void    obj_free(obj_t *obj);

/**
 * Verify if an `obj_t` is valid.
 * @param obj The `obj_t` to verify if is valid.
 * @return OBJ_TRUE if the `obj_t` is valid, OBJ_FALSE otherwise.
 */
int     obj_is_valid(obj_t *obj);

/**
 * Add a geometric vertex to an `obj_t`.
 * @param obj The `obj_t` to which to add the vertex.
 * @param v The geometric vertex to be added.
 * @return 0 if the operation was successful, a negative value otherwise.
 */
int     obj_add_vertex(obj_t *obj, vector3_t *v);

/**
 * Add a texture coordinate vertex to an `obj_t`.
 * @param obj The `obj_t` to which to add the vertex.
 * @param vt The texture coordinate vertex to be added.
 * @return 0 if the operation was successful, a negative value otherwise.
 */
int     obj_add_texture_coordinate(obj_t *obj, vector3_t *vt);

/**
 * Add a normal vertex to an `obj_t`; normals might not be unit vectors.
 * @param obj The `obj_t` to which to add the vertex.
 * @param vn The normal vertex to be added.
 * @return 0 if the operation was successful, a negative value otherwise.
 */
int     obj_add_normal(obj_t *obj, vector3_t *vn);

/**
 * Add a face to an `obj_t`.
 * @param obj The `obj_t` to which to add the face.
 * @param face The `face_t` to be added.
 * @return 0 if the operation was successful, a negative value otherwise.
 */
int     obj_add_face(obj_t *obj, face_t *face);

#endif
