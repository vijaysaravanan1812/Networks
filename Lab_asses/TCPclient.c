

#include<stdio.h>
#include<stdlib.h>

//Network header files
#include <netdb.h> 
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
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

void print(int client_socket)
{
    char hello[MAX] = "Hello server\n";
   // bzero(hello, MAX);

    write(client_socket , hello , sizeof(hello));
     bzero(hello, MAX);
   //  printf("hi\n");
    read(client_socket, hello, sizeof(hello));
    printf("From server %s\n", hello);
}
 

int main()
{
    //create socket
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM , 0);
    
    if (client_socket == -1) 
    { 
 	 	printf("socket creation failed...\n"); 
 	 	exit(0); 
 	} 
 	else 
 	 	printf("Socket successfully created..\n"); 

    // Specify address for socket 
    struct sockaddr_in  server_address;
    bzero(&server_address, sizeof(server_address)); 
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    //Conection
    
   if (connect(client_socket , (struct sockaddr *)&server_address, sizeof(server_address)) != 0) { 
 	 	printf("socket connectiom failed...\n"); 
 	 	exit(0); 
 	} 
 	else 
 	 	printf("Socket connected..\n");   
    //checking connection error
    
    //func(client_socket);
    
    
    func(client_socket);
    //close socket
    close(client_socket);

    return 0;                 
}