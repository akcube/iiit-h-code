#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "../include/globals.h"
#include "../include/student.h"

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

void *sim_student(void *arg){
	Student *s = (Student*) arg;
	Course *courses = (Course*) ++s;
	
	int cur_pref = 0;
	while(cur_pref < 3){
		Course *mypref = getCourseByName(s->pref[cur_pref], courses);
		
	}
}

void *spawn_students(void *arg){

	int cur = 0;
	Student *Students = (Student*) arg;

	for(int time = 0; ; time++, sleep(1)){

		if(cur == num_students) pthread_exit(NULL);

		while(Students[cur].time_filled == time){
			// Spawn thread here
			printf("Student %d has filled in preferences for course registration\n", Students[cur].id);
			cur++;
		}
	}
}