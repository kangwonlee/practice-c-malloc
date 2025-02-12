#include <criterion/criterion.h>
#include "pointers.h"

Test(pointers, allocate_and_deallocate) {
    int* ptr = allocate_integer(42);
    cr_assert_not_null(ptr);
    cr_assert_eq(*ptr, 42);
    deallocate_integer(ptr); // Important: Test deallocation!
}

Test(pointers, allocation_failure) {
  // Simulate allocation failure (more advanced, OS-specific)
  // Or test with very large allocation requests.
  // Example (not completely reliable, OS dependent):
  // size_t huge_size = SIZE_MAX;
  // int* ptr = (int*)malloc(huge_size);
  // cr_assert_null(ptr);

  // A simpler, more portable way to test failure:
  // (Assuming your allocate_integer handles failure gracefully)
  int* ptr = allocate_integer(-1); // Assuming -1 signals an error in your function
  cr_assert_null(ptr);
}

// ... more tests for other functions
