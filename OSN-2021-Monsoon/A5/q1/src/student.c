#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/student.h"

void create_student(Student *s){
	s->pref[0] = s->pref[1] = s->pref[2] = -1;
	s->CQ = 0.0;
	s->allotted = -1;
	s->time_filled = 0;
	s->final_choice = -1;
}

void destroy_student(Student *s){
	memset(s, 0, sizeof(Student));
	free(s);
}

void read_students(Student *S, int num_students){
	S = calloc(num_students, sizeof(Student));

	for(int i=0; i < num_students; i++){
		Student *s = &S[i];
		create_student(s);
		scanf("%lf %d %d %d %d", &(s->CQ), &(s->pref[0]), &(s->pref[1]), &(s->pref[2]), &(s->time_filled));
	}
}