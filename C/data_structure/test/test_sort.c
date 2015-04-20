#include <criterion/criterion.h>
#include "../sort.h"
#include <stdio.h>

Test(Sort,my_quick_sort)
{
    int a[] = {3,2,1};

    my_quick_sort(a,sizeof(a)/sizeof(int));
    
    assert_eq(a[0],1); 
    assert_eq(a[1],2);
    assert_eq(a[2],3);
}


Test(Sort,my_merge_sort)
{
    int a[]  = {4,5,6,7,1};
    int last_elem_pos = sizeof(a) / sizeof(int) - 1;
    assert_eq(last_elem_pos,4);
    my_merge_sort(a,0,last_elem_pos);
    assert_eq(a[0],1);
    assert_eq(a[1],4);
    assert_eq(a[2],5);
    assert_eq(a[3],6);
    assert_eq(a[4],7);
}
