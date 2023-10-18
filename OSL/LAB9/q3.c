#include <stdio.h>
#include <stdlib.h>

#define NUM_SEGMENTS 5
#define SEGMENT_SIZE 256

// Define the segment table structure
struct Segment {
    int base;
    int limit;
};

// Initialize the segment table
struct Segment segmentTable[NUM_SEGMENTS];

// Function to initialize the segment table
void initializeSegmentTable() {
    // Initialize segment table entries with base and limit values
    segmentTable[0].base = 0;
    segmentTable[0].limit = 256;
    segmentTable[1].base = 256;
    segmentTable[1].limit = 256;
    segmentTable[2].base = 512;
    segmentTable[2].limit = 256;
    segmentTable[3].base = 768;
    segmentTable[3].limit = 256;
    segmentTable[4].base = 1024;
    segmentTable[4].limit = 256;
}

// Function to convert a logical address to a physical address
int logicalToPhysical(int segment, int offset) {
    if (segment < 0 || segment >= NUM_SEGMENTS) {
        printf("Segment %d does not exist\n", segment);
        return -1; // Invalid segment
    }

    if (offset < 0 || offset >= segmentTable[segment].limit) {
        printf("Offset %d is out of range for segment %d\n", offset, segment);
        return -1; // Invalid offset
    }

    // Calculate the physical address by adding the segment base and offset
    int physicalAddress = segmentTable[segment].base + offset;
    return physicalAddress;
}

int main() {
    initializeSegmentTable();

    // Define logical addresses to be converted to physical addresses
    int logicalAddress1 = 53;
    int logicalAddress2 = 852;
    int logicalAddress3 = 1222;

    // Convert logical addresses to physical addresses and print the results
    int physicalAddress1 = logicalToPhysical(2, logicalAddress1);
    int physicalAddress2 = logicalToPhysical(3, logicalAddress2);
    int physicalAddress3 = logicalToPhysical(0, logicalAddress3);

    if (physicalAddress1 != -1) {
        printf("(i) 53 byte of segment 2 is at physical address %d\n", physicalAddress1);
    }

    if (physicalAddress2 != -1) {
        printf("(ii) 852 byte of segment 3 is at physical address %d\n", physicalAddress2);
    }

    if (physicalAddress3 != -1) {
        printf("(iii) 1222 byte of segment 0 is at physical address %d\n", physicalAddress3);
    }

    return 0;
}