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
#include <unistd.h>
#include "../WordServices.h"

#define MAX_MSG_SIZE 512
#define MSG_BUFFER_SIZE MAX_MSG_SIZE+10
#define DICT_QUEUE_NAME "/dict"
#define SCOREBOARD_QUEUE_NAME "/scoreboard"
#define INPUT_TXT_QUEUE_NAME "/inputtxt"
#define DICT_CHECK 0
#define SCOREBOARD_UPDATE 1
#define INPUT_TXT_UPDATE 2

mqd_t read_line, return_line;
// char *buffer; // dynamic buffer array

void exitHandler(int sig){
    printf("Cleanly exiting.\n");
    // free(buffer);
    mq_close(return_line);
    mq_close(read_line);
    mq_unlink(DICT_QUEUE_NAME);
    mq_unlink(SCOREBOARD_QUEUE_NAME);
    mq_unlink(INPUT_TXT_QUEUE_NAME);
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
    char in_buffer[MSG_BUFFER_SIZE]; // buffer array


    int pid = fork();

    if (pid == 0)
    {
        pid = fork();

        if (pid == 0)
        {
            read_line = mq_open(INPUT_TXT_QUEUE_NAME, O_CREAT | O_RDONLY,  0660, &attr);

            // check if read_line creation was successful
            if (read_line == -1){
                printf("Queue creation failed :( \n");
                exit(1);
            }

            while(1){
                // receive messages ==================================================
                // mq_receive will block until a message is ready
                if((mq_receive(read_line, in_buffer, MSG_BUFFER_SIZE, NULL)) == -1){
                    printf("Failed to receive message... \n");
                }  
                printf("%s", in_buffer);

                // parse pid and word
                char *client_pid = strtok(in_buffer, "\n");
                printf("client_pid: %s\n", client_pid);
                char *input_txt = strtok(NULL, "\n");
                printf("input: %s\n", input_txt);
                char *word = strtok(NULL, "\n");
                printf("word: %s\n", word);

                /*for (int i = 0; i < strlen(word); i++)
                {
                    printf("%i\n", word[i]);
                }*/

                // get output from isValidDict(word)
                char *return_msg = malloc(sizeof(char) * 4); // very small

        
                if (isValidInput(input_txt, word) && isValidDict(word)) //testing whether isValidInput works independently, shouldnt actually need this line
                {
                    if (!isKnown(input_txt, word))
                    {
                        addToInput(input_txt, word);
                    }

                    return_msg = "1\n";
                }
                else
                {
                    return_msg = "0\n";
                }
                //sprintf(return_msg, "%d", isValidDict(word));

                // send messages =====================================================
                if((return_line = mq_open(client_pid, O_WRONLY)) == -1){
                    printf("Cannot open msg_process queue!\n");
                    exitHandler(0);
                }

                mq_send(return_line, return_msg, strlen(return_msg)+1, 0);

            }
        }

        read_line = mq_open(SCOREBOARD_QUEUE_NAME, O_CREAT | O_RDONLY,  0660, &attr);

        // check if read_line creation was successful
        if (read_line == -1){
            printf("Queue creation failed :( \n");
            exit(1);
        }

        while(1){
            // receive messages ==================================================
            // mq_receive will block until a message is ready
            if((mq_receive(read_line, in_buffer, MSG_BUFFER_SIZE, NULL)) == -1){
                printf("Failed to receive message... \n");
            }  
            printf("%s", in_buffer);

            // parse pid and word
            char *client_pid = strtok(in_buffer, "\n");
            printf("client_pid: %s\n", client_pid);
            char *word = strtok(NULL, "\n");
            printf("word: %s\n", word);

            for (int i = 0; i < strlen(word); i++)
            {
                printf("%i\n", word[i]);
            }

            // get output from isValidDict(word)
            char *return_msg = malloc(sizeof(char) * 4); // very small
            //sprintf(return_msg, "%d", isValidDict(word));
            return_msg = "B\n";

            // send messages =====================================================
            if((return_line = mq_open(client_pid, O_WRONLY)) == -1){
                printf("Cannot open msg_process queue!\n");
                exitHandler(0);
            }

            mq_send(return_line, return_msg, strlen(return_msg)+1, 0);

        }
    }

    // create queue to read from
    read_line = mq_open(DICT_QUEUE_NAME, O_CREAT | O_RDONLY,  0660, &attr);

    // check if read_line creation was successful
    if (read_line == -1){
        printf("Queue creation failed :( \n");
        exit(1);
    }

    // char reply[MSG_BUFFER_SIZE];
    // unsigned int priority = 0;
    // char *message = "Hello";
    
    // TODO: run constantly! 
    while(1){
        // receive messages ==================================================
        // mq_receive will block until a message is ready
        if((mq_receive(read_line, in_buffer, MSG_BUFFER_SIZE, NULL)) == -1){
            printf("Failed to receive message... \n");
        }  
        printf("%s", in_buffer);

        // parse pid and word
        char *client_pid = strtok(in_buffer, "\n");
        printf("client_pid: %s\n", client_pid);
        char *word = strtok(NULL, "\n");
        printf("word: %s\n", word);

        for (int i = 0; i < strlen(word); i++)
        {
            printf("%i\n", word[i]);
        }

        // get output from isValidDict(word)
        char *return_msg = malloc(sizeof(char) * 4); // very small
        sprintf(return_msg, "%d", isValidDict(word));

        // send messages =====================================================
        if((return_line = mq_open(client_pid, O_WRONLY)) == -1){
            printf("Cannot open msg_process queue!\n");
            exitHandler(0);
        }

        mq_send(return_line, return_msg, strlen(return_msg)+1, 0);

    }

    // free(buffer);
    mq_close(read_line);
    mq_close(return_line);
    mq_unlink(DICT_QUEUE_NAME);
    mq_unlink(SCOREBOARD_QUEUE_NAME);
    mq_unlink(INPUT_TXT_QUEUE_NAME);

    return 0;
}
