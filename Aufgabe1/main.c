#include "PrioQueue.h"
#include <stdio.h>

int main()
{

	PrioQueue *queue = pqueue_new();

	pqueue_offer(queue, q_elem_new(3, "1"));
	pqueue_offer(queue, q_elem_new(5, "2"));
	pqueue_peek(queue);
	pqueue_offer(queue,q_elem_new(2, "3"));
	pqueue_offer(queue, q_elem_new(4, "4"));
	pqueue_peek(queue);
	pqueue_offer(queue, q_elem_new(2, "3"));
	pqueue_offer(queue, q_elem_new(4, "4"));
	pqueue_offer(queue, q_elem_new(2, "3"));
	pqueue_peek(queue);
	pqueue_offer(queue, q_elem_new(4, "4"));
	pqueue_offer(queue, q_elem_new(56, "Berta"));

	pqueue_offer(queue, q_elem_new(63, "Anton"));
	pqueue_offer(queue, q_elem_new(163, "Ida"));
	pqueue_offer(queue, q_elem_new(1, "Emil"));

	pqueue_offer(queue, q_elem_new(11, "Nordpol"));
	pqueue_offer(queue, q_elem_new(98, "Quelle"));

	pqueue_offer(queue, q_elem_new(127, "Ludwig"));
	pqueue_offer(queue, q_elem_new(25, "Marta"));

	pqueue_offer(queue, q_elem_new(111, "Zepeline"));
	pqueue_offer(queue, q_elem_new(112, "laura"));

	pqueue_offer(queue, q_elem_new(100, "Lala"));

	pqueue_print(queue);
	// should print: (5,2)(4,4)(4,4)(4,4)(3,1)(2,3)(2,3)(2,3)
	printf("%d\n",pqueue_size(queue));
	pqueue_poll(queue);
	pqueue_print(queue);
	printf("%d\n",pqueue_size(queue));

	pqueue_free(queue);
	// use: valgrind ./PrioQueue
	// to check if your free function works correctly

	return 0;
}
