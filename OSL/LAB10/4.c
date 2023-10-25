#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_BLOCKS 100

// Structure to represent a block in the file system
struct Block {
    int data;
    bool isBad;
    int spareBlock;
};

// Function to initialize the file system with bad blocks and spare blocks
void initializeFileSystem(struct Block filesystem[], int numBlocks) {
    for (int i = 0; i < numBlocks; i++) {
        filesystem[i].data = 0;
        filesystem[i].isBad = false;
        filesystem[i].spareBlock = -1;
    }
    
    // Simulate bad blocks
    filesystem[3].isBad = true;
    filesystem[7].isBad = true;

    // Allocate spare blocks for bad blocks
    filesystem[3].spareBlock = 20;
    filesystem[7].spareBlock = 30;
}

// Function to write data to a block in the file system
void writeBlock(struct Block filesystem[], int blockNumber, int data) {
    if (filesystem[blockNumber].isBad) {
        printf("Block %d is bad. Using spare block %d.\n", blockNumber, filesystem[blockNumber].spareBlock);
        blockNumber = filesystem[blockNumber].spareBlock;
    }
    
    filesystem[blockNumber].data = data;
}

// Function to read data from a block in the file system
int readBlock(struct Block filesystem[], int blockNumber) {
    if (filesystem[blockNumber].isBad) {
        printf("Block %d is bad. Using spare block %d.\n", blockNumber, filesystem[blockNumber].spareBlock);
        blockNumber = filesystem[blockNumber].spareBlock;
    }
    
    return filesystem[blockNumber].data;
}

int main() {
    int numBlocks = MAX_BLOCKS;
    struct Block filesystem[MAX_BLOCKS];

    initializeFileSystem(filesystem, numBlocks);

    // Write data to block 3 (a bad block)
    writeBlock(filesystem, 3, 123);

    // Read data from block 3 (it should use the spare block)
    int data = readBlock(filesystem, 3);
    printf("Data read from block 3: %d\n", data);

    // Write data to a normal block (block 5)
    writeBlock(filesystem, 5, 456);

    // Read data from block 5
    data = readBlock(filesystem, 5);
    printf("Data read from block 5: %d\n", data);

    return 0;
}
