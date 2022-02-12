
#include "../WordServices.h"

/**
 * @brief Tests ../isUsedWord.c
 * 
 * @return int 
 */
int main() 
{
    char *used[] = {"yes", "maybe", "no"};
    printf("%i\n", (sizeof(used) / sizeof(*used))); //cheap way to get size of array element
    int usedQuery = isUsedWord("yes", used, (sizeof(used) / sizeof(*used)));
    printf("%i\n", usedQuery);
    usedQuery = isUsedWord("sure", used, (sizeof(used) / sizeof(*used)));
    printf("%i\n", usedQuery);
}