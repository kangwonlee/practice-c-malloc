cmake_minimum_required(VERSION 3.10)
project(MyProject C)

# Add Jansson library
include_directories(/usr/local/include/jansson)  # Adjust path as needed
link_directories(/usr/local/lib) # Adjust as needed

# Define the include directory
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Find CMocka
find_package(CMocka REQUIRED)

# Build the shared library
add_library(pointers SHARED src/pointers.c)
target_include_directories(pointers PUBLIC ${PROJECT_INCLUDE_DIR})

# Create the test executable
add_executable(my_tests test/test_pointers.c)
target_link_libraries(my_tests
    cmocka
    jansson
    pointers
    ${CMocka_LIBRARIES}
)
target_include_directories(my_tests PRIVATE
    ${PROJECT_INCLUDE_DIR}
    ${CMocka_INCLUDE_DIRS}
)

# Add a test to run the executable
add_test(NAME run_tests COMMAND my_tests)

# Build the main executable
add_executable(my_program src/main.c src/pointers.c)
target_link_libraries(my_program m)  # Link with the math library if needed
target_include_directories(my_program PRIVATE ${PROJECT_INCLUDE_DIR})
