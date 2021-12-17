#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#define PORT 4999
#define MAX 1024
#define N 5 

int clientSockets[N+1];

void* clientHandler(void* client_socket){
    int cliSocket = *((int*)client_socket);
    printf("Thread for client %d created\n", cliSocket);
    
    int currentIndex = 0, i;
    for(i = 0; i < N ; i++)
        if(clientSockets[i] == cliSocket){
            currentIndex = i;
            break;
        }
    char msg[1054], buff[MAX];
    while(1){
        bzero(buff, sizeof(buff));
        recv(cliSocket, buff, MAX, 0);

        if(strlen(buff) > 0){
            printf("From client %d : %s", currentIndex, buff);
            if(strncmp(buff, "bye", 3) == 0){
                send(cliSocket, "bye", sizeof("bye"), 0);
                printf("Client sockfd %d to be closed\n", cliSocket);
                close(cliSocket);

                clientSockets[currentIndex] = -1;
                printf("Remaining connections: \n");
                for(int i = 0; i < N; i++)
                    printf("Index %d: connection fd: %d\n", i, clientSockets[i]);

                printf("Client %d disconnected\n", currentIndex);
                return NULL;
            }
            else{
                for(int i = 0; i < N; i++){
                    if(clientSockets[i] != -1 && clientSockets[i] != 0){
                        bzero(msg, MAX);
						if (i != currentIndex){
							sprintf(msg, "Message from client %d: %s", currentIndex, buff);
							printf("Message sent to %d: %s", i, buff);
							send(clientSockets[i], msg, strlen(msg), 0);
						}
                    }
                }
            }
        }

    }
    return NULL;
}

int main(){
    pthread_t clientThreads[N];

    int serverSocket;
    if((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Socket creation failed!");
        return 1;
    }

    struct sockaddr_in serv_addr, cli_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = PORT;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    socklen_t len = sizeof(serv_addr);

    bzero(&cli_addr, sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = PORT;
    cli_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(serverSocket, (struct sockaddr *)&serv_addr, len) < 0){
        perror("Binding failure!");
        return 2;
    }

    for(int i = 0; i < N; i++)
        clientSockets[i] = 0;

    if(listen(serverSocket, N) < 0){
        perror("Listen error!");
        return 3;
    }

    printf("Listening on port %d\n", PORT);

    int index = 0;
    while(1){
		label:
        index  = N;

        for(int i = 0; i < N; i++) 
            if(clientSockets[i] == 0){
                index = i;
                break;
            }
        clientSockets[index] = accept(serverSocket, (struct sockaddr *)&cli_addr, &len);

        printf("Current connections: \n");
        for(int i = 0; i < N; i++)
            printf("Index %d: connection fd: %d\n", i, clientSockets[i]);

        pthread_create(&clientThreads[index], NULL,  clientHandler, (void *)&clientSockets[index]);

        for(int i = 0;i < N; i++)
            if(clientSockets[i] != -1)
                goto label;
        break;
    }

    for(int i = 0; i < N; i++)
        pthread_join(clientThreads[i], NULL);
    return 0;
}
