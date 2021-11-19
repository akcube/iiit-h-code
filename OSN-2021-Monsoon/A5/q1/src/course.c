#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "../include/course.h"

void create_course(Course *c){
	c->name = NULL;
	c->interest = 0.0;
	c->allotted_ta = -1;
	c->taship_left = -1;
	c->max_slots = 0;
	c->labs_size = 0;
	c->labs = NULL;
	pthread_mutex_init(&(c->lock), NULL);
}

void delete_course(Course *c){
	pthread_mutex_destroy(&(c->lock));
	memset(c, 0, sizeof(Course));
	free(c);
}

Course *getCourseByID(int id, Course *C){
	
	if(id >= 0 && id < num_courses)
		return &C[id];
	else
		return NULL;
}

void read_courses(Course **C, int num_courses){
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