// begin src/main.c

#include <stdio.h>
#include "exercise.h"

int main() {
    int* my_int = allocate_integer(10);
    if (my_int == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1; // Indicate an error
    }

    printf("Value at allocated integer: %d\n", *my_int);
    deallocate_integer(my_int);

    return 0; // Success
}

// end src/main.c
