#include <check.h>
#include <stdlib.h>

#include "clipping.h"
#include "h_triangle.h"
#include "vector4.h"

#define ck_assert_vector4_eq(X, Y)                                             \
    {                                                                          \
        ck_assert_int_eq(X.x, Y.x);                                            \
        ck_assert_int_eq(X.y, Y.y);                                            \
        ck_assert_int_eq(X.z, Y.z);                                            \
        ck_assert_int_eq(X.w, Y.w);                                            \
    }

#define ck_assert_h_triangle_eq(X, Y)                                          \
    {                                                                          \
        for (size_t iter = 0; iter < 3; iter++)                                \
        {                                                                      \
            vector4_t x = X[iter].position;                                    \
            vector4_t y = Y[iter].position;                                    \
            ck_assert_vector4_eq(x, y);                                        \
        }                                                                      \
    }

START_TEST(clip_triangle_before_plane)
{
    h_triangle_t h_triangle = { { { -1, -1, 1, 1 }, { 0, 0, 0 } },
                                { { -1, 1, 1, 1 }, { 0, 0, 0 } },
                                { { 1, 1, 1, 1 }, { 0, 0, 0 } } };

    vector4_t plane = { 0, 0, 1, 0 };

    h_triangle_t ref = {
        { { -1, -1, 1, 1 }, { 0, 0, 0 } },
        { { -1, 1, 1, 1 }, { 0, 0, 0 } },
        { { 1, 1, 1, 1 }, { 0, 0, 0 } },
    };

    h_triangle_t *result = calloc(2, sizeof(h_triangle_t));

    size_t nb_triangle = clip_triangle(&h_triangle, &plane, result);

    ck_assert_int_eq(nb_triangle, 1);

    ck_assert_h_triangle_eq(result[0], ref);
}
END_TEST

START_TEST(clip_triangle_behind_plane)
{
    h_triangle_t h_triangle = {
        { { -1, -1, -1, 1 }, { 0, 0, 0 } },
        { { -1, 1, -1, 1 }, { 0, 0, 0 } },
        { { 1, 1, -1, 1 }, { 0, 0, 0 } },
    };

    vector4_t plane = { 0, 0, 1, 0 };

    h_triangle_t *result = calloc(2, sizeof(h_triangle_t));

    size_t nb_triangle = clip_triangle(&h_triangle, &plane, result);

    ck_assert_int_eq(nb_triangle, 0);
}
END_TEST

START_TEST(clip_triangle_two_clipped_vertex_case_1)
{
    h_triangle_t h_triangle = {
        { { -1, -1, 1, 1 }, { 0, 0, 0 } },
        { { -1, -1, -1, 1 }, { 0, 0, 0 } },
        { { 1, -1, -1, 1 }, { 0, 0, 0 } },
    };

    vector4_t plane = { 0, 0, 1, 0 };

    h_triangle_t ref = {
        { { -1, -1, 1, 1 }, { 0, 0, 0 } },
        { { -1, -1, 0, 1 }, { 0, 0, 0 } },
        { { 0, -1, 0, 1 }, { 0, 0, 0 } },
    };

    h_triangle_t *result = calloc(2, sizeof(h_triangle_t));

    size_t nb_triangle = clip_triangle(&h_triangle, &plane, result);

    ck_assert_int_eq(nb_triangle, 1);

    ck_assert_h_triangle_eq(result[0], ref);
}
END_TEST

START_TEST(clip_triangle_two_clipped_vertex_case_2)
{
    h_triangle_t h_triangle = {
        { { -1, -1, -1, 1 }, { 0, 0, 0 } },
        { { 1, -1, -1, 1 }, { 0, 0, 0 } },
        { { -1, -1, 1, 1 }, { 0, 0, 0 } },
    };

    vector4_t plane = { 0, 0, 1, 0 };

    h_triangle_t ref = {
        { { -1, -1, 1, 1 }, { 0, 0, 0 } },
        { { -1, -1, 0, 1 }, { 0, 0, 0 } },
        { { 0, -1, 0, 1 }, { 0, 0, 0 } },
    };

    h_triangle_t *result = calloc(2, sizeof(h_triangle_t));

    size_t nb_triangle = clip_triangle(&h_triangle, &plane, result);

    ck_assert_int_eq(nb_triangle, 1);

    ck_assert_h_triangle_eq(result[0], ref);
}
END_TEST

START_TEST(clip_triangle_two_clipped_vertex_case_3)
{
    h_triangle_t h_triangle = {
        { { 1, -1, -1, 1 }, { 0, 0, 0 } },
        { { -1, -1, 1, 1 }, { 0, 0, 0 } },
        { { -1, -1, -1, 1 }, { 0, 0, 0 } },
    };

    vector4_t plane = { 0, 0, 1, 0 };

    h_triangle_t ref = {
        { { -1, -1, 1, 1 }, { 0, 0, 0 } },
        { { -1, -1, 0, 1 }, { 0, 0, 0 } },
        { { 0, -1, 0, 1 }, { 0, 0, 0 } },
    };

    h_triangle_t *result = calloc(2, sizeof(h_triangle_t));

    size_t nb_triangle = clip_triangle(&h_triangle, &plane, result);

    ck_assert_int_eq(nb_triangle, 1);

    ck_assert_h_triangle_eq(result[0], ref);
}
END_TEST

START_TEST(clip_triangle_one_clipped_vertex_case_1)
{
    h_triangle_t h_triangle = {
        { { -1, -1, 1, 1 }, { 0, 0, 0 } },
        { { 1, -1, 1, 1 }, { 0, 0, 0 } },
        { { 1, -1, -1, 1 }, { 0, 0, 0 } },
    };

    vector4_t plane = { 0, 0, 1, 0 };

    h_triangle_t ref[2] = { {
                                { { -1, -1, 1, 1 }, { 0, 0, 0 } },
                                { { 1, -1, 1, 1 }, { 0, 0, 0 } },
                                { { 1, -1, 0, 1 }, { 0, 0, 0 } },
                            },
                            {
                                { { -1, -1, 1, 1 }, { 0, 0, 0 } },
                                { { 1, -1, 0, 1 }, { 0, 0, 0 } },
                                { { 0, -1, 0, 1 }, { 0, 0, 0 } },
                            } };

    h_triangle_t *result = calloc(2, sizeof(h_triangle_t));

    size_t nb_triangle = clip_triangle(&h_triangle, &plane, result);

    ck_assert_int_eq(nb_triangle, 2);

    ck_assert_h_triangle_eq(result[0], ref[0]);
    ck_assert_h_triangle_eq(result[1], ref[1]);
}
END_TEST

START_TEST(clip_triangle_one_clipped_vertex_case_2)
{
    h_triangle_t h_triangle = {
        { { 1, -1, 1, 1 }, { 0, 0, 0 } },
        { { 1, -1, -1, 1 }, { 0, 0, 0 } },
        { { -1, -1, 1, 1 }, { 0, 0, 0 } },
    };

    vector4_t plane = { 0, 0, 1, 0 };

    h_triangle_t ref[2] = { {
                                { { -1, -1, 1, 1 }, { 0, 0, 0 } },
                                { { 1, -1, 1, 1 }, { 0, 0, 0 } },
                                { { 1, -1, 0, 1 }, { 0, 0, 0 } },
                            },
                            {
                                { { -1, -1, 1, 1 }, { 0, 0, 0 } },
                                { { 1, -1, 0, 1 }, { 0, 0, 0 } },
                                { { 0, -1, 0, 1 }, { 0, 0, 0 } },
                            } };

    h_triangle_t *result = calloc(2, sizeof(h_triangle_t));

    size_t nb_triangle = clip_triangle(&h_triangle, &plane, result);

    ck_assert_int_eq(nb_triangle, 2);

    ck_assert_h_triangle_eq(result[0], ref[0]);
    ck_assert_h_triangle_eq(result[1], ref[1]);
}
END_TEST

START_TEST(clip_triangle_one_clipped_vertex_case_3)
{
    h_triangle_t h_triangle = { { { 1, -1, -1, 1 }, { 0, 0, 0 } },
                                { { -1, -1, 1, 1 }, { 0, 0, 0 } },
                                { { 1, -1, 1, 1 }, { 0, 0, 0 } } };

    vector4_t plane = { 0, 0, 1, 0 };

    h_triangle_t ref[2] = { {
                                { { -1, -1, 1, 1 }, { 0, 0, 0 } },
                                { { 1, -1, 1, 1 }, { 0, 0, 0 } },
                                { { 1, -1, 0, 1 }, { 0, 0, 0 } },
                            },
                            {
                                { { -1, -1, 1, 1 }, { 0, 0, 0 } },
                                { { 1, -1, 0, 1 }, { 0, 0, 0 } },
                                { { 0, -1, 0, 1 }, { 0, 0, 0 } },
                            } };

    h_triangle_t *result = calloc(2, sizeof(h_triangle_t));

    size_t nb_triangle = clip_triangle(&h_triangle, &plane, result);

    ck_assert_int_eq(nb_triangle, 2);

    ck_assert_h_triangle_eq(result[0], ref[0]);
    ck_assert_h_triangle_eq(result[1], ref[1]);
}
END_TEST

Suite *clipping_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Clipping");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, clip_triangle_before_plane);
    tcase_add_test(tc_core, clip_triangle_behind_plane);
    tcase_add_test(tc_core, clip_triangle_two_clipped_vertex_case_1);
    tcase_add_test(tc_core, clip_triangle_two_clipped_vertex_case_2);
    tcase_add_test(tc_core, clip_triangle_two_clipped_vertex_case_3);
    tcase_add_test(tc_core, clip_triangle_one_clipped_vertex_case_1);
    tcase_add_test(tc_core, clip_triangle_one_clipped_vertex_case_2);
    tcase_add_test(tc_core, clip_triangle_one_clipped_vertex_case_3);
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = clipping_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);

    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
