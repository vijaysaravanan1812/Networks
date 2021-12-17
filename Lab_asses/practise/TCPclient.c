
//tcp client side
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>

#define PORT 5035
#define MAX 4096

void func(int sockfd) 
{ 
    char buff[MAX];
    int n; 
    for (;;) {
                
 	 	n = 0; 
 	 	while ((buff[n++] = getchar()) != '\n'); 
 	 	    write(sockfd, buff, sizeof(buff));  

            if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n");
            break; 
        }
        bzero(buff , MAX);
  	    read(sockfd , buff , sizeof(buff));
        printf("From server : %s" , buff );

 	} 
} 

int main()
{
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(client_socket == -1)
    {
        printf("Fail to create\n");
    }
    else{
        printf("Socket created\n");
    }

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = PORT; 
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) != 0)
    {
        printf("Failed to connect\n");
    }
    else{
        printf("Client connected\n");
    }
    func(client_socket);

    close(client_socket);

}



