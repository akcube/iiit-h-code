#ifndef __COURSESIM_LAB
#define __COURSESIM_LAB

#include <semaphore.h>

typedef struct Lab{
	char *name;
	int num_students;
	int num_left;
	int limit;
	int *ta;
	pthread_mutex_t *ta_lock;
	sem_t ta_free;
} Lab;

void create_lab(Lab *l);
void destroy_lab(Lab *l);
void read_labs(Lab **L, int num_labs);
void *sim_lab(void *arg);

#endif