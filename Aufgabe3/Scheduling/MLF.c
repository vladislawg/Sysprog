#include "MLF.h"
#include "Queue.h"
#include <math.h>

Queue **create_queue_array(int amount){
  Queue **q = malloc(amount*sizeof(Queue));
  for(int i = 0; i < amount; i++){
    q[i]=create_Queue();
  }
  return q;
}

Task *get_next_task(Queue** queues, int amount, int* queue_index){
  for(int i = 0; i < amount; i++){
    if(isEmpty(queues[i])) continue;

    Task *task = queue_peek(queues[i]);
    *queue_index = i;
    return task;
  }
  return NULL;
}


void schedule_MLF(const TaskPool *task_pool, uint16_t num_levels) {
  Queue **queues = create_queue_array(num_levels);
  Task *CPU = NULL;
  Task *newTask = NULL;
  int current_tick = 0;
  int runtime = 0;
  int current_queue = 0;
  int last_queue_index = num_levels -1;

  while (!allDone(task_pool)) {
    newTask = checkArrivals(task_pool, current_tick);
    if(newTask != NULL){
      queue_offer(queues[0], newTask);
    }

    if(runtime == 0 && CPU != NULL){
      if(isDone(CPU)){
        queue_poll(queues[current_queue]);
      }else{
        queue_poll(queues[current_queue]);
        if(current_queue == last_queue_index){
          queue_offer(queues[current_queue], CPU);
        }else{
          queue_offer(queues[current_queue + 1], CPU);
        }
      }
      CPU = NULL;
    }

    if(CPU == NULL){
      CPU = get_next_task(queues, num_levels, &current_queue);
      if(current_queue != last_queue_index){
        runtime = pow(2, current_queue);
      }else{
        runtime = 1000000;
      }
    }

    if(execTask(CPU, 1) < 0){
      printf("%sERROR:%s No Task selected to be executed.\n", COLOR_RED, COLOR_RESET);
      break;
    }

    current_tick ++;
    runtime --;
  }

  for(int i = 0; i < num_levels; i++){
    queue_free(queues[i]);
  }
  free(queues);

  printf("\n");
}
