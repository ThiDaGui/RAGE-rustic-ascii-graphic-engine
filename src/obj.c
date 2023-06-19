/**
 * @file obj.c
 * @brief source file of the obj module
 * @version 0.1
 * @date 2023-06-17
 * 
 * 
 */
#define _GNU_SOURCE
#include "obj.h"

#include <stdlib.h>

face_t *face_init(void)
{
    face_t *face = malloc(sizeof(face_t));
    if (face == NULL)
        return NULL;

    face->v_indices = NULL;
    face->vt_indices = NULL;
    face->vn_indices = NULL;
    face->vertex_count = 0;

    return face;
}

void face_free(face_t *face)
{
    free(face->v_indices);
    free(face->vt_indices);
    free(face->vn_indices);
    free(face);
}

int face_add_vertex(face_t *face, size_t v, size_t vt, size_t vn)
{
    if (face == NULL)
        return OBJ_ERROR;

    size_t size = sizeof(size_t);
    size_t new_count = face->vertex_count + 1;

    /* Store geometric vertex index */
    if ((face->v_indices = reallocarray(face->v_indices, new_count, size))
        == NULL)
        return OBJ_ERROR; // realloc() error
    face->v_indices[face->vertex_count] = v;

    /* Store texture vertex index */
    if ((face->vt_indices = reallocarray(face->vt_indices, new_count, size))
        == NULL)
        return OBJ_ERROR; // realloc() error
    face->vt_indices[face->vertex_count] = vt;

    /* Store normal vertex index */
    if ((face->vn_indices = reallocarray(face->vn_indices, new_count, size))
        == NULL)
        return OBJ_ERROR; // realloc() error
    face->vn_indices[face->vertex_count] = vn;

    face->vertex_count = new_count;

    return OBJ_SUCCESS;
}

obj_t *obj_init(void)
{
    obj_t *obj = malloc(sizeof(obj_t));
    if (obj == NULL)
        return NULL;

    obj->vertices = NULL;
    obj->texture_coords = NULL;
    obj->normals = NULL;
    obj->faces = NULL;
    obj->v_count = 0;
    obj->vt_count = 0;
    obj->vn_count = 0;
    obj->face_count = 0;

    return obj;
}

void obj_free(obj_t *obj)
{
    if (obj->vertices)
    {
        for (size_t i = 0; i < obj->v_count; ++i)
            vector3_free(obj->vertices[i]);
        free(obj->vertices);
    }
    if (obj->texture_coords)
    {
        for (size_t i = 0; i < obj->vt_count; ++i)
            vector3_free(obj->texture_coords[i]);
        free(obj->texture_coords);
    }
    if (obj->normals)
    {
        for (size_t i = 0; i < obj->vn_count; ++i)
            vector3_free(obj->normals[i]);
        free(obj->normals);
    }
    if (obj->faces)
    {
        for (size_t i = 0; i < obj->face_count; ++i)
            face_free(obj->faces[i]);
        free(obj->faces);
    }
    free(obj);
}

int obj_is_valid(obj_t *obj)
{
    if (obj == NULL)
        return OBJ_ERROR_NULL;

    /* Verifications for each face */
    for (size_t i = 0; i < obj->face_count; ++i)
    {
        for (size_t j = 0; j < obj->faces[i]->vertex_count; ++j)
        {
            /* Invalid geometric vertex index */
            if (obj->faces[i]->v_indices[j] > obj->v_count)
                return OBJ_FALSE;
            /* Invalid texture coordinates index */
            if (obj->faces[i]->vt_indices[j] > obj->vt_count)
                return OBJ_FALSE;
            /* Invalid normal vertex index */
            if (obj->faces[i]->vn_indices[j] > obj->vn_count)
                return OBJ_FALSE;
        }
    }

    return OBJ_TRUE;
}

int obj_add_vertex(obj_t *obj, vector3_t *v)
{
    if (obj == NULL)
        return OBJ_ERROR;
    if (v == NULL)
        return OBJ_ERROR;

    size_t size = sizeof(vector3_t);
    size_t new_count = obj->v_count + 1;

    if ((obj->vertices = reallocarray(obj->vertices, new_count, size)) == NULL)
        return OBJ_ERROR;
    obj->vertices[obj->v_count] = v;
    obj->v_count = new_count;

    return OBJ_SUCCESS;
}

int obj_add_texture_coordinate(obj_t *obj, vector3_t *vt)
{
    if (obj == NULL)
        return OBJ_ERROR;
    if (vt == NULL)
        return OBJ_ERROR;

    size_t size = sizeof(vector3_t);
    size_t new_count = obj->vt_count + 1;

    if ((obj->texture_coords =
             reallocarray(obj->texture_coords, new_count, size))
        == NULL)
        return OBJ_ERROR;
    obj->texture_coords[obj->vt_count] = vt;
    obj->vt_count = new_count;

    return OBJ_SUCCESS;
}

int obj_add_normal(obj_t *obj, vector3_t *vn)
{
    if (obj == NULL)
        return OBJ_ERROR;
    if (vn == NULL)
        return OBJ_ERROR;

    size_t size = sizeof(vector3_t);
    size_t new_count = obj->vn_count + 1;

    if ((obj->normals = reallocarray(obj->normals, new_count, size)) == NULL)
        return OBJ_ERROR;
    obj->normals[obj->vn_count] = vn;
    obj->vn_count = new_count;

    return OBJ_SUCCESS;
}

int obj_add_face(obj_t *obj, face_t *face)
{
    if (obj == NULL)
        return OBJ_ERROR;
    if (face == NULL)
        return OBJ_ERROR;

    size_t size = sizeof(face_t);
    size_t new_count = obj->face_count + 1;

    if ((obj->faces = reallocarray(obj->faces, new_count, size)) == NULL)
        return OBJ_ERROR;
    obj->faces[obj->face_count] = face;
    obj->face_count = new_count;

    return OBJ_SUCCESS;
}
