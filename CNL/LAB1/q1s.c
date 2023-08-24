/*To illustrate encryption and decryption of messages using TCP. The client accepts
messages to be encrypted through standard input device. The client will encrypt the string
by adding 4(random value) to ASCII value of each alphabet. The encrypted message is
sent to the server. The server then decrypts the message and displays both encrypted and
decrypted forms of the string. Program terminates after one session.*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define PORTNO 5656

void main() {
    int sock_id, new_sockid, portno, client_len, n = 1;
    struct sockaddr_in server_addr, client_addr;
    
    // Create a socket
    sock_id = socket(AF_INET, SOCK_STREAM, 0);

    // Set up server address details
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("172.16.59.34"); // Server IP address
    server_addr.sin_port = htons(PORTNO); // Port number

    // Bind the socket to the specified IP address and port number
    bind(sock_id, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Listen for incoming client connections
    listen(sock_id, 5); // Allow up to 5 pending connections in the queue

    while (1) {
        char buf[256] = ""; // Initialize a buffer to store incoming message
        
        printf("\nServer Waiting ...\n");

        client_len = sizeof(client_len);

        // Accept a new client connection
        new_sockid = accept(sock_id, (struct sockaddr*)&client_addr, &client_len);

        // Read the encrypted message from the client
        n = read(new_sockid, buf, sizeof(buf));
        
        // Display the encrypted message received from the client
        printf("Encrypted Message from Client: %s\n", buf);

        // Decrypt the received message by subtracting 4 from each character
        for (int i = 0; i < strlen(buf); i++) {
            buf[i] -= 4;
        }

        // Display the decrypted message
        printf("Decrypted Message from Client: %s\n", buf);
        
        // Note: The server response is not sent back to the client in this code
        
        // Close the socket for the current client
        close(new_sockid);
    }
}
