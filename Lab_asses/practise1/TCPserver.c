#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>

#define BACKLOG 5
#define PORT 5035
#define MAX 4096

int func(int client_socket)
{
    char buff[MAX] ; int n = 0;
    for ( ; ;)
    {

        read(client_socket , buff , sizeof(buff));
         printf("From client : %s \t To client " , buff );
         bzero(buff , MAX);
          n = 0;
         while ((buff[n++] = getchar()) != '\n');
            write(client_socket , buff, sizeof(buff));
         if(strncmp("exit" , buff , 4 ) == 0)
        {
             break;
         }
    }

}

int main()
{
	int server_socket, client_socket;
	struct sockaddr_in server_address, client_address;
	
	server_socket = socket(AF_INET , SOCK_STREAM, 0 );
	
	if(server_socket == -1)
	{
		printf("Failed to create\n");
		exit(0);
	}
	else
	{
		printf("Socket created\n");
	}
	bzero(&server_address, sizeof(server_address));
	
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	int b = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
	if(b == -1)
	{
		printf("Failed to create\n");
		exit(0);		
	}
	else{
		printf("Successfully created\n");
	}
	
	int l = listen(server_socket, BACKLOG);
	if(l == -1)
	{
		printf("failed to listen\n");
	
	}
	else{
		printf("listening...\n");
	}
	
	int len = sizeof(client_socket);
	client_socket = accept(server_socket, (struct sockaddr *)&client_socket, &len);
	if(client_socket == -1)
	{
		printf("Failed to accept the client\n");
		exit(0);
	}
	else{
		printf("Client accepted by server\n");
	}
	
	func(client_socket);
	
	close(client_socket);

	return 0;
}


