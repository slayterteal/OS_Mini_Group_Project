// Jackson Wildman
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    char **tempUsed = malloc(usedSize + sizeof(char));

    for (int i = 0; i < usedSize + 1; i++)
    {
        *(tempUsed + i) = malloc(sizeof(*usedWords));
    }

    for (int i = 0; i < usedSize; i++)
    {
        strcpy(*(tempUsed + i), *(usedWords + i));
    }
    
    strcpy(*(tempUsed + usedSize), inputWord);
    usedWords = malloc(sizeof(tempUsed));

    for (int i = 0; i < 4; i++)
    {
        printf("TEMP %s %i\n", *(tempUsed + i), i);
    }

    usedWords = tempUsed;
    

    /*for (int i = 0; i < usedSize + 1; i++)
    {
        *(usedWords + i) = malloc(sizeof(*tempUsed));
    }*/

    for (int i = 0; i < usedSize + 1; i++)
    {
        strcpy(*(usedWords + i), *(tempUsed + i));
        printf("TEMP %s %i\n", *(tempUsed + i), i);
        printf("USED %s %i\n", *(usedWords + i), i);
    }
    
    return tempUsed;
}