#pragma once

#include <stdio.h>
#include <string.h>
#include "cat_unit_test.h"
#include "cat/utility/cat_time.h"//added this include :)

cat_interface_begin;

struct RingBuffer
{
	int index;
	int footer;
	float* values;
	int size;
};

void RingBufferInit(RingBuffer* buffer, int size)
{
	buffer->index = 0;
	buffer->footer = 0;
	buffer->values = (float*) malloc(size * sizeof(float));
	buffer->size = size;
}

void RingBufferClean(RingBuffer* buffer)
{
	free(buffer->values);
	free(buffer);
}

void RingBufferInsert(RingBuffer* buffer, float value)
{
	buffer->values[buffer->index] = value;
	buffer->index = buffer->index == buffer->size ? 0 : buffer->index + 1;
	buffer->footer = buffer->footer > buffer->size ? buffer->size : buffer->footer + 1;
}

float RingBufferAverage(RingBuffer* buffer)
{
	if (buffer->footer == 0)
		return 0.0f;

	float total = 0.0f;
	for (int i = 0; i < buffer->footer; i++)
	{
		total += buffer->values[i];
	}
	return total / buffer->footer;
}

cat_interface_end;
