#include <stdio.h>
#include <string.h>

#define INPUTLENGTH 50
#define NOTFINISHED 0
#define FINISHED 1
#define EMPTY 0
#define NOTEMPTY 1
#define ERROR 404

typedef struct{
  char description[INPUTLENGTH + 1];
  int status;
  int storage;
} task;

// prototypes
void addTask(task toDoList[], int *taskNum);
void taskSelect(int *taskNum);
void removeTask(task toDoList[], int *tasknum);
void printOptions(void);
void taskView(void);
void saveTask(task toDoList[], int *tasknum);
void loadTask(task toDoList[]);

int main(void)
{
  int actionselect, taskoption = 0;
  int *taskselect = &taskoption;
  task toDoList[10];

  loadTask(toDoList);

  do {
    printOptions();
    printf("Please select an option: ");
    scanf("%d", &actionselect);

    switch (actionselect) {
      case 1: {
        taskSelect(taskselect);
        if (*taskselect == ERROR) {
          break;
        } else if (toDoList[*taskselect].storage == NOTEMPTY) {
            printf("Unable to fill entry. Task slot is currently filled");
            break;
        } else {
            addTask(toDoList, taskselect);
            saveTask(toDoList, taskselect);
            break;
        }
    } case 2: {
        taskSelect(taskselect);
        if (*taskselect == ERROR) {
          break;
        } else {
            removeTask(toDoList, taskselect);
            break;
        }
    } case 3: {
        taskView();
        break;
    } case 4:
        return 0;
      default: {
        printf("Invalid entry! Please enter a valid user input");
        break;
      } 
    }  
  } while (1);

  return 0;
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

void printOptions()
{
  printf("\n");
  printf("1. Add Tasks\n");
  printf("2. Remove Tasks\n");
  printf("3. List Tasks\n");
  printf("4. Exit\n\n");
  }

void removeTask(task toDoList[], int *tasknum)
{
  FILE *refreshTask;
  for (int i = 0; i < INPUTLENGTH; i++)
    toDoList[*tasknum].description[i] = '\0';
  toDoList[*tasknum].storage = EMPTY;


  refreshTask = fopen("..data/tasks.tmp", "w");

  if (refreshTask != NULL) {
    for (int i = 0; i < 10; i++) {
      if (toDoList[i].storage != EMPTY)
        fprintf(refreshTask, "Task #%d: %s\n", i, toDoList[i].description);
    }
    fclose(refreshTask);
    remove("../data/tasks.tmp");
    rename("../data/tasks.tmp", "../data/tasks.txt");
    return;
  } else {
      printf("ERROR: Task cannot be performed.");
      remove("..data/tasks.tmp");
      return;
  }
}

void taskSelect(int *taskoption)
{
  printf("Please select the task slot (0-9): ");
  scanf("%d", taskoption);
  if (*taskoption < 0 || *taskoption > 9) {
    printf("Invalid task.\n");
    *taskoption = ERROR;
  } 
}

void taskView()
{
  FILE *fileRead;
  char tempStringBuffer[256];
  printf("\n");

  fileRead = fopen("../data/tasks.txt", "r");

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

void loadTask(task toDoList[]) 
{
  FILE *loadFile;
  char tempStringBuffer[INPUTLENGTH];
  char lineBuffer[256];
  int taskNum;

  loadFile = fopen("../data/tasks.txt", "r");
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
  printf("ERROR: no saved tasks");
  return;
  }
}
