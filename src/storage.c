#include <stdio.h>
#include <string.h>
#include "storage.h"
#include "todoFunctions.h"

void saveTask(task toDoList[], int *tasknum)
{
  FILE *savedTasks;
  char lineParse[256];
  int compareTaskNum;
  
  savedTasks = fopen(TASK_LOC, "r");
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
  savedTasks = fopen(TASK_LOC, "a");
    if (savedTasks != NULL) {
      fprintf(savedTasks, "Task #%d: %s\n", *tasknum, toDoList[*tasknum].description);
      fclose(savedTasks);
      return;
    } else {
      printf("ERROR: File cannot be opened");
      return;
    }
}

void loadTask(task toDoList[]) {  
  FILE *loadFile;  
  char tempStringBuffer[INPUTLENGTH];  
  char lineBuffer[256];  
  int taskNum;  
  loadFile = fopen(TASK_LOC, "r");  
  if (loadFile != NULL) {    
    while(fgets(lineBuffer, sizeof(lineBuffer), loadFile) != NULL) {      
      if ((sscanf(lineBuffer, "Task #%d: %99[^\n]", &taskNum, tempStringBuffer)) == 2) {        
        strncpy(toDoList[taskNum].description, tempStringBuffer, INPUTLENGTH - 1);        
        toDoList[taskNum].description[INPUTLENGTH] = '\0';        
        toDoList[taskNum].storage = NOTEMPTY;      
      }    
    }    
    fclose(loadFile);    
    return;  
  } else {
      loadFile = fopen(TASK_LOC, "a");  
      if (loadFile == NULL) {
      printf("Could not create a save file");
      return;
    }
      fclose(loadFile);
      return;
  }
}
