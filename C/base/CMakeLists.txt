file(GLOB base_src "*.c" "*.h")
add_library(base STATIC  ${base_src})
