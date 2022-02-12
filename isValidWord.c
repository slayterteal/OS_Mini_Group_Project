// Jackson Wildman
#include "WordServices.h"
#include <string.h>

/**
 * @brief runs all checks to see if input word is in 
 * dictionary/already used/contained in the input file.
 * Takes in the user defined inputWord as well as the 
 * array of already entered words (usedWords). Returns a binary
 * 1/0/-1 depending on if the word is valid/not valid/already used. 
 * 
 * @param inputWord 
 * @param usedWords 
 * @param inputFileNumber 
 * @return int 
 */
int isValidWord(char *inputWord, char **usedWords, int usedSize, int inputFileNumber) 
{
    if (!isValidDict(inputWord)) //check if valid dictionary word
    {
        return 0; 
    }

    if (isUsedWord(inputWord, usedWords, usedSize)) //check if word has been used. if not
    {
        return -1;
    }
    else 
    {
        //deciding whether to use addToUsed here or not
        return 0;
    }
    
    if (!isKnown(inputFileNumber, inputWord))
    {
        addToInput(inputFileNumber, inputWord);
        return 1;
    }
}