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

char nextPlayerMsg[500];

/**
 * @brief builds a message (string) for the server to send
 * to the client. Should not matter which turn the game is on.
 * 
 * @param player 
 * @param usedWords 
 * @param usedLength 
 * @param randAlphabet 
 * @return char* 
 */
char *buildNextPlayerMsg(struct Player *player, char **usedWords,int *usedLength, char *randAlphabet){
    // Total size of the message to be sent.(in bytes)
    // int sizeof_message = sizeof(usedWords) + sizeof(randAlphabet) + sizeof(int);
    
    // // one string to rule them all
    // char *nextPlayerMsg = malloc(sizeof_message*sizeof(char));
    memset(nextPlayerMsg, 0, strlen(nextPlayerMsg)); // reset the string at the beginning of the function.

    strcat(nextPlayerMsg, randAlphabet);
    // strcat(nextPlayerMsg, "\n");
    char temp[2];

    temp[0] = player->opponent_score + '0';
    strcat(nextPlayerMsg, "Player Score: ");
    strcat(nextPlayerMsg, &temp[0]); 
    strcat(nextPlayerMsg, "\n");

    temp[0] = player->player_score + '0';
    strcat(nextPlayerMsg, "Opponent Score: ");
    strcat(nextPlayerMsg, &temp[0]); 
    strcat(nextPlayerMsg, "\n");

    if (usedLength == 0){
        // no previous word to display
        // do nothing!
    }
    else {
        // add all previous words to the next player message
        for(int i = 0; i < *usedLength; i++){
            strcat(nextPlayerMsg, usedWords[i]);
            strcat(nextPlayerMsg, "\n");
        } 
    }

    return nextPlayerMsg;
}