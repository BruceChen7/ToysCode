#ifndef __SORT_H__
#define __SORT_H__

void my_quick_sort(int a[],int n);

//used by my_merge_sort
void my_merge_util(int a[],int left,int mid,int right);
void my_merge_sort(int a[],int left, int right);

#endif
