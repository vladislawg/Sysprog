#include <stdlib.h>
#include <stdio.h>

//#include "../Tasks/TaskPool.h"

typedef struct _Element{
  void *data;
  struct _Element *next;
}Element;

typedef struct _Queue{
  int size;
  Element *head;
  Element *tail;
}Queue;


int isEmpty(Queue *q);
Element *create_Element(void *data);
Queue *create_Queue();
void queue_free(Queue *q);
void *queue_offer(Queue *q, void *data);
void *queue_peek(Queue *q);
void *queue_poll(Queue *q);
int queue_size(Queue *q);
void print_queue(Queue *q);
