/**
 * @file POSIXtest.c
 * @author slayter teal (slayter.teal@okstate.edu)
 * @brief This is a testing bed for POSIX messaging. 
 * POSIXtest.c is one process while, POSIXtest0.c is meant to be
 * a seperate process.
 * 
 * The goal is to send and recieve messages and use
 * the data that is shared.
 * 
 * Compile using gcc ./test/POSIXprocess.c ./*.c -o POSIXprocess.out -lrt
 */

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <mqueue.h> // message queue library
#include <signal.h> // cleanly handle CTRL+c
#include <string.h>
#include "../WordServices.h"

#define MAX_MSG_SIZE 512
#define MSG_BUFFER_SIZE MAX_MSG_SIZE+10
#define PROCESS_QUEUE_NAME "/q"

mqd_t read_line, return_line;
// char *buffer; // dynamic buffer array

void exitHandler(int sig){
    printf("Cleanly exiting.\n");
    // free(buffer);
    mq_close(return_line);
    mq_close(read_line);
    mq_unlink(PROCESS_QUEUE_NAME);
    exit(1);
}

/*
The purpose of this code is to have a fixed "read" line, and test
dynamically sending messages based on what is received on the "read" line.
*/
int main(){
    signal(SIGINT, exitHandler);
    
    // set POSIX attributes
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    // create queue to read from
    read_line = mq_open(PROCESS_QUEUE_NAME, O_CREAT | O_RDONLY,  0660, &attr);

    // check if read_line creation was successful
    if (read_line == -1){
        printf("Queue creation failed :( \n");
        exit(1);
    }

    

    char in_buffer[MSG_BUFFER_SIZE]; // buffer array
    // char reply[MSG_BUFFER_SIZE];
    // unsigned int priority = 0;
    // char *message = "Hello";
    
    // TODO: run constantly! 
    //while(1){
        // receive messages ==================================================
        // mq_receive will block until a message is ready
        if((mq_receive(read_line, in_buffer, MSG_BUFFER_SIZE, NULL)) == -1){
            printf("Failed to receive message... \n");
        }  
        printf("%s", in_buffer);

        // parse pid and word
        char *client_pid = strtok(in_buffer, "\n");
        // printf("client_pid: %s\n", client_pid);
        char *word = strtok(NULL, "\n");
        // printf("word: %s\n", word);

        // get output from isValidDict(word)
        char *return_msg = malloc(sizeof(char) * 4); // very small
        sprintf(return_msg, "%d", isValidDict(word));

        // send messages =====================================================
        if((return_line = mq_open(client_pid, O_WRONLY)) == -1){
            printf("Cannot open msg_process queue!\n");
            exitHandler(0);
        }

        mq_send(return_line, return_msg, strlen(return_msg)+1, 0);

    //}

    // free(buffer);
    mq_close(read_line);
    mq_close(return_line);
    mq_unlink(PROCESS_QUEUE_NAME);

    return 0;
}
