/**
 * @file POSIXtest0.c
 * @author slayter teal (slayter.teal@okstate.edu)
 * @brief This is a testing bed for POSIX messaging. 
 * POSIXtest.c is one process while, POSIXtest0.c is meant to be
 * a seperate process.
 * 
 * The goal is to send and recieve messages and use
 * the data that is shared.
 * 
 * Compile using gcc ./test/POSIXtest.c -o POSIXtest.out -lrt
 */

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <mqueue.h> // message queue library
#include <signal.h> // cleanly handle CTRL+c
#include <string.h>

#define MAX_MSG_SIZE 512
#define MSG_BUFFER_SIZE MAX_MSG_SIZE+10
#define PROCESS_QUEUE_NAME "/q"

// message queue descriptors
mqd_t word_process;
mqd_t read_line;

// client pid
char *client_pid;

// dynamic buffer array
char *buffer; 

void exitHandler(int sig){
    printf("Cleanly exiting.\n");
    free(buffer);
    mq_close(read_line);
    mq_unlink(client_pid);
    mq_close(word_process);
    exit(1);
}


/*
Note that both mains need to be able to both, send and receive
messages.
*/
int main(){
    signal(SIGINT, exitHandler);
    char message[256];
    // get process pid
    client_pid = malloc(sizeof(char)*32);
    sprintf(client_pid, "/%d", getpid());
    printf("pid: %s\n", client_pid);

    strcpy(message, client_pid);
    strcat(message, "\n");
    strcat(message, "hello");
    strcat(message, "\n");

    // set read_line attr
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    // create and open read_line
    read_line = mq_open(client_pid, O_CREAT | O_RDONLY,  0660, &attr);

    // send message to word_processing ================================================== 
    while((word_process = mq_open(PROCESS_QUEUE_NAME, O_WRONLY)) == -1){
        printf("Cannot open msg_process queue!\n");
        continue;
    }
    
    mq_send(word_process, message, sizeof(message)+1, 0);
    
    // receive messages =================================================================
    char in_buffer[MSG_BUFFER_SIZE];
    if((mq_receive(read_line, in_buffer, MSG_BUFFER_SIZE, NULL)) == -1){
            printf("Failed to receive message... \n");
        }  
    printf("%s \n", in_buffer);

    mq_close(read_line);
    mq_close(word_process);
    mq_unlink(client_pid);

    return 0;
}