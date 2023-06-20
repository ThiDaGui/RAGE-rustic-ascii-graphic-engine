/**
 * @file parser.h
 * @brief parser header file.
 * @details this module is used to parse a Wavefront .obj file.
 * @see https://en.wikipedia.org/wiki/Wavefront_.obj_file
 * @version 0.1
 * @date 2023-06-19
 *
 *
 */
#ifndef PARSER_H
#define PARSER_H

#include "obj.h"

#define PARSER_SUCCESS (0)
#define PARSER_ERROR (-1)
#define PARSER_ERROR_OBJ_NULL (-2)
#define PARSER_ERROR_FACE_NULL (-3)
#define PARSER_ERROR_INVALID_FILE (-4)
#define PARSER_ERROR_OBJ_NOT_VALID (-5)
#define PARSER_ERROR_EMPTY_STRING (-6)
#define PARSER_ERROR_OVERFLOW (-7)
#define PARSER_ERROR_STRTOUL (-8)
#define PARSER_ERROR_INDEX_ZERO (-9)
#define PARSER_ERROR_EMPTY_VERTEX (-10)
#define PARSER_ERROR_UNKNOWN_VERTEX (-11)
#define PARSER_ERROR_INVALID_FACE (-12)
#define PARSER_ERROR_VERTEX_NULL (-13)
#define PARSER_ERROR_EMPTY_COORDINATE (-14)
#define PARSER_ERROR_UNKNOWN_COORDINATE (-15)
#define PARSER_ERROR_MISSING_COORDINATE (-16)

/**
 * Parse an string containing the data of a vertex element.
 * @param v The initialized `vector3_t` where to set the coordinates data.
 * @param s The string to parse into a vertex. It should be formatted as
 * follows: "-1.000 1.000 0.000", not containing the initial "v", "vn" or "vt"
 * indicating that is a vertex.
 * @return 0 if the operation was successful, a negative value otherwise.
 */
int parse_vertex(vector3_t *v, char *s);

/**
 * Parse an string containing the data of a face element and its vertex
 * reference number.
 * @param face The initialized `face_t` where to add the vertices data.
 * @param s The string to parse into a face. It should be formatted as follows:
 * "v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...", not containing the initial "f"
 * indicating that is a face.
 * @return 0 if the operation was successful, a negative value otherwise.
 */
int parse_face(face_t *face, char *s);

/**
 * Parse the content of a well formatted Wavefront .obj file.
 * @param obj The initialized `obj_t` where to set the data.
 * @param filename The name of the file to try to parse.
 * @return 0 if the operation was successful, a negative value otherwise.
 */
int parse_obj_file(obj_t *obj, const char *filename);

#endif
