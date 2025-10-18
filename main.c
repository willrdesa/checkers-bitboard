#include <stdio.h>
#include "game.h"

//Declarations so the compiler doesn't hate me
unsigned long long* setBoard(void);
void printBoard(unsigned long long redBoard, unsigned long long blackBoard);

int main() {
    printf("# Notation: x,y\n");
    printf("# x: current position of piece\n");
    printf("# y: position of piece after move\n\n");
    printf("# Positions grid:\n");
    for (int i = 0; i < 8; i++) {
        printf("# ");
        for (int j = i * 8; j < 8 * (i + 1); j++) {
            printf("%d ", j);
        }
        printf("\n");
    }
    printf("\n################################\n\n");



    unsigned long long redBoard;
    unsigned long long blackBoard;

    unsigned long long *boards = setBoard();
    blackBoard = boards[0];
    redBoard = boards[1];

    int stop = 0;
    int isRed = 1;

    while (!stop) {
        printBoard(redBoard, blackBoard);
        if (isRed == 1) printf("Red turn: ");
        else printf("Black turn: ");
        int move;
        scanf("%d", &move);
        printf("\n");
        isRed = !isRed;
        if (move == -1) break;
    }
}