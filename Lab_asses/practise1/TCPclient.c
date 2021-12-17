#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>

#define MAX 4096
#define PORT 5035

void func(int client_socket)
{
	char buff[MAX];
	int n;
	for(;;){
		while((buff[n++] = getchar()) != '\n');
	
		write(client_socket , buff, sizeof(buff));
		
		if(strncmp(buff , "exit" , 4 ) == 0){
			printf("client exit\n");
			break;
		}
		bzero(buff , MAX);
		read(client_socket , buff , sizeof(buff));
		printf("From server : %s", buff);
		
	}	
}

int main()
{
	int client_socket;
	
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(client_socket == -1)
	{
		printf("Failed to create\n");
		exit(0);
	}
	else
	{
		printf("Socket successfully created\n");
	}
	
	struct sockaddr_in server_address;
	bzero(&server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(connect(client_socket , (struct sockaddr *)&server_address , sizeof(server_address)) != 0)
	{
		printf("Server connection failed\n");
		exit(0);
	}
	else{
		printf("client connected to server\n");
		
	}
	
	func(client_socket);
	
	close(client_socket);
	
	return 0;

}


