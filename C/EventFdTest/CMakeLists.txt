file(GLOB event_fd_test_src "*.c" "*.h")
find_package(Threads REQUIRED)
add_executable(event_fd_test ${event_fd_test_src})
target_link_libraries(event_fd_test Threads::Threads)
