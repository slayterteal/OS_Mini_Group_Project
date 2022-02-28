/**
 * @file communication.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 * @brief Group D
 * @date 2022-02-27
 */
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "GameLogic.h"

/**
 * @brief A function that takes in a connection id and
 * a message pointer, sends the message to the client, then
 * returns that message.
 * 
 * @param connfd 
 * @param msg 
 */
char *communication(int connfd, char *msg, char *client_response) {
    char temp[512];
    while(1) {
        memset(temp, 0, sizeof(temp));

        // send message to the client
        send(connfd, msg, strlen(msg), 0); 

        recv(connfd, temp, sizeof(temp), 0);
        strcpy(client_response, temp);
        return client_response;
    }
}
