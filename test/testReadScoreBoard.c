#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void readScoreBoard() //searches for a scoreboard file corresponding to a given number of players and rounds. prints the contents of the file.
{
    /*
    should be able to handle max of 120 player value sets, 
    didn't try to do anything with dynamic resizing yet 
    since it's dependent on file length
    */

    char currentChar;
    char *topScores = malloc(120 * 6 * sizeof(int));
    int topScoreCount = 0;
    char **topPlayers = malloc(120 * 86 * sizeof(char));
    char *currentLine = malloc(86 * sizeof(char));
    char *intString = malloc(6 * sizeof(int));

    for (int i = 0; i < 120; i++)
    {
        *(topPlayers + i) = malloc(86 * sizeof(char));
    }
    
    FILE *scoreboard;


    scoreboard = fopen("scoreboard.txt", "r");
    printf("   "); //just changes the formatting for the 1:, 2:, etc
    
    for (int i = 0; i < 86; i++) //print first line for formatting
    {
        currentChar = fgetc(scoreboard);
        printf("%c", currentChar);
    }

    while (currentChar != EOF) //read all values and sort by score
    {
        int playerMatch = 0;
        int printLine = 0;

        for (int i = 0; i < 86; i++)
        {
            currentChar = fgetc(scoreboard);
            *(currentLine + i) = currentChar;

            if(i > 31 && i < 39) //get score to compare later
            {
                *(intString + (i - 32)) = currentChar;
            }
        }

        int fullInt = 0; //final integer after conversion
        int power = 1; //exponent used in the following block to convert string to int
        
        for (int j = 0; j < 21; j++) //convert score string to int for comparison using powers of 10 to convert
        {
            if(*(intString + j) != ' ')
            {
                for (int k = 0; k < 20 - j; k++) //method to take number to a power
                {
                    power = power * (10 * (20 - j));
                }

                if (power == 0) //edge case
                {
                    power = 1;
                }

                fullInt += (*(intString + j) - '0') * power;
            }
        }

        *(topScores + topScoreCount) = fullInt; //copy string value to array
        strcpy(*(topPlayers + topScoreCount), currentLine);
        topScoreCount++;
    }

    int tempScore = 0; //init variables for sorting
    char *tempScoreLine = malloc(86 * topScoreCount * sizeof(char));

    for (int i = 0; i < topScoreCount; i++) //sort relevant players by score
    {
        for (int j = 0; j < topScoreCount; j++)
        {
            if (*(topScores + i) > *(topScores + j))
            {
                tempScore = *(topScores + i);
                strcpy(tempScoreLine, *(topPlayers + i));
                *(topScores + i) = *(topScores + j);
                strcpy(*(topPlayers + i), *(topPlayers + j));
                *(topScores + j) = tempScore;
                strcpy(*(topPlayers + j), tempScoreLine);
            }
        } 
    }

    for (int i = 0; i < 6; i++) //print top 5 scores in the scoreboard
    {
        if (i > 0) //prevents an issue where the last line in the file is read as whitespace and placed 1st
        {
            printf("%i: %s", i, *(topPlayers + i));
        }
    }
}

int main()
{
    readScoreBoard();
}