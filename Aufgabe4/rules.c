#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "config.h"
#include "rules.h"
#include "field.h"
#include "thread.h"
#include "utils.h"

void lock(thread_args* args, int h){
	printf("lock\n");
	pthread_mutex_t* mutex;
	pthread_cond_t* cond;
	bool* row_beeing_read;	//wenn ture -> Reihe ist gesperrt, wenn False -> Reihe ist nicht gesperrt

	//TODO: call to_lock() (utils.h) from to find out if a row needs to be locked at the height h
	to_lock(args,h, &mutex, &cond, &row_beeing_read);
	printf("mutex: %p\n", mutex);
	printf("cond: %p\n", cond);
	printf("row beeing read: %p\n", row_beeing_read);
	printf("%s\n", row_beeing_read);

	//TODO: check if other thread already locked the row and wait if necessary
	//Reihe nicht sperren wenn Objekte mit NULL initialisiert

//	wenn Reihe gesperrt ist sollen die threads warten
//	spurious wakeup beachten
	if(mutex != NULL && cond != NULL && row_beeing_read){
			while(row_beeing_read){
				printf("in while\n");
				pthread_cond_wait(cond, mutex);
		}
	}

	//TODO: lock the row
	//prüfe ob die reihe gesperrt werden muss oder
	//mutex == NULL und cond == NULL reihe muss nicht gesperrt werden
	//mutex != NULL und cond != NULL reihe muss gesperrt werden
	if(mutex != NULL && cond != NULL && !row_beeing_read){
		pthread_mutex_lock(mutex);
	}

}

void unlock(thread_args* args, int h){
	printf("unlock\n");
	pthread_mutex_t* mutex;
	pthread_cond_t* cond;
	bool* row_beeing_read;

	//TODO: call to_lock() to find out if a row needs to be unlocked at the height h
	to_lock(args,h, &mutex, &cond, &row_beeing_read);

 	//TODO: send signal and unlock the row
	if(mutex != NULL && cond != NULL && row_beeing_read){
		printf("send signal an unlock\n");
		row_beeing_read = false;
		pthread_cond_signal(cond);
		pthread_mutex_unlock(mutex);
	}
}


int* hunt_fish(thread_args* args, int h, int w, int height, int width){
	animal** mtx = args -> field -> mtx;

	//loop through surrounding fields
	for (int i = h-1; i < h+2; i++){
		for (int j = w-1; j < w+2; j++){

			//check if field is valid
			if(i < 0 || j < 0 || i >= height || j >= width){
				continue;
			}

			//check if row is locked by neighbor thread, if not, lock
			lock(args, i);

			// return position if fish is found
			if (mtx[i][j].type == FISH){
				int* victim = (int*) emalloc(2*sizeof(int));
				// int victim[2];
				victim[0] = i;
				victim[1] = j;
				return victim;
			}
			//unlock and send signal to neighbor thread
			unlock(args, i);
		}
	}
	return NULL;
}

void reproduct(animal* cell, int gen, int type){
	if(type == FISH && cell -> age != 0 && cell -> age % FISH_PRODUCTION == 0){
		cell -> type = FISH;
		cell -> age = 0;
		cell -> energy = 0;
		cell -> last_modified = gen;
	} else if(type == SHARK && cell -> age != 0 && cell -> age % SHARK_PRODUCTION == 0){
		cell -> type = SHARK;
		cell -> age = 0;
		cell -> energy = SHARK_ENERGY;
		cell -> last_modified = gen;
	} else {
		cell -> type = WATER;
		cell -> age = 0;
		cell -> energy = 0;
		cell -> last_modified = -1;
	}
}

void calculate_shark_generation(thread_args* args){
	animal** mtx = args -> field -> mtx;
	int width = args -> field -> width;
	int height = args -> field -> height;
	int gen = args -> field -> generation;

	int start, end;
	get_area(args, &start, &end);

	for (int i = start; i <= end; i++){
		for (int j = 0; j < width; j++){

			if(mtx[i][j].type == SHARK && mtx[i][j].last_modified != gen){

				// check if shark is starving
				if(mtx[i][j].energy <= 0){
					mtx[i][j].type = WATER;
					continue;
				}

				mtx[i][j].energy--;
				mtx[i][j].age++;

				// check if fish is nearby, consider that hunt_fish() already locks row if necessary
				int* victim = hunt_fish(args, i, j, height, width);
				if(victim != NULL){

					//move shark
					mtx[i][j].energy = SHARK_ENERGY;
					mtx[i][j].last_modified = gen;
					memcpy(&mtx[victim[0]][victim[1]], &mtx[i][j], sizeof(animal));

					//check if shark can reproduct
					reproduct(&mtx[i][j], gen, SHARK);

					//unlock and send signal to neighbor thread
					unlock(args, victim[0]);

				//perform shark walk
				} else {
					int n_h = i;
					int n_w = j;
					for (int k = 0; k<9; k++){
						get_walk_dir(i,j, &n_h, &n_w);

						//check if row is locked by neighbor thread, if not, lock
						lock(args, n_h);	//SOLUTION

						// check if direction is valid
						if(n_w >= 0 && n_h >= 0 && n_h < height && n_w < width && mtx[n_h][n_w].type == WATER){

							mtx[i][j].last_modified = gen;
							memcpy(&mtx[n_h][n_w], &mtx[i][j], sizeof(animal));
							reproduct(&mtx[i][j], gen, SHARK);

							//unlock and send signal to neighbor thread
							unlock(args, n_h);
							break;
						}
						//unlock and send signal to neighbor thread
						unlock(args, n_h);
					}
				}
			}
		}
	}
}

void calculate_fish_generation(thread_args* t_args){
	animal** mtx = t_args -> field -> mtx;
	int gen = t_args -> field -> generation;
	int width = t_args -> field -> width;
	int height = t_args -> field -> height;

	int start, end;
	get_area(t_args, &start, &end);

	for (int i = start; i <= end; i++){
		for (int j = 0; j < width; j++){

			if(mtx[i][j].type == FISH && mtx[i][j].last_modified != gen){

				mtx[i][j].age++;

				int n_h = i;
				int n_w = j;

				// perform fish walk
				for(int k = 0; k < 9; k++){
					get_walk_dir(i,j, &n_h, &n_w);

					//check if row is locked by neighbor thread, if not, lock
					lock(t_args, n_h);	//SOLUTION

					// check if field is valid
					if(n_w >= 0 && n_w < width && n_h >= 0 && n_h < height && mtx[n_h][n_w].type == WATER){
						mtx[i][j].last_modified = gen;
						memcpy(&mtx[n_h][n_w], &mtx[i][j], sizeof(animal));
						reproduct(&mtx[i][j], gen, FISH);

						//unlock and send signal to neighbor thread
						unlock(t_args, n_h);

						break;
					}
					//unlock and send signal to neighbor thread
					unlock(t_args, n_h);
				}
			}
		}
	}
}
