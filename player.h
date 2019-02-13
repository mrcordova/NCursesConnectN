//
// Created by noahc on 2/9/2019.
//

#include <curses.h>


#ifndef NCURSESCONNECTN_PLAYER_H
#define NCURSESCONNECTN_PLAYER_H
typedef enum{Player1 = 0, Player2 = 1}TurnType;

typedef struct Player_Struct{
    WINDOW* curwin;
    int yLoc;
    int xLoc;
    int curC;
    TurnType turn;
    int marker;
}Player;

Player playerMove(WINDOW* win, int y, int x, int c, TurnType turn);
bool isGameOver(int pies, Player player);
void dropChar(Player player);
char currentPlayer(TurnType turn);
#endif //NCURSESCONNECTN_PLAYER_H
