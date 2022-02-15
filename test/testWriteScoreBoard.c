#include <stdio.h>

struct Player
{
    char *first;
    char *last;
    char *country;
    int score;
    char *wl;
    int numFound;
    int numDict;
};

void writeScoreBoard(struct Player winner) //takes a player, the number of players and rounds, the array of final scores, and an int acting as a boolean to write the winner to the scoreboard.
{
    FILE *scoreboard;

    if (scoreboard = fopen("scoreboard.txt", "r")) //if file doesn't exist, make it. if it does, append it.
    {
        scoreboard = fopen("scoreboard.txt", "a");
    }
    else
    {
        scoreboard = fopen("scoreboard.txt", "w");
        fprintf(scoreboard, "First Name  Last Name    Country  Score   W/L   # Words Found   # Words Added to Dict\n");
    }
    
    fprintf(scoreboard, "%10s %10s %10s %6i %5s %15i %23i\n", winner.first, winner.last, winner.country, winner.score, winner.wl, winner.numFound, winner.numDict);
    fclose(scoreboard);
}

int main()
{
    struct Player winner = {"John", "Smith", "USA", 35, "Win", 10, 12};
    writeScoreBoard(winner);
}