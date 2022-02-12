// gcc -Wall ./*.c -o a.out
#include "WordServices.h"
#include "GameLogic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    printf("It compiles! \n");
    struct Player *test_player = malloc(sizeof(struct Player));
    char **usedWords = malloc(2*sizeof(char*));
    for (int i = 0; i < 2; i++){
        usedWords[i] = malloc((10)*sizeof(char));
    }
    strcpy(usedWords[0], "Hello");
    strcpy(usedWords[1], "World");

    char *randAlphabet = "ABCDE";
    char *inputWord = "Fuzz";

    int usedLength = 2;
    test_player->score = 4;
    char *test_msg = buildNextPlayerMsg(
                        test_player, 
                        usedWords,
                        &usedLength,  
                        randAlphabet, 
                        inputWord);

    printf("Test Msg: \n %s", test_msg);

    // free memory
    for (int i = 0; i < 1; i++){
        free(usedWords[i]);
    }
    free(usedWords);

    return 0;
}