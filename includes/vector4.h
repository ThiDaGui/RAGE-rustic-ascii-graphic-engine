/**
 * @file vector4.h
 * @brief header file of the vector4 module
 * @version 0.1
 * @date 2023-06-19
 * 
 * 
 */
#ifndef VECTOR4_H
#define VECTOR4_H

#include "vector3.h"

/**
 * @struct vector4_t
 * @brief is a 4d vector
 * @var vector4_t::x
 * x
 * @var vector4_t::y
 * y
 * @var vector4_t::z
 * z
 * @var vector4_t::w
 * w
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
 * @brief Allocate and initializes a `vector4_t` to zero.
 * @see vector4_free
 * @return The initialized `vector4_t`
 */
vector4_t *vector4_init(void);

/**
 * @brief Allocate and initializes a homogenous `vector4_t` to {0, 0, 0, 1}.
 * @see vector4_free
 * @retval NULL if allocation failed
 * @return The initialized `vector4_t`
 */
vector4_t *vector4_h_init(void);

/**
 * @brief Frees an initialized `vector4_t`.
 * @param v The `vector4_t` to free.
 */
void vector4_free(vector4_t *vector4);

/**
 * @brief set x, y, z and w of an initialize vector4_t to the values given
 * @param vector4 `vector4_t` to set
 * @param x `float`
 * @param y `float`
 * @param z `float`
 * @param w `float`
 */
void vector4_set(vector4_t *vector4, float x, float y, float z, float w);

/**
 * @brief Create a homogenous `vector4_t` from a `vector3_t` and store it in result.
 * @param vector3 `vector3_t` to convert
 * @param result `vector4_t` to store the result
 * @return result
 */
vector4_t *vector4_from_vector3(vector3_t *vector3, vector4_t *result);

/**
 * @brief Create a `vector3_t` from a homogenous `vector4`
 * @param vector4 `vector4_t` to convert
 * @param result `vector3_t` to store the result
 * @return result
 */
vector3_t *vector3_from_vector4(vector4_t *vector4, vector3_t *result);

/**
 * @brief normalize the vector4_t passed as argument and return it as an homogenous vector4_t
 * @param vector4 `vector4_t` to normalize
 * @return vector4_t
 * 
 */
vector4_t *vector4_normalize(vector4_t *vector4);

/* =================== Operations ============================= */

/**
 * @brief perform a linear combination of the two vector4_t passed as argument and store the result in the third vector4_t
 * @param vector4_a the first vector4_t
 * @param vector4_b the second vector4_t
 * @param lambda the coefficient of the linear combination
 * @param vector4_result the vector4_t to store the result
 */
void vector4_linear(vector4_t *vector4_a, vector4_t *vector4_b, float lambda,
                    vector4_t *vector4_result);
/**
 * @brief perform a linear interpolation of the two vector4_t passed as argument and store the result in the third vector4_t
 * @param vector4_a the first vector4_t
 * @param vector4_b the second vector4_t
 * @param lambda the coefficient of the linear interpolation
 * @param vector4_result the vector4_t to store the result
 */
void vector4_LERP(vector4_t *vector4_a, vector4_t *vector4_b, float lambda,
                  vector4_t *vector4_result);

/**
 * 
 * @brief UNDECLARED FUNCTION. DO NOT USE
 * @details  multiply a vector4_t by a real
 * @param[in] lambda float
 * @param[in] vector4 vector4_t
 * @param[out] result vector4_t
 */
void vector4_multiply(float lambda, vector4_t *vector4, vector4_t *result);

/** 
 * @brief dot product of two vector4_t and put the result in a float
 * @param vector4_a the first vector4_t
 * @param vector4_b the second vector4_t
 * @param result the float to store the result
 * 
 */
void vector4_dot_vector4(vector4_t *vector4_a, vector4_t *vector4_b,
                        float *result);

/**
 * @brief UNDECLARED FUNCTION. DO NOT USE
 * @details cross product of two vector4_t and put the result in another vector4_t
 * @param[in] vector4_a 'vector4_t'
 * @param[in] vector4_b 'vector4_t'
 * @param[out] result   'vector4_t'
 */
void vector4_cross_vector4(vector4_t *vector4_a, vector4_t *vector4_b,
                          vector4_t *result);

#endif // VECTOR4_H
