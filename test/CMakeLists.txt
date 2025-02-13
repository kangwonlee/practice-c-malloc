# test/CMakeLists.txt
find_package(CMocka REQUIRED)

# Create a library for your source code
add_library(pointers_lib ${CMAKE_CURRENT_SOURCE_DIR}/../src/pointers.c)
target_include_directories(pointers_lib PUBLIC ${PROJECT_INCLUDE_DIR})

add_executable(my_tests test_pointers.c)

# Link test executable with CMocka, Jansson, and your code.
target_link_libraries(my_tests
    cmocka
    jansson
    pointers_lib
)

# Use the variable defined in the root CMakeLists.txt
target_include_directories(my_tests PRIVATE ${PROJECT_INCLUDE_DIR})

# Add a custom command to run the tests and capture output.
add_test(NAME run_tests COMMAND my_tests)
