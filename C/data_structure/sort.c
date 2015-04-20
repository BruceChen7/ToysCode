#include "sort.h"
#include <stdlib.h>
#include <assert.h>

void swap(int a[],int pos,int another_pos)
{ 
    int temp = a[pos];
    a[pos] = a[another_pos];
    a[another_pos] = temp;
}

//快速排序
//使用随机产生哨兵值,然后交换到第一个
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

void my_merge_sort(int a[],int left, int right)
{
    if(left < right)
    {
        int mid =  left + (right-left)/2;

        my_merge_sort(a,left,mid); 
        my_merge_sort(a,mid+1,right);
        my_merge_util(a,left,mid,right); 
    }


}

void my_merge_util(int a[],int left,int mid,int right)
{
    assert(mid >= left);
    assert(right>= mid);

    int left_array_length  = mid -left + 1;
    int right_array_length =right - mid;

    int left_array[left_array_length];
    int right_array[right_array_length];

    int i,j;

    for(i = 0; i < left_array_length ; i++) 
        left_array[i] = a[left+i];

    for(j = 0 ; j < right_array_length ; j++)
        right_array[j] = a[j+1+mid];

    i = 0;
    j = 0;

    //Be careful
    //Here is left
    int k = left;

    while( i < left_array_length && j < right_array_length)
    {
        if(left_array[i] <= right_array[j])
        {
            a[k] = left_array[i];
            i++;
        }
        else 
        {
            a[k] = right_array[j];
            j++;
        }
        k++;
    }

    while( i < left_array_length)
    {
        a[k]  = left_array[i];
        i++;
        k++; 
    }

    while( j < right_array_length)
    {
        a[k] = right_array[j]; 
        j++;
        k++;
    } 


}
