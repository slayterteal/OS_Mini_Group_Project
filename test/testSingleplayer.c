/**
 * @file testSingleplayer.c
 * @author slayter teal (slayter.teal@okstate.edu)
 * @brief test code for the singleplayer functionality
 */

// gcc -Wall ./test/testSingleplayer.c ./*.c -o a.out 

#include "../GameLogic.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// temp include
#include "../WordServices.h"

struct Player *generatePlayer();

int main(){
    // struct Player *player = generatePlayer();
    
    // test get random alphabet
    char *input_text = "input_01.txt";
    char *randAlphabet = getRandomAlphabet(input_text);
    printf("Random Alphabet = %s\n", randAlphabet);

    return 0;
}

/**
 * @brief A function to generate the test player.
 * 
 * @return struct Player* 
 */
struct Player *generatePlayer(){
    struct Player *player = malloc(sizeof(struct Player));
    player->opponent_pid = 0;
    player-> player_pid = 0;
    player-> player_turn = 0; // go first
    player->firstname = malloc(sizeof(char)*20);
    strcpy(player->firstname, "Test");
    player->lastname = malloc(sizeof(char)*20);
    strcpy(player->lastname, "Player");
    player->country = malloc(sizeof(char)*20);
    strcpy(player->country, "Narnia");
    player->opponent_score = 0;
    player->player_score = 0;
    player->number_of_words_found = 0;
    player->number_of_words_added = 0;

    return player;
}