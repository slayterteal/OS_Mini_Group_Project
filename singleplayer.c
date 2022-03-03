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
#include <mqueue.h> // message queue library
#include <signal.h> // cleanly handle CTRL+c

#define MAX_MSG_SIZE 512
#define MSG_BUFFER_SIZE MAX_MSG_SIZE+10
#define DICT_QUEUE_NAME "/dict"
#define SCOREBOARD_QUEUE_NAME "/scoreboard"
#define INPUT_TXT_QUEUE_NAME "/inputtxt"

// TODO: Remove
#include <stdio.h>

// message queue descriptors
mqd_t word_process_dict, word_process_scoreboard, word_process_input_txt;
mqd_t read_line;

// client pid
char *client_pid;

// dynamic buffer array
char *buffer; 

/*void exitHandler(int sig){
    printf("Cleanly exiting.\n");
    free(buffer);
    mq_close(read_line);
    mq_unlink(client_pid);
    mq_close(word_process);
    exit(1);
}*/

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
    
    char **usedWords = malloc(sizeof(char)*20);
    *usedWords = malloc(sizeof(char) * 20);
    int num_of_passes = 0; 
    int turn_counter = 0;
    int usedLength = 0;
    int validBit = 0;
    // get random alphabet from input_xx.txt
    char *randAlphabet = getRandomAlphabet(input_text);

    //signal(SIGINT, exitHandler);
    char message[256];
    // get process pid
    client_pid = malloc(sizeof(char)*32); //using 'client' (server) ids for message passing, pretty much just left in to prove we could rework to use for multiplayer
    sprintf(client_pid, "/%d", getpid());
    printf("pid: %s\n", client_pid);

    strcpy(message, client_pid);
    strcat(message, "\n");
    //strcat(message, "hello");
    //strcat(message, "\n");

    //ADDED++++++++++++++++++
    // int fd;
    // char * named_pipe = "/tmp/pipe"; //create new named pipe with w/r permissions
    // mkfifo(named_pipe, 0666);

    // char valid_bit[1];
    // char input[20];
    //ADDED++++++++++++++++++

    // set read_line attr
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;
    char in_buffer[MSG_BUFFER_SIZE];

    read_line = mq_open(client_pid, O_CREAT | O_RDONLY,  0660, &attr); //open all queues

    // send message to word_processing ================================================== 
    while((word_process_dict = mq_open(DICT_QUEUE_NAME, O_WRONLY)) == -1){
        printf("Cannot open msg_process queue! DICT\n");
        continue;
    }

    while((word_process_scoreboard = mq_open(SCOREBOARD_QUEUE_NAME, O_WRONLY)) == -1){
        printf("Cannot open msg_process queue! SCOREBOARD\n");
        continue;
    }

    while((word_process_input_txt = mq_open(INPUT_TXT_QUEUE_NAME, O_WRONLY)) == -1){
        printf("Cannot open msg_process queue! INPUT\n");
        continue;
    }
    
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

                // create and open read_line
                strcpy(message, client_pid); //build isValidDict msg
                strcat(message, "\n");
                strcat(message, user_input);
                //strcat(message, "\n");

                if (strcmp(user_input, "\n") == 0) //pass
                {
                    validBit = 2;
                }
                else
                {
                    mq_send(word_process_dict, message, sizeof(message)+1, 0); //send msg to isValidDict fork
        
                    // receive messages =================================================================
                    if((mq_receive(read_line, in_buffer, MSG_BUFFER_SIZE, NULL)) == -1){ //read from isValidDict fork
                            printf("Failed to receive message... \n");
                    }  

                    printf("RECEIVED DICT: %s \n", in_buffer); //returned from isValidDict fork
                    int validDict = in_buffer[0] - '0';

                    mq_send(word_process_scoreboard, message, sizeof(message)+1, 0); //send msg to scoreboard fork

                    if((mq_receive(read_line, in_buffer, MSG_BUFFER_SIZE, NULL)) == -1){ //try to read from scoreboard fork
                            printf("Failed to receive message... \n");
                    }  

                    printf("RECEIVED SCOREBOARD: %s \n", in_buffer); //received scoreboard val

                    strcpy(message, client_pid); //build message for input txt fork
                    strcat(message, "\n");
                    strcat(message, input_text);
                    strcat(message, "\n");
                    strcat(message, user_input);

                    mq_send(word_process_input_txt, message, sizeof(message)+1, 0); //send msg to input txt fork

                    if((mq_receive(read_line, in_buffer, MSG_BUFFER_SIZE, NULL)) == -1){ //try to read from input txt fork
                            printf("Failed to receive message... \n");
                    }  

                    printf("RECEIVED INPUT_TXT: %s \n", in_buffer); //return val from input txt fork

                    int inputValid = in_buffer[0] - '0';

                    if (inputValid && validDict)
                    {
                        validBit = 1;
                    }
                    else
                    {
                        validBit = 0;
                    }
                    
                    //WIP++++++
                    /*printf("USEDLENGTH %i\n", usedLength);

                    for (int i = 0; i < usedLength; i++)
                    {
                        printf("USED: %s\n", usedWords[i]);
                    }

                    if (isUsedWord(user_input, usedWords, usedLength)) //denotes repeat word
                    {
                        validBit = -1;
                    }*/
                    //WIP++++++

                    /*for (int i = 0; i < strlen(in_buffer); i++)
                    {
                        printf("%c", in_buffer[i]);
                    }*/
                    
                    //validBit = isValidWord(user_input, sizeof(user_input), &usedWords, &usedLength, input_text);
                    

                    /*strcpy(message, client_pid);
                    strcat(message, "\n");
                    strcat(message, user_input);
                    //strcat(message, "\n");

                    mq_send(word_process, message, sizeof(message)+1, 0);*/

                    // printf("VALID: %i", validBit);

                    player->player_score = (int)(player->player_score + calculateScore(validBit, user_input));
                    /*
                    The player can only leave their turn by entering a 
                    valid word, or passing.
                    */
                }
                
                if(validBit == 1){ // word is valid
                    // alternate Turn
                    player->number_of_words_found++;
                    turn_counter = alternateTurn(&turn_counter);
                    //usedLength++;

                    /*if (usedLength == 1) //WIP, currently causes hanging/memory issues
                    {
                        strcpy(usedWords[0], user_input);
                    }
                    else
                    {
                        //char **tempUsed = addToUsed(usedWords, user_input, usedLength); //add to used array
                        usedWords = calloc(usedLength, sizeof(char) * 20);
                        usedWords[usedLength - 1] = calloc(1, sizeof(char) * 20);

                        printf("AFDSVF\n");
                        for (int i = 0; i < usedLength; i++)
                        {
                            strcpy(usedWords[i], user_input);
                        }
                    }*/

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

            strcpy(message, client_pid);
            strcat(message, "\n");
            strcat(message, word);
            //strcat(message, "\n");

            mq_send(word_process_dict, message, sizeof(message)+1, 0);

            // receive messages =================================================================
            if((mq_receive(read_line, in_buffer, MSG_BUFFER_SIZE, NULL)) == -1){
                    printf("Failed to receive message... \n");
            }  

            printf("RECEIVED DICT: %s \n", in_buffer);
            validBit = in_buffer[0] - '0';
            //validBit = isValidWord(word, sizeof(word), &usedWords, &usedLength, input_text);
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
    mq_close(read_line);
    mq_close(word_process_dict);
    mq_close(word_process_scoreboard);
    mq_close(word_process_input_txt);
    mq_unlink(client_pid);
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