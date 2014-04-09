cmake_minimum_required (VERSION 2.6)

project (buildyourownlisp)

file (MAKE_DIRECTORY bin)

add_executable(bin/lispy src/main.c)
