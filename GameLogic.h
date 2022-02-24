/**
 * @file GameLogic.h
 * @author Slayter Teal (slayter.teal@okstate.edu)
 * @brief A header file containing the various Game 
 * related functions.
 * 
 */
#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include "./Player.h"

int calculateScore(int validBit, char *word);
int alternateTurn(int *turnTracker);
char *buildNextPlayerMsg(struct Player *player, 
                        char **usedWords,
                        int *usedLength, 
                        char *randAlphabet, 
                        char *inputWord);
int declareWinner(struct Player *player);
void singleplayer(struct Player *player);
char *selectInputTxt();
void writeScoreBoard(struct Player *winner);

#endif