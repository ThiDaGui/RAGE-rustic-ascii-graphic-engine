#ifndef VECTOR4_H
#define VECTOR4_H

#include "vector3.h"

/**
 * @struct vector4_t
 * 
 * @brief is a 4d vector
 * 
 */
typedef struct vector4_t
{
    float x; 
    float y;
    float z;
    float w;
} vector4_t;

/* =================== Wrapping =============================== */

extern const vector4_t VECTOR4_INIT;
extern const vector4_t VECTOR4_H_INIT;

/**
 * @fn vector4_t *vector4_init(void)
 * 
 * @brief Allocate and initializes a `vector4_t` to zero.
 * @return The initialized `vector4_t`
 */
vector4_t *vector4_init(void);

/**
 * @fn vector4_t *vector4_h_init(void)
 * @brief Allocate and initializes a homogenous `vector4_t` to {0, 0, 0, 1}.
 * @return The initialized `vector4_t`
 */
vector4_t *vector4_h_init(void);

/**
 * @fn void vector4_free(vector4_t *v)
 * @brief Frees an initialized `vector3_t`.
 * @param vector4 The `vector3_t` to free.
 */
void vector4_free(vector4_t *v);

/**
 * @fn void vector4_set(vector4_t *v, float x, float y, float z, float w)
 * @brief set x, y, z and w of an initialize `vector4_t` to the values given
 * @param v The `vector4_t` to set
 * @param x `float`
 * @param y `float`
 * @param z `float`
 * @param w `float`
 */
void vector4_set(vector4_t *v, float x, float y, float z, float w);

/**
 * @fn vector4_t *vector4_from_vector3(vector3_t *src, vector4_t *dst)
 * @brief Create a homogenous `vector4_t` from a `vector3_t`.
 * @param[in] src The `vector3_t` to convert to `vector4_t`. src needs to be freed outside of the function
 * @param[out] dst The new vector4_t to return
 * @return vector4_t* A `vector4_t` filled with the value of ds
 */
vector4_t *vector4_from_vector3(vector3_t *src, vector4_t *dst);

/**
 * @fn vector4_t *vector4_from_vector3(vector3_t *src, vector4_t *dst);
 * @brief Create a `vector3_t` from a homogenous `vector4`
 * @param[in] src The  `vector4_t` to  convert to a `vector3_t`. 
 * @param[out] dst The `vector3_t` to return 
 * @return dst 
 */
vector3_t *vector3_from_vector4(vector4_t *src, vector3_t *dst);

/**
 * @brief normalize the vector4_t passed as argument and return it
 * 
 * @param[in] vector4 a `vector4_t` to normalize
 * @return vector4 
 */
vector4_t *vector4_normalize(vector4_t *vector4);

/* =================== Operations ============================= */

/**
 * @fn void vector4_linear(vector4_t *vector4_a, vector4_t *vector4_b, float lambda, vector4_t *vector4_result)
 * 
 *
 * @brief add two `vector4_t` and put the result in another `vector4_t`
 * @param v1 `vector4_t`
 * @param v2 `vector4_t`
 * @param result `vector4_t`
 */
void vector4_linear(vector4_t *vector4_a, vector4_t *vector4_b, float lambda,
                    vector4_t *vector4_result);

void vector4_LERP(vector4_t *vector4_a, vector4_t *vector4_b, float lambda,
                  vector4_t *vector4_result);

/**
 * @fn void vector4_multiply(float lambda, vector4_t *vector4, vector4_t *result)
 * 
 * @brief multiply a vector4_t by a real
 * @param[in] lambda float
 * @param[in] vector4 vector4_t
 * @param[out] result vector4_t
 */
void vector4_multiply(float lambda, vector4_t *vector4, vector4_t *result);

/**
 * @fn void vector4_dot_vector4(vector4_t *vector4_a, vector4_t *vector4_b, float *result)
 * 
 * @brief dot product of two vector4_t and put the result in a float
 * @param[in] vector4_a `vector4_t`
 * @param[in] vector4_b `vector4_t`
 * @param[out] result `float`
 * 
 */
void vector4_dot_vector4(vector4_t *vector4_a, vector4_t *vector4_b,
                        float *result);

/**
 * @fn void vector4_cross_vector4(vector4_t *vector4_a, vector4_t *vector4_b, vector4_t *result)
 * 
 * @brief cross product of two vector4_t and put the result in another vector4_t
 * @param[in] vector4_a 'vector4_t'
 * @param[in] vector4_b 'vector4_t'
 * @param[out] result   'vector4_t'
 */
void vector4_cross_vector4(vector4_t *vector4_a, vector4_t *vector4_b,
                          vector4_t *result);

#endif // VECTOR4_H
