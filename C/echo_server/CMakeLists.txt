add_subdirectory(tests)
file(GLOB echo_server_src "*.c" "*.h")
MESSAGE(${echo_server_src})
add_library(echo_server_lib STATIC ${echo_server_src})
