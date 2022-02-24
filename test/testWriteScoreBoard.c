#include <stdio.h>
#include "../GameLogic.h"

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

int main()
{
    struct Player *winner = {"John", "Smith", "USA", 35, "Win", 10, 12};
    writeScoreBoard(winner);
}