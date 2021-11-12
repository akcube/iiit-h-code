#ifndef __COURSESIM_STUDENT
#define __COURSESIM_STUDENT

typedef struct Student{
	int pref[3];
	double CQ;
	int allotted;
	int time_filled;
	int final_choice;
} Student;

void create_student(Student *s);
void destroy_student(Student *s);
void read_students(Student *S, int num_students);

#endif