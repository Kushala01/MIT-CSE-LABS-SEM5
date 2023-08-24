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

void main() {
    int len, result, sock_id, n = 1;
    struct sockaddr_in address;
    char ch[256], buf[256];

    // Create a socket
    sock_id = socket(AF_INET, SOCK_STREAM, 0);

    // Set up the server address
    address.sin_family = AF_INET;
    address.sin_port = htons(6996);
    address.sin_addr.s_addr = inet_addr("172.16.59.34");
    len = sizeof(address);

    // Connect to the server
    result = connect(sock_id, &address, len);

    if (result == -1) {
        perror("\nClient Error !!!!\n");
        exit(1);
    }

    printf("\nEnter String : \t");
    gets(ch);
    ch[strlen(ch)] = '\0'; // Ensure string is null-terminated

    // Encrypt the string by adding 4 to ASCII values of each character
    for (int i = 0; i < strlen(ch); i++) {
        ch[i] += 4;
    }

    // Send the encrypted string to the server
    write(sock_id, ch, strlen(ch));

    // Display the response from the server (note: missing read operation)
    puts(buf);
}
