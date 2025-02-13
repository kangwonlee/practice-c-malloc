#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <jansson.h>
#include "pointers.h"
#include <string.h>
#include <stdlib.h>

// --- Test Cases ---

static void test_allocate_integer_success(void **state) {
    int *ptr = allocate_integer(42);
    assert_non_null(ptr);
    assert_int_equal(*ptr, 42);
    free(ptr);
}

static void test_allocate_integer_failure(void **state) {
    will_return(__wrap_malloc, 0);
    int *ptr = allocate_integer(123);
    assert_null(ptr);
}

static void test_deallocate_integer(void **state) {
    int *ptr = malloc(sizeof(int));
    *ptr = 99;
    deallocate_integer(ptr);
}

// --- malloc wrapper for mocking ---
void *__wrap_malloc(size_t size) {
    check_expected(size);
    return (void *)mock();
}

// --- JSON Report Generation ---

typedef struct {
    const char *name;
    int status;
} TestResult;

void generate_json_report(TestResult *results, size_t num_tests) {
    json_t *root = json_object();
    json_t *json_results = json_array();

    for (size_t i = 0; i < num_tests; i++) {
        json_t *test_result = json_object();
        json_object_set_new(test_result, "name", json_string(results[i].name));
        json_object_set_new(test_result, "status", json_string(results[i].status == 0 ? "passed" : "failed"));
        json_array_append_new(json_results, test_result);
    }

    json_object_set_new(root, "results", json_results);
    char *json_str = json_dumps(root, JSON_INDENT(4));
    printf("%s\n", json_str);
    free(json_str);
    json_decref(root);
}

// Wrapper function (Corrected Signature)
static void test_wrapper(void **state) {
    TestResult *test_result = (TestResult *)*state;
    int result;

    // Find the original test function based on the name
    const struct CMUnitTest *tests[] = {
        cmocka_unit_test(test_allocate_integer_success),
        cmocka_unit_test(test_allocate_integer_failure),
        cmocka_unit_test(test_deallocate_integer),
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    CMUnitTestFunction original_test_func = NULL;

     for (size_t i = 0; i < num_tests; i++) {
        if (strcmp(tests[i]->name, test_result->name) == 0) {
            original_test_func = tests[i]->test_func;
            break;
        }
    }

    if (original_test_func) {
        result = original_test_func(state); // Call original with correct signature
    }
    else
    {
        result = -1; //Indicate that the test was not found.
    }
    test_result->status = result;
}

int main(void) {
    TestResult test_results[3];

    const struct CMUnitTest tests[] = {
        cmocka_unit_test_prestate(test_allocate_integer_success, &test_results[0]),
        cmocka_unit_test_prestate(test_allocate_integer_failure,  &test_results[1]),
        cmocka_unit_test_prestate(test_deallocate_integer,       &test_results[2]),
    };

    // Set test names
    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        test_results[i].name = tests[i].name;
    }
   
    int num_tests_run = cmocka_run_group_tests(tests, NULL, NULL);

    generate_json_report(test_results, sizeof(test_results) / sizeof(test_results[0]));

    return num_tests_run;
}
