#ifndef VECTOR4_H
#define VECTOR4_H

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} vector4_t;

/* =================== Wrapping =============================== */

/**
 * Allocate and initializes a `vector4_t` to zero.
 * @return The initialized `vector4_t`
 */
vector4_t *vector4_init(void);

/**
 * Allocate and initializes a homogenous `vector4_t` to {0, 0, 0, 1}.
 * @return The initialized `vector4_t`
 */
vector4_t *vector4_h_init(void);

/**
 * Frees an initialized `vector3_t`.
 * @param v The `vector3_t` to free.
 */
void vector4_free(vector4_t *v);

/**
 * set x, y, z and w of an initialize `vector4_t` to the values given
 * @param v The `vector4_t` to set
 * @param x `float`
 * @param y `float`
 * @param z `float`
 * @param w `float`
 */
void vector4_set(vector4_t *, float, float, float, float);

/**
 * Create a `vector4_t` from a `vector3_t`
 */

/* =================== Operations ============================= */

/**
 * add two `vector4_t` and put the result in another `vector4_t`
 * @param v1 `vector4_t`
 * @param v2 `vector4_t`
 * @param result `vector4_t`
 */
void vector4_add(vector4_t *, vector4_t *, vector4_t *);

/**
 * dot product of two vector4_t and put the result in a float
 * @param v1 `vector4_t`
 * @param v2 `vector4_t`
 * @param result `float`
 */
int v_dot_v(vector4_t *, vector4_t *, float *);

/**
 * cross product of two vector4_t and put the result in another vector4_t
 * @param v1 `vector4_t`
 * @param v2 `vector4_t`
 * @param result `vector4_t`
 */
int v_cross_v(vector4_t *, vector4_t *, vector4_t *);

#endif // VECTOR4_H
