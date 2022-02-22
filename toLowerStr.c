#include <stdio.h>
#include <ctype.h>

void toLowerStr(char *inputStr, int inputSize)
{
	for (int i = 0; i < inputSize; i++)
	{
		*(inputStr + i) = tolower(*(inputStr + i));
	}
}
