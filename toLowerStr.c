/**
 * @file toLowerStr.c
 * @author Jackson Wildman (jawildm@okstate.edu)
 * @brief Group D
 * @date 2022-02-27
 * 
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "WordServices.h"

/**
 * @brief Takes in a string and stringsize, and returns a lower case string
 * 
 * @param inputStr 
 * @param inputSize 
 * @return char* 
 */
char *toLowerStr(char *inputStr, int inputSize)
{
    	char *tempStr = malloc(inputSize);

	for (int i = 0; i < inputSize; i++)
	{
        	*(tempStr + i) = tolower(*(inputStr + i));
	}

	return tempStr;
}
