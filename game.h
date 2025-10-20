#include "bitlibrary.h"
#include <stdio.h>

void printBoard(unsigned long long redBoard, unsigned long long blackBoard) {
    for (int i = 0; i < 8; i++) {
        for (int j = 8 * i; j < 8 * (i + 1); j++) {
            if (getBit(redBoard, j) == 1) printf("r ");
            else if (getBit(blackBoard, j) == 1) printf("b ");
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
    static unsigned long long boards[2];

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
    return boards;
}

/* checkLegalMoves
 * @param unsigned long long int redBoard: board of red
 * @param unsigned long long int blackBoard: board of black
 * @param int pos: position of selected piece
 * @param int player: 0 for black, 1 for red
 * @returns int: 0 for false, 1 for true
*/
void checkLegalMoves(unsigned long long int redBoard, unsigned long long int blackBoard, int player, int legalMoves[][2]) {
    unsigned long long int playerBoard = player == 0 ? blackBoard : redBoard;

    int count = 0;
    for (int pos = 0; pos < 64; pos++) {
        if (getBit(playerBoard, pos) == 1) {
            int posVertical = (player == 0) ? pos + 8 : pos - 8;

            if (pos % 8 < 7) {
                if (getBit(redBoard, posVertical + 1) == 0 && getBit(blackBoard, posVertical + 1) == 0) {
                    legalMoves[count][0] = pos;
                    legalMoves[count][1] = posVertical + 1;
                    count++;
                }
            } if (pos % 8 > 0) {
                if (getBit(redBoard, posVertical - 1) == 0 && getBit(blackBoard, posVertical - 1) == 0) {
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
void checkLegalCaptures(unsigned long long int redBoard, unsigned long long int blackBoard, int player, int legalMoves[][2]) {
    unsigned long long int playerBoard = player == 0 ? blackBoard : redBoard;

    int count = 0;
    for (int pos = 0; pos < 64; pos++) {
        if (getBit(playerBoard, pos) == 1) {
            int posAdv, posAfter;
            unsigned long long int advBoard;
            if (player == 0) {
                posAdv = pos + 8;
                posAfter = pos + 16;
                advBoard = redBoard;
            } else {
                posAdv = pos - 8;
                posAfter = pos - 16;
                advBoard = blackBoard;
            }

            if (pos % 8 < 7) {
                if (getBit(redBoard, posAfter + 2) == 0 && getBit(blackBoard, posAfter + 2) == 0) {
                    if (getBit(advBoard, posAdv + 1) == 1) {
                        legalMoves[count][0] = pos;
                        legalMoves[count][1] = posAfter + 2;
                        count++;
                    }
                }
            } if (pos % 8 > 0) {
                if (getBit(redBoard, posAfter - 2) == 0 && getBit(blackBoard, posAfter - 2) == 0) {
                    if (getBit(advBoard, posAdv - 1) == 1) {
                        legalMoves[count][0] = pos;
                        legalMoves[count][1] = posAfter - 2;
                        count++;
                    }
                }
            }
        }
    }
}

/* move
 * @param unsigned long long redBoard: board of red
 * @param unsigned long long blackBoard: board of black
 * @param int initialPos: initial position of selected piece
 * @param int finalPos: position that piece is moving
 * @param int player: 0 for black, 1 for red
 * @returns int*: updated boards
*/


void move(unsigned long long *boards, int initialPos, int finalPos, int player) {
    int legalMoves[24][2];
    int isLegal = 0;
    checkLegalMoves(boards[1], boards[0], player, legalMoves);

    //Check if move is legal
    for (int i = 0; i < sizeof(legalMoves) / sizeof(legalMoves[0]); i++) {
        if ((initialPos == legalMoves[i][0]) && (finalPos == legalMoves[i][1])) {
            isLegal = 1;
            break;
        }
    }

    unsigned long long bitBoard = player == 1 ? boards[1] : boards[0];
    if (isLegal == 1) {
        bitBoard = modifyBit(bitBoard, initialPos, 0);
        bitBoard = modifyBit(bitBoard, finalPos, 1);
    } else return;
    if (player == 1) boards[1] = bitBoard;
    else boards[0] = bitBoard;
}

/* capture
 * @param int initialPos: initial position of selected piece
 * @param int finalPos: position that piece is moving
 * @param int player: 0 for black, 1 for red
 * @returns int*: updated boards
*/