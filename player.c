//
// Created by noahc on 2/9/2019.
//

#include "player.h"
#include <curses.h>
#include "checkWin.h"
extern int pOneDrops, pTwoDrops; // Global variables from main.c
extern bool tie;
Player playerMove(WINDOW* win, int y, int x, int c, TurnType turn){
   Player player ;
   player.curwin = win;
   player.xLoc = x;
   player.yLoc = y;
   player.curC = c ;
   //getmaxyx(player.curwin,player.yLoc,player.xLoc);
   player.turn = turn;
   int maxX = getmaxx(win);
   char placeC =   currentPlayer(player.turn);

   switch (player.curC){
       case 97:
       case 106:
       if(player.xLoc > 0) {
           mvwaddch(player.curwin, player.yLoc, player.xLoc, ' ');
           player.xLoc = player.xLoc - 1;
           mvwaddch(player.curwin, player.yLoc, player.xLoc, placeC);
           wmove(player.curwin, player.yLoc, player.xLoc);
           wrefresh(player.curwin);//refresh

       }
         break;
       case 115:
       case 107:
           if(player.xLoc < maxX-1) {
               mvwaddch(player.curwin, player.yLoc, player.xLoc, ' ');
               player.xLoc = player.xLoc + 1;
               mvwaddch(player.curwin, player.yLoc, player.xLoc, placeC);
               wmove(player.curwin, player.yLoc, player.xLoc);
               wrefresh(player.curwin);//refresh
           }

           break;
       case 32:
       case 10:
           dropChar(player);
           if((player.turn%2)==0){
               mvwaddch(player.curwin,player.yLoc,player.xLoc,'X');
               wmove(player.curwin, player.yLoc, player.xLoc);
               pOneDrops= pOneDrops +1;
               player.turn = (player.turn + 1)%2;
               wrefresh(player.curwin); // refresh

           }
           else if ((player.turn%2)==1){
               mvwaddch(player.curwin,player.yLoc,player.xLoc,'O');
               wmove(player.curwin, player.yLoc, player.xLoc);
               pTwoDrops= pTwoDrops +1;
               player.turn = (player.turn + 1)%2;
               wrefresh(player.curwin); // refresh
           }

           break;
       default:
           break;
   }


return player;
};
void dropChar(Player player){
    int curY, curX;
    int y = getmaxy(player.curwin);
    int counter = y-4;
    y = y -4;
    char placeC =   currentPlayer(player.turn);

    getyx(player.curwin,curY,curX);
    for(int i = 1 ; i < counter; ++i){
        if( mvwinch(player.curwin,y,curX) == '*') {

            mvwaddch(player.curwin, y, curX, placeC);
            wrefresh(player.curwin);
            break;
        }
            y = y-1;
            curY++;


    }


}
char currentPlayer(TurnType turn){
    if( turn == 0){
        return 'X';
    }
    else if (turn == 1){
        return 'O';
    }
    return 0;
}
bool isGameOver(int pies, Player player){
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
                    player.marker=90;
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
    int vertWin=0;
    int dy= 0;

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
    int lDiaWin=0;
    int lx=0,ly=0;
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
    int rDiaWin=0;
    int x = 0;
    int y = 0;
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
    int tieGame=0;
    int tY=3;
   // int tX=0;
    for(int i = begX;i < maxX+1;i++){
        if(mvwinch(checkWin,tY,i)!='*'){
            tieGame=tieGame+1;
           // tX=tX+1;
        }
    }
    if(tieGame==maxX+1){
        tie = true;
        return true;
    }
   /* if( winner(pies, player)) {
        //wmove(player.curwin, player.yLoc, player.xLoc);
        return true;
    }
    else if(tie(pies,player)){
      //  wmove(player.curwin, player.yLoc, player.xLoc);
        return true;
    }*/
    wmove(player.curwin, player.yLoc, player.xLoc);
   /* WINDOW* checkWin= player.curwin;
   int curY = player.yLoc;
   int curX = player.xLoc;
    int begY, begX;
    int maxX,maxY;
    int horiWin=0,rDiaWin=0,lDiaWin=0, vertWin=0;

    getbegyx(checkWin,begY,begX);
    getmaxyx(checkWin,maxY,maxX);
    for(int i =begY+3;i<maxY-3;i++){

        for(int j = begX; j < maxX+2;j++){
            //x=j+1;
            if(horiWin==(pies)){
                return true;
            }
            if ((mvwinch(checkWin,i,j)=='X')){
                horiWin = horiWin+1;

            }
            else if((mvwinch(checkWin,i,j)=='O') || (mvwinch(checkWin,i,j)=='*')){
                horiWin=0;
            }

        }

        horiWin=0;
    }//horizon win end
    int x= 0;
    int y=0;
    for(int i =begY+3;i<maxY-3;i++){
        for(int j = begX; j < maxX+2;j++){
            x=j+1;
            y=i+1;
               if(mvwinch(checkWin,i,j)=='X'){
                   rDiaWin= rDiaWin+1;

                   while(mvwinch(checkWin,y,x)=='X'){
                       rDiaWin=rDiaWin+1;
                       x=x+1;
                       y=y+1;
                   }

               }
               else if((mvwinch(checkWin,i,j)=='O')|| (mvwinch(checkWin,i,j)=='*')) {
                   rDiaWin = 0;
               }
               if(rDiaWin==pies){
                   return true;
               }
            rDiaWin=0;
        }

        rDiaWin=0;
    }//right DiaWin
    int lx = 0;
    int ly= 0;
    for(int i =begY+3;i<maxY-3;i++) {
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
    int dy= 0;
    for(int i =begY+3;i<maxY-3;i++){

        for(int j = begX; j < maxX+2;j++){

            if(vertWin==(pies)){
                return true;
            }
            if ((mvwinch(checkWin,i,j)=='X')){
                 dy= i;
                while (mvwinch(checkWin, dy, j) == 'X') {
                    vertWin = vertWin + 1;
                    dy = dy + 1;
                }

            }
            else if((mvwinch(checkWin,i,j)=='O') || (mvwinch(checkWin,i,j)=='*')){
                vertWin=0;
            }
            if(vertWin==(pies)){
                return true;
            }
            vertWin=0;
        }

    }//Vertical win end
   mvwinch(player.curwin,curY,curX);

    if(pOneDrops >= pies || pTwoDrops>=pies){
       if( winner(pies, player)) {
           return true;
       }
       else if(tie(pies,player)){
            wmove(player.curwin, player.yLoc, player.xLoc);
           return true;
       }
    } */


    return false;
}