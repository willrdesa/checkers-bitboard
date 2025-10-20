#include "bitlibrary.h"
#include <stdio.h>

//indexes 0 for black board, 1 for red board, 3 for black kings board, 4 for red kings board
void printBoard(unsigned long long *boards) {
    for (int i = 0; i < 8; i++) {
        for (int j = 8 * i; j < 8 * (i + 1); j++) {
            if (getBit(boards[0], j) == 1) printf("b ");
            else if (getBit(boards[1], j) == 1) printf("r ");
            else if (getBit(boards[2], j) == 1) printf("B ");
            else if (getBit(boards[3], j) == 1) printf("R ");
            else printf("0 ");
        }
        printf("\n");
    }
}

//Sets the initial board
unsigned long long* setBoard() {
    unsigned long long redBoard = 0;
    unsigned long long blackBoard = 0;
    int isOdd = 1;
    static unsigned long long boards[4];

    for (int i = 0; i < 3; i++) {
        for (int j = 8 * i + isOdd; j < 8 * (i + 1); j += 2) {
            blackBoard = modifyBit(blackBoard, j, 1);
        }
        isOdd = !isOdd;
    }
    for (int i = 5; i < 8; i++) {
        for (int j = 8 * i + isOdd; j < 8 * (i + 1); j += 2) {
            redBoard = modifyBit(redBoard, j, 1);
        }
        isOdd = !isOdd;
    }
    boards[0] = blackBoard;
    boards[1] = redBoard;
    boards[2] = 0;
    boards[3] = 0;
    return boards;
}

/* checkLegalMoves
 * @param unsigned long long int redBoard: board of red
 * @param unsigned long long int blackBoard: board of black
 * @param int pos: position of selected piece
 * @param int player: 0 for black, 1 for red
 * @returns int: 0 for false, 1 for true
*/
void checkLegalMoves(unsigned long long int *boards, int player, int legalMoves[][2]) {
    unsigned long long int playerBoard = player == 0 ? boards[0] : boards[1];

    int count = 0;
    for (int pos = 0; pos < 64; pos++) {
        if (getBit(playerBoard, pos) == 1) {
            int posVertical = (player == 0) ? pos + 8 : pos - 8;

            if (pos % 8 < 7) {
                if (getBit(boards[1], posVertical + 1) == 0 && getBit(boards[0], posVertical + 1) == 0) {
                    legalMoves[count][0] = pos;
                    legalMoves[count][1] = posVertical + 1;
                    count++;
                }
            } if (pos % 8 > 0) {
                if (getBit(boards[1], posVertical - 1) == 0 && getBit(boards[0], posVertical - 1) == 0) {
                    legalMoves[count][0] = pos;
                    legalMoves[count][1] = posVertical - 1;
                    count++;
                }
            }
        }
    }
}

/* checkLegalCaptures
 * @param int pos: position of selected piece
 * @param int player: 0 for black, 1 for red
 * @returns int*: positions of available captures
*/
void checkLegalCaptures(unsigned long long int *boards, int player, int legalCaptures[][3]) {
    unsigned long long int playerBoard = player == 0 ? boards[0] : boards[1];

    int count = 0;
    for (int pos = 0; pos < 64; pos++) {
        if (getBit(playerBoard, pos) == 1) {
            int posAdv, posAfter;
            unsigned long long int advBoard;
            if (player == 0) {
                posAdv = pos + 8;
                posAfter = pos + 16;
                advBoard = boards[0];
            } else {
                posAdv = pos - 8;
                posAfter = pos - 16;
                advBoard = boards[1];
            }

            if (pos % 8 < 7) {
                if (getBit(boards[1], posAfter + 2) == 0 && getBit(boards[0], posAfter + 2) == 0) {
                    if (getBit(advBoard, posAdv + 1) == 1) {
                        legalCaptures[count][0] = pos;
                        legalCaptures[count][1] = posAfter + 2;
                        legalCaptures[count][2] = posAdv + 1;
                        count++;
                    }
                }
            } if (pos % 8 > 0) {
                if (getBit(boards[1], posAfter - 2) == 0 && getBit(boards[0], posAfter - 2) == 0) {
                    if (getBit(advBoard, posAdv - 1) == 1) {
                        legalCaptures[count][0] = pos;
                        legalCaptures[count][1] = posAfter - 2;
                        legalCaptures[count][2] = posAdv - 1;
                        count++;
                    }
                }
            }
        }
    }
}

/* move
 * @param unsigned long long *boards: boards[0] for red and boards[1] for black
 * @param int initialPos: initial position of selected piece
 * @param int finalPos: position that piece is moving
 * @param int player: 0 for black, 1 for red
 * @returns int*: updated boards
*/
void move(unsigned long long *boards, int initialPos, int finalPos, int player) {
    int legalMoves[24][2];
    int isLegal = 0;
    checkLegalMoves(boards, player, legalMoves);

    //Check if move is legal
    for (int i = 0; i < sizeof(legalMoves) / sizeof(legalMoves[0]); i++) {
        if ((initialPos == legalMoves[i][0]) && (finalPos == legalMoves[i][1])) {
            isLegal = 1;
            break;
        }
    }
    if (initialPos == 0 && finalPos == 0) isLegal = 0;

    unsigned long long bitBoard = player == 1 ? boards[1] : boards[0];
    if (isLegal == 1) {
        bitBoard = modifyBit(bitBoard, initialPos, 0);
        bitBoard = modifyBit(bitBoard, finalPos, 1);
    } else return;
    if (player == 1) boards[1] = bitBoard;
    else boards[0] = bitBoard;
}

/* capture
 * @param unsigned long long *boards: boards[0] for black and boards[1] for red
 * @param int initialPos: initial position of selected piece
 * @param int finalPos: position that piece is moving
 * @param int player: 0 for black, 1 for red
 * @returns int*: updated boards
*/
void capture(unsigned long long *boards, int initialPos, int finalPos, int player) {
    int legalCaptures[24][3];
    int isLegal = 0;
    checkLegalCaptures(boards, player, legalCaptures);
    int advPos = -1;

    //Check if capture is legal
    for (int i = 0; i < sizeof(legalCaptures) / sizeof(legalCaptures[0]); i++) {
        if ((initialPos == legalCaptures[i][0]) && (finalPos == legalCaptures[i][1])) {
            advPos = legalCaptures[i][2];
            isLegal = 1;
            break;
        }
    }
    if (initialPos == 0 && finalPos == 0) isLegal = 0;

    unsigned long long playerBoard, advBoard;
    if (player == 1) {
        playerBoard = boards[1];
        advBoard = boards[0];
    } else {
        playerBoard = boards[0];
        advBoard = boards[1];
    }

    if (isLegal == 1) {
        playerBoard = modifyBit(playerBoard, initialPos, 0);
        playerBoard = modifyBit(playerBoard, finalPos, 1);
        advBoard = modifyBit(advBoard, advPos, 0);
    } else return;

    if (player == 1) {
        boards[1] = playerBoard;
        boards[0] = advBoard;
    } else {
        boards[0] = playerBoard;
        boards[1] = advBoard;
    }
}

int checkWin(unsigned long long *boards) {
    if (countBits(boards[0]) == 0) return 1;
    else if (countBits(boards[1]) == 0) return 0;
    else return -1;
}