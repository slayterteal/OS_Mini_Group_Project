/**
 * @file selectInputTxt.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 * 
 */
#include <string.h>
#include <stdlib.h>
#include <time.h>

int randNumber();

char *selectInputTxt(char *input_file){
    int randNum = randNumber();
    //TODO: if statement for checking if the value of randNum is 10 or not
    strcat(input_file, "input");
    if(randNum < 10){
        char temp[2];
        temp[0] = randNum+'0';
        strcat(input_file, "_0");
        strcat(input_file, &temp[0]);
        strcat(input_file, ".txt");
    }
    else{
        strcat(input_file, "_10");
        strcat(input_file, ".txt");
    }
    return input_file;
}

int randNumber(){
    int lower = 1;
    int upper = 10;

    srand(time(0)); // use time for random seed
    int num = (rand() % (upper-lower+1)) + lower; // from geeksforgeeks :p
    return num;
}