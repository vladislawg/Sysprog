#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "field.h"
#include "thread.h"

//secure memory allocation
void* emalloc(size_t size) {
	void *buf = malloc(size);
	if(buf == NULL){
		perror("memory allocation failed");
		exit(1);
	}
	return buf;
}

//get random walk direction from h and w
void get_walk_dir(int h, int w, int* n_h, int* n_w){
	int dir = random()%8;

	if(dir < 3){
		*n_h = h-1;
	} else if(dir < 5){
		*n_h = h;
	} else {
		*n_h = h+1;
	}

	if(dir == 0 || dir == 3 || dir == 5){
		*n_w = w-1;
	} else if(dir == 1 || dir == 6){
		*n_w = w;
	} else {
		*n_w = w+1;
	}	
}

// get this thread's area of responsibility
void get_area(thread_args* args, int* start, int* end){
	int id = args -> id;
	field* field = args -> field;

	int area_size = field -> height / field -> num_threads;
	
	*start = id * area_size;
	if(id == field -> num_threads-1){
		*end = field -> height - 1;
	} else {
		*end = *start + area_size - 1;
	}
}

// gets mutex and signal object needed to lock the row h
// mutex, cond and beeing_read are set NULL if row doesn't need to be locked at height h
void to_lock(thread_args* t_args, int h, pthread_mutex_t** mutex, pthread_cond_t** cond, bool** beeing_read){
	int end, start;
	get_area(t_args, &start, &end);

	int id = t_args -> id;
	int height = t_args -> field -> height;

	if(h == start){
		*mutex = &t_args -> field -> upper_row_mutex[id];
		*cond = &t_args -> field -> upper_row_cond[id];
		*beeing_read = &t_args -> field -> upper_row_beeing_read[id];
	} else if(h == end){
		*mutex = &t_args -> field -> lower_row_mutex[id];
		*cond = &t_args -> field -> lower_row_cond[id];
		*beeing_read = &t_args -> field -> lower_row_beeing_read[id];
	} else if(h > 0 && h == start-1){
		*mutex = &t_args -> field -> lower_row_mutex[id-1];
		*cond = &t_args -> field -> lower_row_cond[id-1];
		*beeing_read = &t_args -> field -> lower_row_beeing_read[id-1];
	} else if(h < height-1 && h == end+1){
		*mutex = &t_args -> field -> upper_row_mutex[id+1];
		*cond = &t_args -> field -> upper_row_cond[id+1];
		*beeing_read = &t_args -> field -> upper_row_beeing_read[id+1];
	} else {
		*mutex = NULL;
		*cond = NULL;
		*beeing_read = NULL;
	}
}