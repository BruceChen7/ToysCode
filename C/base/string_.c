#include "string_.h"
#include <stdio.h>
#include <string.h>

static void swap(char *a,char *b){
    char temp;
    temp = *a;
    *a = *b;
    *b = temp; 
}

void permute_string(char *str,int from,int to) {
    if(from == to) {
        printf("%s\n",str);
    } else  { 
        int i;
        for(i = from; i <= to ; i++) {
            swap(str+from,str+i);
            permute_string(str,from+1,to);
            swap(str+from ,str+i); 
        }
    }
}
