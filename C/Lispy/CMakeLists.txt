set(CMAKE_C_FLAGS "-std=c99")
include_directories("./")
add_subdirectory(utils)
add_subdirectory(tests)

set(src mpc.c calculate.c utils/utils.h)
add_library(mpc ${src})

add_executable(calculate calculate.c mpc.c)
target_link_libraries(calculate mpc m)
