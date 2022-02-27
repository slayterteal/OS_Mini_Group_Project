// Jackson Wildman
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
    
    // int tempNum = inputNumber;
    // int numLength = 0;
    // char *fileName = calloc(20, sizeof(char));
    // char *fileNum = calloc(10, sizeof(char));

    // while (tempNum != 0) //determine amount of digits for string conversion
    // {
    //     tempNum /= 10;
    //     numLength++;
    // }

    // if (inputNumber < 10) //conforms to naming convention in pdf
    // {
    //     printf("%s", fileName);
    //     strcat(fileName, "input_0");
    //     *(fileNum) = inputNumber + '0';
    // }
    // else //pull out all digits of input int to stick into filename otherwise, should work for all positive int
    // {
    //     strcat(fileName, "input_");

    //     for (int i = 0; i < numLength; i++) //run for all digits
    //     {
    //         tempNum = inputNumber;
            
    //         for (int j = 0; j < numLength - i - 1; j++) //pull out leftmost - i digit
    //         {
    //             tempNum /= 10;
    //         }

    //         *(fileNum + i) = tempNum % 10 + '0'; //easy int to char, thank you ascii
    //     }
    // }

    // *(fileNum + numLength) = '\0'; //ensure no newline in num
    // strcat(fileName, fileNum);
    // strcat(fileName, ".txt");

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
