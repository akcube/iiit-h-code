#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>

#include "../include/course.h"
#include "../include/lab.h"
#include "../include/globals.h"
#include "../include/utils.h"

void create_course(Course *c){
	c->name = NULL;
	c->state = LOOKING_FOR_TA;
	c->interest = 0.0;
	c->max_slots = 0;
	c->occupied_slots = 0;
	c->allotted_slots = -1;
	c->labs_size = 0;
	c->labs = NULL;
	pthread_mutex_init(&(c->lock), NULL);
	pthread_mutex_init(&(c->cond_lock), NULL);
	pthread_cond_init(&(c->finished), NULL);

	pthread_mutex_lock(&(c->lock));
}

void delete_course(Course *c){
	pthread_mutex_destroy(&(c->lock));
	pthread_cond_destroy(&(c->finished));
	pthread_mutex_destroy(&(c->cond_lock));
	memset(c, 0, sizeof(Course));
	free(c);
}

Course *getCourseByID(int id, Course *C){
	if(id >= 0 && id < num_courses)
		return &C[id];
	return NULL;
}

void *sim_course(void *arg){
	pair *parg = (pair*) arg;
	Course *c = parg->first;
	Lab *Labs = parg->second;
	
	pthread_mutex_t *current_ta_lock;
	int holding_ta = -1;
	char *holding_lab = NULL;

	while(c->state != REMOVED){

		if(c->state == LOOKING_FOR_TA){

			// Search for free TA
			bool NO_FREE_TA = true;
			for(int i=0; i < c->labs_size; i++){
				int l_id = c->labs[i];
				Lab *lab = &Labs[l_id];

				for(int j=0; j < lab->num_students; j++){
					// TA in use by some other course, come back later
					if(pthread_mutex_trylock(&(lab->ta_lock[j])) != 0){
						NO_FREE_TA = false;
					}
					else{
						if(lab->ta[j] <= 0){
							pthread_mutex_unlock(&(lab->ta_lock[j]));
						}
						else{
							// Found TA
							NO_FREE_TA = false;
							lab->ta[j]--;
							current_ta_lock = &(lab->ta_lock[j]);
							holding_ta = j;
							holding_lab = lab->name;
							cprintf(RED, "TA %d from lab %s has been allocated to course %s for their %d(nt/rd/st) TA ship\n", \
									j, lab->name, c->name, lab->limit - lab->ta[j]);

							if(lab->ta[j] == 0){
								sem_post(&(lab->ta_free));
							}

							c->occupied_slots = 0;
							c->allotted_slots = rand()%(c->max_slots) + 1;

							cprintf(GREEN, "Course %s has been allocated %d seats\n", c->name, c->allotted_slots);
							goto ta_found;
						}
					}
				}
			}

			ta_found:
			if(NO_FREE_TA){
				c->state = REMOVED;
				break;
			}
			if(holding_ta != -1)
				c->state = WAITING_FOR_STUDENTS;
		}
		else if(c->state == WAITING_FOR_STUDENTS){
			pthread_mutex_unlock(&(c->lock));
			// TODO are we allowed to sleep here?
			sleep(1);

			// Conduct tutorial
			pthread_mutex_lock(&(c->lock));
			cprintf(YELLOW, "Tutorial has started for Course %s with %d seats filled out of %d\n", \
					c->name, c->occupied_slots, c->allotted_slots);
			c->state = TUT_IN_PROGRESS;
			sleep(2);
			pthread_mutex_unlock(current_ta_lock);
			current_ta_lock = NULL;
			cprintf(BLUE, "TA %d from lab %s has completed the tutorial and left the course %s\n", \
					holding_ta, holding_lab, c->name);
			holding_ta = -1;
			holding_lab = NULL;
			c->state = LOOKING_FOR_TA;
			pthread_mutex_lock(&(c->cond_lock));
			pthread_cond_broadcast(&(c->finished));
			pthread_mutex_unlock(&(c->cond_lock));
		}
	}
	pthread_mutex_unlock(&(c->lock));
	pthread_exit(NULL);
}

void read_courses(Course **C){
	Course *T = *C = calloc(num_courses, sizeof(Course));
	char buf[1024];

	for(int i=0; i<num_courses; i++){
		Course *c= &T[i];
		
		create_course(c);
		scanf("%s %lf %d %d", buf, &(c->interest), &(c->max_slots), &(c->labs_size));
		c->name = strdup(buf);

		c->labs = malloc(sizeof(int) * c->labs_size);
		for(int j=0; j < c->labs_size; j++){
			int t; scanf("%d", &t);
			c->labs[j] = t;
		}
	}
}