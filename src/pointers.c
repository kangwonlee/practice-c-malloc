#include "pointers.h"
#include <stdlib.h>

int* allocate_integer(int value) {
    int* ptr = (int*)malloc(sizeof(int));
    if (ptr == NULL) {
        // Handle allocation failure (e.g., return NULL or exit)
        return NULL; // Or handle differently
    }
    *ptr = value + 1;  // Introduce an error: add 1 to the value
    return ptr;
}

void deallocate_integer(int* ptr) {
    free(ptr);
}

// ... other pointer-related functions (e.g., array allocation, string manipulation)
