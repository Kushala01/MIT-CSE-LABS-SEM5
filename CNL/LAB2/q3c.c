//Implement simple TCP daytime server using select().

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORTNO 10300

int main() {
    int sockfd, n;
    struct sockaddr_in servaddr;
    char buf[256];

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation error");
        exit(1);
    }

    // Set up server address details
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("172.16.59.43"); // Server IP address
    servaddr.sin_port = htons(PORTNO); // Port number

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection error");
        exit(1);
    }

    // Read data from the server
    n = read(sockfd, buf, sizeof(buf) - 1);
    if (n < 0) {
        perror("Read error");
        exit(1);
    }
    buf[n] = '\0';

    // Print the received message from the server
    printf("Received from server: %s\n", buf);

    // Close the socket
    close(sockfd);

    return 0;
}
/*The code establishes a connection to a server using a TCP socket.

It creates a socket using the socket() function, with the domain AF_INET (IPv4) and type SOCK_STREAM (TCP).

The server address structure, servaddr, is initialized using the memset() function to ensure no garbage values are present in the structure.

The server address details are set up: sin_family is set to AF_INET, sin_addr.s_addr is set to the server's IP address, and sin_port is set to the specified port number.

The client connects to the server using the connect() function. If the connection fails, an error message is printed, and the program exits.

Data is read from the server using the read() function, storing it in the buf array. The n variable holds the number of bytes read.

A null terminator is added to the received data in the buf array to convert it into a string.

The received message from the server is printed to the console using printf().

The socket is closed using the close() function to release resources.*/
