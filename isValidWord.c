/**
 * @file isValidWord.c
 * @author Jackson Wildman (jawildm@okstate.edu)
 * @brief Group D
 * @date 2022-27-02
 * 
 */
#include "WordServices.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief runs all checks to see if input word is in 
 * dictionary/already used/contained in the input file.
 * Takes in the user defined inputWord as well as the 
 * array of already entered words (usedWords). Returns a binary
 * 1/0/-1/-2 depending on if the word is valid/not valid/already used/pass condition. 
 * 
 * @param inputWord 
 * @param usedWords 
 * @param inputFileName
 * @return int 
 */
int isValidWord(char *inputWord, int inputSize, char ***usedWords, int *usedSize, char *inputFileName){
    char *lowerWord = toLowerStr(inputWord, inputSize);

    if (strlen(inputWord) < 3) // pass
    {
        return -2;
    }

    printf("one\n");

    if (!isValidDict(lowerWord)) // check if valid dictionary word
    {
        return 0; // invalid
    }

    printf("two\n");

    if (isUsedWord(lowerWord, *usedWords, *usedSize)) //check if word has been used. if not
    {
        printf("is");
        return -1;
    }
    else // add to array of used words
    {
        printf("isn't");
        char **tempWords = addToUsed(*usedWords, lowerWord, *usedSize);
        printf("YO\n");
        *usedSize = *usedSize + 1;
        *usedWords = calloc(600, sizeof(char)); //arbitrary size, can easily be changed if needed

        for (int i = 0; i < *usedSize; i++)
        {
            *(*(usedWords) + i) = malloc(20 * sizeof(char));
        }

        for (int i = 0; i < *usedSize; i++)
        {
            strcpy(*(*(usedWords) + i), *(tempWords + i));
        }
    }

    printf("three\n");
    
    if (!isKnown(inputFileName, lowerWord))
    {
        addToInput(inputFileName, lowerWord);
    }

    printf("four\n");

    return 1; // valid
}
