/*Implement concurrent Remote Math Server To perform arithmetic operations in the
server and display the result to the client. The client accepts two integers and an
operator from the user and sends it to the server. The server then receives integers and
operator. The server will perform the operation on integers and sends the result back
to the client which is displayed on the client screen. Then both the processes
terminate*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORTNO 5656
#define MAX_CLIENTS 5

// Function to perform arithmetic operation
int performOperation(int a, int b, char op) {
    // Perform addition, subtraction, multiplication, or division based on the operator
    int result = 0;
    switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b != 0) {
                result = a / b;
            } else {
                printf("Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Invalid operator.\n");
    }
    return result;
}

// Function to handle client requests
void handleClient(int client_socket) {
    int a, b, result;
    char op;

    // Receive operands and operator from the client
    recv(client_socket, &a, sizeof(a), 0);
    recv(client_socket, &b, sizeof(b), 0);
    recv(client_socket, &op, sizeof(op), 0);

    // Perform arithmetic operation
    result = performOperation(a, b, op);

    // Send the result back to the client
    send(client_socket, &result, sizeof(result), 0);

    close(client_socket);
}

int main() {
    int sock_id, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create a socket
    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_id == -1) {
        perror("Socket creation error");
        exit(1);
    }

    // Set up server address details
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNO);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(sock_id, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding error");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(sock_id, MAX_CLIENTS) == -1) {
        perror("Listening error");
        exit(1);
    }

    printf("Server is listening...\n");

    // Accept and handle client connections
    while (1) {
        client_sock = accept(sock_id, (struct sockaddr *)&client_addr, &client_len);
        if (client_sock == -1) {
            perror("Accepting error");
            exit(1);
        }
        printf("Connection accepted from a client\n");

        // Create a child process to handle the client
        if (fork() == 0) {
            close(sock_id); // Child process doesn't need the listening socket
            handleClient(client_sock); // Handle the client's request
            exit(0); // Terminate the child process
        } else {
            close(client_sock); // Parent process doesn't need this client socket
        }
    }

    return 0;
}
