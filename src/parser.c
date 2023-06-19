/**
 * @file parser.c
 * @brief source file of the parser module
 * @version 0.1
 * @date 2023-06-19
 * 
 * 
 */
#include "parser.h"

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACE_DELIMITER " \t\n"
#define FACE_VERTEX_DELIMITER '/'

#define ID_COMMENT "#"
#define ID_GEOMETRIC_VERTEX "v"
#define ID_TEXTURE_COORDINATES "vt"
#define ID_NORMAL_VERTEX "vn"
#define ID_FACE "f"

/**
 * Parse a line.
 */
int parse_line(obj_t *obj, const char *line)
{
    /* Duplicated line since 'strtok_r' does not work on constant variables */
    char *line_copy = strdup(line);

    char *save_ptr;
    char *token = strtok_r(line_copy, SPACE_DELIMITER, &save_ptr);

    if (token)
    {
        if (strcmp(token, ID_GEOMETRIC_VERTEX) == 0)
        {
            vector3_t *v = vector3_init();
            if (v == NULL)
                return PARSER_ERROR;
            if (parse_vertex(v, save_ptr) == PARSER_ERROR)
            {
                vector3_free(v);
                return PARSER_ERROR;
            }
            if (obj_add_vertex(obj, v) == PARSER_ERROR)
            {
                vector3_free(v);
                return PARSER_ERROR;
            }
        }
        else if (strcmp(token, ID_TEXTURE_COORDINATES) == 0)
        {
            vector3_t *vt = vector3_init();
            if (vt == NULL)
                return PARSER_ERROR;
            if (parse_vertex(vt, save_ptr) == PARSER_ERROR)
            {
                vector3_free(vt);
                return PARSER_ERROR;
            }
            if (obj_add_texture_coordinate(obj, vt) == PARSER_ERROR)
            {
                vector3_free(vt);
                return PARSER_ERROR;
            }
        }
        else if (strcmp(token, ID_NORMAL_VERTEX) == 0)
        {
            vector3_t *vn = vector3_init();
            if (vn == NULL)
                return PARSER_ERROR;
            if (parse_vertex(vn, save_ptr) == PARSER_ERROR)
            {
                vector3_free(vn);
                return PARSER_ERROR;
            }
            if (obj_add_normal(obj, vn) == PARSER_ERROR)
            {
                vector3_free(vn);
                return PARSER_ERROR;
            }
        }
        else if (strcmp(token, ID_FACE) == 0)
        {
            face_t *face = face_init();
            if (face == NULL)
                return PARSER_ERROR;
            if (parse_face(face, save_ptr) == PARSER_ERROR)
            {
                face_free(face);
                return PARSER_ERROR;
            }

            if (obj_add_face(obj, face) == PARSER_ERROR)
            {
                face_free(face);
                return PARSER_ERROR;
            }
        }
    }

    /* Cleanup */
    free(line_copy);

    return PARSER_SUCCESS;
}

/**
 * Parse a vertices group: "v", "v/vt/vn", "v/vt", or "v//vn"
 */
int parse_face_vertices(char *s, size_t *v, size_t *vt, size_t *vn)
{
    size_t val;
    char *end_ptr;
    char *token = s;
    size_t i = 0;

    while (token && *token != '\0')
    {
        errno = 0;

        val = strtoul(token, &end_ptr, 10);
        if (errno == ERANGE && val == ULONG_MAX)
            return PARSER_ERROR_OVERFLOW;
        if (errno != 0 && val == 0)
            return PARSER_ERROR_STRTOUL;

        if (end_ptr != token && val == 0)
            return PARSER_ERROR_INDEX_ZERO;
        if (end_ptr == token && i != 1)
            return PARSER_ERROR_EMPTY_VERTEX; // No digits were found and is
                                              // not "vt"

        switch (i)
        {
        case 0:
            *v = val;
            break;
        case 1:
            *vt = val;
            break;
        case 2:
            *vn = val;
            break;
        default:
            return PARSER_ERROR_UNKNOWN_VERTEX;
        }

        if (*end_ptr == FACE_VERTEX_DELIMITER && *(end_ptr + 1) != '\0')
        {
            token = end_ptr + 1;
        }
        else if (*end_ptr == '\0')
        {
            token = end_ptr;
        }
        else
        {
            return PARSER_ERROR;
        }
        i += 1;
    }

    return PARSER_SUCCESS;
}

/* ================================ */

int parse_vertex(vector3_t *v, char *s)
{
    if (v == NULL)
        return PARSER_ERROR_VERTEX_NULL;

    char *save_ptr;
    char *token = strtok_r(s, SPACE_DELIMITER, &save_ptr);

    float val;
    char *end_ptr;

    size_t i = 0;

    while (token)
    {
        errno = 0;

        val = strtof(token, &end_ptr);
        if (errno == ERANGE && val == HUGE_VALF)
            return PARSER_ERROR_OVERFLOW;
        if (errno != 0 && val == 0)
            return PARSER_ERROR_STRTOUL;
        if (end_ptr == token)
            return PARSER_ERROR_EMPTY_COORDINATE;

        /* Set vertex indices depending on the order found */
        switch (i)
        {
        case 0:
            v->x = val;
            break;
        case 1:
            v->y = val;
            break;
        case 2:
            v->z = val;
            break;
        default:
            return PARSER_ERROR_UNKNOWN_COORDINATE;
        }

        token = strtok_r(NULL, SPACE_DELIMITER, &save_ptr);
        i += 1;
    }

    if (i != 3)
        return PARSER_ERROR_MISSING_COORDINATE;

    return PARSER_SUCCESS;
}

int parse_face(face_t *face, char *s)
{
    if (face == NULL)
        return PARSER_ERROR_FACE_NULL;

    char *save_ptr;
    char *token = strtok_r(s, SPACE_DELIMITER, &save_ptr);
    if (!token)
        return PARSER_ERROR_EMPTY_STRING; // Empty string

    int ret;
    size_t v, vt, vn;

    while (token)
    {
        v = 0, vt = 0, vn = 0;

        /* Try parse a vertices group */
        if ((ret = parse_face_vertices(token, &v, &vt, &vn)) != PARSER_SUCCESS)
            return ret;

        /* Add vertex to face */
        if (face_add_vertex(face, v, vt, vn) != OBJ_SUCCESS)
            return PARSER_ERROR;

        token = strtok_r(NULL, SPACE_DELIMITER, &save_ptr);
    }

    if (face->vertex_count < 3)
        return PARSER_ERROR_INVALID_FACE;

    return PARSER_SUCCESS;
}

int parse_obj_file(obj_t *obj, const char *filename)
{
    if (obj == NULL)
        return PARSER_ERROR_OBJ_NULL;

    /* Read file */
    FILE *stream;
    char *line = NULL;
    size_t line_len = 0;

    stream = fopen(filename, "r");
    if (stream == NULL)
        return PARSER_ERROR_INVALID_FILE;

    /* Read line by line from file */
    while (getline(&line, &line_len, stream) != -1)
    {
        parse_line(obj, line);
    }

    /* Check that parsed obj is valid */
    if (obj_is_valid(obj) == OBJ_FALSE)
    {
        free(line);
        fclose(stream);
        return PARSER_ERROR_OBJ_NOT_VALID;
    }

    /* Cleanup */
    free(line);
    fclose(stream);

    return PARSER_SUCCESS;
}
