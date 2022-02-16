/*
Player struct, keeps track of player data throughout the game.
*/

#ifndef PLAYER_H_
#define PLAYER_H_

struct Player{
    int opponent_pid;
    int player_pid;
    char *firstname;
    char *lastname;
    char *country;
    int opponent_score;
    int player_score;
    int number_of_words_found;
    int number_of_words_added;
};

#endif