
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int isKnown(int inputNumber, char* inputWord) //add word to selected input file. super dirty way of doing it as of now
{
    FILE *inputFile;
    int tempNum = inputNumber;
    int numLength = 0;
    char *fileName = malloc(20 * sizeof(char));
    char *fileNum = malloc(10 * sizeof(char));

    while (tempNum != 0) //determine amount of digits for string conversion
    {
        tempNum /= 10;
        numLength++;
    }

    if (inputNumber < 10) //conforms to naming convention in pdf
    {
        strcat(fileName, "input_0");
        *(fileNum) = inputNumber + '0';
    }
    else //pull out all digits of input int to stick into filename otherwise, should work for all positive int
    {
        strcat(fileName, "input_");

        for (int i = 0; i < numLength; i++) //run for all digits
        {
            tempNum = inputNumber;
            
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

    inputFile = fopen(fileName, "r");

    char *currentLine = malloc(20 * sizeof(char));
    fgets(currentLine, 20, inputFile);
    fgets(currentLine, 20, inputFile);

    while (!feof(inputFile))
    {
        fgets(currentLine, 20, inputFile);
        *(currentLine + strlen(currentLine) - 1) = '\0'; //fixes newline from fgets

        if (strcmp(currentLine, inputWord) == 0)
        {
            return 1;
        }
    }

    //if not known, add to input_xx.txt

    fclose(inputFile);
    return 0;
}

int main() //test code
{
    int knownQuery = isKnown(1, "yes");
    printf("%i", knownQuery);
}