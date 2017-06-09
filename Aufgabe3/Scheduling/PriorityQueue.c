#include "PriorityQueue.h"

PrioQueue *createQueue(){
  PrioQueue *q = NULL;
  q = malloc(sizeof(PrioQueue));

  q -> size = 0;
  q -> root = NULL;
}


q_elem* q_elem_new(Task *task, uint16_t arrival, uint16_t total){
	struct q_elem_s *new_Elem = NULL;
	new_Elem = malloc(sizeof(q_elem));
	new_Elem -> task = task;
	new_Elem -> arrival = arrival;
	new_Elem -> total = total;
	return new_Elem;
}


int pqueue_offer(PrioQueue *queue, q_elem* newElem){
	if(queue == NULL){
		printf("Einfügen Fehlgeschlagen!\nEs Exestiert keine Queue!\n");
		return -1;
	}

	if(newElem == NULL){
		printf("Einfügen Fehlgeschlagen!\nEs existiert kein Element!\n");
		return -1;
	}

	if(queue -> size == 0){
		queue -> root = newElem;
	 	queue -> root -> next = NULL;
		queue -> size = queue -> size + 1;
  }else{
    if(queue -> root -> total >= newElem -> total){
		  q_elem *temp = queue -> root;
			queue -> root = newElem;
			queue -> root -> next = temp;
			queue -> size ++;
    }else{
			q_elem *current = queue -> root;
			q_elem *temp = NULL;
			while(current -> next != NULL && current -> next -> total <= newElem -> total ){
					current = current -> next;
			}
			temp = current -> next;
			current -> next = newElem;
			newElem -> next = temp;
			queue -> size ++;
		}
	}

	return 1;
}

Task* pqueue_peek(PrioQueue *queue){
	if(queue == NULL){
		printf("Keine Queue vorhanden\n");
		return NULL;
	}

	if(queue -> size == 0){
		return NULL;
	}
	q_elem *highest = queue -> root;
	return highest -> task;
}

Task* pqueue_poll(PrioQueue *queue){
	if(queue == NULL){
		printf("Keine Queue vorhanden\n");
		return NULL;
	}

	if(queue -> size == 0){
		return NULL;
	}

	q_elem *highest = queue -> root;
  queue -> root = queue -> root -> next;
	Task *t = highest -> task;
	queue -> size --;
	free(highest);
  return t;
}

void pqueue_free(PrioQueue *queue){
  if(queue == NULL){
    printf("keine Queue\n");
  }

  q_elem *temp = NULL;
  while(queue -> root != NULL){
    temp = queue -> root;
    queue -> root = queue -> root -> next;
    free(temp);
  }
  free(queue);
}



void pqueue_print(PrioQueue *queue){
	if(queue == NULL){
		printf("Keine Queue vorhanden\n");
		exit(1);
	}

	q_elem *temp = queue -> root;
	while(temp != NULL){
		//printf("While");
	printTask(temp -> task);
  printf("\n");

		temp = temp -> next;
	}
  	printf("root:");
    printTask(queue -> root -> task);
    printf("\n");
}
