#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "pointers.h"

// Test that allocate_integer() returns a valid pointer.
static void test_allocate_integer_valid_pointer(void **state) {
    int *ptr = allocate_integer(10);
    assert_non_null(ptr);
    free(ptr);
}

// Test that allocate_integer() allocates the correct amount of memory.
static void test_allocate_integer_correct_size(void **state) {
    int *ptr = allocate_integer(10);
    assert_int_equal(sizeof(int), _msize(ptr));
    free(ptr);
}

// Test that allocate_integer() sets the value of the allocated integer.
static void test_allocate_integer_set_value(void **state) {
    int *ptr = allocate_integer(10);
    assert_int_equal(10, *ptr);
    free(ptr);
}

// Test that deallocate_integer() frees the allocated memory.
static void test_deallocate_integer_frees_memory(void **state) {
    int *ptr = allocate_integer(10);
    deallocate_integer(ptr);
    // Note: It's difficult to directly test that the memory is freed.
    // This test primarily serves as an example of how to use deallocate_integer().
}

int main(void) {
    const struct CMUnitTest tests = {
        cmocka_unit_test(test_allocate_integer_valid_pointer),
        cmocka_unit_test(test_allocate_integer_correct_size),
        cmocka_unit_test(test_allocate_integer_set_value),
        cmocka_unit_test(test_deallocate_integer_frees_memory),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
