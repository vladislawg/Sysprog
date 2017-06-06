#include "MLF.h"
#include "Queue.h"

Queue **create_queue_array(uint16_t num_levels){
  Queue **q = malloc(num_levels);
  if(q == NULL){
    printf("Error\n");
  }

  for(int i = 0; i<num_levels; i++){
    q[i]=malloc(sizeof(Queue));
    if(q[i] == NULL){
      printf("error\n");
    }else{
      printf("alldone\n");
    }
  }
}


void schedule_MLF(const TaskPool *task_pool, uint16_t num_levels) {
  Queue **q = create_queue_array(num_levels);


  srand(time(NULL));
  Task *CPU = NULL;

  while (!allDone(task_pool)) {
      CPU = task_pool->task[rand() % task_pool->size];
      if (execTask(CPU, 1) < 0) {
          printf("%sERROR:%s No Task selected to be executed.\n", COLOR_RED, COLOR_RESET);
          break;
      }
    }
  printf("\n");
}
