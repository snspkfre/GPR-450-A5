#include "cat_profiler.h"
#include "cat/utility/cat_time.h"

//extern void cat_platform_time_rate(void);
//extern void cat_platform_time(void);
extern void cat_console_clear(void);

void RingBufferInit(RingBuffer* buffer, int size)
{
	buffer->index = 0;
	buffer->header = 0;
	buffer->footer = 0;
	buffer->size = size;
	buffer->values = (int64_t*)malloc(size * sizeof(int64_t));

	for (int i = 0; i < size; i++)
	{
		buffer->values[i] = 0;
	}
}

void RingBufferClean(RingBuffer* buffer)
{
	if (buffer == NULL)
		return;
	free(buffer->values);
	//free(buffer);
}

void RingBufferInsert(RingBuffer* buffer, int64_t value)
{
	buffer->values[buffer->index] = value;
	buffer->index = buffer->index == buffer->size ? 0 : buffer->index + 1;
	buffer->footer = buffer->footer > buffer->size ? buffer->size : buffer->footer + 1;
}

void RingBufferClear(RingBuffer* buffer)
{
	buffer->index = 0;
	
	for (int i = 0; i < buffer->footer; i++)
	{
		buffer->values[i] = 0;
	}
	buffer->footer = 0;
}

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
	RingBuffer* buffer = (RingBuffer*)malloc(sizeof(RingBuffer*));
	RingBufferInit(buffer, size);
	double test = 0;
	int64_t volatile initalTick = 0;
	int64_t volatile lastTick = 0;
	int64_t volatile dt = 0;
	
	cat_console_clear();
	cat_platform_time_rate();

	for (int i = 0; i < 10; ++i)
	{
		if (buffer == NULL)
			return;
		initalTick = cat_platform_time();
		dt = initalTick - lastTick;
		lastTick = initalTick;
		RingBufferInsert(buffer, dt);
		printf("\ntick average: %f", RingBufferAverage(buffer));
		
		test += 1;
	}

	//for (int i = 0; i < 10000; i++)
	//{
	//	initalTick = (double)cat_platform_time();
	//	dt = initalTick - lastTick;
	//	lastTick = initalTick;
	//	RingBufferInsert(buffer, dt);
	//	printf("tps: %f", RingBufferAverage(buffer));

	//	test += 1;

	//	cat_console_clear();
	//}

	RingBufferClean(buffer);
	RingBufferClean(buffer);
	free(buffer);
}
