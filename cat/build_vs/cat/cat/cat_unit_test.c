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

float* vec3fProj(vec3f v_out, const vec3f v1, const vec3f v2)
{
	float v_temp = (dotProduct(v2, v1) / dotProduct(v1, v1));
	v_out[0] = v1[0] * v_temp;
	v_out[1] = v1[1] * v_temp;
	v_out[2] = v1[2] * v_temp;

	return v_out;
}

float* vec3fAdd(vec3f v_out, const vec3f v1, const vec3f v2)
{
	v_out[0] = v1[0] + v2[0];
	v_out[1] = v1[1] + v2[1];
	v_out[2] = v1[2] + v2[2];

	return v_out;
}

float* componentMult(vec3f v_out, const vec3f v1, const float scalar)
{
	for(int i = 0; i <= 2; i++)
		v_out[i] = v1[i] * scalar;

	return v_out;
}


float execTest_f_v3f_v3f(test_f_vec3f_vec3f func, const vec3f v1, const vec3f v2)
{
	return (*func)(v1, v2);
}

float* execTest_fp_v3f_v3f_v3f(test_fp_vec3f_vec3f_vec3f func, vec3f v_out, const vec3f v1, const vec3f v2)
{
	return (*func)(v_out, v1, v2);
}

float* execTest_fp_v3f_v3f_f(test_fp_vec3f_vec3f_f func, vec3f v_out, const vec3f v1, const float scalar)
{
	return (*func)(v_out, v1, scalar);
}

void runUnitTests(void)
{

	vec3f v_out, v1 = { 1, 0, 0 }, v2 = { 0, 1, 0 };
	float scalar = 1;
	
	float expD = 0;
	test_f_vec3f_vec3f dTest = dotProduct;
	float dTestResult = ExecTest(dTest, v1, v2);
	expD == dTestResult ? printf("\nDot test Pass") : printf("\nDot test Fail");//Do something else with this

	vec3f expC = { 0, 0, 1 };
	test_fp_vec3f_vec3f_vec3f cTest = crossProduct;

	//test_data data;
	//data.func = &cTest;

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

	vec3f expP = { 0, 0, 0 };
	test_fp_vec3f_vec3f_vec3f pTest = vec3fProj;
	float* pTestResult = ExecTest(pTest, v_out, v1, v2);
	for (int i = 0; i < 3; i++)
	{
		if (expP[i] != pTestResult[i])
		{
			printf("\nProjection test Fail");
			break;
		}
		if (i == 2)
		{
			printf("\nProjection test Pass");
		}
	}

	vec3f expA = { 1, 1, 0 };
	test_fp_vec3f_vec3f_vec3f aTest = vec3fAdd;
	float* aTestResult = ExecTest(aTest, v_out, v1, v2);
	for (int i = 0; i < 3; i++)
	{
		if (expA[i] != aTestResult[i])
		{
			printf("\nAddition test Fail");
			break;
		}
		if (i == 2)
		{
			printf("\nAddition test Pass");
		}
	}

	vec3f expCM = { 1, 0, 0 };
	test_fp_vec3f_vec3f_f cmTest = componentMult;
	float* cmTestResult = ExecTest(cmTest, v_out, v1, scalar);
	for (int i = 0; i < 3; i++)
	{
		if (expCM[i] != cmTestResult[i])
		{
			printf("\nComponent multiplication test Fail");
			break;
		}
		if (i == 2)
		{
			printf("\nComponent multiplication test Pass");
		}
	}


	//abstract this function
	//test multiple values
}
