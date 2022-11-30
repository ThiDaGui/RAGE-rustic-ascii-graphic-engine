#ifndef TMATRIX_H
#define TMATRIX_H

#define TMATRIX_SIZE 4
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

#define TMATRIX_INIT                                                           \
    {                                                                          \
        4, 4, (float *)NULL                                                    \
    }

typedef struct tmatrix_t
{
    float data[TMATRIX_SIZE * TMATRIX_SIZE];
} tmatrix_t;

int tmatrix_init(tmatrix_t *);
int tm_dot_tm(tmatrix_t *, tmatrix_t *, tmatrix_t *);

#endif
