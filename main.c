#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main() {
    printf("# Notation: x,y\n");
    printf("# x: current position of piece\n");
    printf("# y: position of piece after move\n\n");
    printf("# Positions grid:\n");
    for (int i = 0; i < 8; i++) {
        printf("# ");
        for (int j = i * 8; j < 8 * (i + 1); j++) {
            if (j < 10) printf(" ");
            printf("%d ", j);
        }
        printf("\n");
    }
    printf("\n################################\n\n");

    unsigned long long *boards = setBoard();

    int stop = 0;
    int isRed = 1;

    while (!stop) {
        printBoard(boards);
        if (isRed == 1) printf("RED TURN:\n");
        else printf("BLACK TURN:\n");

        int x, y;
        printf("x: ");
        scanf("%d", &x);
        printf("y: ");
        scanf("%d", &y);
        printf("\n");
        move(boards, x, y, isRed);
        capture(boards, x, y, isRed);

        if (checkWin(boards) == 0) {
            printf("BLACK WINS!");
            break;
        }
        else if (checkWin(boards) == 1) {
            printf("RED WINS!");
            break;
        }

        isRed = !isRed;
    }
}