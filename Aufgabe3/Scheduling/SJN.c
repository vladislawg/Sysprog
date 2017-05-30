#include "SJN.h"
#include "Queue.h"



void schedule_SJN(const TaskPool *task_pool) {
  Task *CPU = NULL;
  int current_tick = 0;
  Task *newTask;
  PrioQueue *queue = createQueue();

  while (!allDone(task_pool)) {
    newTask = checkArrivals(task_pool, current_tick);
    if(newTask != NULL){
      pqueue_offer(queue, q_elem_new(newTask, newTask -> arrival_tick, newTask -> total_ticks));
    }

    if(CPU == NULL){
      CPU = pqueue_poll(queue);
    }else if(isDone(CPU)){
      CPU = pqueue_poll(queue);
    }
    if (execTask(CPU, 1) < 0) {
      printf("%sERROR:%s No Task selected to be executed.\n", COLOR_RED, COLOR_RESET);
      break;
    }
    current_tick ++;
  }
  return;
}
