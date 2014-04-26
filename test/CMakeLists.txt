enable_testing()

find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CHECK_LIBRARIES})

include_directories(. ../src)

add_executable(parser_test parser_test.c ../vendor/mpc.c)
target_link_libraries(parser_test ${LIBS})
add_test(parser_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/parser_test)

add_executable(eval_test eval_test.c ../vendor/mpc.c)
target_link_libraries(eval_test ${LIBS})
add_test(eval_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/eval_test)
