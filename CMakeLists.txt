cmake_minimum_required(VERSION 3.10)
project(MyProject C)

# Add Jansson library.  You'll need to have Jansson installed.
# This is a simplified example; a real project might use find_package()
# or a more robust method to locate Jansson.
include_directories(/usr/local/include/jansson)  # Adjust path as needed
link_directories(/usr/local/lib) # Adjust as needed

add_subdirectory(src)
add_subdirectory(test)
