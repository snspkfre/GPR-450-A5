#pragma once

#include "cat/cat_platform.h"
#include <stdio.h>
#include <string.h>

cat_interface_begin;

typedef float vec3f[3];
typedef float (*test_f_vec3f_vec3f)(const vec3f, const vec3f);
typedef float* (*test_fp_vec3f_vec3f_vec3f)(vec3f, const vec3f, const vec3f);

float dotProduct(const vec3f v1, const vec3f v2);
float* crossProduct(vec3f v_out, const vec3f v1, const vec3f v2);
float* vec3fProj(vec3f v_out, const vec3f v1, const vec3f v2);
float* vec3fAdd(vec3f v_out, const vec3f v1, const vec3f v2);
//scalar vector / component multiplication


void initTest_f_v3f_v3f(test_f_vec3f_vec3f* funcPtr)
{
    unused(funcPtr);
}

void initTest_fp_v3f_v3f_v3f(test_fp_vec3f_vec3f_vec3f* funcPtr)
{
    unused(funcPtr);
}

float execTest_f_v3f_v3f(test_f_vec3f_vec3f, const vec3f, const vec3f);
float* execTest_fp_v3f_v3f_v3f(test_fp_vec3f_vec3f_vec3f, vec3f, const vec3f, const vec3f);

void cleanTest_f_v3f_v3f(test_f_vec3f_vec3f* funcPtr)
{
    unused(funcPtr);
}

void cleanTest_fp_v3f_v3f_v3f(test_fp_vec3f_vec3f_vec3f* funcPtr)
{
    unused(funcPtr);
}

#define InitTest(X) _Generic((X),						    \
                test_f_vec3f_vec3f*: initTest_f_v3f_v3f,		\
         test_fp_vec3f_vec3f_vec3f*: initTest_fp_v3f_v3f_v3f  \
              )(X)

#define ExecTest(X, ...) _Generic((X),						\
                test_f_vec3f_vec3f: execTest_f_v3f_v3f,		\
         test_fp_vec3f_vec3f_vec3f: execTest_fp_v3f_v3f_v3f  \
              )(X, __VA_ARGS__)

#define CleanTest(X) _Generic((X),						    \
                test_f_vec3f_vec3f*: cleanTest_f_v3f_v3f,		\
         test_fp_vec3f_vec3f_vec3f*: cleanTest_fp_v3f_v3f_v3f \
              )(X)

void runUnitTests(void);

cat_interface_end;
