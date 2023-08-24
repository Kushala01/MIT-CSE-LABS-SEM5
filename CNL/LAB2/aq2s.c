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

#define PORTNO 5656
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

// Function to remove duplicate words from a sentence
void removeDuplicates(char *sentence) {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int wordCount = 0;

    char *word = strtok(sentence, " ");
    while (word != NULL && wordCount < MAX_WORDS) {
        int duplicate = 0;
        for (int i = 0; i < wordCount; i++) {
            if (strcmp(words[i], word) == 0) {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) {
            strcpy(words[wordCount], word);
            wordCount++;
        }
        word = strtok(NULL, " ");
    }

    sentence[0] = '\0';
    for (int i = 0; i < wordCount; i++) {
        strcat(sentence, words[i]);
        strcat(sentence, " ");
    }
}

int main() {
    int sock_id, new_sockid, client_len;
    struct sockaddr_in server_addr, client_addr;

    // Create a socket
    sock_id = socket(AF_INET, SOCK_STREAM, 0);

    // Set up server address details
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORTNO);

    // Bind the socket to the server address
    bind(sock_id, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    // Listen for incoming connections
    listen(sock_id, 5);

    printf("Server is listening on port %d...\n", PORTNO);

    while (1) {
        char sentence[1024] = {0};
        client_len = sizeof(client_addr);

        // Accept a new client connection
        new_sockid = accept(sock_id, (struct sockaddr *)&client_addr, &client_len);

        printf("Client connected\n");

        // Process the client's requests
        while (1) {
            // Read data from the client
            read(new_sockid, sentence, sizeof(sentence));

            // Check if the client wants to stop
            if (strcmp(sentence, "Stop\n") == 0) {
                printf("Stopping server...\n");
                break;
            }

            // Print the received data from the client
            printf("Received from client: %s\n", sentence);

            // Remove duplicate words from the sentence
            removeDuplicates(sentence);

            // Send the modified sentence back to the client
            write(new_sockid, sentence, sizeof(sentence));
        }

        // Close the connection with the current client
        close(new_sockid);
    }

    // Close the listening socket
    close(sock_id);
    return 0;
}
