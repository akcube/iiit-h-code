#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "../include/lab.h"

void create_lab(Lab *l){
	l->name = NULL;
	l->num_students = 0;
	l->limit = 0;
	l->ta = NULL;
	l->ta_lock = NULL;
	sem_init(&(l->ta_free), 0, 0);
}

void destroy_lab(Lab *l){
	sem_destroy(&(l->ta_free));
	memset(l, 0, sizeof(Lab));
	free(l);
}

void *sim_lab(void *arg){
	Lab *lab = (Lab*) arg;
	int ct = 0;
	while(sem_wait(&(lab->ta_free))){
		ct++;
		if(ct == lab->num_students){
			printf("Lab %s no longer has students available for TA ship\n", lab->name);
			pthread_exit(NULL);
		}
	}
}

void read_labs(Lab **L, int num_labs){
	
	Lab *T = *L = calloc(num_labs, sizeof(Lab));
	char buf[1024];

	for(int i=0; i < num_labs; i++){
		Lab *l = &T[i];
		create_lab(l);
		scanf("%s %d %d", buf, &(l->num_students), &(l->limit));

		l->name = strdup(buf);
		l->ta = malloc(l->num_students, sizeof(int));
		l->ta_lock = malloc(l->num_students, sizeof(pthread_mutex_t));

		for(int j=0; j < l->num_students; j++){
			l->ta[j] = l->limit;
			pthread_mutex_init(&(l->ta_lock[j]), NULL);
		}
	}
}
