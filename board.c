//
// Created by noahc on 2/5/2019.
//
#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include <curses.h>
Board makeBoard(int numRows, int numCols, char blankChar) {
    Board board;

    board.theBoard = (char**)malloc(numRows * sizeof(char*));
    for (int i = 0; i < numRows; ++i) {
        board.theBoard[i] = (char*)malloc(numCols * sizeof(char));
        for (int j = 0; j < numCols; ++j) {
            board.theBoard[i][j] = blankChar;
        }
    }

    board.numRows = numRows;
    board.numCols = numCols;
    board.blankChar = blankChar;
    return board;
}

void printBoard(Board board) {
    //print column header
    printf("  "); //make things line up
    for (int i = 0; i < board.numCols; ++i) {
        printf("%d ", i);
    }
    printf("\n");

    for (int row = 0; row < board.numRows; ++row) {
        printf("%d ", row); //print row header
        for (int col = 0; col < board.numCols; ++col) {
            printf("%c ", board.theBoard[row][col]);
        }
        printf("\n");
    }
}
void fillWindow(WINDOW* win, char fillChar){
    int x, y ;
    int curRow,curCol;
    getyx(win,curRow,curCol);
    getmaxyx(win,y,x);
    for (int i = 3; i < y-3; ++i) {
        for (int j = 0; j < x; ++j) {
            mvwaddch(win, i, j, fillChar);
        }
    }
    wmove(win,curRow+1,curCol+1);

}
void cleanUpBoard(Board* board) {

    for (int row = 0; row < board->numRows; ++row) {
        free(board->theBoard[row]);
    }
    free(board->theBoard);
    board->theBoard = NULL;
    board->numRows = 0;
    board->numCols = 0;
}
