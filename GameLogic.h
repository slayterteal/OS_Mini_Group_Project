/**
 * @file GameLogic.h
 * @author Slayter Teal (slayter.teal@okstate.edu)
 * @brief Group D
 * @date 2022-02-27
 * 
 */
#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include "./Player.h"

int calculateScore(int validBit, char *word);
int alternateTurn(int *turnTracker);
char *buildNextPlayerMsg(struct Player *player, char **usedWords,int *usedLength, char *randAlphabet);
int declareWinner(struct Player *player);
void singleplayer(struct Player *player, int connfd);
char *selectInputTxt();
void writeScoreBoard(struct Player *winner, char *scoreFile);
void readScoreBoard(int connfd, char *scoreboard);
char *communication(int connfd, char *msg, char *client_response);

#endif