/**
 * @file main.c
 * @author slayter teal
 * @brief This is a testing bed for POSIX messaging. 
 * main.c is one process while, main0.c is meant to be
 * a seperate process.
 * 
 * The goal is to send and recieve messages and use
 * the data that is shared.
 * 
 * I'll also be including notes and links to various things in 
 * seperate README.
 * 
 * Compile using gcc main.c -o main -lrt
 */

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h> // message queue library
#include <signal.h> // cleanly handle CTRL+c

#define MAX_MSG_SIZE
#define MSG_BUFFER_SIZE MAX_MSG_SIZE+10

mqd_t queue_send, queue_read;
char *buffer; // dynamic buffer array

void INThandler(int);

/*
Note that both mains need to be able to both, send and receive
messages.

Note that main/main0 are identical (accept for the data sent),
this is intentional, as all client instances will essentially be identical
as well. 
*/
int main(){
    signal(SIGINT, INThandler);
    // Sending "Hello" through a POSIX message queue.
    // the name should be dynamic in our project
    queue_send = mq_open("/m", O_CREAT | O_EXCL | O_WRONLY,  0600, NULL);

    // check if creation was successful
    if (queue_send == -1){
        printf("Queue creation failed :( \n");
        exit(1);
    }

    char *buffer; // buffer array
    unsigned int priority = 0;
    char *message = "Hello";
    // run constantly. 
    while(1){
        
        /*
        Check of the opponent has opened it's queue.
        */
        if((queue_read = mq_open("/m0", O_RDONLY)) == -1){
            printf("No opponent queue open! \n");
            continue;
        }

        /*
        We don't want to start sending messages into our queue until we know an 
        opponent is available to read them. If 'queue_read' is valid, then we know
        an opponent is looking at the queue, so we can send a message.
        */
        mq_send(queue_send, message, sizeof(message)+1, 10);

        // receive messages ==============================
        // get message_queue attributes
        struct mq_attr attr;
        mq_getattr(queue_read, &attr);

        buffer = calloc(attr.mq_msgsize, 1);
        if(buffer == NULL){
            printf("Something has gone wrong... \n");
            free(buffer);
            mq_close(queue_send);
            mq_close(queue_read);
            exit(1);
        }

        if((mq_receive(queue_read, buffer, attr.mq_msgsize, &priority)) == -1){
            printf("Failed to receive message... \n");
        }
        else {
            printf("%s \n", buffer);
        }

        // reset buffer
        buffer = NULL;
    }

    free(buffer);
    mq_close(queue_send);
    mq_close(queue_read);

    return 0;
}

void INThandler(int sig){
    printf("Cleanly exiting.");
    free(buffer);
    mq_close(queue_send);
    mq_close(queue_read);
    exit(1);
}