#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

// function declarations
WINDOW *createNewWindow(int height, int width, int starty, int startx);

int main(void)
{
  // window declarations
  WINDOW *mainWindow;
  WINDOW *headerWindow;
  int startx, starty, width, height, titleheight, titleStarty, titleCenterx, titleCentery;

  // input declarations
  int ch;
  initscr(); // enables curses mode
  cbreak(); // disable buffering from keyboard input
  curs_set(0); // disables visual for cursor 

  // placement declarations
  height = 24;
  width = 60;
  starty = (LINES - height) / 2; // centering the window
  startx = (COLS - width) / 2;
  titleheight = height / 7;
  titleStarty = starty / 7;
  refresh();

  // a bit spaghetti but ill fix it when needed or when i think 
  // of a solution
  mainWindow = createNewWindow(height, width, starty + 2, startx);
  headerWindow = createNewWindow(titleheight, width, titleStarty + 6, startx);
  refresh();

  // text insertions
  
  // Title
  const char *title = "To Do List";
  titleCenterx = (width - strlen(title)) / 2;
  titleCentery = 1;
  mvwprintw(headerWindow, titleCentery, titleCenterx, "To Do List");
  wrefresh(headerWindow);

  // main window body
  const char *mselect1 = "Add Task";
  const char *mselect2 = "Remove Tasks";
  const char *mselect3 = "View Tasks";
  const char *mselect4 = "Exit";
  int mainCenter1 = (width - strlen(mselect1)) / 2;
  int mainCenter2 = (width - strlen(mselect2)) / 2;
  int mainCenter3 = (width - strlen(mselect3)) / 2;
  int mainCenter4 = (width - strlen(mselect4)) / 2;

  mvwprintw(mainWindow, 9, mainCenter1, mselect1);
  mvwprintw(mainWindow, 11, mainCenter2, mselect2);
  mvwprintw(mainWindow, 13, mainCenter3, mselect3);
  mvwprintw(mainWindow, 15, mainCenter4, mselect4);
  wrefresh(mainWindow);

  // temporary end window for size testing 
  if ((ch = getch()) == 'q') {
    endwin();
    return 0;
  }

}

// function for creating a new window (will make a separate function in 
// order to prep for future iterations past v1)
WINDOW *createNewWindow(int height, int width, int starty, int startx) 
{
  WINDOW *newWindow;

  newWindow = newwin(height, width, starty, startx); // creates a window
  box(newWindow, 0, 0); // draws lines on window perimeters

  wrefresh(newWindow); // refreshes the window

  return newWindow;
}
