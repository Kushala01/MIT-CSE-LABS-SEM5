#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 9

// Function to print the tic-tac-toe board
void printBoard(char *board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c", board[i * 3 + j]);
            if (j < 2) printf(" | ");
        }
        printf("\n");
        if (i < 2) printf("---------\n");
    }
}

// Function to check for a win
int checkWin(char *board, char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i] == player && board[i + 3] == player && board[i + 6] == player)
            return 1;
        if (board[i * 3] == player && board[i * 3 + 1] == player && board[i * 3 + 2] == player)
            return 1;
    }
    if (board[0] == player && board[4] == player && board[8] == player)
        return 1;
    if (board[2] == player && board[4] == player && board[6] == player)
        return 1;

    return 0;
}

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    char *board = (char *)shmat(shmid, NULL, 0);

    // Initialize the game board
    for (int i = 0; i < 9; i++) {
        board[i] = ' ';
    }

    int currentPlayer = 1; // Player 1 starts
    int moves = 0;
    int playerChoice;

    while (moves < 9) {
        printf("Tic-Tac-Toe Game\n");
        printBoard(board);
        printf("Player %d's turn (1-9): ", currentPlayer);

        while (1) {
            scanf("%d", &playerChoice);

            if (playerChoice >= 1 && playerChoice <= 9 && board[playerChoice - 1] == ' ') {
                break;
            } else {
                printf("Invalid choice. Please choose an empty cell (1-9).\n");
            }
        }

        if (currentPlayer == 1) {
            board[playerChoice - 1] = 'X';
            currentPlayer = 2;
        } else {
            board[playerChoice - 1] = 'O';
            currentPlayer = 1;
        }

        moves++;

        if (checkWin(board, 'X')) {
            printf("Player 1 (X) wins!\n");
            break;
        } else if (checkWin(board, 'O')) {
            printf("Player 2 (O) wins!\n");
            break;
        }

        if (moves == 9) {
            printf("It's a draw!\n");
        }
    }

    printBoard(board);

    shmdt(board);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
