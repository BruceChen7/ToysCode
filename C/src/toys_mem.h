#ifndef __TOYS_MEM_H__
#define __TOYS_MEM_H__

// Prototypes
void* toys_mem_alloc(long nbytes,const char *file,int line);
void* toys_mem_calloc(long count,long nbytes, const char *file,int line);
void toys_mem_free(void *ptr,const char *flie, int line);
void toys_mem_resize(void *ptr,long nbytes,const char *file,int line);

// Macro 
#define TOYS_AOLLOC(nbytes) \
	toys_mem_alloc((nbytes),__FILE__,__LINE__)

#define TOYS_CALLOC(count,nbytes) \
	toys_mem_calloc((count),(nbytes),__FILE__,__LINE__) 

#define TOYS_FREE(ptr) do                \
{                                        \
	toys_mem_free(ptr,__FILE__,__LINE__);\
	ptr = 0;                             \
}while(0)	

#define RESIZE(ptr,nbytes) do             \
{                                        \
	ptr = toys_mem_resize(ptr,nbytes,__FILE__,__LINE__); \
}while(0)
#endif
