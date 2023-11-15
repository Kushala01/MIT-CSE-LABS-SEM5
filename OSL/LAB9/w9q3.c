#include <stdio.h>
#include <stdlib.h>

struct Segment {
    int base;
    int limit;
};
struct Segment segmentTable[5];

void initializeSegmentTable() {
    segmentTable[0].base = 1400;
    segmentTable[0].limit = 1000;
    segmentTable[1].base = 6300;
    segmentTable[1].limit = 400;
    segmentTable[2].base = 4300;
    segmentTable[2].limit = 400;
    segmentTable[3].base = 3200;
    segmentTable[3].limit = 1100;
    segmentTable[4].base = 4700;
    segmentTable[4].limit = 1000;
}

int logicalToPhysical(int segment, int offset) {
    if (segment < 0 || segment >= 5) {
        printf("Segment %d does not exist\n", segment);
        return -1;
    }if (offset < 0 || offset >= segmentTable[segment].limit) {
        printf("Offset %d is out of range for segment %d\n", offset, segment);
        return -1; 
    }int physicalAddress = segmentTable[segment].base + offset;
    return physicalAddress;
}

int main() {
    initializeSegmentTable();
    int logicalAddress1 = 53;
    int logicalAddress2 = 852;
    int logicalAddress3 = 1222;
    int physicalAddress1 = logicalToPhysical(2, logicalAddress1);
    int physicalAddress2 = logicalToPhysical(3, logicalAddress2);
    int physicalAddress3 = logicalToPhysical(0, logicalAddress3);
    if (physicalAddress1 != -1)   printf("(i) 53 byte of segment 2 is at physical address %d\n", physicalAddress1);
    if (physicalAddress2 != -1)   printf("(ii) 852 byte of segment 3 is at physical address %d\n", physicalAddress2);
    if (physicalAddress3 != -1)   printf("(iii) 1222 byte of segment 0 is at physical address %d\n", physicalAddress3);
    return 0;
}