// storage.h - stores calls directly related to 
// save state manipulation

#ifndef STORAGE_H
#define STORAGE_H

#include "todoFunctions.h"
#define TASK_LOC "data/tasks.txt"
#define TEMP_LOC "data/tasks.tmp"

// function prototypes
void saveTask(task toDoList[], int *tasknum);
void loadTask(task toDoList[]);

#endif
