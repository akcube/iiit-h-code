#ifndef __COURSESIM_COURSE
#define __COURSESIM_COURSE

typedef struct Course{
	char *name;
	double interest;
	int max_slots;
	int allotted_ta;
	int taship_left;
	int labs_size;
	int *labs;
} Course;

void create_course(Course *c);
void delete_course(Course *c);
void read_courses(Course *C, int num_courses);

#endif