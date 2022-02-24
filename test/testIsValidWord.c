#include "../WordServices.h"
#include "../isValidWord.c"
#include "../isUsedWord.c"
#include "../isKnown.c"
#include "../addToUsed.c"
#include "../addToInput.c"
#include "../isValidDict.c"
#include <stdio.h>
#include <string.h>

int main()
{
	char **usedWords = malloc(300 * sizeof(char)); //arbitrary test size

    	for (int i = 0; i < 3; i++) //alloc for each element
    	{
        	*(usedWords + i) = malloc(20 * sizeof(char));
    	}

    	*(usedWords) = "one"; //fill array
    	*(usedWords + 1) = "two";
    	*(usedWords + 2) = "three";
    	int usedSize = 3; //keep track of size!
    	char *inputWord1 = "test"; //not in input_01 by default, valid word, not used already
    	char *inputWord2 = ""; //pass condition
    	char *inputWord3 = "adsgag"; //invalid word
    	char *inputWord4 = "two"; //not in input_01, valid word, contained in usedWords
    	char *inputWord5 = "test"; //test that usedWords updates correctly, make sure to check input_xx
	
    	int returnVal = 0; //test all five strings
	returnVal = isValidWord(inputWord1, strlen(inputWord1), &usedWords, &usedSize, 1);
	printf("%i\n",returnVal);
    	returnVal = isValidWord(inputWord2, strlen(inputWord2), &usedWords, &usedSize, 1);
	printf("%i\n",returnVal);
    	returnVal = isValidWord(inputWord3, strlen(inputWord3), &usedWords, &usedSize, 1);
	printf("%i\n",returnVal);
    	returnVal = isValidWord(inputWord4, strlen(inputWord4), &usedWords, &usedSize, 1);
	printf("%i\n",returnVal);
	returnVal = isValidWord(inputWord5, strlen(inputWord5), &usedWords, &usedSize, 1);
	printf("%i\n",returnVal);
	return 0;
}
