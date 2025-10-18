#include "bitlibrary.h"
#include <stdio.h>

//Prints the board
// void printBoard(unsigned long long bitBoard) {
//     for (int i = 0; i < 8; i++) {
//         for (int j = 8 * i; j < 8 * (i + 1); j++) {
//             printf("%llu ", getBit(bitBoard, j));
//         }
//         printf("\n");
//     }
// }

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
 * @param int pos: position of selected piece
 * @param int player: 0 for black, 1 for red
 * @returns int*: positions of available moves
*/

/* checkLegalCaptures
 * @param int pos: position of selected piece
 * @param int player: 0 for black, 1 for red
 * @returns int*: positions of available captures
*/

/* move
 * @param int initialPos: initial position of selected piece
 * @param int finalPos: position that piece is moving
 * @param int player: 0 for black, 1 for red
 * @returns int*: updated boards
*/

/* capture
 * @param int initialPos: initial position of selected piece
 * @param int finalPos: position that piece is moving
 * @param int player: 0 for black, 1 for red
 * @returns int*: updated boards
*/