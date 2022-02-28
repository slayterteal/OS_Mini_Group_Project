/**
 * @file getRandomAlphabet.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 * @brief Group D
 * @date 2022-27-02
 */

#include "WordServices.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Get the Random Alphabet string from the first
 * line of the specified input_xx.txt
 * 
 * @param input_text 
 * @return char* 
 */
char *getRandomAlphabet(char *input_text){
    char *randAlphabet = malloc(sizeof(char)*12);
    FILE *input;
    input = fopen(input_text, "r");
    fgets(randAlphabet, 12, input);
    fclose(input);
    return randAlphabet; 
}