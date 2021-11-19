#ifndef __COURSESIM_LAB
#define __COURSESIM_LAB

typedef struct Lab{
	char *name;
	int num_students;
	int limit;
	int *tas;
} Lab;

void create_lab(Lab *l);
void destroy_lab(Lab *l);
void read_labs(Lab **L, int num_labs);

#endif