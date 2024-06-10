#include <check.h>
#include <stdlib.h>

// #define ARRAY_DEBUG // add `-DARRAY_DEBUG` to a cmd line
#include "../array.h"

ARRAY_DEFINE(int);
ARRAY_PTR_DEFINE(int);

START_TEST(test_array_new)
{
    ARRAY(int) *int_array = array_new(ARRAY(int));

    ck_assert_ptr_nonnull(int_array);
    ck_assert_int_eq(int_array->capacity, ARRAY_INIT_CAP);
    ck_assert_int_eq(int_array->count, 0);
    ck_assert_ptr_nonnull(int_array->items);

    array_free(int_array);
}
END_TEST

START_TEST(test_array_new_with_cap)
{
    ARRAY(int) *int_array = array_new_with_cap(ARRAY(int), 10);

    ck_assert_ptr_nonnull(int_array);
    ck_assert_ptr_nonnull(int_array->items);
    ck_assert_int_eq(int_array->capacity, 10);
    ck_assert_int_eq(ARRAY_LEN(int_array), 0);

    array_free(int_array);
}
END_TEST

START_TEST(test_array_append)
{
    ARRAY(int) *arr = array_new(ARRAY(int));
    array_append(arr, 10);
    array_append(arr, 20);
    array_append(arr, 30);

    ck_assert_int_eq(ARRAY_LEN(arr), 3);
    ck_assert_int_eq(ARRAY_GET(arr, 0), 10);
    ck_assert_int_eq(ARRAY_GET(arr, 1), 20);
    ck_assert_int_eq(ARRAY_GET(arr, 2), 30);

    array_free(arr);
}
END_TEST

START_TEST(test_array_unset)
{
    ARRAY(int) *arr = array_new(ARRAY(int));

    array_append(arr, 10);
    array_append(arr, 20);
    array_append(arr, 30);
    array_unset(arr, 1);

    ck_assert_int_eq(ARRAY_LEN(arr), 2);
    ck_assert_int_eq(ARRAY_GET(arr, 0), 10);
    ck_assert_int_eq(ARRAY_GET(arr, 1), 30);

    array_free(arr);
}
END_TEST

START_TEST(test_array_compact)
{
    ARRAY(int) *arr = array_new(ARRAY(int));
    for (int i = 0; i < 16; ++i) {
        array_append(arr, i);
    }

    ck_assert_int_eq(ARRAY_LEN(arr), 16);
    ck_assert_int_eq(arr->capacity, 32);

    for (int i = 0; i < 8; ++i) {
        array_unset(arr, 0);
    }

    ck_assert_int_eq(ARRAY_LEN(arr), 8);
    array_compact(arr);
    ck_assert_int_eq(arr->capacity, 8);

    array_free(arr);
}
END_TEST

START_TEST(test_array_ptr_append)
{
    ARRAY_PTR(int) *arr = array_new(ARRAY_PTR(int));

    int *item1 = ARRAY_MALLOC(sizeof(int));
    int *item2 = ARRAY_MALLOC(sizeof(int));
    *item1 = 10;
    *item2 = 20;

    array_ptr_append(arr, item1);
    array_ptr_append(arr, item2);

    ck_assert_int_eq(ARRAY_LEN(arr), 2);
    ck_assert_int_eq(*ARRAY_PTR_GET(arr, 0), 10);
    ck_assert_int_eq(*ARRAY_PTR_GET(arr, 1), 20);

    array_ptr_free(arr);
}
END_TEST

Suite *array_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("array.h");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_array_new);
    tcase_add_test(tc_core, test_array_new_with_cap);
    tcase_add_test(tc_core, test_array_append);
    tcase_add_test(tc_core, test_array_unset);
    tcase_add_test(tc_core, test_array_compact);
    tcase_add_test(tc_core, test_array_ptr_append);
    
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed = 0;
    Suite *s;
    SRunner *sr;

    s = array_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

