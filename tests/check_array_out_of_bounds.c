#include <check.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <stdio.h>

void test_assert(bool condition, const char *msg, const char *file, int line);
#define ARRAY_ASSERT(expr, msg) test_assert((expr), "Condition is not met:" msg, __FILE__, __LINE__)
// #define ARRAY_DEBUG // add `-DARRAY_DEBUG` to a cmd line
#include "../array.h"

ARRAY_DEFINE(int);
ARRAY_PTR_DEFINE(int);

#include "./try-catch/try-catch.h"

START_TEST(test_array_out_of_bounds)
{
    ARRAY(int) *my_array;
    
    try {
        my_array = array_new(ARRAY(int));
        int item = ARRAY_GET(my_array, 10);
        (void)item;
    } catch(...) {
        ck_assert(true == true);
    } success {
        ck_assert(true == false);
    }
    array_free(my_array);
}
END_TEST

Suite *array_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("array.h");

    tc_core = tcase_create("Core");
 
    tcase_add_test(tc_core, test_array_out_of_bounds);
    
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

void test_assert(bool condition, const char* msg, const char* file, int line)
{
    (void)msg;
    (void)file;
    (void)line;
    if (!condition) {
        // fprintf(stderr, "Assertion failed: %s\nFile: %s, Line: %d\n", msg, file, line);
        throw();
    }
}


