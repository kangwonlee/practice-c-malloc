cmake_minimum_required(VERSION 3.10) # Or higher

project(c-pointers-dynamic-memory)

set(CMAKE_C_STANDARD 11) # Or your preferred standard

# Find Criterion (if using)
find_package(Criterion REQUIRED)

# Create the library
add_library(pointers src/pointers.c)
target_include_directories(pointers PUBLIC include)

# Create the tests
add_executable(test_pointers test/test_pointers.c)
target_link_libraries(test_pointers pointers Criterion::Criterion)

# Example executable
add_executable(example examples/main.c)
target_link_libraries(example pointers)
