/**
 * @file testSelectInputTxt.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 * @brief test code for selectInputTxt.c
 */

// gcc -Wall ./test/testSelectInputTxt.c ./*.c -o a.out 
#include <stdio.h>
#include <stdlib.h>
#include "../GameLogic.h"

int main(){
    char *input_file = malloc(sizeof(char)+12);
    input_file = selectInputTxt(input_file);
    printf("Input file is: %s \n", input_file); 
    return 0;
}