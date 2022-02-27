// Jackson Wildman
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "WordServices.h"

/**
 * @brief add word to selected input file. 
 * Takes in the array of previously used words, the 
 * user inputed word, and the size of the user size array.
 * Returns a pointer to the new array of strings.
 * kind of dirty way of doing it as of now
 * 
 * @param usedWords 
 * @param inputWord 
 * @param usedSize 
 * @return char** 
 */
char **addToUsed(char **usedWords, char* inputWord, int usedSize) 
{
    printf("WHAT\n");
    char **tempUsed = calloc((200 * usedSize) + (200 * sizeof(char)), sizeof(char));
    printf("WHY\n");

    for (int i = 0; i < usedSize + 1; i++)
    {
        //printf("%s", *(tempUsed + i));
        *(tempUsed + i) = malloc(100 * sizeof(char));
    }

    for (int i = 0; i < usedSize; i++)
    {
        strcpy(*(tempUsed + i), *(usedWords + i));
    }
    
    strcpy(*(tempUsed + usedSize), inputWord);
    return tempUsed;
}
