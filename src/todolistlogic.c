#include <stdio.h>

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
void removeTask(task toDoList[], int *taskNum);
void printOptions(void);
void taskView(task toDoList[]);
void makeTasksEmpty(task toDoList[]);

int main(void)
{
  int actionselect, taskoption = 0;
  int *taskselect = &taskoption;
  task toDoList[10];

  makeTasksEmpty(toDoList);
  
  do {
    printOptions();
    printf("Please select an option: ");
    scanf("%d", &actionselect);

    switch (actionselect) {
      case 1: {
        taskSelect(taskselect);
        if (*taskselect == ERROR) {
          break;
        } else if (toDoList[taskselect].storage == NOTEMPTY) {
            printf("Unable to fill entry. Task slot is currently filled");
            break;
        } else {
            addTask(toDoList, taskselect);
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
        taskView(toDoList);
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
  for (int i = 0; i < INPUTLENGTH; i++)
    toDoList[*tasknum].description[i] = '\0';
  toDoList[*tasknum].storage = EMPTY;
  printf("\n");
  return;
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

void taskView(task task[])
{
  int tasknum;
  printf("\n");

  for (int i = 0; i < 10; i++) {
    if (task[i].storage != EMPTY) {
      tasknum = i;
      printf("Task #%d: %s\n", tasknum, task[tasknum].description);
    }
  }
}

void makeTasksEmpty(task toDoList[])
{
  for (int i = 0; i < 10; i++){
    for (int n = 0; n < INPUTLENGTH; n++) {
      toDoList[i].description[INPUTLENGTH] = '\n';
    }
    toDoList[i].storage = EMPTY;
  }
}
