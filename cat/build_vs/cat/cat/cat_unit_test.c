#include "cat_unit_test.h"

float execTest_f_v3f_v3f(testf_vec3f_vec3f func, const vec3f v1, const vec3f v2)
{
	return (*func)(v1, v2);
}

float* execTest_fp_v3f_v3f_v3f(testfp_vec3f_vec3f_vec3f func, vec3f v_out, const vec3f v1, const vec3f v2)
{
	return (*func)(v_out, v1, v2);
}

void runTests()
{
	vec3f v_out, v1 = { 1, 0, 0 }, v2 = { 0, 1, 0 };
	
	testf_vec3f_vec3f dTest = dotProduct;
	InitTest(dTest);
	ExecTest(dTest, v1, v2);//returns output so check if its expected
	CleanTest(dTest);

	testfp_vec3f_vec3f_vec3f cTest = crossProduct;
	InitTest(cTest);
	ExecTest(cTest, v_out, v1, v2);//returns output so check if its expected
	CleanTest(cTest);
}
