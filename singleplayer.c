/**
 * @file singleplayer.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 */

#include "GameLogic.h"
#include "WordServices.h"
#include <stdlib.h>
#include <string.h>

// TODO: Remove
#include <stdio.h>

struct Player *generateComputer();

 /**
  * @brief The singleplayer game! A single client enters
  * and interacts with a server generated "computer player".
  * 
  * @param socket
  * @param player 
  */
 //TODO: ADD SOCKET AS A INPUT! UPDATE GAMELOGIC.H
 void singleplayer(struct Player *player){
    // set up the game, define game constants =============
    struct Player *computer = generateComputer();
    char *input_text = malloc(sizeof(char)*12);
    input_text = selectInputTxt(input_text);
    
    char **usedWords = malloc(sizeof(char)*10);
    int num_of_passes = 0; 
    int turn_counter = 0;
    int usedLength = 0;
    int validBit = 0;
    // get random alphabet from input_xx.txt
    char *randAlphabet = getRandomAlphabet(input_text);
    
    // run the game ======================================
    //TODO: REMOVE
    char user_input[100];
    while(num_of_passes != 2){
        if(turn_counter == 0){ // player's turn
            player->opponent_score = computer->player_score;
            char *nextPlayerMsg = buildNextPlayerMsg(player, usedWords, &usedLength, randAlphabet);
            
            memset(user_input, 0, sizeof(user_input));
            // wait for user input
            /* TODO: replace with socket logic! <--->
            This code should send the nextPlayerMsg down the pipe,
            for display on the client side terminal, then wait for input.
            Input would be stored in user_input, memset should probably remain,
            it clears the string.
            */
            printf("%s", nextPlayerMsg);
            printf("Enter valid word: ");
            fgets(user_input, sizeof(user_input), stdin);

            // determine the validity of the score
            // update the player's score count.
            validBit = isValidWord(user_input, sizeof(user_input), &usedWords, &usedLength, input_text);
            player->player_score = (int)(player->player_score + calculateScore(validBit, user_input));

            /*
            The player can only leave their turn by entering a 
            valid word, or passing.
            */
            if(validBit == 1){ // word is valid
                // alternate Turn
                player->number_of_words_found++;
                turn_counter = alternateTurn(&turn_counter);
            }
            else if(validBit == 0){ // word is invalid, try again
                /* TODO: replace with socket logic! <--->
                Send the string below through the socket.
                The code above the if statement should be usable as the
                turn hasn't changed.
                */
                printf("Word was INVALID, Try again.\n");           
            }
            else if(validBit == -1){ // word is a repeat, try again
                /* TODO: replace with socket logic! <--->
                Send the string below through the socket.
                The code above the if statement should be usable as the
                turn hasn't changed.
                */
                printf("Word was a REPEAT, Try again.\n"); 
            }
            else{ // player has passed
                num_of_passes++;
                turn_counter = alternateTurn(&turn_counter);
            }
        }
        else { // computer's turn
            char* word = generateWord(input_text);
            validBit = isValidWord(word, sizeof(word), &usedWords, &usedLength, input_text);
            computer->player_score = (int)(computer->player_score + calculateScore(validBit, word));
            
            turn_counter = alternateTurn(&turn_counter);
        }

    }
    
    // end the game ======================================
    switch(declareWinner(player)){
        case 1:
            player->win_or_lose = "W";
            break;
        case 0:
            player->win_or_lose = "T";
            break;
        case -1:
            player->win_or_lose = "L";
            break;
    }
    writeScoreBoard(player);
    printf("\nGoodbye! \n");
    // write to scoreboard
    // "Would you like to read the scoreboard?"
    // free all memory and exit the program.
    free(computer);
    free(player);
    free(input_text);
    free(randAlphabet);
}

struct Player *generateComputer(){
    struct Player *computer = malloc(sizeof(struct Player));
    computer->opponent_pid = 0;
    computer-> player_pid = 0;
    computer->player_turn = 1; // go second
    computer->firstname = malloc(sizeof(char)*20);
    strcpy(computer->firstname, "Test");
    computer->lastname = malloc(sizeof(char)*20);
    strcpy(computer->lastname, "Player");
    computer->country = malloc(sizeof(char)*20);
    strcpy(computer->country, "Narnia");
    computer->opponent_score = 0;
    computer->player_score = 0;
    computer->number_of_words_found = 0;
    computer->number_of_words_added = 0;
    computer->win_or_lose = malloc(sizeof(char)*2);
    return computer;
}