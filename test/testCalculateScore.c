// Slayter Teal

#include "../GameLogic.h"
#include <stdio.h>

int main(){
    char *test_word = "hello";
    int score = 0;
    score = calculateScore(0, test_word);
    printf("Score = %d \n", score);
    score = calculateScore(1, test_word);
    printf("Score = %d \n", score);
    score = calculateScore(-1, test_word);
    printf("Score = %d \n", score);

    return 0;
}