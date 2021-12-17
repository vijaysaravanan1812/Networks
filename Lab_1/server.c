#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 8081 
#define SA struct sockaddr 
 
void func(int sockfd) 
{ 
 	char buff[MAX];  		
    int n; 
 	for (;;) {
  	    bzero(buff, MAX);
        read(sockfd, buff, sizeof(buff)); 
 	    printf("From client: %s\t To client : ", buff); 
 	 	bzero(buff, MAX);
        n = 0; 
 	 	while ((buff[n++] = getchar()) != '\n') ; 
 			write(sockfd, buff, sizeof(buff)); 
        if (strncmp("exit", buff, 4) == 0) {  	 	 				printf("Server Exit...\n"); 
 	 	 	break; 
 	 	} 
 	} 
} 
 
 
int main() 
{ 
    int sockfd, client_socket, len; 
    struct sockaddr_in server_address, client_address; 
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
 	if (sockfd == -1) { 
 	 	printf("socket creation failed...\n"); 
 	 	exit(0); 
 	} 
 	else 
 	 	printf("Socket successfully created..\n");
        bzero(&server_address, sizeof(server_address)); 
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        server_address.sin_port = htons(PORT); 
 
    if ((bind(sockfd, (SA*)&server_address, sizeof(server_address))) != 0) {  	
         	printf("socket bind failed...\n");
            exit(0); 
 	} 
 	else 
 	 	printf("Socket successfully binded..\n"); 
 
 
    if ((listen(sockfd, 5)) != 0) {  	
        printf("Listen failed...\n");  	exit(0); 
    } 
 	else 
 	 	printf("Server listening..\n"); 
        len = sizeof(client_address); 
 
 	    client_socket = accept(sockfd, (SA*)&client_address, &len);
        if (client_socket < 0) { 
            printf("server accept failed...\n"); 
 	 	exit(0); 
 	    } 
 	    else 
 	 	    printf("server accept the client...\n"); 
 
 	 
        func(client_socket);
        close(sockfd); 
} 
