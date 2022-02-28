/**
 * @file isValidDict.c
 * @author Jackson Wildman (jawildm@okstate.edu)
 * @brief Group D
 * @date 2022-27-02
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "WordServices.h"

/**
 * @brief checks the dictionary.txt to conform if
 * the inputed word is valid (in the dictionary).
 * Returns a True/False, 1/0
 * 
 * @param inputWord 
 * @return int 
 */
int isValidDict(char *inputWord)
{
    FILE *dict;

    dict = fopen("dictionary.txt", "r");
    char *dictWord = malloc(50 * sizeof(char));
    char *aInput = malloc(50 * sizeof(char));
    strcat(aInput, inputWord);
    aInput[strlen(aInput) - 1] = '\r';
    while (!feof(dict)) //runs until valid or eof
    {
        fgets(dictWord, 50, dict);
        //*(dictWord + strlen(dictWord) - 2) = '\0'; //fixes newline from fgets
	//printf("%s", dictWord); 						   
	char *lowerDict = toLowerStr(dictWord, strlen(dictWord));

	/*if (lowerDict[0] == inputWord[0] && lowerDict[1] == inputWord[1])
	{
		printf("%s",lowerDict);
        for (int i = 0; i < strlen(lowerDict); i++)
	{
		printf("%i\n", lowerDict[i]);
		printf("%i\n", aInput[i]);
        }
        //lowerDict[strlen(lowerDict) - 1] = '\0';
		printf("%s%s", aInput, lowerDict);
		printf("%i, %i, %i", strcmp(aInput, lowerDict), strlen(aInput), strlen(lowerDict));
	}*/


        if (lowerDict[strlen(lowerDict) - 1] == '\n')
        {
        	lowerDict[strlen(lowerDict) - 1] = '\0';
        }
        if (strcmp(aInput, lowerDict) == 0)
        {
            return 1;
        }
    }
    
    return 0;
}

