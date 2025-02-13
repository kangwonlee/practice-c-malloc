#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <jansson.h> // Include Jansson
#include "pointers.h" // Include your header
#include <string.h>
#include <stdlib.h>

// --- Test Cases ---

// Test case 1: Successful allocation
static void test_allocate_integer_success(void **state) {
    int *ptr = allocate_integer(42);
    assert_non_null(ptr);
    assert_int_equal(*ptr, 42);
    free(ptr); // Clean up!  Important for avoiding memory leaks during testing.
}

// Test case 2: Allocation failure (mocked)
static void test_allocate_integer_failure(void **state) {
    // Mock malloc to return NULL, simulating allocation failure.
    will_return(__wrap_malloc, 0); // Tell CMocka to make the WRAPPED malloc return 0
    int *ptr = allocate_integer(123);
    assert_null(ptr);
}

// Test case 3: Deallocation
static void test_deallocate_integer(void **state) {
    int *ptr = malloc(sizeof(int)); // Allocate directly for this test
    *ptr = 99;
    deallocate_integer(ptr);
    // Ideally, you'd check for a double-free error, but that's
    // tricky to do reliably in a portable way.  Valgrind is best for this.
}

// --- malloc wrapper for mocking ---

// This is crucial for mocking malloc.  The linker will use this
// version *instead* of the real malloc during testing.
void *__wrap_malloc(size_t size) {
    // check_expected() is how CMocka verifies parameters passed to mocks.
    // We don't need to check the size in this simple example,
    // but it's good practice.
    check_expected(size);
    return (void *)mock(); // mock() returns the value set by will_return()
}

// --- JSON Report Generation (Corrected) ---

// Structure to hold test results
typedef struct {
    const char *name;
    int status;  // 0 for pass, non-zero for fail
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

// Wrapper function to capture test results
static int test_wrapper(void **state, const struct CMUnitTest *test) {
    int result = test->test_func(state); // Call the actual test function
    TestResult *test_result = (TestResult *)*state;
    test_result->status = result; // Store the result
    return result;
}


int main(void) {
    // Array to store the results.  MUST be the same size as the `tests` array.
    TestResult test_results[3];

      const struct CMUnitTest tests[] = {
        cmocka_unit_test_prestate(test_allocate_integer_success, &test_results[0]),
        cmocka_unit_test_prestate(test_allocate_integer_failure,  &test_results[1]),
        cmocka_unit_test_prestate(test_deallocate_integer,       &test_results[2]),
    };

    // Set test names in our result array *before* running tests.
    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
    {
        test_results[i].name = tests[i].name;
    }

    // Wrap the tests
    struct CMUnitTest wrapped_tests[3];
      for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
    {
        wrapped_tests[i] = tests[i];
        wrapped_tests[i].test_func = test_wrapper;
    }


    int num_tests_run = cmocka_run_group_tests(wrapped_tests, NULL, NULL);

    generate_json_report(test_results, sizeof(test_results) / sizeof(test_results[0]));

    return num_tests_run;
}
