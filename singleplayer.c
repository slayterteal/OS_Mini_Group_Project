/**
 * @file singleplayer.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 * @brief Group D
 * @date 2022-02-27
 *
 * Reference: https://www.geeksforgeeks.org/named-pipe-fifo-example-c-program/
 */
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "GameLogic.h"
#include "WordServices.h"
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

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
 void singleplayer(struct Player *player, int connfd){
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

    //ADDED++++++++++++++++++
    // int fd;
    // char * named_pipe = "/tmp/pipe"; //create new named pipe with w/r permissions
    // mkfifo(named_pipe, 0666);

    // char valid_bit[1];
    // char input[20];
    //ADDED++++++++++++++++++
    
    // run the game ======================================
    char *user_input = malloc(sizeof(char)*512);
    while(num_of_passes != 2){
        if(turn_counter == 0){ // player's turn
            player->opponent_score = computer->player_score;
            // if (user_input != NULL) memset(user_input, 0, sizeof(user_input));
            char *nextPlayerMsg = buildNextPlayerMsg(player, usedWords, &usedLength, randAlphabet);
            // wait for user input
           strcpy(user_input, communication(connfd, strcat(nextPlayerMsg, "Enter a word: "), user_input));

            // determine the validity of the score
            // update the player's score count.

            
            // fd = open(named_pipe, O_WRONLY); //take user input to pass to word processing in separate process

            // write(fd, user_input, strlen(user_input)+1); //write user input to named pipe
            // close(fd);

            // fd = open(named_pipe, O_RDONLY); //wait for return data from word services
            // read(fd, valid_bit, sizeof(valid_bit));
            // printf("Valid: %c\n", valid_bit[0]); //for testing
            // close(fd);
            

            while(1){
                validBit = isValidWord(user_input, sizeof(user_input), &usedWords, &usedLength, input_text);
                // validBit = valid_bit[0] - '0';
                // printf("VALID: %i", validBit);
                player->player_score = (int)(player->player_score + calculateScore(validBit, user_input));
                /*
                The player can only leave their turn by entering a 
                valid word, or passing.
                */
                if(validBit == 1){ // word is valid
                    // alternate Turn
                    player->number_of_words_found++;
                    turn_counter = alternateTurn(&turn_counter);
                    break;
                }
                else if(validBit == 0){ // word is invalid, try again
                    strcpy(user_input, communication(connfd,"Word was INVALID, Try again.", user_input));
                    printf("Word was INVALID, Try again.");  
                    //fd = open(named_pipe, O_RDONLY); //wait for return data from word services
                    //read(fd, valid_bit, sizeof(valid_bit));
                    //printf("Valid: %c\n", valid_bit[0]); //for testing
                    //close(fd);      
                }
                else if(validBit == -1){ // word is a repeat, try again
                    strcpy(user_input, communication(connfd,"Word was REPEAT, Try again.", user_input));
                    printf("Word was a REPEAT, Try again."); 
                }
                else{ // player has passed
                    num_of_passes++;
                    turn_counter = alternateTurn(&turn_counter);
                    break;
                }
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
    writeScoreBoard(player, "singleplayer.txt");
    readScoreBoard(connfd, "singleplayer.txt");
    free(computer);
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