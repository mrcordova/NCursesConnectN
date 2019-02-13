//
// Created by noahc on 2/5/2019.
//

#ifndef NCURSESCONNECTN_BOARD_H
#define NCURSESCONNECTN_BOARD_H

#include <curses.h>

typedef struct Board_Struct{
    char** theBoard;
    int numRows;
    int numCols;
    char blankChar;
}Board;



Board makeBoard(int numRows, int numCols, char blankChar);
void printBoard(Board board);
void cleanUpBoard(Board* board);
void fillWindow(WINDOW* win, char fillChar);

#endif //NCURSESCONNECTN_BOARD_H
