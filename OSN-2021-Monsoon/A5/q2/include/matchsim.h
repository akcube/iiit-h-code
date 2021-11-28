#ifndef __SIM_MATCH
#define __SIM_MATCH

#include <pthread.h>
#include <semaphore.h>

typedef struct Match{
	int home_score;
	int away_score;

	pthread_cond_t home_c;
	pthread_cond_t away_c;
	pthread_mutex_t lock;
	pthread_cond_t HN_free;
	pthread_cond_t A_free;
	pthread_cond_t HAN_free;

	pthread_mutex_t redundant_lock;
	pthread_cond_t redundant_cond;
} Match;

typedef struct GoalInfo{
	int team_id;
	int time;
	double prob;
} GoalInfo;

void init_match();
void read_chances(GoalInfo *Chances);
void *sim_match(void *arg);

#endif