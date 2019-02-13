//
// Created by noahc on 2/10/2019.
//

#include "checkWin.h"
bool winner(int pies, Player player){


    if(horizWin(pies,player)){
        return true;
    }
    else if(vertWin(pies,player)){
        return true;
    }
    else if(leftDialog(pies,player)){
        return true;
    }
    else if (rightDialog(pies,player)){
        return true;
    }
    return false;
};
bool horizWin(int pies, Player player){
    WINDOW* checkWin= player.curwin;

    int begY, begX;
    int maxX,maxY;
    int horiWin=0;
    player.curC = currentPlayer(player.turn);
    getbegyx(checkWin,begY,begX);
    getmaxyx(checkWin,maxY,maxX);
    if(player.curC=='X') {
        for (int i = begY + 3; i < maxY - 3; i++) {

            for (int j = begX; j < maxX + 2; j++) {
                //x=j+1;
                if (horiWin == (pies)) {
                    return true;
                }
                if ((mvwinch(checkWin, i, j) == 'X')) {
                    horiWin = horiWin + 1;

                } else if ((mvwinch(checkWin, i, j) == 'O') || (mvwinch(checkWin, i, j) == '*')) {
                    horiWin = 0;
                }

            }

            horiWin = 0;
        }//horizon win end
    }
    else if (player.curC=='O') {
        for (int i = begY + 3; i < maxY - 3; i++) {

            for (int j = begX; j < maxX + 2; j++) {
                //x=j+1;
                if (horiWin == (pies)) {
                    return true;
                }
                if ((mvwinch(checkWin, i, j) == 'O')) {
                    horiWin = horiWin + 1;

                } else if ((mvwinch(checkWin, i, j) == 'X') || (mvwinch(checkWin, i, j) == '*')) {
                    horiWin = 0;
                }

            }

            horiWin = 0;
        }//horizon win end
    }
    return false;
};
bool vertWin(int pies, Player player){
    WINDOW* checkWin= player.curwin;

    int begY, begX;
    int maxX,maxY;
    int vertWin=0;
    getbegyx(checkWin,begY,begX);
    getmaxyx(checkWin,maxY,maxX);
    int dy= 0;
    player.curC = currentPlayer(player.turn);
    if(player.curC=='X') {
        for (int i = begY + 3; i < maxY - 3; i++) {

            for (int j = begX; j < maxX + 2; j++) {

                if (vertWin == (pies)) {
                    return true;
                }
                if ((mvwinch(checkWin, i, j) == 'X')) {
                    dy = i;
                    while (mvwinch(checkWin, dy, j) == 'X') {
                        vertWin = vertWin + 1;
                        dy = dy + 1;
                    }

                } else if ((mvwinch(checkWin, i, j) == 'O') || (mvwinch(checkWin, i, j) == '*')) {
                    vertWin = 0;
                }
                if (vertWin == (pies)) {
                    return true;
                }
                vertWin = 0;
            }

        }//Vertical win end
    }
    else if (player.curC=='O') {
        for (int i = begY + 3; i < maxY - 3; i++) {

            for (int j = begX; j < maxX + 2; j++) {

                if (vertWin == (pies)) {
                    return true;
                }
                if ((mvwinch(checkWin, i, j) == 'O')) {
                    dy = i;
                    while (mvwinch(checkWin, dy, j) == 'O') {
                        vertWin = vertWin + 1;
                        dy = dy + 1;
                    }

                } else if ((mvwinch(checkWin, i, j) == 'X') || (mvwinch(checkWin, i, j) == '*')) {
                    vertWin = 0;
                }
                if (vertWin == (pies)) {
                    return true;
                }
                vertWin = 0;
            }

        }
    }
return false;
};
bool leftDialog(int pies, Player player){
    //y++, x-- move down once and to the left one
    WINDOW* checkWin= player.curwin;
    int begY, begX;
    int maxX,maxY;
    int lDiaWin=0;
    getbegyx(checkWin,begY,begX);
    getmaxyx(checkWin,maxY,maxX);
    int lx = 0;
    int ly= 0;
    player.curC = currentPlayer(player.turn);
    if(player.curC=='X') {
        for (int i = begY + 3; i < maxY - 3; i++) {
            for (int j = begX; j < maxX + 2; j++) {
                lx = j - 1;
                ly = i + 1;
                if (mvwinch(checkWin, i, j) == 'X') {
                    lDiaWin = lDiaWin + 1;

                    while (mvwinch(checkWin, ly, lx) == 'X') {
                        lDiaWin = lDiaWin + 1;
                        lx = lx - 1;
                        ly = ly + 1;
                    }

                } else if ((mvwinch(checkWin, i, j) == 'O') || (mvwinch(checkWin, i, j) == '*')) {
                    lDiaWin = 0;
                }
                if (lDiaWin == pies) {
                    return true;
                }
                lDiaWin = 0;
            }

            lDiaWin = 0;
        }//LEFT Dialog win
    }
    else if(player.curC=='O') {
        for (int i = begY + 3; i < maxY - 3; i++) {
            for (int j = begX; j < maxX + 2; j++) {
                lx = j - 1;
                ly = i + 1;
                if (mvwinch(checkWin, i, j) == 'O') {
                    lDiaWin = lDiaWin + 1;

                    while (mvwinch(checkWin, ly, lx) == 'O') {
                        lDiaWin = lDiaWin + 1;
                        lx = lx - 1;
                        ly = ly + 1;
                    }

                } else if ((mvwinch(checkWin, i, j) == 'X') || (mvwinch(checkWin, i, j) == '*')) {
                    lDiaWin = 0;
                }
                if (lDiaWin == pies) {
                    return true;
                }
                lDiaWin = 0;
            }

            lDiaWin = 0;
        }//LEFT Dialog win
    }
 return false;
};
bool  rightDialog(int pies, Player player) {

    WINDOW *checkWin = player.curwin;

    int begY, begX;
    int maxX, maxY;
    int rDiaWin = 0;
    getbegyx(checkWin,begY,begX);
    getmaxyx(checkWin,maxY,maxX);
    int x = 0;
    int y = 0;
    player.curC=currentPlayer(player.turn);
    if(player.curC=='X') {
        for (int i = begY + 3; i < maxY - 3; i++) {
            for (int j = begX; j < maxX + 2; j++) {
                x = j + 1;
                y = i + 1;
                if (mvwinch(checkWin, i, j) == 'X') {
                    rDiaWin = rDiaWin + 1;

                    while (mvwinch(checkWin, y, x) == 'X') {
                        rDiaWin = rDiaWin + 1;
                        x = x + 1;
                        y = y + 1;
                    }

                } else if ((mvwinch(checkWin, i, j) == 'O') || (mvwinch(checkWin, i, j) == '*')) {
                    rDiaWin = 0;
                }
                if (rDiaWin == pies) {
                    return true;
                }
                rDiaWin = 0;
            }

            rDiaWin = 0;
        }//right DiaWin
    }
    else if(player.curC=='O') {
        for (int i = begY + 3; i < maxY - 3; i++) {
            for (int j = begX; j < maxX + 2; j++) {
                x = j + 1;
                y = i + 1;
                if (mvwinch(checkWin, i, j) == 'O') {
                    rDiaWin = rDiaWin + 1;

                    while (mvwinch(checkWin, y, x) == 'O') {
                        rDiaWin = rDiaWin + 1;
                        x = x + 1;
                        y = y + 1;
                    }

                } else if ((mvwinch(checkWin, i, j) == 'X') || (mvwinch(checkWin, i, j) == '*')) {
                    rDiaWin = 0;
                }
                if (rDiaWin == pies) {
                    return true;
                }
                rDiaWin = 0;
            }

            rDiaWin = 0;
        }//right DiaWin
    }
    return false;
};