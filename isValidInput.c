/**
 * @file isValidInput.c
 * @author Jackson Wildman (jawildm@okstate.edu)
 * @brief Group D
 * @date 2022-1-3
 * 
 */
#include "WordServices.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isValidInput(char *input_txt, char *input_word)
{
    FILE *inputFile;
    inputFile = fopen(input_txt, "r"); //this block pretty much just exists for testing. shouldnt have to hit that else in the real game

    char *randomAlphabet = malloc(20 * sizeof(char));
    fgets(randomAlphabet, 20, inputFile);
    char *lowerAlpha = toLowerStr(randomAlphabet, strlen(randomAlphabet));
    int valid = 0;
    int skipIndices[strlen(lowerAlpha)];

    for (int i = 0; i < strlen(lowerAlpha); i++)
    {
        skipIndices[i] = 0;
    }

    for (int i = 0; i < strlen(input_word); i++)
    {
        for (int j = 0; j < strlen(lowerAlpha); j++)
        {
            printf("%c %c", lowerAlpha[j], input_word[i]);

            if (lowerAlpha[j] == input_word[i] && skipIndices[j] == 0)
            {
                valid = 1;
                skipIndices[j] = 1;
            }
        }

        if (valid == 0)
        {
            return 0;
        }
    }

    return 1;
}