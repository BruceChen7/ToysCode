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
