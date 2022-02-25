#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "WordServices.h"

char *toLowerStr(char *inputStr, int inputSize)
{
    	char *tempStr = malloc(inputSize);

	for (int i = 0; i < inputSize; i++)
	{
        	*(tempStr + i) = tolower(*(inputStr + i));
	}

	return tempStr;
}
