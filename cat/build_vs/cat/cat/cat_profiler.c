//author: victor and annabelle

#include "cat_profiler.h"
#include "cat/utility/cat_time.h"

extern void cat_console_clear(void);

void RingBufferInit(RingBuffer* buffer, int size)
{
	buffer->index = 0;
	buffer->header = 0;
	buffer->footer = 0;
	buffer->size = size;
	buffer->values = (int64_t*)malloc(size * sizeof(int64_t));
	
	if (buffer->values == NULL)
		return;

	for (int i = 0; i < size; i++)
	{
		buffer->values[i] = 0;
	}
}

void RingBufferClean(RingBuffer* buffer)
{
	if (buffer == NULL || buffer->values == NULL)
	{
		printf("clean already null");
		return;
	}

	free(buffer->values);
}

//sets a value at the next index
void RingBufferInsert(RingBuffer* buffer, int64_t value)
{
	buffer->values[buffer->index] = value;
	buffer->index = buffer->index == buffer->size - 1 ? 0 : buffer->index + 1;
	buffer->footer = buffer->footer > buffer->size -1 ? buffer->size : buffer->footer + 1;
}

//sets all ringbuffer param back to zero
void RingBufferClear(RingBuffer* buffer)
{
	buffer->index = 0;
	
	for (int i = 0; i < buffer->footer; i++)
	{
		buffer->values[i] = 0;
	}
	buffer->footer = 0;
}

//finds the average of ringbuffer, excludes inital zero values
double RingBufferAverage(RingBuffer* buffer)
{
	if (buffer->footer == 0)
		return 0;

	int64_t total = 0;
	for (int i = 0; i < buffer->footer; i++)
	{
		total += buffer->values[i];
	}
	return 1.0 * total / buffer->footer;
}

void RunProfilerTests(void)
{
	int size = 1024;
	RingBuffer buffer;
	RingBufferInit(&buffer, size);
	double testOn = 0, testOnLogn = 0, testOsqn = 0;
	int64_t volatile initalTick;
	int64_t volatile lastTick = cat_platform_time();
	int64_t volatile dt = 0;
	int timeLooping = 5000;
	
	cat_console_clear();
	double tps = cat_platform_time_rate();

	//O(log2(n)
	for (int i = 0; i < timeLooping; i++)
	{
		if (&buffer == NULL)
			return;

		initalTick = cat_platform_time();
		dt = initalTick - lastTick;
		lastTick = initalTick;
		RingBufferInsert(&buffer, dt);
		printf("\n%d second average: %f", i, RingBufferAverage(&buffer) / tps);
		testOnLogn += dt;

		for (int j = 1; j < timeLooping; j *= 2)
		{
			unused(j);
		}
	}

	printf("\n\n-----------------------------------------------------------\n");

	RingBufferClear(&buffer);
	lastTick = cat_platform_time();

	//O(n)
	for (int i = 0; i < timeLooping; i++)
	{
		if (&buffer == NULL)
			return;

		initalTick = cat_platform_time();
		dt = initalTick - lastTick;
		lastTick = initalTick;
		RingBufferInsert(&buffer, dt);
		printf("\n%d second average: %f", i, RingBufferAverage(&buffer) / tps);

		for (int j = 0; j < timeLooping; j++)
		{
			unused(j);
		}

		testOn += dt;
	}


	printf("\n\n-----------------------------------------------------------\n");
	RingBufferClear(&buffer);
	lastTick = cat_platform_time();
	
	//O(n^2)
	/*for (int k = 0; k < timeLooping; k++)
	{
		if (&buffer == NULL)
			return;

		initalTick = cat_platform_time();
		dt = initalTick - lastTick;
		lastTick = initalTick;
		RingBufferInsert(&buffer, dt);
		printf("\n%d second average: %f", k, RingBufferAverage(&buffer) / tps);
		testOsqn += dt;

		for (int i = 0; i < timeLooping; i++)
		{
			unused(i);
			for (int j = 0; j < timeLooping; j++)
			{
				unused(j);
			}
		}
	}*/
	
	printf("\n\n-----------------------------------------------------------\n");
	printf("\nAverage time in seconds of O(log_2(n)) loop: %f \nAverage time in seconds of O(n) loop:%f \nAverage time in seconds of O(n^2) loop: %f", 
		testOnLogn / timeLooping / tps, testOn / timeLooping / tps, testOsqn / timeLooping / tps);

	RingBufferClear(&buffer);
	RingBufferClean(&buffer);
}
