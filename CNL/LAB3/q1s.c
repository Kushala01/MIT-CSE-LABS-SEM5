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
    int m, n;  // Matrix dimensions
    struct sockaddr_in sadd, cadd;  // Server and client address structures
    
    // Create a UDP socket
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    sadd.sin_family = AF_INET;
    sadd.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address
    sadd.sin_port = htons(PORTNO);  // Port number
    
    // Bind the socket to the server's address
    int result = bind(sd, (struct sockaddr *)&sadd, sizeof(sadd));
    int len = sizeof(cadd);
    
    // Receive matrix dimensions from the client
    recvfrom(sd, &m, sizeof(m), 0, (struct sockaddr *)&cadd, &len);
    recvfrom(sd, &n, sizeof(n), 0, (struct sockaddr *)&cadd, &len);
    
    int arr[m][n];  // Array to hold the combined matrix
    int recvarr[n];  // Temporary array to receive matrix rows
    int rowCount = 0;  // Counter for rows
    
    // Loop to receive rows and build the combined matrix
    while (rowCount < m) {
        recvfrom(sd, recvarr, n * sizeof(int), 0, (struct sockaddr *)&cadd, &len);
        for (int i = 0; i < n; i++) {
            arr[rowCount][i] = recvarr[i];  // Store row data in the combined matrix
        }
        rowCount++;
    }
    
    // Display the combined matrix
    printf("After combining the matrix is: \n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[i][j]);  // Print matrix element
        }
        printf("\n");
    }
    
    return 0;  
}
