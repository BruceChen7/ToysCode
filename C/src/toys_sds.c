#include "toys_sds.h" 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h> 

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


sds toys_sds_expand_size(sds s,size_t add_len)
{
	struct toys_sds_hdr* sh, *new_sh;
	sh = (void *)(s-SDS_HDR_SIZE); 

	size_t free_size = toys_sds_avail(s); 

	//nothing to do if there are enough size
	//
	if(free_size >= add_len)
		return s;

	size_t len = toys_sds_len(s);
	size_t new_len = (len+add_len);

	if(new_len < SDS_MAX_PRESIZE)
		new_len *= 2;
	else 
		new_len += SDS_MAX_PRESIZE;

	new_sh = realloc(sh,new_len+SDS_HDR_SIZE+1); 

	if(new_sh == NULL)
		return NULL;

	new_sh->free = new_len - len;
	return new_sh->buf; 
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

sds toys_sds_cat(sds s,const void *t,size_t len)
{ 
	size_t avail_len = toys_sds_avail(s); 
	size_t s_len = toys_sds_len(s);
	struct toys_sds_hdr *sh = (void *)(s-SDS_HDR_SIZE);

	if(avail_len  < len) 
	{
		 s = toys_sds_expand_size(s,len); 
		 if( s == NULL)
			 return NULL;
	}

	memcpy(s+s_len,t,len);

	sh->len = s_len + len;
	sh->free = avail_len - len;
	sh->buf[sh->len] = '\0'; 
	return (sds)sh->buf ;
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
