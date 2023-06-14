#ifndef VECTOR3_H
#define VECTOR3_H
/**
 * @struct vector3_t
 * @brief is a 3d vector 
 */
typedef struct
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
 * @brief set x, y and z of an initialize `vector3_t` to the values given
 * @param v The `vector3_t` to set
 * @param x `float`
 * @param y `float`
 * @param z `float`
 */
void vector3_set(vector3_t *vector3, float x, float y, float z);

/* =================== Operations ============================= */

/**
 * add two vector3_t and put the result in another vector3_t
 * @param v1 `vector3_t`
 * @param v2 `vector3_t`
 * @param result `vector3_t`
 */
void vector3_linear(vector3_t *vector3_a, vector3_t *vector3_b, float lambda,
                    vector3_t *result);

void vector3_LERP(vector3_t *vector3_a, vector3_t *vector3_b, float lambda,
                  vector3_t *result);

void vector3_pc_BLERP(vector3_t *vector3_a, float z_a, float lambda_a,
                      vector3_t *vector3_b, float z_b, float lambda_b,
                      vector3_t *vector3_c, float z_c, float lambda_c,
                      vector3_t *result);

/**
 * @brief dot product of two vector3_t and put the result in a float
 * @param v1 `vector3_t`
 * @param v2 `vector3_t`
 * @param result `float`
 * @retval int
 */
int v_dot_v(vector3_t *, vector3_t *, float *);

/**
 * cross product of two vector3_t and put the result in another vector3_t
 * @param v1 `vector3_t`
 * @param v2 `vector3_t`
 * @param result `vector3_t`
 * @retval int
 */
int v_cross_v(vector3_t *, vector3_t *, vector3_t *);

#endif
