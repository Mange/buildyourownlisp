cmake_minimum_required (VERSION 2.6)

project (buildyourownlisp)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )

# Make output dir
#file (MAKE_DIRECTORY bin)
add_subdirectory(src)
