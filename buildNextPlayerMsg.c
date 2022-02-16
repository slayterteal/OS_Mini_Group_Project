/**
 * @file buildNextPlayerMsg.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 * 
 */

/*
• the set of random alphabets
• the player’s current score,
• the opponent player’s current score,
• words that have been used in the game so far, and
• the starting character of the word

I think it would be better if each element is pushed to the next player
in successive order.
*/

#include "GameLogic.h"
#include <string.h>
#include <stdlib.h>

char *buildNextPlayerMsg(struct Player *player, 
                        char **usedWords,
                        int *usedLength,
                        char *randAlphabet, 
                        char *inputWord){
    // Total size of the message to be sent.(in bytes)
    int sizeof_message = sizeof(usedWords) 
                         + sizeof(randAlphabet) 
                         + sizeof(inputWord) 
                         + sizeof(int);
    
    // one string to rule them all
    char *nextPlayerMsg = malloc(sizeof_message*sizeof(char));

    strcat(nextPlayerMsg, randAlphabet);
    strcat(nextPlayerMsg, "\n");
    char score = player->player_score + '0';
    strcat(nextPlayerMsg, &score); 
    strcat(nextPlayerMsg, "\n");
    for(int i = 0; i < *usedLength; i++){
        strcat(nextPlayerMsg, usedWords[i]);
        strcat(nextPlayerMsg, "\n");
    } 

    return nextPlayerMsg;
}