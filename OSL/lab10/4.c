#include <stdio.h>
#include <stdbool.h>

#define MAX_BLOCKS 10

struct Block {
    int data;
    bool isBad;
    int spareBlock;
};

void initializeFileSystem(struct Block filesystem[], int numBlocks) {
    for (int i = 0; i < numBlocks; i++) {
        filesystem[i] = (struct Block){0, false, -1};
    }filesystem[3].isBad = true;
    filesystem[7].isBad = true;
    filesystem[3].spareBlock = 20;
    filesystem[7].spareBlock = 30;
}

void writeAndReadBlock(struct Block filesystem[], int blockNumber, int data) {
    if (filesystem[blockNumber].isBad) {
        printf("Block %d is bad. Using spare block %d.\n", blockNumber, filesystem[blockNumber].spareBlock);
        blockNumber = filesystem[blockNumber].spareBlock;
    }filesystem[blockNumber].data = data;
    int readData = filesystem[blockNumber].data;
    printf("Data read from block %d: %d\n", blockNumber, readData);
}

int main() {
    int numBlocks = MAX_BLOCKS;
    struct Block filesystem[MAX_BLOCKS];
    initializeFileSystem(filesystem, numBlocks);
    writeAndReadBlock(filesystem, 3, 123);
    writeAndReadBlock(filesystem, 5, 456);
    return 0;
}