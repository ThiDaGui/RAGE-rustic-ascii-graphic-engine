//
// Created by damiendidier on 21/03/2021.
//
#include "matrix.h"

#include <stdlib.h>

int init_null_mat(matrix_t *m, size_t height, size_t width)
{
    m->height = height;
    m->width = width;
    m->data = (float *)calloc(height * width, sizeof(float));
    if (m->data == NULL)
        return 1;
    return 0;
}

int init_mat(matrix_t *m, size_t height, size_t width, float *data)
{
    m->height = height;
    m->width = width;
    m->data = data;
    return 0;
}

int m_dot_m(matrix_t *A, matrix_t *B, matrix_t *result)
{
    if (!(A->width == B->height))
    {
        return 1;
    }
    for (size_t i = 0; i < A->height; i++)
    {
        for (size_t j = 0; j < B->width; j++)
        {
            for (size_t k = 0; k < B->height; k++)
            {
                result->data[result->width * i + j] +=
                    A->data[A->width * i + k] * B->data[B->width * k + j];
            }
        }
    }
    return 0;
}
