#include "Queue.h"


int isEmpty(Queue *q){
  return q -> size == 0;
}

Element *create_Element(void *data){
  Element *elem = malloc(sizeof(Element));
  elem -> data = data;
  elem -> next = NULL;
  return elem;
}

Queue *create_Queue(){
  Queue *q = malloc(sizeof(Queue));
  q -> size = 0;
  q -> head = NULL;
  q -> tail = NULL;
  return q;
}

void queue_free(Queue *q){
  Element *cur = q -> tail;
  while(cur != NULL){
    Element *temp = cur -> next;
    free(cur);
    cur = temp;
  }
  free(q);
}

void *queue_offer(Queue *q, void *data){
  Element *new_Elem = create_Element(data);

  if(isEmpty(q)){
    q -> tail = new_Elem;
    q -> head = new_Elem;
  }else{
    q -> head -> next = new_Elem;
    q -> head = new_Elem;
  }
  q -> size ++;
  return q;
}

void *queue_peek(Queue *q){
  if(isEmpty(q)) return NULL;
  return q -> tail -> data;
}

void *queue_poll(Queue *q){
  if(isEmpty(q)) return NULL;

  Element *temp = q -> tail;
  q -> tail = temp -> next;
  void *data = temp -> data;
  free(temp);
  q -> size --;

  if(isEmpty(q)){
    q -> head = NULL;
    q -> tail = NULL;
  }

  return data;
}

int queue_size(Queue *q){
  return q -> size;
}

void print_queue(Queue *q){
	if (isEmpty(q)){
    printf("Queue is empty!\n\n");
  }else{
    printf("Queue :\n");
  	Element *tmp = q -> tail;

    while (tmp != NULL){
      printf("%p\n",tmp -> data);
      tmp = tmp -> next;
    }
  }
}
