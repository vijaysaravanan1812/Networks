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


void* recv_msg(void * sock){
    int sockfd = *((int *)sock);
    char buff[MAX];
    while(1){
        bzero(buff, sizeof(buff));
        recv(sockfd, buff, sizeof(buff), 0);
        if(strncmp(buff, "bye", 3) == 0){
            return NULL;;
        }
        printf("%s", buff);
    }
    return NULL;
}


int main(){
    pthread_t recv_thread;

    int sockfd;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Socket creation failed!\n");
        return 1;
    }

    struct sockaddr_in cli_addr;
    bzero(&cli_addr, sizeof(cli_addr));
    cli_addr.sin_port = PORT;
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    socklen_t len = sizeof(cli_addr);
    if(connect(sockfd, (struct sockaddr *)&cli_addr, len) < 0){
        perror("Connect error!");
        return 2;
    }

    printf("Enter your message and press enter to send it: ");

    pthread_create(&recv_thread,NULL, recv_msg, (void*)&sockfd);

    char buff[MAX];
    int n;
    while(1){
        bzero(buff, sizeof(buff));
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        send(sockfd, buff, strlen(buff), 0);
        if ((strncmp(buff, "bye", 3)) == 0)
        {
            printf("Client exit...\n");
            break;
        }
        
    }
    pthread_join(recv_thread, NULL);
    return 0;
}

