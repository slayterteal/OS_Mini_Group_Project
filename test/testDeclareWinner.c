/**
 * @file testDeclareWinner.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 * 
 */

#include "../GameLogic.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief testing code for declareWinner.c
 * 
 * @return int 
 */
int main(){
    struct Player *test_player;
    test_player = malloc(sizeof(struct Player));
    
    test_player->opponent_score = 10;
    test_player->player_score = 1;
    if(declareWinner(test_player) == -1){
        printf("you lose! \n");
    }
    else if(declareWinner(test_player) == 0){
        printf("tie! \n");
    }
    else{
        printf("you win! \n");
    }

    test_player->opponent_score = 1;
    test_player->player_score = 1;
    if(declareWinner(test_player) == -1){
        printf("you lose! \n");
    }
    else if(declareWinner(test_player) == 0){
        printf("tie! \n");
    }
    else{
        printf("you win! \n");
    }

    test_player->opponent_score = 1;
    test_player->player_score = 2;
    if(declareWinner(test_player) == -1){
        printf("you lose! \n");
    }
    else if(declareWinner(test_player) == 0){
        printf("tie! \n");
    }
    else{
        printf("you win! \n");
    }

    return 0;
}