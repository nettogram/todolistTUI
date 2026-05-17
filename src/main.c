#include <stdio.h>
#include <string.h>
#include "storage.h"
#include "todoFunctions.h"

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


