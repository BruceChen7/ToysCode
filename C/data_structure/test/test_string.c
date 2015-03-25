#include <criterion/criterion.h>
#include "../string_.h"

Test(StringAlgorithm, PermutationOfString)
{
    char a[] = "ABC";
    permute_string(a,0,2);

}
