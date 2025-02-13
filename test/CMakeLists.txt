# test/CMakeLists.txt
find_package(CMocka REQUIRED)

# Create a library for your source code
add_library(pointers_lib ${CMAKE_CURRENT_SOURCE_DIR}/../src/pointers.c)
target_include_directories(pointers_lib PUBLIC ${PROJECT_INCLUDE_DIR})

add_executable(my_tests test_pointers.c)

# Link test executable with CMocka, Jansson, and your code.
target_link_libraries(my_tests
    cmocka  # This was already correct, BUT we need it *again* below
    jansson
    pointers_lib
)

# VERY IMPORTANT: Link with cmocka AGAIN, but this time *specifically* for
# the functions that are used outside the test functions themselves (like
# cmocka_test_state_failed). find_package(CMocka) sets CMocka_LIBRARIES.
target_link_libraries(my_tests ${CMocka_LIBRARIES})


# Use the variable defined in the root CMakeLists.txt
target_include_directories(my_tests PRIVATE ${PROJECT_INCLUDE_DIR})

# Add a custom command to run the tests and capture output.
add_test(NAME run_tests COMMAND my_tests)
