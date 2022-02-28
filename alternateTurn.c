/**
 * @file alternateTurn.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 * @brief Group D
 * @date 2022-27-02
 */

#include "GameLogic.h"

/**
 * @brief A very simple method that flips the turn
 * tracker to denote a change of turns.
 * 
 * @param turnTracker
 * @return int 
 */
int alternateTurn(int *turnTracker){
    return !*turnTracker;
}