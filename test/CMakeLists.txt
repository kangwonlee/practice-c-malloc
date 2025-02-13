# Find CMocka.  You'll need CMocka installed.
find_package(CMocka REQUIRED)

add_executable(my_tests test_pointers.c)

# Link test executable with CMocka, Jansson, and your code.
target_link_libraries(my_tests
    cmocka
    jansson
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/pointers.c  # Link directly to source
)

# Add a custom command to run the tests and capture output.
add_test(NAME run_tests COMMAND my_tests)
