#include <stdio.h>
#include <ncurses.h>
#include "storage.h"
#include "todoFunctions.h"

// function definitions
void printOptions()
{
  printf("\n");
  printf("1. Add Tasks\n");
  printf("2. Remove Tasks\n");
  printf("3. List Tasks\n");
  printf("4. Exit\n\n");
  }


void taskSelect(int *taskoption, int height, int width, int starty, int startx)
{
  WINDOW *taskselectwin
  taskselectwin = createNewWindow(height, witdth, starty, startx);
  mvwprintw(taskselectwin, 1, 1, "Please select the task slot (1-10): ");
  wscanw(taskselectwin, "%d", taskoption);
  while (1) {
    if (*taskoption < 1 || *taskoption > 10) {
      *taskoption = ERROR;
      werase(taskselectwin);
      wrefresh(taskselectwin);
      delwin(taskselectwin);
      return;
    } else {
        *taskoption--;
        werase(taskselectwin);
        wrefresh(taskselectwin);
        delwin(taskselectwin);
        return;
    }
  }
}

void addTask(task toDoList[], int *tasknum)
{
  int ch, i = 0;
  ch = getchar(); // clear buffer of extra NULL
  printf("Enter to do list task here: ");
  while ((ch = getchar()) != '\n') {
    if (i < INPUTLENGTH) { 
      toDoList[*tasknum].description[i++] = ch;
      toDoList[*tasknum].storage = NOTEMPTY;
    } else {
        printf("Error: Input exceeds character limit.");
      for (i = 0; i < INPUTLENGTH; i++)
        toDoList[*tasknum].description[i] = ch;
      toDoList[*tasknum].storage = EMPTY;
      printf("\n");
      return;
      }
    }
    toDoList[*tasknum].description[i] = '\0';
    printf("\n");
    return;
}


void removeTask(task toDoList[], int *tasknum)
{
  FILE *refreshTask;
  for (int i = 0; i < INPUTLENGTH; i++)
    toDoList[*tasknum].description[i] = '\0';
  toDoList[*tasknum].storage = EMPTY;


  refreshTask = fopen(TEMP_LOC, "w");

  if (refreshTask != NULL) {
    for (int i = 0; i < 10; i++) {
      if (toDoList[i].storage == NOTEMPTY)
        fprintf(refreshTask, "Task #%d: %s\n", i, toDoList[i].description);
    }
    fclose(refreshTask);
    remove(TASK_LOC);
    rename(TEMP_LOC, TASK_LOC);
    return;
  } else {
      printf("ERROR: Task cannot be performed.");
      remove(TEMP_LOC);
      return;
  }
}

void taskView()
{
  FILE *fileRead;
  char tempStringBuffer[256];
  printf("\n");

  fileRead = fopen(TASK_LOC, "r");

  if (fileRead != NULL) {
    while (fgets(tempStringBuffer, sizeof(tempStringBuffer), fileRead) != NULL) {
      printf("%s", tempStringBuffer);
    }
  } else {
      printf("ERROR: No tasks saved.\n");
      return;
  }
  fclose(fileRead);
  return;
}

void makeTasksEmpty(task toDoList[])
{
  for (int i = 0; i < 10; i++){
    for (int n = 0; n < INPUTLENGTH; n++) {
      toDoList[i].description[n] = '\0';
    }
    toDoList[i].storage = EMPTY;
  }
}
