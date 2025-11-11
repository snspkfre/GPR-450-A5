#pragma once

#include "cat/cat_platform.h"
#include <stdio.h>
#include <string.h>

cat_interface_begin;

typedef float vec3f[3];
typedef float (*testf_vec3f_vec3f)(const vec3f, const vec3f);
typedef float* (*testfp_vec3f_vec3f_vec3f)(vec3f, const vec3f, const vec3f);

float dotProduct(const vec3f vector1, const vec3f vector2) { return 1.0f; }
float* crossProduct(vec3f result, const vec3f vector1, const vec3f vector2);
//void runTests(const char* filePath);

/*typedef testFunc*/ int(*func)(int*, int*) = dotProduct;//declaring a function pointer
#define testFunction(X) _Generic((X),						\
                testf_vec3f_vec3f: initTest_f_v3f_v3f,		\
         testfp_vec3f_vec3f_vec3f: initTest_fp_v3f_v3f_v3f  \
              )(X)

struct
{
	func*;
	void* expected;
	void* args;
};

int* temp1, temp2;
void brug()
{
	int temp = func(temp1, temp2);//how to call a function pointer
}
cat_interface_end;
