#include "../Tasks/TaskPool.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct q_elem_s
{
	Task *task;
  uint16_t arrival;
  uint16_t total;
	struct q_elem_s *next;
}q_elem;

typedef struct _PrioQueue
{
	int size;
	q_elem *root;
}PrioQueue;


PrioQueue *createQueue();
q_elem* q_elem_new(Task *task, uint16_t arrival, uint16_t total);
int pqueue_offer(PrioQueue *queue, q_elem* newElem);
void pqueue_print(PrioQueue *queue);
Task* pqueue_peek(PrioQueue *queue);
Task* pqueue_poll(PrioQueue *queue);
void pqueue_free(PrioQueue *queue);
