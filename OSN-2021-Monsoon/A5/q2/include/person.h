#ifndef __SIM_PERSON
#define __SIM_PERSON

enum { WAITING, SPECTATING, LEAVING };

typedef struct Person{
	char *name;
	int type;
	int arrival_time;
	int patience_time;
	int R;

	int state;
	int zone_id;
	sem_t *semptr;
} Person;

typedef struct Group{
	sem_t people_left;
	int id;
	pthread_cond_t exit_sim;
	int size;
	Person *people;
} Group;

void read_groups(Group *Groups);
void *spawn_spec(void *arg);

#endif