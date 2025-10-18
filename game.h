#include "bitlibrary.h"
#include <stdio.h>

//Prints the board
void printBoard(unsigned long long bitBoard) {
    for (int i = 0; i < 8; i++) {
        for (int j = 8 * i; j < 8 * (i + 1); j++) {
            printf("%llu ", getBit(bitBoard, j));
        }
        printf("\n");
    }
}

//Sets the initial board
unsigned long long setBoard() {
    unsigned long long bitBoard = 0;
    int isOdd = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 8 * i + isOdd; j < 8 * (i + 1); j += 2) {
            bitBoard = modifyBit(bitBoard, j, 1);
        }
        isOdd = !isOdd;
    }
    for (int i = 5; i < 8; i++) {
        for (int j = 8 * i + isOdd; j < 8 * (i + 1); j += 2) {
            bitBoard = modifyBit(bitBoard, j, 1);
        }
        isOdd = !isOdd;
    }
    return bitBoard;
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