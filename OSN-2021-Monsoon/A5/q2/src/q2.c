#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

#include "../include/global.h"
#include "../include/matchsim.h"
#include "../include/person.h"
#include "../include/zones.h"
#include "../include/utils.h"

struct timespec start = {0};
int spectating_time = 0;
int num_groups = 0;
int num_chances = 0;
Match MatchInfo = {0};

pthread_t run_game, *spawn_spec_t;

int main(void){

	Zone *Zones = malloc(sizeof(Zone)*num_zones);
	read_zones(Zones);

	scanf("%d ", &spectating_time);

	scanf("%d ", &num_groups);
	Group *Groups = malloc(sizeof(Group)*num_groups);
	read_groups(Groups);

	scanf("%d ", &num_chances);
	GoalInfo *Chances = malloc(sizeof(GoalInfo)*num_chances);
	read_chances(Chances);

	init_match();
	spawn_spec_t = malloc(sizeof(pthread_t)*num_groups);
	for(int i=0; i<num_groups; i++){
		pair *spawn_spec_arg = malloc(sizeof(pair));
		spawn_spec_arg->first = &Groups[i];
		spawn_spec_arg->second = Zones;
		pthread_create(&spawn_spec_t[i], NULL, spawn_spec, spawn_spec_arg);
	}
	pthread_create(&run_game, NULL, sim_match, Chances);
	pthread_join(run_game, NULL);
}