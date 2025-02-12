cmake_minimum_required(VERSION 3.10)

project(c-pointers-dynamic-memory)

set(CMAKE_C_STANDARD 11)

# Find Criterion (using pkg-config) - preferred and more robust
find_package(PkgConfig REQUIRED)  # Find pkg-config first
pkg_check_modules(Criterion REQUIRED criterion) # Use pkg_check_modules

# Create the library
add_library(pointers src/pointers.c)
target_include_directories(pointers PUBLIC include)

# Create the tests
add_executable(test_pointers test/test_pointers.c)
target_link_libraries(test_pointers pointers ${Criterion_LIBRARIES}) # Link using the target

# Example executable (optional)
add_executable(example src/main.c)
target_link_libraries(example pointers)
