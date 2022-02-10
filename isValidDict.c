#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int isValidDict(char *inputWord) //check dictionary.txt to confirm validity
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

int main() //test code
{
    int isValid = isValidDict("test");
    printf("%i", isValid);
}