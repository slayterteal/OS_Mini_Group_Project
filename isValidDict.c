// Jackson Wildman
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    
    while (!feof(dict)) //runs until valid or eof
    {
        fgets(dictWord, 50, dict);
        *(dictWord + strlen(dictWord) - 2) = '\0'; //fixes newline from fgets

        if (strcmp(inputWord, dictWord) == 0)
        {
            return 1;
        }
    }
    
    return 0;
}

