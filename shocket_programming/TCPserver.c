#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netdb.h> 
#define BACKLOG 5
#define PORT 5035
#define MAX 4096

#include<netinet/in.h>

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

void print(int client_socket)
{
       char hello[MAX] = "hello to client\n";
   write(client_socket, hello, sizeof(hello));
   // bzero(hello, MAX);
    read(client_socket, hello, sizeof(hello));
    printf("From Client %s\n", hello);
    //bzero(hello, MAX);
    
}



int main()
{
    //create a server socket 
    int server_socket ,  client_socket;
    int len;
    // create variable on sockaddr_in
    struct sockaddr_in server_address, client_address;
    
    //AF_INET --> ip version 4
    //Sock_Stream --> TCP
    //0 --> protocal
    server_socket = socket(AF_INET, SOCK_STREAM , 0);

    // socket() return either -1 or +ve 
    if (server_socket == -1)
    {
        printf("server socket failed to create\n");
        exit(0);
    }
    else{
        printf("socket successfully created\n");
        //define server address 
    }

    //bzero parameter
    //Address of variable
    //size of that variable
    bzero(&server_address, sizeof(server_address));

    //set values to server_address 
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    

    //bind the socket specified ip and port   
                                     
    int b = bind(server_socket, (struct sockaddr *)&server_address , sizeof(server_address));
    if(b == 0)                                                                                                                                            
        printf("Binded Successfully\n");                                                                                                             
    else    
    {                                                                                                                                            
        printf("Binding Error\n"); 
        exit(0) ;                                                                                                                           
    }   

    //listen the network
    int l = listen(server_socket , BACKLOG);
    if(l == 0)                                                                                                                                            
        printf("Listening...\n");                                                                                                                    
    else {                                                                                                                                               
        printf("Not listening..\n"); 
        exit(0);
    }

    //Accept the connection
    len = sizeof(client_address); 
    client_socket = accept(server_socket , (struct sockaddr *)&client_socket , &len);
    if (client_socket < 0)
    {
        printf("Server accept failed\n");
        exit(0);
    }
    else {
        printf("Server accept the client\n");
        //send message  
    }
        
    
    print(client_socket);
    //close socket
    close(server_socket);
    return 0;
}