/**
 * @file generateWord.c
 * @author Jackson Wildman (you@domain.com)
 * @brief Group D
 * @date 2022-02-27
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief use this method to make a computer player 
 * grab a word from chosen input_x.txt. 
 * returns a random word from the chosen text file
 * 
 * @param inputFile
 * @return char* 
 */
char *generateWord(char *inputFileName) 
{
    FILE *inputFile;
    inputFile = fopen(inputFileName, "r"); //this block pretty much just exists for testing. shouldnt have to hit that else in the real game

    char *currentLine = malloc(20 * sizeof(char));
    int wordCount = -1;
    fgets(currentLine, 20, inputFile);
    fgets(currentLine, 20, inputFile);

    while(!feof(inputFile))
    {
        fgets(currentLine, 20, inputFile);
        wordCount++;
    }

    fclose(inputFile);
    
    inputFile = fopen(inputFileName, "r"); //this block pretty much just exists for testing. shouldnt have to hit that else in the real game
    char **inputFileWords = malloc(wordCount * sizeof(char*));

    for (int i = 0; i < wordCount; i++)
    {
        *(inputFileWords + i) = malloc(20 * sizeof(char));
    }

    fgets(currentLine, 20, inputFile);
    fgets(currentLine, 20, inputFile);
    fgets(currentLine, 20, inputFile);

    for (int i = 0; i < wordCount; i++)
    {
        fgets(currentLine, 20, inputFile);
	printf("%s",currentLine);
        strcpy(*(inputFileWords + i), currentLine);
    }

    for (int i = 0; i < wordCount; i++)
    {
        printf("%s", *(inputFileWords + i));
    }

    fclose(inputFile);

    srand(time(0));
    int wordIndex = rand() % wordCount;
    inputFileWords[wordIndex][strlen(inputFileWords[wordIndex]) - 1] = '\n';
        
    /*for (int i = 0; i < strlen(*(inputFileWords + wordIndex) - 1); i++)
    {
	    printf("%i\n", inputFileWords[wordIndex][i]);
	    //inputFileWords[wordIndex][i + 1] = inputFileWords[wordIndex][i];
    }

    char *fixedInput = calloc(strlen(inputFileWords[wordIndex]) + 1, sizeof(char));
    //strcat(fixedInput, "\n");
    strcat(fixedInput, inputFileWords[wordIndex]);
    strcat(fixedInput, "\n");*/
    return inputFileWords[wordIndex];
}
