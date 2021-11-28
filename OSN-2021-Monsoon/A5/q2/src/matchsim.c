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
	pthread_cond_init(&MatchInfo.home_c, NULL);
	pthread_cond_init(&MatchInfo.away_c, NULL);
	
	pthread_mutex_init(&MatchInfo.redundant_lock, NULL);
	pthread_cond_init(&MatchInfo.redundant_cond, NULL);
}

void *sim_match(void *arg){
	GoalInfo *Chances = (GoalInfo*) arg;

	for(int i=0; i<num_chances; i++){
		struct timespec t = getTimespec(Chances[i].time);
		pthread_mutex_lock(&MatchInfo.redundant_lock);
		pthread_cond_timedwait(&MatchInfo.redundant_cond, &MatchInfo.redundant_lock, &t);
		pthread_mutex_unlock(&MatchInfo.redundant_lock);
		if(Chances[i].prob >= 0.5){
			pthread_mutex_lock(&MatchInfo.lock);
			switch(Chances[i].team_id){
				case ZONE_H:
					MatchInfo.home_score++;
					cprintf(WHITE, "t=%d: Team H have scored their %d(th/st/nd) goal\n", Chances[i].time, MatchInfo.home_score);
					pthread_cond_broadcast(&MatchInfo.home_c);
				break;
				case ZONE_A:
					MatchInfo.away_score++;
					cprintf(WHITE, "t=%d: Team A have scored their %d(th/st/nd) goal\n", Chances[i].time, MatchInfo.away_score);
					pthread_cond_broadcast(&MatchInfo.away_c);
				break;
			}
			pthread_mutex_unlock(&MatchInfo.lock);
		}
		else{
			cprintf(WHITE, "t=%d: Team %c missed the chance to score their %d(th/st/nd) goal\n", Chances[i].time, ((Chances[i].team_id == ZONE_A) ? 'A' : 'H'), MatchInfo.home_score);
		}
		
	}
	return NULL;
}