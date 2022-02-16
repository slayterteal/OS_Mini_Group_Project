/**
 * @file testAlternateTurn.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 */

#include "../GameLogic.h"
#include <stdio.h>

// test alternateTurn() function.
int main(){
    int turn = 0;
    turn = alternateTurn(&turn);
    printf("Current turn: %d \n", turn);
    turn = alternateTurn(&turn);
    printf("Current turn: %d \n", turn);
    return 0;
}