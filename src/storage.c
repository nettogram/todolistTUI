#include <stdio.h>
#include "storage.h"
#include "todoFunctions.h"

void saveTask(task toDoList[], int *tasknum)
{
  FILE *savedTasks;
  char lineParse[256];
  int compareTaskNum;
  
  savedTasks = fopen("../data/tasks.txt", "r");
  if (savedTasks != NULL) {
    while (fgets(lineParse, sizeof(lineParse),savedTasks) != NULL) {
      if (sscanf(lineParse, "Task #%d:", &compareTaskNum) == 1) {
        if (compareTaskNum == *tasknum) {
          printf("ERROR: Task slot is already filled");
          fclose(savedTasks);
          return;
        }
      }
    }
    fclose(savedTasks);
  }
  savedTasks = fopen("../data/tasks.txt", "a");
    if (savedTasks != NULL) {
      fprintf(savedTasks, "Task #%d: %s\n", *tasknum, toDoList[*tasknum].description);
      fclose(savedTasks);
      return;
    } else {
      printf("ERROR: File cannot be opened");
      return;
    }
}
