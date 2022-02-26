// Jackson Wildman
#include "WordServices.h"
#include <string.h>
#include <stdlib.h>

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

    if (strlen(inputWord) <= 1) // pass
    {
        return -2;
    }

    if (!isValidDict(lowerWord)) // check if valid dictionary word
    {
        return 0; // invalid
    }

    if (isUsedWord(lowerWord, *usedWords, *usedSize)) //check if word has been used. if not
    {
        return -1;
    }
    else // add to array of used words
    {
        char **tempWords = addToUsed(*usedWords, lowerWord, *usedSize);
        *usedSize = *usedSize + 1;
        *usedWords = malloc(300 * sizeof(char)); //arbitrary size, can easily be changed if needed

        for (int i = 0; i < *usedSize; i++)
        {
            *(*(usedWords) + i) = malloc(20 * sizeof(char));
        }

        for (int i = 0; i < *usedSize; i++)
        {
            strcpy(*(*(usedWords) + i), *(tempWords + i));
        }
    }
    
    if (!isKnown(inputFileName, lowerWord))
    {
        addToInput(inputFileName, lowerWord);
    }

    return 1; // valid
}
