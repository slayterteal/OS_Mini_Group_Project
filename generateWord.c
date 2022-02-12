// Jackson Wildman
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief //use this method to make a computer player 
 * grab a word from chosen input_x.txt. 
 * returns a random word from the chosen text file
 * 
 * @param inputFileNumber 
 * @return char* 
 */
char *generateWord(int inputFileNumber) 
{
    FILE *inputFile;
    int tempNum = inputFileNumber;
    int numLength = 0;
    char *fileName = malloc(20 * sizeof(char));
    char *fileNum = malloc(10 * sizeof(char));

    while (tempNum != 0) //determine amount of digits for string conversion
    {
        tempNum /= 10;
        numLength++;
    }

    if (inputFileNumber < 10) //conforms to naming convention in pdf
    {
        strcat(fileName, "input_0");
        *(fileNum) = inputFileNumber + '0';
    }
    else //pull out all digits of input int to stick into filename otherwise, should work for all positive int
    {
        strcat(fileName, "input_");

        for (int i = 0; i < numLength; i++) //run for all digits
        {
            tempNum = inputFileNumber;
            
            for (int j = 0; j < numLength - i - 1; j++) //pull out leftmost - i digit
            {
                tempNum /= 10;
            }

            *(fileNum + i) = tempNum % 10 + '0'; //easy int to char, thank you ascii
        }
    }

    *(fileNum + numLength) = '\0'; //ensure no newline in num
    strcat(fileName, fileNum);
    strcat(fileName, ".txt");

    inputFile = fopen(fileName, "r"); //this block pretty much just exists for testing. shouldnt have to hit that else in the real game

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

    char **inputFileWords = malloc(wordCount * sizeof(char*));

    for (int i = 0; i < wordCount; i++)
    {
        *(inputFileWords + i) = malloc(20 * sizeof(char));
    }

    inputFile = fopen(fileName, "r"); //this block pretty much just exists for testing. shouldnt have to hit that else in the real game

    fgets(currentLine, 20, inputFile);
    fgets(currentLine, 20, inputFile);

    for (int i = 0; i < wordCount; i++)
    {
        fgets(currentLine, 20, inputFile);
        strcpy(*(inputFileWords + i), currentLine);
    }

    for (int i = 0; i < wordCount; i++)
    {
        printf("%s", *(inputFileWords + i));
    }

    fclose(inputFile);

    srand(time(0));
    int wordIndex = rand() % wordCount;

    return *(inputFileWords + wordIndex);
}
