//author: liv and victor

#pragma once

#include "cat/cat_platform.h"
#include <stdio.h>
#include <string.h>

cat_interface_begin;

typedef float vec3f[3];
typedef float (*test_f_vec3f_vec3f)(const vec3f, const vec3f);
typedef float* (*test_fp_vec3f_vec3f_vec3f)(vec3f, const vec3f, const vec3f);
typedef float* (*test_fp_vec3f_vec3f_f)(vec3f, const vec3f, const float);

float dotProduct(const vec3f v1, const vec3f v2);
float* crossProduct(vec3f v_out, const vec3f v1, const vec3f v2);
float* vec3fProj(vec3f v_out, const vec3f v1, const vec3f v2);
float* vec3fAdd(vec3f v_out, const vec3f v1, const vec3f v2);
float* componentMult(vec3f v_out, const vec3f v1, const float scalar);


float execTest_f_v3f_v3f(test_f_vec3f_vec3f, const vec3f, const vec3f);
float* execTest_fp_v3f_v3f_v3f(test_fp_vec3f_vec3f_vec3f, vec3f, const vec3f, const vec3f);
float* execTest_fp_v3f_v3f_f(test_fp_vec3f_vec3f_f, vec3f, const vec3f, const float);


#define ExecTest(X, ...) _Generic((X),						\
                test_f_vec3f_vec3f: execTest_f_v3f_v3f,		\
         test_fp_vec3f_vec3f_vec3f: execTest_fp_v3f_v3f_v3f,  \
         test_fp_vec3f_vec3f_f: execTest_fp_v3f_v3f_f  \
              )(X, __VA_ARGS__)

void runUnitTests(void);

typedef struct {
    void* func; //function to be tested
    //void* exp; //expected result
} test_data;

cat_interface_end;
