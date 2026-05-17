#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

// function declarations
WINDOW *createNewWindow(int height, int width, int starty, int startx);
WINDOW *createSubWindow(WINDOW *mainWin, int height, int width);
int menu(int height, int width, int starty, int startx);

// menu window choices
char *choices[] = {
  "Add Tasks",
  "Remove Tasks",
  "View Tasks",
  "Exit Program",
};

int main(void)
{
  // window declarations
  WINDOW *headerWindow;
  int startx, starty;
  int width, height;
  int titleheight, titleStarty;
  int titleCenterx, titleCentery;
  int userSelection;

  // input declarations
  int ch;
  initscr(); // enables curses mode
  cbreak(); // disable buffering from keyboard input
  curs_set(0); //disables visual for cursor 

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
  headerWindow = createNewWindow(titleheight, width, titleStarty + 6, startx);
  refresh();
  
  // Title
  const char *title = "To Do List";
  titleCenterx = (width - strlen(title)) / 2;
  titleCentery = 1;
  mvwprintw(headerWindow, titleCentery, titleCenterx, "To Do List");
  wrefresh(headerWindow);

  userSelection = menu(height, width, starty, startx);

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

  return newWindow;
}

WINDOW *createSubWindow(WINDOW *mainWin, int height, int width) 
{
  WINDOW *subWindow;
  int subWinHeight = height / 2;
  int subWinWidth = width / 2;
  int startY = (height - subWinHeight) / 2;
  int startX = (width - subWinWidth) / 2;

  subWindow = derwin(mainWin, subWinHeight, subWinWidth, startY, startX); // creates a sub window based on a parent window

  return subWindow;
}

int menu(int height, int width, int starty, int startx)
{
// Menu Window declarations
  ITEM **menuItems;
  MENU *mainMenu;
  WINDOW *menuWindow;
  WINDOW *menuChoices;
  int numofchoices;
  int ch;
  int choice = -1;
  
  // menu initialization
  numofchoices = ARRAY_SIZE(choices); // counts number of choices 
  menuItems = (ITEM **)calloc(numofchoices + 1, sizeof(ITEM *)); // creates space for choices
  
  for ( int i = 0; i < numofchoices; ++i) // plugs choices into amount of choices
    menuItems[i] = new_item(choices[i], choices[i]);

  menuItems[numofchoices] = (ITEM *) NULL; // adds a null ending to the end (necessary for ITEM * variable type)
  mainMenu = new_menu((ITEM **)menuItems); // makes the actual menu type

  // menu window initialization
  menuWindow = createNewWindow(height, width, starty + 2, startx);
  menuChoices = createSubWindow(menuWindow, height, width);
  keypad(menuWindow, TRUE);

  // cconnects window to menu type
  set_menu_win(mainMenu, menuWindow);
  set_menu_sub(mainMenu, menuChoices);
  
  // menu formatting
  set_menu_mark(mainMenu, "> ");
  set_menu_fore(mainMenu, A_REVERSE | A_BOLD);
  set_menu_back(mainMenu, A_NORMAL);
  
  // putting window on screen
  post_menu(mainMenu);
  wrefresh(menuWindow);
  wrefresh(menuChoices);

  // loop that reads for user input
  while ((ch = wgetch(menuWindow)) != 'q') {
    switch (ch) {
      case KEY_DOWN:
      menu_driver(mainMenu, REQ_DOWN_ITEM);
      break;

      case KEY_UP:
      menu_driver(mainMenu, REQ_DOWN_ITEM);
      break;

      case 10: // enter - item selection
      choice = item_index(current_item(mainMenu));
      break;
    }
    
    // refreshes per key press
    wrefresh(menuWindow);
    wrefresh(menuChoices);

    if (choice != -1) break;
    
  }
  
  // menu cleanup
  unpost_menu(mainMenu);
  free_menu(mainMenu);
  
  // clearing menu items and window
  for (int i = 0; i < numofchoices; i++) free_item(menuItems[i]);
  free(menuItems);
  delwin(menuChoices);
  delwin(menuWindow);

  return choice; // returns the value to use for main()
}
