/**
 * @file writeScoreBoard.c
 * @author Jackson Wildman (jawildm@okstate.edu)
 * @brief Group D
 * @date 2022-27-02
 * 
 */
#include "GameLogic.h"
#include "WordServices.h"
#include <stdio.h>

/**
 * @brief Writes a player to the scoreboard.
 * takes a player, the number of players and rounds,
 * the array of final scores, and an int acting as a boolean
 * to write the winner to the scoreboard.
 * 
 * @param winner 
 */
void writeScoreBoard(struct Player *winner, char *scoreFile) 
{
    FILE *scoreboard;

    if ((scoreboard = fopen(scoreFile, "r"))) //if file doesn't exist, make it. if it does, append it.
    {
        scoreboard = fopen(scoreFile, "a");
    }
    else
    {
        scoreboard = fopen(scoreFile, "w");
        fprintf(scoreboard, "First Name  Last Name    Country  Score   W/L   # Words Found   # Words Added to Dict\n");
    }
    
    fprintf(scoreboard, "%10s %10s %10s %6i %5s %15i %23i\n", winner->firstname, winner->lastname, winner->country, winner->player_score, winner->win_or_lose, winner->number_of_words_found, winner->number_of_words_added);
    fclose(scoreboard);
}