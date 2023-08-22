/*Write a client program to send a manually crafted HTTP request packet to a Web Server
and display all fields received in HTTP Response at client Side.*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

#define PORTNO 5656

int main() {
    int sd;  // Socket descriptor
    struct sockaddr_in address;  // Address structure for server
    sd = socket(AF_INET, SOCK_DGRAM, 0);  // Create UDP socket
    address.sin_family = AF_INET;  // IPv4 address family
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address
    address.sin_port = htons(PORTNO);  // Port number
    char buf[256];  // Buffer to hold HTTP request
    int len = sizeof(address);  // Length of address structure

    printf("Enter the request: ");
    scanf("%[^\n]", buf);  // Input the HTTP request
    sendto(sd, buf, sizeof(buf), 0, (struct sockaddr *)&address, len);  // Send the HTTP request to server

    return 0;
}
