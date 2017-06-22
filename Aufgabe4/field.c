#include <stdio.h>
#include <stdbool.h>

#include "field.h"
#include "rules.h"
#include "config.h"
#include "utils.h"

// reads population from file specified in config.h
// parameters passed: address of int height and width from field struct
// to allow adjustment to population_set file

// return value: struct animal matrix
// this function allocates all memory needed for the return value
animal** population_from_file(int* height, int* width){


	FILE* fp = fopen(POPULATION_SET_FILE, "r");

	if(fp == NULL){
		perror("opening file failed");
		exit(1);
	}

	char h_str[10];
	char w_str[10];
	int i = 0;
	char c = fgetc(fp);

	// extract height
	while(c != ' '){
		h_str[i] = c;
		i++;
		c = fgetc(fp);
	}
	h_str[i] = '\0';
	i = 0;
	c = fgetc(fp);
	*(height) = atoi(h_str);

	// extract width
	while(c != '\n'){
		w_str[i] = c;
		i++;
		c = fgetc(fp);
	}
	w_str[i] = '\0';

	*(width) = atoi(w_str);

	//declare field
	animal** mtx = (animal**) emalloc(*(height) * sizeof(animal*));
	for (int i = 0;i < *(height);i++){
		mtx[i] = (animal*) emalloc(*(width) * sizeof(animal));
	}

	// fill field
	for(int i = 0; i < *(height); i++){
		for(int j = 0; j < *(width); j++){

			int c = fgetc(fp);

			if(feof(fp)){
				perror("incorrect field size");
				exit(1);
			}
			mtx[i][j].type = c - '0';
			mtx[i][j].age = 0;
			mtx[i][j].energy = 0;
			mtx[i][j].last_modified = -1;
			if(mtx[i][j].type == SHARK){
				mtx[i][j].energy = SHARK_ENERGY;
			}
		}
		fgetc(fp);
	}
	return mtx;
}

field* make_field(int num_threads){
	field* g_field;

	//TODO: initialize field and it's members listed in field.h
	g_field = (field*) malloc(sizeof(field));
	int height = 0;
	int width = 0;

	g_field -> mtx = population_from_file(&height, &width);

	//erstellen der instanz für das Feld
	g_field -> height = height;
	g_field -> width = width;
	g_field -> num_threads = NUM_THREADS;
	g_field -> generation = 0;
	g_field -> num_calc_ready = 0;
	g_field -> printed = true;

	//TODO: initialize mutex and other variables for synchronization of threads
	pthread_mutex_init(&g_field -> generation_mutex, NULL);
	pthread_cond_init(&g_field -> generation_cond, NULL);
	pthread_mutex_init(&g_field -> num_calc_ready_mutex, NULL);
	pthread_cond_init(&g_field -> num_calc_ready_cond, NULL);

	pthread_mutex_init(&g_field -> field_printed_mutex, NULL);
	pthread_cond_init(&g_field -> field_printed_cond, NULL);


	// initialize mutex and signal/wait object arrays
	g_field -> upper_row_mutex = (pthread_mutex_t*) emalloc(num_threads * sizeof(pthread_mutex_t));
	g_field -> upper_row_cond = (pthread_cond_t*) emalloc(num_threads * sizeof(pthread_cond_t));
	g_field -> upper_row_beeing_read = (bool*) emalloc(num_threads * sizeof(bool));

	g_field -> lower_row_mutex = (pthread_mutex_t*) emalloc(num_threads * sizeof(pthread_mutex_t));
	g_field -> lower_row_cond = (pthread_cond_t*) emalloc(num_threads * sizeof(pthread_cond_t));
	g_field -> lower_row_beeing_read = (bool*) emalloc(num_threads * sizeof(bool));

	// initialize mutex and signal/wait objects
	for (int i = 0; i < NUM_THREADS; i++){
		pthread_mutex_init(&g_field->upper_row_mutex[i], NULL);
		pthread_cond_init(&g_field->upper_row_cond[i], NULL);
		g_field -> upper_row_beeing_read[i] = false;

		pthread_mutex_init(&g_field->lower_row_mutex[i], NULL);
		pthread_cond_init(&g_field->lower_row_cond[i], NULL);
		g_field -> lower_row_beeing_read[i] = false;
	}

	return g_field;
}
