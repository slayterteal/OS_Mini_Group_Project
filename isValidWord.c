#include "isValidDict.c"
#include "isUsedWord.c"

int isValidWord(char *inputWord, char **usedWords, int usedLength, int inputFileNumber) //runs all checks to see if input word is in dictionary/already used/contained in the input file
{
    if (!isValidDict(inputWord)) //check if valid dictionary word
    {
        return 0; 
    }

    if (isUsedWord(inputWord, usedWords, (sizeof(usedWords)/sizeof(*usedWords)))) //check if word has been used. if not
    {
        return 0;
    }
    else 
    {
        //deciding whether to use addToUsed here or not
    }
    
    if (!isKnown(inputFileNumber, inputWord))
    {
        addToInput(inputFileNumber, inputWord);
        return 1;
    }
}