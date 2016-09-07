add_subdirectory(tests) 

set(BaseSrc
    toys_sds.c
    toys_list.c
    toys_mem.c
    sort.c
    graph.c
    )

add_library(base ${BaseSrc})


