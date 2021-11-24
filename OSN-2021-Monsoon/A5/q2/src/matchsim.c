#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "../include/global.h"
#include "../include/matchsim.h"
#include "../include/person.h"
#include "../include/zones.h"
#include "../include/utils.h"

void read_chances(GoalInfo *Chances){

	int LUT[26] = {['A'-'A'] = ZONE_A, ['H'-'A'] = ZONE_H};

	for(int i=0; i<num_chances; i++){
		GoalInfo *C = &Chances[i];
		char z;
		scanf("%c %d %lf ", &z, &C->time, &C->prob);
		C->team_id = LUT[z-'A'];
	}
}

void init_match(){
	clock_gettime(CLOCK_REALTIME, &start);

	MatchInfo.home_score = 0;
	MatchInfo.away_score = 0;

	pthread_mutex_init(&MatchInfo.lock, NULL);
	sem_init(&MatchInfo.home, 0, 0);
	sem_init(&MatchInfo.away, 0, 0);

	pthread_mutex_init(&MatchInfo.redundant_lock, NULL);
	pthread_cond_init(&MatchInfo.redundant_cond, NULL);
}

void *sim_match(void *arg){
	pthread_mutex_lock(&MatchInfo.redundant_lock);
	GoalInfo *Chances = (GoalInfo*) arg;

	for(int i=0; i<num_chances; i++){
		struct timespec t = getTimespec(Chances[i].time);
		pthread_cond_timedwait(&MatchInfo.redundant_cond, &MatchInfo.redundant_lock, &t);
		if(Chances[i].prob >= 0.5){
			
			pthread_mutex_lock(&MatchInfo.lock);

			switch(Chances[i].team_id){
				case ZONE_H:
					sem_post(&MatchInfo.home);
					MatchInfo.home_score++;
				break;
				case ZONE_A:
					sem_post(&MatchInfo.away);
					MatchInfo.away_score++;
				break;
			}

			pthread_mutex_unlock(&MatchInfo.lock);
		}
	}
	return NULL;
}