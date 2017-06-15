#include <stdbool.h>
#include "thread.h"

//secure memory allocation
void* emalloc(size_t size);

//get random walk direction from h and w
void get_walk_dir(int h, int w, int* n_h, int* n_w);

// get this thread's area of responsibility
void get_area(thread_args* t_args, int* start, int* end);

// gets mutex and signal object needed to lock the row h
// mutex, cond and beeing_read are set NULL if row doesn't need to be locked at height h
void to_lock(thread_args* args, int h, pthread_mutex_t** mutex, pthread_cond_t** cond, bool** beeing_read);