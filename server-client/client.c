/**
 * @file client.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 * @brief Group D
 * @date 2022-02-27
 * 
 * gcc ./server-client/client.c -o client.out
 * 
 * Reference:
 * https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
 */
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8889


void error(const char *msg) {
    perror(msg);
    exit(0);
}

void communicating(int sockfd) {
    char msg_buffer[512]; // buffer for msg send/receive
    int n;
    while(1) {
        
        // read from the server =======================================
        memset(msg_buffer, 0, sizeof(msg_buffer));
        recv(sockfd, msg_buffer, sizeof(msg_buffer), 0);
        printf("%s", msg_buffer);
        if ((strncmp(msg_buffer, "exit", 4)) == 0) {
            printf("Client exiting..\n");
            break;
        }

        // take in user input, send to server ==========================
        memset(msg_buffer, 0, sizeof(msg_buffer));
        printf("\n");
        n = 0;
        while ((msg_buffer[n++] = getchar()) != '\n');
        write(sockfd, msg_buffer, sizeof(msg_buffer));
    }
}

int main() {
    // connecting to a server =================================================
    int sockfd;
    struct sockaddr_in server_address;
    struct hostent *server;

    char buffer[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("Error opening the socket.");
    bzero((char *) &server_address, sizeof(server_address));
    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);

    if (connect(sockfd,(struct sockaddr *) &server_address,sizeof(server_address)) < 0) 
        error("Error connecting..");

    // end connecting ==========================================================
    communicating(sockfd);
    close(sockfd);
    return 0;
}