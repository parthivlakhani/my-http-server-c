// Server side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0}; // for storing client's message
    char message[1024]; // for storing server's message
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
    while(1)
    {    
        memset(buffer, 0,sizeof(buffer));
        valread = read( new_socket , buffer, 1024);
        if(valread>0){
          printf("Client: %s\n",buffer );
          buffer[strcspn(buffer, "\n")] =0;
          if(strcmp(message, "bye")==0){
            printf("Client disconnected\n");
            break;
          }
        }
        printf("Server: ");
        fgets(message, 1024, stdin);
        message[strcspn(message, "\n")]=0;;
        send(new_socket, message, strlen(message), 0);
        if(strcmp(message,"bye") == 0){
          printf("Server disconnected\n");
          break;
        }
    }
    close(new_socket);
    close(server_fd);
    return 0;
}

