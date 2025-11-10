#include "cat_unit_test.h"

//file reading uses animal3D as a reference

void runTests(const char* filePath)
{
	FILE* file = fopen(filePath, "r");

	if (!file)
		return;

	const char FunctionNames[][32] = 
	{
		"[Dot Product]",
	};

	enum FunctionToTest
	{
		DotProduct,
	};

	char line[256];
	int linesz = sizeof(line);
	int func = DotProduct;
	testFunc functionOps[] = 
	{
		dotProduct,
	};

	while (true)
	{
		fgets(line, linesz, file);

		if (*line == '[')
		{
			//change section
			for (int i = 0; i < sizeof(FunctionNames) / sizeof(FunctionNames[0]); i++)
			{
				if (strncmp(line, FunctionNames[i], strnlen(FunctionNames[i], 32)))
				{
					func = i;
				}
			}

			continue;
		}

		switch (func)
		{
		case DotProduct:
			sscanf();
			int result = (int) *functionOps[DotProduct].function();
			break;
		}
	}
}
