#include <stdio.h>
#include "game.h"

//Declarations so the compiler doesn't hate me
unsigned long long* setBoard(void);
void printBoard(unsigned long long redBoard, unsigned long long blackBoard);
void checkLegalMoves(unsigned long long redBoard, unsigned long long blackBoard, int player, int legalMoves[][2]);

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

        int legalMoves[12][2];
        checkLegalMoves(redBoard, blackBoard, isRed, legalMoves);
        if (isRed == 1) printf("Red turn: ");
        else printf("Black turn: ");
        int move;
        scanf("%d", &move);
        printf("\n");
        isRed = !isRed;
        if (move == -1) break;
    }
}