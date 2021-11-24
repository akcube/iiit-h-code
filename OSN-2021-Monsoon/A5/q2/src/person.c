#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

#include "../include/global.h"
#include "../include/matchsim.h"
#include "../include/person.h"
#include "../include/zones.h"
#include "../include/utils.h"

void create_group(Group *g, int people){
	sem_init(&(g->people_left), 0, people);
	pthread_cond_init(&(g->exit_sim), NULL);
	g->people = malloc(sizeof(Person) * people);
	g->size = people;
}

void read_groups(Group *Groups){

	int LUT[26] = {['A'-'A'] = ZONE_A, ['H'-'A'] = ZONE_H, ['N'-'A'] = ZONE_N};

	for(int i=0; i<num_groups; i++){
		int p; scanf("%d", &p);
		Group *G = &Groups[i];
		create_group(G, p);
		
		char buf[1024];
		for(int j=0; j<p; j++){
			Person *P = &(G->people[j]);
			char z;
			scanf("%s %c %d %d %d", buf, &z, &(P->arrival_time), &(P->patience_time), &(P->R));
			P->name = strdup(buf);
			P->zone_id = LUT[z-'A'];
		}
	}
}

void *sim_spec(void *arg){
	pair *parg = (pair*) arg;
	Person *p = parg->first;
	Zone *zones = parg->second;

	

	return NULL;	

}

void *spawn_spec(void *arg){
	pair *parg = (pair*) arg;
	Group *group = parg->first;
	Zone *zones = parg->second;

	int cur = 0;
	for(int time = 0; ; time++, sleep(1)){

		if(cur == group->size) pthread_exit(NULL);

		while(cur < group->size && group->people[cur].arrival_time == time){
			pthread_t *sim_spec_t = malloc(sizeof(pthread_t));
			pair *argptr = malloc(sizeof(pair));
			argptr->first = &(group->people[cur]);
			argptr->second = zones;
			pthread_create(sim_spec_t, NULL, sim_spec, argptr);
			cur++;
		}
	}
}