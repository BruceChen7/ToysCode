#include "toys_mem.h"
#include "toys_utils.h"
#include <assert.h>
#include <stdlib.h> //used for malloc
void* toys_mem_alloc(long nbytes, const char *file,int line) {
    void *ptr;
    TOYS_ASSERT(nbytes > 0,"the size which is allocated must be larger than 0");
    ptr = malloc(nbytes);

    /* Fix Me by using user-defined exception */
    if(ptr == NULL)
        fprintf(stderr,"Allocation Error in file : %s  line : %d",file,line);
    return ptr;
}


void* toys_mem_calloc(long ncount,long nbytes,const char *file,int line) {
    void *ptr;
    TOYS_ASSERT(ncount>0,"the number of allocated space must be larger than 0");
    TOYS_ASSERT(nbytes>0,"each block's size must be larger than 0");

    ptr = calloc(ncount ,nbytes);

    if(ptr == NULL)
        fprintf(stderr,"Allocation Error in file : %s  line : %d",file,line);
    return ptr;
}

void* toys_mem_resize(void *ptr,long nbytes,const char *file,int line) {
    TOYS_ASSERT(ptr!=NULL, "the pointer can't be null");
    TOYS_ASSERT(nbytes >= 0,"the size which is reallocated must be larger than 0");

    ptr = realloc(ptr,nbytes);

    if(ptr == NULL)
        fprintf(stderr,"Reallocation Error in file : %s  line : %d",file,line);

    return ptr;

}

void toys_mem_free(void *ptr,const char *file,int line)
{
    if(ptr)
        free(ptr);
}
