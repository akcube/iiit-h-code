#ifndef __COURSESIM_STUDENT
#define __COURSESIM_STUDENT

typedef struct Student{
	int pref[3];
	double CQ;
	int allotted;
	int time_filled;
	int final_choice;
	int id;

	pthread_mutex_t lock;
} Student;

// Util
int student_time_cmp(const void *, const void *);

void create_student(Student *s, int id);
void destroy_student(Student *s);
void read_students(Student **S, int num_students);

void *spawn_students(void *arg);

#endif