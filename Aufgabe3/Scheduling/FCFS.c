#include "FCFS.h"

void schedule_FCFS(const TaskPool *task_pool) {
    // TODO
  //  printf("NOT IMPLEMENTED!\n");

    Task *CPU = NULL;
    int max_task = task_pool -> size;
    int index;

    while (!allDone(task_pool)) {

      if(index != max_task){
        CPU = task_pool->task[index];
      }

        if (execTask(CPU, 1) < 0) {
            printf("%sERROR:%s No Task selected to be executed.\n", COLOR_RED, COLOR_RESET);
            break;
        }
        index ++;
    }
    printf("\n");

    return;
}
