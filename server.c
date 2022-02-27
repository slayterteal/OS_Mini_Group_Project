/**
 * @file GameServer.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 * @brief Group D
 * @date 2022-02-17
 * 
 * gcc server.c -o server.out
 * 
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
#define PORT 8888


void error(const char *msg) {
    perror(msg);
    exit(1);
}

/**
 * @brief A function that takes in a connection id and
 * a message pointer, sends the message to the client, then
 * returns that message.
 * 
 * @param connfd 
 * @param msg 
 */
char communication(int connfd, char *msg) {
    char msg_buffer[512];
    int n;
    while(1) {
        memset(msg_buffer, 0, sizeof(msg_buffer));

        // send message to the client
        send(connfd, msg, strlen(msg), 0); 

        recv(connfd, msg_buffer, sizeof(msg_buffer), 0);
        return *msg_buffer;
    }
}

void exitHandler(int sig){
    // wait for all processes to exit
    wait(NULL); // no effect for clients
    exit(1);
}

int main() {
    // catch <CTRL+C> to clean nicely
    signal(SIGINT, exitHandler);

    // ignore when a client exits, prevents zombies!
    signal(SIGCHLD,SIG_IGN);
    
    // server setup ===============================================================
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_adr, cli_adr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
         error("There was an error opening the socket.");
    bzero((char *) &serv_adr, sizeof(serv_adr));
    
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = INADDR_ANY;
    serv_adr.sin_port = htons(PORT);
    
    if (bind(sockfd, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
        error("There was an error binding the socket.");
    listen(sockfd, 5);
    clilen = sizeof(cli_adr);

    // end of setup =================================================================
    printf("Server is running! \n");

    int pid;
    while (1) { // waiting for connections
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_adr, &clilen);
        if (newsockfd < 0)
            error("There was an error accepting the client.");
        //fork for accepting multiple clients
        pid = fork();
        if (pid < 0) {
            error("There was an error forking the application.");
        }
        if (pid == 0) { // client process
            // the client process should NEVER exit this if block
            close(sockfd);
            char *client_msg = malloc(sizeof(char)*512); // used to get user message
            while(1){
                /*
                inside of a while loop
                main menu
                    return selection
                some if loops
                    pass variables to the appropriate functions
                    return to the main menu.
                */

                client_msg = communication(newsockfd, "Test message\n");
                printf("Client response: %s", client_msg); // client response
            }
            close(newsockfd);
        } 
        else { // parent process
            close(newsockfd);
        }
    }
   return 0;
}