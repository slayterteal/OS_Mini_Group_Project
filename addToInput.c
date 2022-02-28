/**
 * @file addToInput.c
 * @author Jackson Wildman (jawildm@okstate.edu)
 * @brief Group D
 * @date 2022-02-27
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief adds word to selected input file. 
 * super dirty way of doing it as of now
 * 
 * @param inputFileName
 * @param inputWord 
 */
void addToInput(char *inputFileName, char* inputWord) 
{

    FILE *inputFile;
    if ((inputFile = fopen(inputFileName, "r"))) //this block pretty much just exists for testing. shouldnt have to hit that else in the real game
    {
        inputFile = fopen(inputFileName, "a");
    }
    else
    {
        inputFile = fopen(inputFileName, "w");
    }

    fprintf(inputFile, "%s", inputWord);

    fclose(inputFile);
}
