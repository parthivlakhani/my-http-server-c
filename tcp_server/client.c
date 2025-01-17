// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char const *argv[])
{
    int sock = 0; long valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0}; // for storing server's message
    char message[1024]; // for storing client's message
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    while(1){
      printf("Client: ");
      fgets(message, 1024, stdin);
      message[strcspn(message, "\n")] = 0; 
      send(sock , message , strlen(message) , 0 );
      if(strcmp(message, "bye")==0){
        printf("Client disconnected\n");
        break;
      }
      
      memset(buffer, 0, sizeof(buffer));
      valread = read( sock , buffer, 1024);
      if(valread > 0){
        printf("Server: %s\n",buffer);
        buffer[strcspn(buffer, "\n")] = 0;
        if(strcmp(buffer,"bye")==0){
          printf("Server disconnected\n");
          break;
        }
      }
    }
    close(sock);
    return 0;
}

