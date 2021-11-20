#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "../include/lab.h"
#include "../include/course.h"
#include "../include/student.h"
#include "../include/utils.h"

int num_students = 0; 
int num_labs = 0;
int num_courses = 0;
Course *Courses;
Student *Students;
Lab *Labs;

pthread_t spawn_students_t;

int main(void){
	
	scanf("%d %d %d", &num_students, &num_labs, &num_courses);

	read_courses(&Courses);
	read_students(&Students, num_students);
	read_labs(&Labs, num_labs);
	qsort(Students, num_students, sizeof(Student), student_time_cmp);

	pthread_t lab_thread_t[num_labs];
	for(int i=0; i<num_labs; i++)
		pthread_create(&lab_thread_t[i], NULL, sim_lab, &Labs[i]);

	pair *spawn_students_arg = malloc(sizeof(pair));
	spawn_students_arg->first = (void*) Students;
	spawn_students_arg->second = (void*) Courses;
	pthread_create(&spawn_students_t, NULL, spawn_students, spawn_students_arg);

	pthread_t course_thread_t[num_courses];
	pair course_args[num_courses];
	for(int i=0; i<num_courses; i++){
		course_args[i].first = &Courses[i];
		course_args[i].second = Labs;
		pthread_create(&course_thread_t[i], NULL, sim_course, &course_args[i]);
	}

	pthread_join(spawn_students_t, NULL);
}