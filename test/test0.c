/*
REFERENCED EXAMPLE FROM https://www.geeksforgeeks.org/named-pipe-fifo-example-c-program/
*/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;
    char * named_pipe = "/tmp/pipe"; //create new named pipe with w/r permissions
    mkfifo(named_pipe, 0666);

    char valid_bit[1];
    char input[20];

    while (1)
    {
        fd = open(named_pipe, O_WRONLY | O_RDONLY); //take user input to pass to word processing in separate process
        fgets(input, 20, stdin);

        write(fd, input, strlen(input)+1); //write user input to named pipe
        //close(fd);

        //fd = open(named_pipe, O_RDONLY); //wait for return data from word services
        read(fd, valid_bit, sizeof(valid_bit));
        printf("Valid: %c\n", valid_bit[0]); //for testing
        close(fd);
    }
    return 0;
}