/*Write a concurrent TCP client-server ‘C’ program where the client accepts a
sentence from the user and sends it to the server. The server will check for
duplicate words in the string. Server will find the number of occurrences of
duplicate words present and remove the duplicate words by retaining single
occurrence of the word and send the resultant sentence to the client. The client
displays the received data on the client screen. The process repeats until the user
enters the string “Stop”. Then both processes terminate.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORTNO 5656

int main() {
    int sock_id, portno, n;
    struct sockaddr_in server_addr;
    char sentence[1024] = {0};

    // Create a socket
    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_id == -1) {
        perror("Socket creation error");
        exit(1);
    }

    // Set up server address details
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("172.16.59.43"); // Server IP address
    server_addr.sin_port = htons(PORTNO); // Port number

    // Connect to the server
    if (connect(sock_id, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection error");
        exit(1);
    }

    while (1) {
        // Get user input
        printf("Enter a sentence (or 'Stop' to quit): ");
        fgets(sentence, sizeof(sentence), stdin);

        // Send the sentence to the server
        write(sock_id, sentence, sizeof(sentence));

        // Check if the user wants to stop
        if (strcmp(sentence, "Stop\n") == 0) {
            printf("Client stopping...\n");
            break;
        }

        // Receive and print response from the server
        read(sock_id, sentence, sizeof(sentence));
        printf("Received from server: %s\n", sentence);
    }

    // Close the socket
    close(sock_id);

    return 0;
}
