cmake_minimum_required (VERSION 2.6)

project (buildyourownlisp)

# Make output dir
file (MAKE_DIRECTORY bin)

add_executable(bin/lispy src/main.c src/parsing.c vendor/mpc.c)
target_link_libraries(bin/lispy edit m)
