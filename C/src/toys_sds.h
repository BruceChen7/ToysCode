#ifndef  __TOYS_SDS_H_
#define  __TOYS_SDS_H_

#include <sys/types.h>
#include <stdarg.h>

typedef  char* sds;

struct toys_sds_hdr {
	//the length of the c-style string 
	unsigned int len;
	// the free space which can be used
	unsigned int free;
	char buf[];
};

//creat a new sds string with the content specified by the init poninter and init_len 
sds toys_sds_new_len(const void *init ,size_t init_len);

//create a new sds string which use init c-style string 
sds toys_sds_new(const char *init);

//create a empty sds
sds toys_sds_empty(void);

//obtain the length of sds 
size_t toys_sds_len(const sds s);

sds toys_sds_dup(const sds s); 

// free the space 
void toys_sds_free(sds s);

size_t toys_sds_avail(const sds s); 

//concatenation of two sds
sds toys_sds_cat(sds s,const char  *t);

sds  toys_sds_free_splitres(sds *tokens, int count);

void toys_sds_toupper(sds s); 
void toys_sds_tolower(sds s);
//free the space which s takes up include the len and free member
void toys_sds_free(sds s);
void toys_sds_update_len(sds s);


void toys_sds_clear(sds s);

// compare two sds string
int  toys_sds_cmp(const sds s1,const sds s2); 
sds toys_sds_map_chars(sds s,const char *from, const char *to,size_t set_len); 
sds toys_sds_join(char **argv,int argc,char *sep); 

#endif

