#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "SDL.h"

#include "config.h"
#include "field.h"
#include "rules.h"
#include "thread.h"
#include "utils.h"

int thread_counter = 0;

void* thread(void* t_args){
	thread_args* args = (thread_args*) t_args;
	field* field = args -> field;
	printf("id %d\n", args -> id);

	// find out area of responsipility
	int start, end;
	get_area(args, &start, &end);

	while(1){

		// make sure that field has already been printed before modifying it
		pthread_mutex_lock(&field -> field_printed_mutex);
			while(!field -> printed){
				pthread_cond_wait(&field -> field_printed_cond, &field-> field_printed_mutex);
			}
		pthread_mutex_unlock(&field -> field_printed_mutex);


		// update field
		calculate_shark_generation(args);
		calculate_fish_generation(args);


		//TODO: make sure all threads finished updating their areas before proceeding
		pthread_mutex_lock(&field -> num_calc_ready_mutex);
		field -> num_calc_ready ++;																					//Counter für Threads die fertig sind mit der Berechnung
	//	field -> num_calc_ready %= field -> num_threads;
		if (field -> num_calc_ready == field -> num_threads) {							//Nur der Letzte thread ist zuständig für die Erhöhung der generation und das fertigstellen des Printen
				printf("Thread with id: %d", args -> id);
			// last thread goes here
			field -> printed = false;
			//TODO: increase generation number of field struct
			field -> generation ++;
			field -> num_calc_ready = 0;
			pthread_cond_signal(&field -> num_calc_ready_cond);
			pthread_cond_signal(&field -> field_printed_cond);
		}
		printf("num %d\n", field -> num_calc_ready);
		while(field -> num_calc_ready % field -> num_threads != 0){				//Alle threads warten bis die Berechnung fertiggestellt ist
			printf("While\n");
			printf("%d\n", field -> num_calc_ready);
			pthread_cond_wait(&field -> num_calc_ready_cond, &field -> num_calc_ready_mutex);
		}
		pthread_cond_signal(&field -> num_calc_ready_cond);								//Signal für das fertigstellen der Berechnung
		pthread_mutex_unlock(&field -> num_calc_ready_mutex);							

		printf("ready %d\n", args -> id);

	}


	return 0;
}
