#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/course.h"

void create_course(Course *c){
	c->name = NULL;
	c->interest = 0.0;
	c->allotted_ta = -1;
	c->taship_left = -1;
	c->max_slots = 0;
	c->labs_size = 0;
	c->labs = NULL;
}

void delete_course(Course *c){
	memset(c, 0, sizeof(Course));
	free(c);
}

void read_courses(Course *C, int num_courses){
	C = calloc(num_courses, sizeof(Course));
	char buf[1024];

	for(int i=0; i<num_courses; i++){
		Course *c= &C[i];
		
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