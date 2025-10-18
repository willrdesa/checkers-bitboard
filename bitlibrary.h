#include <stdio.h>
#include <string.h>

// Basic bit operations
unsigned long long int modifyBit(unsigned long long int value, int position, int operation) {
    // operation : 0= clear , 1= set , 2= toggle
    unsigned long long mask = 1ULL << position;
    switch (operation) {
        case 0: return value & ~mask;
        case 1: return value | mask;
        case 2: return value ^ mask;
    }
    return value ;
}

//Gets bit in given position
unsigned long long int getBit(unsigned long long int value, int position) {
    return (value >> position) & 1ULL;
}

// Counting and finding
int countBits(unsigned long long int value) {
    unsigned int maxValue = modifyBit(0, 15, 1);
    int count = 0;
    while (maxValue > 0) {
        if (value >= maxValue) {
            count++;
            value -= maxValue;
        }
        maxValue /= 2;
    }
    return count;
}

// Shift operations
unsigned int shiftLeft(unsigned long long int value, int positions) {
    return value << positions;
}

unsigned int shiftRight(unsigned long long int value, int positions) {
    return value >> positions;
}

 // Display functions
void printBinary(unsigned long long int value) {
    unsigned int maxValue = modifyBit(0, 7, 1);
    while (maxValue > 0) {
        if (value >= maxValue) {
            printf("1");
            value -= maxValue;
        } else printf("0");
        maxValue /= 2;
    }
    printf("\n");
}
void printHex(unsigned long long int value) {
    unsigned int maxValue = modifyBit(0, 15, 1);
    char out[5];
    char temp[5];
    int pos = 0;

    while (maxValue > 0) {
        int remainder = value % 16;
        value = value / 16;

        temp[pos++] = remainder < 10 ? '0' + remainder : 'A' + (remainder - 10);
        maxValue /= 16;
    }
    temp[pos] = '\0';

    for (int i = 0; i < pos; i++) out[pos - i - 1] = temp[i];
    out[pos] = '\0';
    printf("%s\n", out);
}