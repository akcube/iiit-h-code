#include <stdio.h>
#include <pthread.h>
#include "../include/lab.h"
#include "../include/course.h"
#include "../include/student.h"

Course *Courses;
Student *Students;
Lab *Labs;

int main(void){
	
	int num_students, num_labs, num_courses;
	scanf("%d %d %d", &num_students, &num_labs, &num_courses);

	read_courses(Courses, num_courses);
	read_students(Students, num_students);
	read_labs(Labs, num_labs);

	

}