/**
 * @file vector3.h
 * @brief header file of the vector3 module
 * @version 0.1
 * @date 2023-06-19
 */
#ifndef VECTOR3_H
#define VECTOR3_H
/**
 * @struct vector3_t
 * @brief is a 3d vector
 */
typedef struct vector3_t
{
    float x;
    float y;
    float z;
} vector3_t;

/* =================== Wrapping =============================== */

extern const vector3_t VECTOR3_INIT;

/**
 * @fn vector3_t *vector3_init(void)
 * @brief Allocate and initializes a `vector3_t` to zero.
 * @see vector3_free
 * @retval NULL if allocation failed
 * @return The initialized `vector3_t`.
 */
vector3_t *vector3_init(void);

/**
 * @fn void vector3_free(vector3_t *v)
 * @brief Frees an initialized `vector3_t`.
 * @param v The `vector3_t` to free.
 */
void vector3_free(vector3_t *v);

/**
 * @brief set x, y and z of an initialize vector3_t to the values given
 * @param vector3 `vector3_t` to set
 * @param x `float`
 * @param y `float`
 * @param z `float`
 */
void vector3_set(vector3_t *vector3, float x, float y, float z);

/* =================== Operations ============================= */

/**
 * @brief perform a linear combination of two vector3_t and put the result in
 * another
 * @param vector3_a first `vector3_t`
 * @param vector3_b second `vector3_t`
 * @param lambda the coefficient of the linear combination
 * @param result the `vector3_t` to put the result in
 */
void vector3_linear(vector3_t *vector3_a, vector3_t *vector3_b, float lambda,
                    vector3_t *result);

/**
 * @brief perform a linear interpolation of two vector3_t and put the result in
 * the result vector3_t
 * @param vector3_a the first `vector3_t`
 * @param vector3_b the second `vector3_t`
 * @param lambda the coefficient of the linear interpolation
 * @param result the `vector3_t` to put the result in
 */
void vector3_LERP(vector3_t *vector3_a, vector3_t *vector3_b, float lambda,
                  vector3_t *result);

/**
 * @brief perform a perspective correct baricentric linear interpolation of
 * three vector3_t and put the result in the result vector3_t
 * @param vector3_a the first `vector3_t`
 * @param z_a depth of the first `vector3_t`
 * @param lambda_a coefficient for the first `vector3_t`
 * @param vector3_b the second `vector3_t`
 * @param z_b depth of the second `vector3_t`
 * @param lambda_b coefficient for the second `vector3_t`
 * @param vector3_c the third `vector3_t`
 * @param z_c depth of the third `vector3_t`
 * @param lambda_c coefficient for the third `vector3_t`
 * @param result the `vector3_t` to put the result in
 */
void vector3_pc_BLERP(vector3_t *vector3_a, float z_a, float lambda_a,
                      vector3_t *vector3_b, float z_b, float lambda_b,
                      vector3_t *vector3_c, float z_c, float lambda_c,
                      vector3_t *result);

/**
 * @brief dot product of the two vector3_t a and b and put the result in result
 * @param a the first `vector3_t`
 * @param b the second `vector3_t`
 * @param result the `float` to put the result in
 * @return int 0
 */
int v_dot_v(vector3_t *a, vector3_t *b, float *result);

/**
 * @brief cross product of the two vector3_t a and b and put the result in
 * result
 * @param a the first `vector3_t`
 * @param b the second `vector3_t`
 * @param result the `vector3_t` to put the result in
 * @return 0
 */
int v_cross_v(vector3_t *a, vector3_t *b, vector3_t *result);

#endif
