#ifndef VECTOR3_H
#define VECTOR3_H

typedef struct
{
    float x;
    float y;
    float z;
} vector3_t;

/* =================== Wrapping =============================== */

extern const vector3_t VECTOR3_INIT;

/**
 * Allocate and initializes a `vector3_t` to zero.
 * @return The initialized `vector_t`.
 */
vector3_t *vector3_init(void);

/**
 * Frees an initialized `vector3_t`.
 * @param v The `vector3_t` to free.
 */
void vector3_free(vector3_t *v);
/**
 * set x, y and z of an initialize `vector3_t` to the values given
 * @param v The `vector3_t` to set
 * @param x `float`
 * @param y `float`
 * @param z `float`
 */
void vector3_set(vector3_t *, float, float, float);

/* =================== Operations ============================= */

/**
 * add two vector3_t and put the result in another vector3_t
 * @param v1 `vector3_t`
 * @param v2 `vector3_t`
 * @param result `vector3_t`
 */
void vector3_add(vector3_t *, vector3_t *, vector3_t *);

/**
 * dot product of two vector3_t and put the result in a float
 * @param v1 `vector3_t`
 * @param v2 `vector3_t`
 * @param result `float`
 */
int v_dot_v(vector3_t *, vector3_t *, float *);

/**
 * cross product of two vector3_t and put the result in another vector3_t
 * @param v1 `vector3_t`
 * @param v2 `vector3_t`
 * @param result `vector3_t`
 */
int v_cross_v(vector3_t *, vector3_t *, vector3_t *);

#endif
