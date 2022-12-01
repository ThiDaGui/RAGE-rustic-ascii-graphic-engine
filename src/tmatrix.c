#include "tmatrix.h"

#include <stddef.h>
#include <string.h>

int tmatrix_init(tmatrix_t *tmatrix)
{
    if (tmatrix == NULL)
        return 1;
    memset(tmatrix->data, 0, TMATRIX_SIZE * TMATRIX_SIZE * sizeof(float));
    return 0;
}

int tm_dot_tm(tmatrix_t *A, tmatrix_t *B, tmatrix_t *result)
{
    for (size_t i = 0; i < TMATRIX_SIZE; i++)
    {
        for (size_t j = 0; j < TMATRIX_SIZE; j++)
        {
            result->data[TMATRIX_SIZE * i + j] = 0;
            for (size_t k = 0; k < TMATRIX_SIZE; k++)
            {
                result->data[TMATRIX_SIZE * i + j] +=
                    A->data[TMATRIX_SIZE * i + k]
                    * B->data[TMATRIX_SIZE * k + j];
            }
        }
    }
    return 0;
}
