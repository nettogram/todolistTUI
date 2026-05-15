// todoFunctions.h - header that stores calls related to 
// to do list manipulation

#ifndef TODOFUNCTIONS_H
#define TODOFUNCTIONS_H

// definitions for acronyms
#define INPUTLENGTH 50
#define NOTFINISHED 0
#define FINISHED 1
#define EMPTY 0
#define NOTEMPTY 1
#define ERROR 404

// struct that stores to do list 
typedef struct{
  char description[INPUTLENGTH + 1];
  int status;
  int storage;
} task;

// prototypes for to do list functions - functions that
// manipulate the to do list
void printOptions(void);
void taskSelect(int *taskNum);
void addTask(task toDoList[], int *taskNum);
void removeTask(task toDoList[], int *tasknum);
void taskView(void);

#endif





