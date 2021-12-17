
//Tcp chat
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<netdb.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#define MAX 4096
#define BACKLOG 5
#define PORT 5035


void func(int client_socket)
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
    int len;
    struct sockaddr_in server_address, client_address;

    server_socket = socket(AF_INET, SOCK_STREAM, 0 );

    if (server_socket == -1 )
    {
        printf("failed to create \n");
        exit(0);
    }
    else
    {
        printf("Socket sucessfully created\n");

    }
 

    bzero(&server_address, sizeof(server_address));
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int b = bind(server_socket, (struct sockaddr *)&server_address , sizeof(server_address));
    if(b == 0){
        printf("Bind successfull \n");
    }
    else 
    {
        printf("Bind failed\n");
        exit(0);

    }

    int l = listen(server_socket, BACKLOG);
    if(l == 0)
    {
        printf("listening.. \n");
    }
    else{
        printf("Listen failed \n");
        exit(0);
    }
    int i = 0;
    len = sizeof(client_socket);
    client_socket = accept(server_socket, (struct sockaddr *)&client_socket, &len);
    if (client_socket == -1)
    {
       
        printf("failed to accept \n");
    }
    else {
     
         printf("Accepted \n");

    }

    func(client_socket);

    close(client_socket);
    

    return 0 ;
}

