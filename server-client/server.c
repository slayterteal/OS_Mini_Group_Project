/**
 * @file GameServer.c
 * @author Slayter Teal (slayter.teal@okstate.edu)
 * @brief Group D
 * @date 2022-02-17
 * 
 * gcc ./server-client/server.c -o server.out
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
#include <mqueue.h>
#include <signal.h>
#include "../GameLogic.h"
#define PORT 8889


void error(const char *msg) {
    perror(msg);
    exit(1);
}

struct Player *createPlayer(int connfd, struct Player *player, char *client_response){
    player->opponent_pid = 0;
    player-> player_pid = 0;
    player-> player_turn = 0; 
    player->firstname = malloc(sizeof(char)*64);
    strcpy(player->firstname, strtok(communication(connfd, "Enter player name: ", client_response), "\n"));
    player->lastname = malloc(sizeof(char)*64);
    strcpy(player->lastname, strtok(communication(connfd, "Enter player last name: ", client_response), "\n"));
    player->country = malloc(sizeof(char)*64);
    strcpy(player->country, strtok(communication(connfd, "Enter player country: ", client_response), "\n"));
    player->opponent_score = 0;
    player->player_score = 0;
    player->number_of_words_found = 0;
    player->number_of_words_added = 0;

    return player;
}

void exitHandlerTop(int sig){
    // wait for all processes to exit
    wait(NULL); // no effect for clients
    exit(1);
}

int main() {
    // catch <CTRL+C> to clean nicely
    signal(SIGINT, exitHandlerTop);

    // ignore when a client exits, prevents zombies!
    signal(SIGCHLD,SIG_IGN);
    
    // server setup ===============================================================
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_adr, cli_adr;

    // char valid_bit[1];
    // char input[20];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
         error("There was an error opening the socket.");
    
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
        // fork for accepting multiple clients
        pid = fork();
        if (pid < 0) {
            error("There was an error forking the application.");
        }
        if (pid == 0) { // client process
            // the client process should NEVER exit this if block
            close(sockfd);
            char client_response [512]; // used to get user message
            char main_menu[128];
            struct Player *player = malloc(sizeof(struct Player));
            strcpy(main_menu, "1. Singleplayer Mode\n2. Multiplayer Mode\n3. Exit");
            while(1){
                memset(client_response, 0, sizeof(client_response));
                strcpy(client_response, communication(newsockfd, main_menu, client_response));
               int menu_option = client_response[0] - '0';
               if(menu_option == 1){
                   printf("singleplayer \n");
                   player = createPlayer(newsockfd, player, client_response);
                   singleplayer(player, newsockfd);
               }
               else if(menu_option == 2){
                   printf("Mujahid Egan did not do his part.\n");
               }
               else if(menu_option == 3){
                   printf("Exit.\n");
                   free(player);
                   exitHandlerTop(0);
               }
               else{ // invalid option
                    printf("\nInvalid Option, Try Again\n");
                   continue;
               }
            }
            close(newsockfd);
        } 
        else { // parent process
            close(newsockfd);
        }
    }
   return 0;
}