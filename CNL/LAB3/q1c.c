/*Write a UDP client-server program where t he client sends rows of a matrix, and the
server combines them together as a matrix.*/
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
    int m, n;  // Matrix dimensions
    int len = sizeof(address);  // Length of address structure

    printf("Enter the number of rows: ");
    scanf("%d", &m);  // Input number of rows
    sendto(sd, &m, sizeof(m), 0, (struct sockaddr *)&address, len);  // Send rows to server

    printf("Enter the number of columns: ");
    scanf("%d", &n);  // Input number of columns
    sendto(sd, &n, sizeof(n), 0, (struct sockaddr *)&address, len);  // Send columns to server

    int arr[n];  // Array to hold matrix row data
    int rowCount = 0;  // Counter for rows
    while (rowCount < m) {  // Loop to send rows
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);  // Input values for current row
        }
        sendto(sd, arr, n * sizeof(int), 0, (struct sockaddr *)&address, len);  // Send row data to server
        rowCount++;  // Increment row count
    }
    return 0;  // End of program
}
