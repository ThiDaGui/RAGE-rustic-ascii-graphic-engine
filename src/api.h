#ifndef API_H
#define API_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector3.h"
#include "tmatrix.h"
#include "matrix.h"

int v_dot_m(vector3_t*, tmatrix_t*, vector3_t*);
float fastisqrt(float number);
#endif
