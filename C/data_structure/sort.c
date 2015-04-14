#include "sort.h"
#include <stdlib.h>

void swap(int a[],int pos,int another_pos)
{ 
    int temp = a[pos];
    a[pos] = a[another_pos];
    a[another_pos] = temp;
}

void my_quick_sort(int a[], int n)
{ 
    if( n  <= 1)
        return ;

    int pivot = rand() % n;

    //交换哨兵元素到0位置
    swap(a,0,pivot); 

    int i = 1;

    //下一个小于a[0]元素将要存放的位置-1
    int last = 0;

    for(i = 1 ; i < n ; i++)
    {
        if(a[i] < a[0])
        {   
             swap(a,++last,i); 
        }
    }
    swap(a,0,last);

    my_quick_sort(a,last);
    my_quick_sort(a+last+1,n-last-1); 

}
