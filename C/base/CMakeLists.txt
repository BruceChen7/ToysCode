add_subdirectory(tests) 

set(BaseSrc
    toys_sds.c
    toys_list.c
    toys_mem.c
    sort.c
    )

add_library(base ${BaseSrc})


