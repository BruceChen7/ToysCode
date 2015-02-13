#include "toys_sds.h" 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h> 
#define SDS_HDR_SIZE sizeof(struct toys_sds_hdr)
/* #define CHECK_SIZE(X) do{ }while(0) */
/* #define  */

// obtain the length of sds 
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
	size_t init_len = (init == NULL)?0:strlen(init);
	return toys_sds_new_len(init,strlen(init));

}

//creat an empty sds 
sds toys_sds_empty(void)
{
	return toys_sds_new_len("",0); 
}


void toys_sds_free(sds s)
{
	struct toys_sds_hdr *sh  = (void *)(s-SDS_HDR_SIZE);
	free(sh);
}

size_t toys_sds_avail(const sds s)
{
	struct toys_sds_hdr* sh = (void *)(s-SDS_HDR_SIZE);
	return sh->free;	
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

void toys_sds_toupper(sds s)
{
	int i ;
	int len = toys_sds_len(s);
	for(i = 0 ; i < len ;i++)
		s[i] = toupper(s[i]);
}

void toys_sds_tolower(sds s)
{
	int j ;
	int len = toys_sds_len(s); 
	for( j = 0 ; j < len ; j++)
		s[j] = tolower(s[j]);
}

sds toys_sds_join(char **argv,int argc,char *sep)
{

}



