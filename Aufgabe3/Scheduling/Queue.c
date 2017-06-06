#include "Queue.h"


int isEmpty(Queue *q){
  if(q -> root == NULL) return 0;
  else return 1;
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
  q -> root = NULL;
  q -> zeitscheibe = 0;
  return q;
}

void queue_free(Queue *q){
  if(isEmpty(q) == 1){
    Element *temp = q -> root;
    while(temp != NULL){
      Element *cur = temp;
      temp = temp -> next;
      free(cur -> data);
      free(cur);
    }
  }
  free(q);
}

void *queue_offer(Queue *q, void *data){
  Element *new_Elem = create_Element(data);
  q -> size ++;
  if(isEmpty(q) == 0){
    q -> root = new_Elem;
  }else{
    Element *temp = q -> root;
    while (temp -> next != NULL){
      temp = temp -> next;
    }
    temp -> next = new_Elem;
  }
  return q;
}

void *queue_peek(Queue *q){
  if(isEmpty(q) == 1) return q -> root -> data;

  return NULL;
}

void *queue_poll(Queue *q){
  if(isEmpty(q) == 1){
    Element *temp = q -> root;
    q -> root = temp -> next;
    void *data = temp -> data;
    free(temp);
    q -> size --;
    return data;
  }
  return NULL;
}

int queue_size(Queue *q){
  return q -> size;
}

void print_queue(Queue *q){
	if (isEmpty(q) == 1){
		printf("Queue :\n");
		Element *tmp = q->root;

    while (tmp != NULL){
      printf("%s\n",tmp -> data);
      tmp = tmp->next;
    }
	}else{
		printf("Queue is empty!\n\n");
	}
}
