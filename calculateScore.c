/**
 * @file calculateScore.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 * @brief Group D
 * @date 2022-02-27
 */
#include <string.h>
#include "GameLogic.h"

/**
 * @brief takes in a validBit and a word then calculates
 * the score based on whether or not it is considered valid.
 * 
 * @param validBit 
 * @param word 
 * @return returns an int score
 */
int calculateScore(int validBit, char *word){
    /*
    Scoring is based entirely around word length, thus build a 
    simple switch statement to determine what score the player 
    received.

    The numbers are shifted up 1 to account for endline characters
    */
    if(validBit == 1){ // the word is valid, gain points
        int wordLength = strlen(word);
        if(wordLength <= 5){
            // 1
            return 1;
        }
        else if(wordLength == 6){
            // 2
            return 2;
        }
        else if(wordLength == 7){
            // 3
            return 3;
        }
        else if(wordLength == 8){
            // 5
            return 5;
        }
        else { // wordLength >= 8
            // 11
            return 11;
        }
    }
    else if(validBit == 0){ // the word is NOT valid, lose 1 point
        return -1;
    }
    else if(validBit == -2){
        return 0; // this is a pass, don't change the score.
    }
    else{ // the word is a repreat, lost 2 points
        return -2;
    }

}