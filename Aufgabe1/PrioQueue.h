/*
 * PrioQueue.h
 *
 * A simple, singly linked list based priority queue.
 *
 * The values are ordered descending by their
 * priority (highest priority = head of the queue).
 *
 * Author: CIT
 */
// Only typedef here to limit access to the members to the source file.
typedef struct PrioQueue PrioQueue;
typedef struct q_elem_s q_elem;
/**
 * Creates an empty priority queue.
 *
 * returns: an empty priority queue.
 */
PrioQueue* pqueue_new();
/**
 * Creates a new queue element.
 * priority: the elements priority
 * name: the elements name
 *
 * returns the new element
 */
q_elem* q_elem_new(int priority, char* name);

/**
 * Deletes the queue and frees all allocated memory.
 */
void pqueue_free(PrioQueue *queue);

/*
 * Insert the element with its defined priority into the queue.
 *
 * newElem: new element to be inserted
 *
 * returns : the ńame of the element or NULL when an error occurred.
 */
char* pqueue_offer(PrioQueue *queue, q_elem* newElem);

/**
 * Retrieves the element with the highest priority from the queue.
 *
 * returns: the name or NULL if queue is empty..
 */
char* pqueue_peek(PrioQueue *queue);

/**
 * Retrieves and REMOVES the element with the highest priority from the queue.
 *
 * returns: the name or NULL if queue is empty.
 */
char* pqueue_poll(PrioQueue *queue);

/**
 * The current size of the queue.
 *
 * returns: the current size of the queue.
 */
int pqueue_size(PrioQueue *queue);

/**
 * Prints the current elements in the queue to stdout.
 *
 * The elements get printed in the following form:
 * 
 * (<prio>,<name>)(<prio>,<name>) ...
 *
 * with the head of the queue as first element.
 */
void pqueue_print(PrioQueue *queue);

