#ifndef __TOYS_UTILS_H__
#define __TOYS_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#define TOYS_ASSERT(_exp,_msg) do{ \
    if(!(_exp)) \
    {          \
        fprintf(stderr,"Assertion Failed : %s in line %d of %s\n",_msg,__LINE__,__FILE__);\
        abort();\
    }\
}while(0)

#endif
