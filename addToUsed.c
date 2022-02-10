#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char **addToUsed(char **usedWords, char* inputWord, int usedSize) //add word to selected input file. kind of dirty way of doing it as of now
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

int main() //test code
{
    char **usedWords = malloc(3 * 20 * sizeof(char));
    printf("SIZE %i\n", (sizeof(usedWords) / sizeof(*usedWords)));

    for (int i = 0; i < 3; i++)
    {
        *(usedWords + i) = malloc(20 * sizeof(char));
    }

    *usedWords = "yes";
    *(usedWords + 1) = "no";
    *(usedWords + 2) = "maybe";

    for (int i = 0; i < 4; i++)
    {
        printf("%s", *(usedWords + i));
    }

    usedWords = addToUsed(usedWords, "why", 3);

    printf("%i", (sizeof(usedWords) / sizeof(*usedWords)));

    for (int i = 0; i < 4; i++)
    {
        printf("%s", *(usedWords + i));
    }
}