//
// Created by damiendidier on 21/03/2021.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

#define MATRIX_INIT { 0,0,(float*)NULL };

typedef struct matrix_t
{
    size_t height;
    size_t width;
    float* data;
}matrix_t;

int init_null_mat(matrix_t*, size_t, size_t);
int init_mat(matrix_t* , size_t , size_t , float* );
int m_dot_m(matrix_t*, matrix_t*, matrix_t*);

#endif //RAGE_RUSTIC_ASCII_GRAPHIC_ENGINE_MATRIX_H
