//
// Created by noahc on 2/10/2019.
//
#include "player.h"
#include <curses.h>
#ifndef NCURSESCONNECTN_CHECKWIN_H
#define NCURSESCONNECTN_CHECKWIN_H
bool winner(int pies, Player player);
bool horizWin(int pies,Player player);
bool vertWin(int pies,Player player);
bool leftDialog(int pies,Player player);
bool rightDialog(int pies,Player player);

#endif //NCURSESCONNECTN_CHECKWIN_H
