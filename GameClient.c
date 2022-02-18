/**
 * @file GameClient.c
 * @author Mujahid Egan (mujahid.egan@okstate.edu)
 * 
 * @brief A client file that will connect to the server and allow you to send messages to it
 * 
 * @date 2022-02-17
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <sys/types.h>
#include <winsock.h>
#include <sys/types.h>
#include <Winsock2.h>
#include <ws2tcpip.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void talking(int sockfd)
{
    char buff[256];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Type your message: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From server: %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client exiting..\n");
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    int sockfd, portno;
    struct sockaddr_in serv_adr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("Error opening the socket.");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"Error, there is no host.\n");
        exit(0);
    }
    bzero((char *) &serv_adr, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_adr.sin_addr.s_addr,
         server->h_length);
    serv_adr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_adr,sizeof(serv_adr)) < 0) 
        error("Error connecting..");
    talking(sockfd);
    close(sockfd);
    return 0;
}