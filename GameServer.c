/**
 * @file GameServer.c
 * @author Mujahid Egan (mujahid.egan@okstate.edu)
 * 
 * @brief The server that will run the game when accessed by clients
 * 
 * @date 2022-02-17
 * 
 */

#include <Winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <sys/types.h>
#include <winsock.h>
#include <sys/types.h>
#include <ws2tcpip.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

void talking(int connfd)
{
    char buff[256];
    int n;
    for (;;) {
        bzero(buff, 256);
   
        read(connfd, buff, sizeof(buff));
        printf("From client: %s\t To client : ", buff);
        bzero(buff, 256);
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
          //copying the client message and then sending it back
        write(connfd, buff, sizeof(buff));
   
        if (strncmp("exit", buff, 4) == 0) {
             //an exit call so the client can close the connection
            printf("Server exiting..\n");
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_adr, cli_adr;
    //setting up the socket for connecting from the client
    if (argc < 2) {
         fprintf(stderr, "Error, no provided port.\n");
         exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
         error("There was an error opening the socket.");
    bzero((char *) &serv_adr, sizeof(serv_adr));
    portno = atoi(argv[1]);
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = INADDR_ANY;
    serv_adr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
        error("There was an error binding the socket.");
    listen(sockfd, 5);
    clilen = sizeof(cli_adr);

    int pid;
    while (1) {
         newsockfd = accept(sockfd, (struct sockaddr *) &cli_adr, &clilen);
         if (newsockfd < 0)
                error("There was an error accepting the client.");
         //fork for accepting multiple clients
         pid = fork();
         if (pid < 0) {
              error("There was an error forking the application.");
         }
         if (pid == 0) {
            close(sockfd);
            //commnicate with the server
            talking(newsockfd);
            close(newsockfd);
          } else {
             //parent process
             close(newsockfd);
          }
    }
   return 0;
}