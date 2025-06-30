# begin CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(MyProject C)


set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)


# Build the shared library
add_library(pointers SHARED src/exercise.c)
target_include_directories(pointers PUBLIC ${PROJECT_INCLUDE_DIR})


# Build the main program
add_executable(my_program src/main.c src/exercise.c)
target_link_libraries(my_program m)
target_include_directories(my_program PRIVATE ${PROJECT_INCLUDE_DIR})


# end CMakeLists.txt
