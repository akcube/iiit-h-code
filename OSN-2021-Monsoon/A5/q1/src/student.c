#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#include "../include/globals.h"
#include "../include/student.h"
#include "../include/course.h"
#include "../include/utils.h"

void create_student(Student *s, int id){
	s->pref[0] = s->pref[1] = s->pref[2] = -1;
	s->CQ = 0.0;
	s->allotted = -1;
	s->time_filled = 0;
	s->final_choice = -1;
	s->id = id;
	pthread_mutex_init(&(s->lock), NULL);
}

void destroy_student(Student *s){
	pthread_mutex_destroy(&(s->lock));
	memset(s, 0, sizeof(Student));
	free(s);
}

void read_students(Student **S, int num_students){
	
	Student *T = *S = calloc(num_students, sizeof(Student));

	for(int i=0; i < num_students; i++){
		Student *s = &T[i];
		create_student(s, i);
		scanf("%lf %d %d %d %d", &(s->CQ), &(s->pref[0]), &(s->pref[1]), &(s->pref[2]), &(s->time_filled));
	}
}

int student_time_cmp(const void *a, const void *b){
	Student *A = (Student*) a;
	Student *B = (Student*) b;
	return A->time_filled > B->time_filled;
}

bool mathamagic(double prob){
	if(prob > 0.5) return true;
	else return false;
}

void *sim_student(void *arg){

	pair *parg = (pair*) arg;
	Student *s = (Student*) parg->first;
	Course *courses = (Course*) parg->second;
	
	int cur_pref = 0;
	while(cur_pref < 3){
		Course *mypref = getCourseByID(s->pref[cur_pref], courses);

		// Course thread releases lock only when waiting for students, sanity check in if
		pthread_mutex_lock(&(mypref->lock));

		if(mypref->state == REMOVED){
			pthread_mutex_unlock(&(mypref->lock));
			// Change preferences
			Course *old = mypref;
			cur_pref++;
			if(cur_pref < 3){
				mypref = getCourseByID(s->pref[cur_pref], courses);
				// TODO print together
				printf("Student %d has changed current preference from ", s->id);
				printf("%s (priority %d) to %s (priority %d)\n", old->name, cur_pref, mypref->name, cur_pref+1);
			}
			continue;
		}

		if(mypref->state == WAITING_FOR_STUDENTS && mypref->occupied_slots < mypref->allotted_slots){

			// We have a slot, assign student the slot and attend tutorial
			mypref->occupied_slots++;
			pthread_cond_wait(&(mypref->finished), &(mypref->lock));
			pthread_mutex_unlock(&(mypref->lock));
			printf("Student %d has been allocated a seat in course %s\n", s->id, mypref->name);

			// Tut is over
			double prob = mypref->interest * s->CQ;
			if(mathamagic(prob)){
				// Student locks preference
				printf("Student %d has selected course %s permanently\n", s->id, mypref->name);
				free(arg);
				pthread_exit(NULL);
			}
			else{
				// Student has withdrawn
				printf("Student %d has withdrawn from the course %s\n", s->id, mypref->name);

				// Change preferences
				Course *old = mypref;
				cur_pref++;
				if(cur_pref < 3){
					mypref = getCourseByID(s->pref[cur_pref], courses);
					// TODO print together
					printf("Student %d has changed current preference from ", s->id);
					printf("%s (priority %d) to %s (priority %d)\n", old->name, cur_pref, mypref->name, cur_pref+1);
				}
			}
		}
		else{
			pthread_mutex_unlock(&(mypref->lock));
		}
	}

	printf("Student %d couldn't get any of his preferred courses\n", s->id);
	free(arg);
	pthread_exit(NULL);
}

void *spawn_students(void *arg){

	int cur = 0;
	pair *parg = (pair*) arg;
	Student *Students = (Student*) parg->first;

	for(int time = 0; ; time++, sleep(1)){

		if(cur == num_students) pthread_exit(NULL);

		while(Students[cur].time_filled == time){
			printf("Student %d has filled in preferences for course registration\n", Students[cur].id);
			
			// Spawn thread here
			pthread_t *sim_student_t = malloc(sizeof(pthread_t));

			// Create argument which is Student + Courses base ptr
			pair *argptr = malloc(sizeof(pair));
			argptr->first = (void*) &Students[cur];
			argptr->second = (void*) parg->second;
			pthread_create(sim_student_t, NULL, sim_student, argptr);
			cur++;
		}
	}
}