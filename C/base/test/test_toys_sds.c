#include "../toys_sds.h"
#include <string.h> 
#include <stdio.h>
#include <criterion/criterion.h>

Test(TestToysSds,Basic)
{
	sds test_string= "Hello world";

	//create the first 2 word string from the test_string 
	sds y =  toys_sds_new_len(test_string,2); 
	assert_strings_eq("He",y);

	//test for toys_sds_len
	size_t len = toys_sds_len(y);
	assert_eq(len,2);

	//test for toys_sds_new
	sds x = toys_sds_new(test_string);
	assert_strings_eq(test_string,x);
	assert_eq(strlen(test_string),toys_sds_len(x));

	//test for toys_sds_empty
	assert_strings_eq("",toys_sds_empty()); 

	//test for toys_sds_toupper 
	toys_sds_toupper(x);
	assert_strings_eq(x,"HELLO WORLD");

	//test for toys_sds_tolower
	toys_sds_tolower(x);
	assert_strings_eq(x,"hello world"); 

	//test for toys_sds_avail
	assert_eq(toys_sds_avail(x),0);

	//test for toys_sds_expand_size
	//the size of "hello world" is 11
	//then we expand the size of the new_string2 to (11+8)*2
	//now the available free space is (11+8)*2 -11,which is 27
	assert_eq(toys_sds_len(x),11);
	x = toys_sds_expand_size(x,8);
	assert_eq(toys_sds_avail(x),27);

	//test for toys_sds_cat
	y = toys_sds_new(" Bruce Chen");
	x = toys_sds_cat_len(x,y,toys_sds_len(y));
	assert_strings_eq(x,"hello world Bruce Chen"); 

	//to ensure y has enough space 
	y = toys_sds_expand_size(y,14);
	assert_strings_eq(y," Bruce Chen");

	//when there is enough space 
	//x is copied into y
	toys_sds_cpy(y,x);
	assert_strings_eq(y,x);
	
	//when there is not enough space
	//the resturned sds is the copied x
	y  = toys_sds_empty();
	y = toys_sds_cpy(y,x);
	assert_strings_eq(y,x); 

}

Test(ADVANCED_SDS ,ADVANCED) 
{
	sds x = toys_sds_new("foo");
	sds y = toys_sds_cat_snprintf(x,"%d %d %d",1,2,3);
	assert_strings_eq(y,"foo1 2 3");
	assert_strings_eq(x,"foo1 2 3");
	
	x = toys_sds_empty();
	y = toys_sds_cat_snprintf(x,"%s %s %s","foo","bar","chen"); 
	assert_strings_eq(x,"foo bar chen");
	assert_strings_eq(y,"foo bar chen"); 

}

