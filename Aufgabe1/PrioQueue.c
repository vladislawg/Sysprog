#include "PrioQueue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct q_elem_s
{
	char* name;
	int priority;
	struct q_elem_s *next;
};

struct PrioQueue
{
	int size;
	q_elem *root;
};

PrioQueue* pqueue_new(){

	struct PrioQueue *pq = NULL;
	pq = (struct PrioQueue *)malloc(sizeof(struct PrioQueue));
	pq -> size = 0;
	pq -> root = NULL;

	if(pq != NULL){
		printf("Allokation erforlgreich ...\n");
	}else{
		printf("Allokation Fehlgeschlagen !\n");
		exit(1);
	}

	return pq;
}

q_elem* q_elem_new(int priority, char* name){
	struct q_elem_s *new_Elem = NULL;
	new_Elem = (struct q_elem_s *)malloc(sizeof(struct q_elem_s));
	new_Elem -> name = malloc(strlen(name)*sizeof(char*));
	strcpy(new_Elem -> name, name);
	new_Elem -> priority = priority;

	if(new_Elem != NULL){
		printf("Neues Element erstellt ...\n");
	}else{
		printf("Neues Element konnte nicht erstellt werden!\n");
		return NULL;
	}

	return new_Elem;
}


void pqueue_free(PrioQueue *queue){
	if(queue == NULL){
		printf("keine Queue\n");
	}

	q_elem *temp = NULL;
	while(queue -> root != NULL){
		temp = queue -> root;
		queue -> root = queue -> root -> next;
    free(temp -> name);
		free(temp);

	}

	free(queue);
}

char* pqueue_offer(PrioQueue *queue, q_elem* newElem){
	if(queue == NULL){
		printf("Einfügen Fehlgeschlagen!\nEs Exestiert keine Queue!\n");
		return NULL;
	}

	if(newElem == NULL){
		printf("Einfügen Fehlgeschlagen!\nEs existiert kein Element!\n");
		return NULL;
	}

	if(queue -> size == 0){
		queue -> root = newElem;
	 	queue -> root -> next = NULL;
		queue -> size = queue -> size + 1;
	}else{
		if(queue -> root -> priority <= newElem -> priority){
			q_elem *temp = queue -> root;
			queue -> root = newElem;
			queue -> root -> next = temp;
			queue -> size ++;
		}else{
			q_elem *current = queue -> root;
			q_elem *temp = NULL;
			while(current -> next != NULL && current -> next -> priority >= newElem -> priority ){
					current = current -> next;
			}
			temp = current -> next;
			current -> next = newElem;
			newElem -> next = temp;
			queue -> size ++;
		}
	}

	return newElem -> name;

}

char* pqueue_peek(PrioQueue *queue){
	if(queue == NULL){
		printf("Keine Queue vorhanden\n");
		return NULL;
	}

	if(queue -> size == 0){
		return NULL;
	}

	q_elem *temp = queue -> root;
	q_elem *highest = queue -> root;
	while(temp != NULL){
		if(highest -> priority > temp -> priority){
			highest = highest;
		}else{
			highest = temp;
		}
		temp = temp -> next;
	}
	return highest -> name;
}

char* pqueue_poll(PrioQueue *queue){
	if(queue == NULL){
		printf("Keine Queue vorhanden\n");
		return NULL;
	}

	if(queue -> size == 0){
		return NULL;
	}

	q_elem *highest = queue -> root;
	queue -> root = queue -> root -> next;
	char *name = highest -> name;
	queue -> size --;
	free(highest -> name);
	free(highest);
	return name;
}

int pqueue_size(PrioQueue *queue){
	return queue -> size;
}

void pqueue_print(PrioQueue *queue){
	if(queue == NULL){
		printf("Keine Queue vorhanden\n");
		exit(1);
	}

	q_elem *temp = queue -> root;
	while(temp != NULL){
		//printf("While");
		printf("(%d,%s) ",temp -> priority, temp -> name);

		temp = temp -> next;
	}

	printf("\n");
	printf("root: %s\n", queue -> root -> name);
}
