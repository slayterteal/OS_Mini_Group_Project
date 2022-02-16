/**
 * @file declareWinner.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 */
#include "GameLogic.h"

/**
 * @brief a function that tells the calling player the result
 * of the game. -1 for loss, 0 for tie, and 1 for a win.
 * 
 * @param player 
 * @return int 
 */
int declareWinner(struct Player *player){
    if(player->player_score < player->opponent_score){
        return -1; // you lose!
    }
    else if(player->player_score == player->opponent_score){
        return 0; // tie!
    }
    else{
        return 1; // you win!
    }
}