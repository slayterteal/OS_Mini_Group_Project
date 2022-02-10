#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int isUsedWord(char *inputWord, char **usedWords, int usedLength) //determine if word has been used already, if used return 1, otherwise add to array and return 0
{
    for (int i = 0; i < usedLength; i++)
    {
        if (strcmp(inputWord, *usedWords) == 0)
        {
            return 1;
        }
    }
    
    return 0;
}

int main() //test code
{
    char *used[] = {"yes", "maybe", "no"};
    printf("%i\n", (sizeof(used) / sizeof(*used))); //cheap way to get size of array element
    int usedQuery = isUsedWord("yes", used, (sizeof(used) / sizeof(*used)));
    printf("%i\n", usedQuery);
    usedQuery = isUsedWord("sure", used, (sizeof(used) / sizeof(*used)));
    printf("%i\n", usedQuery);
}