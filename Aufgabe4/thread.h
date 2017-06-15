#ifndef WATOR_THREAD_H
#define WATOR_THREAD_H

#include "field.h"

typedef struct thread_args{
    int id;
    field* field;
}thread_args;

// function as parameter for new thread created
void* thread(void* t_args);

#endif // WATOR_THREAD_H