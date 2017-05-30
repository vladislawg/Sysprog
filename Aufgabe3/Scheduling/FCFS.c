#include "FCFS.h"

void schedule_FCFS(const TaskPool *task_pool) {
  Task *CPU = NULL;
  int index = 0;

    for(int i = 0; i < task_pool -> size; i++){
      CPU = task_pool->task[i];

      while(!isDone(CPU)){
        if (execTask(CPU, 1) < 0) {
          printf("%sERROR:%s No Task selected to be executed.\n", COLOR_RED, COLOR_RESET);
          break;
        }
      }
    }
    return;
}
