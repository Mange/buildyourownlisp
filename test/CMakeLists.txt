enable_testing()

find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CHECK_LIBRARIES})

include_directories(. ../src)

add_executable(test_parser test_parser.c ../vendor/mpc.c)
target_link_libraries(test_parser ${LIBS})
add_test(test_parser ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_parser)
