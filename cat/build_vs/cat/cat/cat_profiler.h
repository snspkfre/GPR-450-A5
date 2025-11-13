#pragma once

#include "cat/cat_platform.h"
#include <stdio.h>
#include <string.h>

cat_interface_begin;

typedef struct
{
	int64_t* values;
	int index;
	int header;
	int footer;
	int size;
} RingBuffer;

void RingBufferInit(RingBuffer* buffer, int size);
void RingBufferClean(RingBuffer* buffer);
void RingBufferInsert(RingBuffer* buffer, int64_t value);
void RingBufferClear(RingBuffer* buffer);
double RingBufferAverage(RingBuffer* buffer);
void RunProfilerTests(void);

cat_interface_end;
