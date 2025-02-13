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

// --- JSON Report Generation ---
// This is a very simplified example. A real-world implementation would
// be more robust and handle errors more gracefully.
void generate_json_report(const struct CMUnitTest *tests, size_t num_tests) {
    json_t *root = json_object();
    json_t *results = json_array();

    for (size_t i = 0; i < num_tests; i++) {
        json_t *test_result = json_object();
        json_object_set_new(test_result, "name", json_string(tests[i].name));

        // Get the test state (passed/failed). This requires some CMocka internals.
        // This part might need adjustments depending on CMocka version.
        // The _cmocka_run_group_tests function sets up the test environment.
        // We need to dig into that to get the result.  This is the trickiest
        // part of the JSON reporting.
        int status = tests[i].function(NULL);  // Simplified way to get result for demonstration

        json_object_set_new(test_result, "status", json_string(status == 0 ? "passed" : "failed"));
        json_array_append_new(results, test_result);
    }

    json_object_set_new(root, "results", results);

    // Dump the JSON to a string and print it (or save to a file)
    char *json_str = json_dumps(root, JSON_INDENT(4)); // Pretty-print
    printf("%s\n", json_str);

    // Clean up
    free(json_str);
    json_decref(root);
}


int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_allocate_integer_success),
        cmocka_unit_test(test_allocate_integer_failure),
        cmocka_unit_test(test_deallocate_integer),
    };

     //Run Tests and get the number of tests that were run.
    int num_tests_run = cmocka_run_group_tests(tests, NULL, NULL);

    //Now that the tests have been executed, the results are accessible.
    // Pass these results into the function which will print them in json format
    generate_json_report(tests, sizeof(tests) / sizeof(tests[0]));

    return num_tests_run;
}