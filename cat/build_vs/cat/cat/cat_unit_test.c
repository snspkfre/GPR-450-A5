#include "cat_unit_test.h"

float dotProduct(const vec3f v1, const vec3f v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

float* crossProduct(vec3f v_out, const vec3f v1, const vec3f v2)
{
	v_out[0] = v1[1] * v2[2] - v1[2] * v2[1];
	v_out[1] = v1[2] * v2[0] - v1[0] * v2[2];
	v_out[2] = v1[0] * v2[1] - v1[1] * v2[0];

	return v_out;
}

float execTest_f_v3f_v3f(testf_vec3f_vec3f func, const vec3f v1, const vec3f v2)
{
	return (*func)(v1, v2);
}

float* execTest_fp_v3f_v3f_v3f(testfp_vec3f_vec3f_vec3f func, vec3f v_out, const vec3f v1, const vec3f v2)
{
	return (*func)(v_out, v1, v2);
}

void runUnitTests(void)
{
	vec3f v_out, v1 = { 1, 0, 0 }, v2 = { 0, 1, 0 };
	
	float expD = 0;
	testf_vec3f_vec3f dTest = dotProduct;
	InitTest(&dTest);
	float dTestResult = ExecTest(dTest, v1, v2);
	expD == dTestResult ? printf("\nDot test Pass") : printf("\nDot test Fail");//Do something else with this
	CleanTest(&dTest);

	vec3f expC = { 0, 0, 1 };
	testfp_vec3f_vec3f_vec3f cTest = crossProduct;
	InitTest(&cTest);
	float* cTestResult = ExecTest(cTest, v_out, v1, v2);
	for (int i = 0; i < 3; i++)
	{
		if (expC[i] != cTestResult[i])
		{
			printf("\nCross test Fail");
			break;
		}
		if (i == 2)
		{
			printf("\nCross test Pass");
		}
	}

	//printf("\n%f", ExecTest(cTest, v_out, v1, v2)[2]);
	CleanTest(&cTest);

	//need to do vector projection and add more tests
}
