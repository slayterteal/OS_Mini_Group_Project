
#include "../WordServices.h"

int main() //test code
{
    char **usedWords = malloc(3 * 20 * sizeof(char));
    printf("SIZE %i\n", (sizeof(usedWords) / sizeof(*usedWords)));

    for (int i = 0; i < 3; i++)
    {
        *(usedWords + i) = malloc(20 * sizeof(char));
    }

    *usedWords = "yes";
    *(usedWords + 1) = "no";
    *(usedWords + 2) = "maybe";

    for (int i = 0; i < 4; i++)
    {
        printf("%s", *(usedWords + i));
    }

    usedWords = addToUsed(usedWords, "why", 3);

    printf("%i", (sizeof(usedWords) / sizeof(*usedWords)));

    for (int i = 0; i < 4; i++)
    {
        printf("%s", *(usedWords + i));
    }
}