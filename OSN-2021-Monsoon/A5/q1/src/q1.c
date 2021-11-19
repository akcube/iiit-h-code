#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "../include/lab.h"
#include "../include/course.h"
#include "../include/student.h"

int num_students, num_labs, num_courses;
Course *Courses;
Student *Students;
Lab *Labs;

pthread_t spawn_students_t;

int main(void){
	
	scanf("%d %d %d", &num_students, &num_labs, &num_courses);

	read_courses(&Courses, num_courses);
	read_students(&Students, num_students);
	read_labs(&Labs, num_labs);

	qsort(Students, num_students, sizeof(Student), student_time_cmp);

	pthread_create(&spawn_students_t, NULL, spawn_students, Students);

	pthread_join(spawn_students_t, NULL);
}