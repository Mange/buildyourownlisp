include_directories(.)
include_directories(../vendor)
add_executable(lispy main.c parser.c ../vendor/mpc.c)
target_link_libraries(lispy ${LIBS} edit)
