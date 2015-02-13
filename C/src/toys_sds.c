#include "toys_sds.h" 

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h> 
#define SDS_HDR_SIZE sizeof(struct toys_sds_hdr)
/* #define CHECK_SIZE(X) do{ }while(0) */
/* #define  */

size_t toys_sds_len(const sds s)
{
	struct toys_sds_hdr *sh = (void *)(s-SDS_HDR_SIZE);
	return sh->len ; 
}


//creat a new sds string which content is specified with init
sds toys_sds_new_len(const void *init,size_t init_len)
{
	struct toys_sds_hdr *new_sds  = NULL;

	if(init)
	{
		new_sds = malloc(SDS_HDR_SIZE+init_len + 1); 
	}
	else 
	{
		new_sds = calloc(SDS_HDR_SIZE + init_len + 1,1);
	}

	if(new_sds == NULL)
		return NULL;

	new_sds->len = init_len;
	new_sds->free = 0;
	
	if(init_len && init)
	{
		memcpy(new_sds->buf,init,init_len);
		new_sds->buf[init_len] 	= '\0';
	}
	return (char *)new_sds->buf; 
}


sds toys_sds_new(const char *init)
{

}

sds toys_sds_empty(void)
{

}

sds toys_sds_cat(sds s,const char *t)
{

}

void toys_sds_clear(sds s)
{

}

int toys_sds_cmp(const sds s1,const sds s2)
{



}

sds toys_sds_join(char **argv,int argc,char *sep)
{

}


