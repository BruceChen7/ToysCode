#include <check.h>		
#include "../src/toys_sds.h"

START_TEST(test_toys_sds_create)
{
	/* printf("Hello world"); */
	


}
END_TEST

Suite* sds_suit(void)
{

	Suite *s = suite_create("Toy sds testing ");
	TCase* tc_core = tcase_create("core case");
	tcase_add_test(tc_core,test_toys_sds_create); 
	suite_add_tcase(s,tc_core);
	return s; 
}

int main()
{
	int number_failed ;
	// the new suit to be test
	Suite* s =  sds_suit(); 
	SRunner*  sr = srunner_create(s);

	srunner_run_all(sr,CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	/* printf("the test number for failed is %d",) */
	return 0; 
}
