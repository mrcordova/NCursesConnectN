#include <stdio.h>
#include <ncurses.h>
#include "board.h"
//#include "move.h"
//#include "win.h"
//#include "CursorTrakedWindow.h"
#include <curses.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "player.h"

typedef struct BoardGame{
    char** theBoard;
    int numRows;
    int numCols;
    char blankChar;
}BoardGame;
int pOneDrops, pTwoDrops;
bool tie=false;
int main(int argc, char *argv[]) {
    int rows =  atoi(argv[2]);
    int cols = atoi(argv[3]) ;
    int pies = atoi(argv[4]);
    FILE* fp = fopen(argv[5],"w");
  //  fclose(fp);
   // strcpy(path, argv[5]);
   // FILE* fp = fopen(path, "a+");
   // src_dump(fp);
   // fclose(fp);
    initscr();
    cbreak();
    noecho();
    WINDOW* win = newwin(rows+6,cols,0,0);// main window
    WINDOW* playArea = subwin(win,3,cols,0,0); // player is located
    WINDOW* ann = subwin(win,2,cols,rows-3,0); // announce winners here
   // Player player;

    // Board game = makeBoard(rows,cols,'*');
   // printBoard(game);
    refresh();
    wrefresh(win); //
    touchwin(playArea);
    wrefresh(playArea);
    touchwin(ann);
    wrefresh(ann);
    box(win,0,0); // goes first or it covers smaller boxes and characters like '*'
    box(playArea,0,0);
    wborder(playArea,' ',' ',0,0,' ',' ',' ',' ');
    box(ann,0,0);
    fillWindow(win,'*');

    wrefresh(win);
   // mvwprintw(win,1,1,"*"); // this function moves the character '*' anyway in the window "win", default being 0,0(left top corner)
// move to left or right

    int mv ;
    int x, y;
    //int playerTurn=0;
    Player play;
    play.turn = 0;
    getyx(win,y,x);
   play.curwin = win;
  play.xLoc = x;
  play.yLoc = y;
   play.curC = 'X';
    mvwaddch(play.curwin, play.yLoc, play.xLoc, 'X');
    wmove(play.curwin, play.yLoc, play.xLoc);
    wrefresh(win);
    do{
        mv = wgetch(win);
       play = playerMove(win,play.yLoc,play.xLoc,mv,play.turn);
       wrefresh(win);
       scr_dump(argv[5]);


    }while( (isGameOver(pies, play)) == false );
    if((play.turn==0) && (tie==false)){
        wresize(win,20, 20);
        wrefresh(win);
        touchwin(ann);
       // wrefresh(ann);
        mvwprintw(win, rows+3, 0, "Player 1 wins!");

      //  wprintw(ann,"Player 1 wins!");
    }
    else if((play.turn==1) && (tie==false) ){
        wresize(win,20, 20);
        wrefresh(win);
        touchwin(ann);
        mvwprintw(win, rows+3, 0, "Player 2 wins!");

    }
    else if(tie) {
        wresize(win,20, 20);
        wrefresh(win);
        touchwin(ann);
        mvwprintw(win, rows+3, 0, "Tie Game!");

    }
    wrefresh(ann);
    wrefresh(win);
    scr_dump(argv[5]);

    fclose(fp);
    delwin(win);
    delwin(ann);
    delwin(playArea);
    endwin(); // Ncurses end

   return 0;
}