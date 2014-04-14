include_directories(.)
include_directories(../vendor)
add_executable(lispy main.c parsing.c ../vendor/mpc.c)
target_link_libraries(lispy edit m)
