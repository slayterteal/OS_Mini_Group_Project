/**
 * @file generateWord.c
 * @author Jackson Wildman (you@domain.com)
 * @brief Group D
 * @date 2022-02-27
 * 
 */

/*
REFERENCED EXAMPLE FROM https://www.geeksforgeeks.org/named-pipe-fifo-example-c-program/
*/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "WordServices.h"

int wordMessaging()
{
    int fd1;
    char * named_pipe = "/tmp/pipe"; //create new named pipe with w/r permissions
    mkfifo(named_pipe, 0666);

    char input[100];
    char valid_bit[1];

    while (1)
    {
        // First open in read only and read
        fd1 = open(named_pipe,O_RDONLY); //read input data from user
        read(fd1, input, 100);
        close(fd1);

        fd1 = open(named_pipe,O_WRONLY); //pass input into word processing and write result to named pipe
        valid_bit[0] = isValidDict(input) + '0';
        
        write(fd1, valid_bit, strlen(valid_bit)+1);
        printf("%s", input);
        close(fd1);
    }

    return 0;
}