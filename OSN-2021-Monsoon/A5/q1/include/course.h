#ifndef __COURSESIM_COURSE
#define __COURSESIM_COURSE

enum CourseStates {LOOKING_FOR_TA, WAITING_FOR_STUDENTS, TUT_IN_PROGRESS, REMOVED};

typedef struct Course{
	char *name;
	int state;
	double interest;
	int max_slots;
	int occupied_slots;
	int allotted_slots;
	int labs_size;
	int *labs;

	pthread_cond_t finished;
} Course;

void create_course(Course *c);
void delete_course(Course *c);
void read_courses(Course **C);
Course *getCourseByID(int id, Course *C);

#endif