/*Where the client accepts a sentence from the user and sends it to the server. The server
will check for duplicate words in the string. Server will find number of occurrences of
duplicate words present and remove the duplicate words by retaining single occurrence of
the word and send the resultant sentence to the client. The client displays the received
data on the client screen. The process repeats until the user enter the string “Stop”. Then
both the processes terminate.*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

int main() {
    while (1) { // Infinite loop to keep the client running
        int len, result, sockfd, n = 1;
        struct sockaddr_in address;
        char ch[256], buf[256];

        // Create a socket
        sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);

        // Set up server address details
        address.sin_family = AF_LOCAL;
        address.sin_addr.s_addr = inet_addr("172.16.59.34"); // Server IP address
        address.sin_port = htons(4003); // Port number

        len = sizeof(address);

        // Connect to the server
        result = connect(sockfd, (struct sockaddr *)&address, len);
        if (result == -1) {
            printf("\nCLIENT ERROR");
            exit(1);
        }

        printf("\nEnter the string: ");
        gets(ch);
        ch[strlen(ch)] = '\0'; // Ensure the string is null-terminated
        
        // Check if the user wants to stop
        if (strcmp(ch, "Stop") == 0) {
            close(sockfd); // Close the socket
            break; // Exit the loop
        }

        // Send the input string to the server
        write(sockfd, ch, strlen(ch));

        // Read the response from the server
        read(sockfd, buf, sizeof(buf));

        printf("\nString after removing duplicates: ");
        puts(buf); // Display the modified string received from the server
        
        // Close the socket
        close(sockfd);
    }
}
