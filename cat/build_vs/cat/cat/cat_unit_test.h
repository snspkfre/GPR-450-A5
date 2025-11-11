#pragma once

#include "cat/cat_platform.h"
#include <stdio.h>
#include <string.h>

cat_interface_begin;

int dotProduct(int vec1[3], int vec2[3]) { return (vec1[0] * vec2[0]) + (vec1[1] * vec2[1]) + (vec1[2] * vec2[2]); }
void runTests(const char* filePath);

/*typedef testFunc*/ int(*func)(int*, int*) = dotProduct;//declaring a function

int* temp1, temp2;
void brug()
{
	int temp = func(temp1, temp2);//how to call a function pointer
}
cat_interface_end;
