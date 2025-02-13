# src/CMakeLists.txt

add_executable(my_program main.c pointers.c)
target_link_libraries(my_program m) # Link with the math library if needed.

# Use the variable defined in the root CMakeLists.txt
target_include_directories(my_program PRIVATE ${PROJECT_INCLUDE_DIR})
