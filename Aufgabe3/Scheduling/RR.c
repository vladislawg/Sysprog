#include "RR.h"

typedef struct _CicleElement{
  Task *task;
  struct _CicleElement *next;
  struct _CicleElement *prev;
} CircleElement;

void schedule_RR(const TaskPool *task_pool, uint16_t quantum_max) {
  Task *CPU = NULL;
  CircleElement *current = NULL;
  CircleElement *temp = NULL;
  Task *newTask = NULL;
  int current_tick = 0;
  int runtime = 0;
  while (!allDone(task_pool)) {
      newTask = checkArrivals(task_pool, current_tick);
      if(newTask != NULL){
        if(current == NULL){
          current = calloc(1, sizeof(CircleElement));
          current -> task = newTask;
        }else{
          temp =  calloc(1, sizeof(CircleElement));
          temp -> task = newTask;
          if(current -> next == NULL){
            current -> prev = temp;
            current -> next = temp;
            temp -> prev = current;
            temp -> next = current;
          } else {
            temp -> next = current;
            temp -> prev = current -> prev;
            current -> prev -> next = temp;
            current -> prev = temp;

          }

        }
      }


      if (CPU == NULL){
        runtime = 0;
      } else if (isDone(CPU)){
        if (current -> next == NULL) {
          free(current);
          current = NULL;
        } else {
          current -> prev -> next = current -> next;
          current -> next -> prev = current -> prev;
          CircleElement *next = current -> next;
          free(current);
          current = next;
        }
        CPU = current -> task;
        runtime = 0;
      } else if (runtime >= quantum_max) {
        if (current -> next != NULL) {
          current = current -> next;
          runtime = 0;
        }
      }

      if (current != NULL) CPU = current -> task;
      else CPU = NULL;

      if (execTask(CPU, 1) < 0) {
          printf("%sERROR:%s No Task selected to be executed.\n", COLOR_RED, COLOR_RESET);
          break;
      }
      current_tick ++;
      runtime ++;

  }
  printf("\n");
  return;
}
