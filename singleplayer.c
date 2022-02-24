/**
 * @file singleplayer.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 */

#include "GameLogic.h"
#include "WordServices.h"
#include <stdlib.h>
#include <string.h>

// struct Player *generateComputer();

// /**
//  * @brief The singleplayer game! A single client enters
//  * and interacts with a server generated "computer player".
//  * 
//  * @param player 
//  */
// void singleplayer(struct Player *player){
//     // set up the game ==================================
//     // generate computer player
//     struct Player *computer = generateComputer();
    
//     char *input_text = malloc(sizeof(char)*12);
//     input_text = selectInputTxt(input_text);
//     char** usedWords;
//     int num_of_passes; 

//     // get random alphabet from input_xx.txt


//     // run the game ======================================

// }

// struct Player *generateComputer(){
//     struct Player *computer = malloc(sizeof(struct Player));
//     struct Player *computer = malloc(sizeof(struct Player));
//     computer->opponent_pid = 0;
//     computer-> player_pid = 0;
//     computer->player_turn = 1; // go second
//     computer->firstname = malloc(sizeof(char)*20);
//     strcpy(computer->firstname, "Test");
//     computer->lastname = malloc(sizeof(char)*20);
//     strcpy(computer->lastname, "Player");
//     computer->country = malloc(sizeof(char)*20);
//     strcpy(computer->country, "Narnia");
//     computer->opponent_score = 0;
//     computer->player_score = 0;
//     computer->number_of_words_found = 0;
//     computer->number_of_words_added = 0;

//     return computer;
// }