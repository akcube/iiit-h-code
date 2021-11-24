#ifndef __SIM_PERSON
#define __SIM_PERSON


typedef struct Person{
	char *name;
	int zone_id;
	int arrival_time;
	int patience_time;
	int R;
} Person;

typedef struct Group{
	sem_t people_left;
	pthread_cond_t exit_sim;
	int size;
	Person *people;
} Group;

void read_groups(Group *Groups);
void *spawn_spec(void *arg);

#endif