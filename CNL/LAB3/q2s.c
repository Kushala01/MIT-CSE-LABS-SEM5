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
    char buf[256];  // Buffer to hold HTTP request
    struct sockaddr_in sadd, cadd;  // Server and client address structures
    sd = socket(AF_INET, SOCK_DGRAM, 0);  // Create UDP socket
    sadd.sin_family = AF_INET;  // IPv4 address family
    sadd.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address
    sadd.sin_port = htons(PORTNO);  // Port number
    int result = bind(sd, (struct sockaddr *)&sadd, sizeof(sadd));  // Bind the socket
    int len = sizeof(cadd);

    // Receive the manually crafted HTTP request from the client
    recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&cadd, &len);
    
    // Craft a command to send the HTTP request and save the response to a file
    char command[512];
    sprintf(command, "echo -en %s | nc stackoverflow.com 80 > x.html", buf);
    
    // Execute the command using the system function
    system(command);

    return 0;
}
