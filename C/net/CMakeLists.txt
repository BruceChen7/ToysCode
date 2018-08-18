add_subdirectory(tests)
set(NetSrc
    echo_client.c
    echo_server.c
   )
add_library(net ${NetSrc})
