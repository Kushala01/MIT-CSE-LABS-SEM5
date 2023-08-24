//Implement simple TCP daytime server using select().

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#define PORTNO 10300
#define MAX_CLIENTS 5

void printCurrentTime() {
    // Function to print the current time in a specific format
    time_t now;
    struct tm *timeinfo;
    char buffer[80];
    time(&now);
    timeinfo = localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("[%s] ", buffer);
}

int main() {
    int sockfd, newsockfd, portno, clilen, n;
    char buf[256];
    struct sockaddr_in seraddr, cliaddr;
    fd_set readfds;
    int client_sockets[MAX_CLIENTS] = {0}; // Array to store client socket descriptors

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation error");
        exit(1);
    }

    // Set up server address details
    memset(&seraddr, 0, sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = INADDR_ANY;
    seraddr.sin_port = htons(PORTNO);

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0) {
        perror("Binding error");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) < 0) {
        perror("Listen error");
        exit(1);
    }

    // Initialize the set of file descriptors for reading
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);

    printf("Server is listening on port %d...\n", PORTNO);

    while (1) {
        // Create a temporary copy of the readfds set for select
        fd_set temp_fds = readfds;
        if (select(FD_SETSIZE, &temp_fds, NULL, NULL, NULL) < 0) {
            perror("Select error");
            exit(1);
        }

        // Loop through all possible file descriptors
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &temp_fds)) {
                if (i == sockfd) {
                    // New client connection
                    clilen = sizeof(cliaddr);
                    newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
                    if (newsockfd < 0) {
                        perror("Accept error");
                        exit(1);
                    }
                    // Add the new client socket to the readfds set
                    FD_SET(newsockfd, &readfds);
                    printCurrentTime();
                    printf("New client connected\n");
                } else {
                    // Data from existing client
                    n = read(i, buf, sizeof(buf));
                    if (n <= 0) {
                        if (n == 0) {
                            printCurrentTime();
                            printf("Client disconnected\n");
                        } else {
                            perror("Read error");
                        }
                        // Close the client socket and remove it from the readfds set
                        close(i);
                        FD_CLR(i, &readfds);
                    } else {
                        // Respond with the current time
                        time_t now;
                        struct tm *timeinfo;
                        time(&now);
                        timeinfo = localtime(&now);
                        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
                        write(i, buf, strlen(buf));
                        printCurrentTime();
                        printf("Sent time to client: %s\n", buf);
                    }
                }
            }
        }
    }

    return 0;
}
/*The code implements a simple TCP daytime server using the select() function to handle multiple clients concurrently.

The printCurrentTime() function formats and prints the current time.

The main function sets up a socket and binds it to a server address.

It initializes a set of file descriptors (readfds) with the server socket and starts listening for incoming connections.

The program enters an infinite loop where it uses select() to monitor socket activity.

For each file descriptor that is ready in temp_fds, it checks if it's the server socket (indicating a new client connection) or an existing client socket (indicating data from a client).

For new client connections, it accepts the connection, adds the new socket to readfds, and prints a message.

For existing client sockets, it reads data and handles disconnections. If the client socket is closed, it is removed from readfds.

If data is received from a client, the server responds with the current time.

This loop continues indefinitely, handling multiple clients simultaneously.

The code ensures proper cleanup by closing sockets and handling errors.*/
