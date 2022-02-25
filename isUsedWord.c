// Jackson Wildman
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "WordServices.h"

/**
 * @brief //determine if word has been used already, 
 * if used return 1, otherwise add to array and return 0
 * 
 * @param inputWord 
 * @param usedWords 
 * @param usedLength 
 * @return int 
 */
int isUsedWord(char *inputWord, char **usedWords, int usedLength) 
{
    for (int i = 0; i < usedLength; i++)
    {
        if (strcmp(inputWord, *(usedWords + i)) == 0)
        {
            return 1;
        }
    }
    
    return 0;
}

