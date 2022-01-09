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
	sem_init(&(g->people_left), 0, 0);
	pthread_cond_init(&(g->exit_sim), NULL);
	g->people = malloc(sizeof(Person) * people);
	g->size = people;
}

int cmpfunc(const void *a, const void *b){
	Person *A = (Person*) a;
	Person *B = (Person*) b;
	return A->arrival_time > B->arrival_time;
}

void read_groups(Group *Groups){

	int LUT[26] = {['A'-'A'] = ZONE_A, ['H'-'A'] = ZONE_H, ['N'-'A'] = ZONE_N};

	for(int i=0; i<num_groups; i++){
		int p; scanf("%d", &p);
		Group *G = &Groups[i];
		G->id = i;
		create_group(G, p);
		
		char buf[1024];
		for(int j=0; j<p; j++){
			Person *P = &(G->people[j]);
			char z;
			scanf("%s %c %d %d %d", buf, &z, &(P->arrival_time), &(P->patience_time), &(P->R));
			P->name = strdup(buf);
			P->type = LUT[z-'A'];
			P->state = WAITING;
			P->zone_id = -1;
			P->semptr = &G->people_left;
		}
		qsort(G->people, G->size, sizeof(Person), cmpfunc);
	}
}

int sz_avail[3] = {	[ZONE_H] = 2, [ZONE_A] = 1, [ZONE_N] = 3 };
int avail[3][3] = {	
					[ZONE_H] = { ZONE_H, ZONE_N, -1 }, 
					[ZONE_A] = { ZONE_A, -1, -1 },
					[ZONE_N] = { ZONE_H, ZONE_A, ZONE_N }
				  };
pthread_cond_t *cond_avail[3] = { 
									[ZONE_H] = &MatchInfo.HN_free,
									[ZONE_A] = &MatchInfo.A_free,
									[ZONE_N] = &MatchInfo.HAN_free,
								};

void *sim_spec(void *arg){
	pair *parg = (pair*) arg;
	Person *p = parg->first;
	Zone *zones = parg->second;

	cprintf(CYAN, "t=%d: %s has reached the stadium\n", p->arrival_time, p->name);

	struct timespec patience = getTimespec(p->arrival_time + p->patience_time);
	while(p->state == WAITING){

		for(int i=0; i < sz_avail[p->type]; i++){
			int zid = avail[p->type][i];

			if(sem_trywait(&zones[zid].free) == 0){
				cprintf(GREEN, "t=%d: %s has got a seat in zone %c\n", get_time(), p->name, zones[zid].name);
				p->state = SPECTATING;
				p->zone_id = zid;
				break;
			}
		}

		if(p->state == SPECTATING) break;
		pthread_mutex_lock(&MatchInfo.lock);
		if(pthread_cond_timedwait(cond_avail[p->type], &MatchInfo.lock, &patience) != 0){
			p->state = LEAVING;
		}
		pthread_mutex_unlock(&MatchInfo.lock);
	}

	if(p->state == LEAVING) {
		cprintf(RED, "t=%d: %s couldn't get a seat\n", get_time(), p->name);
		sem_post(&zones[p->zone_id].free);
		sem_post(p->semptr);
		pthread_exit(NULL);
	}

	struct timespec endspec = getTimespec(get_time() + spectating_time);
	while(p->state == SPECTATING && p->type != ZONE_N){
		pthread_mutex_lock(&MatchInfo.lock);
		if((p->type == ZONE_H && MatchInfo.away_score >= p->R) || (p->type == ZONE_A && MatchInfo.home_score >= p->R)){
			pthread_mutex_unlock(&MatchInfo.lock);
			p->state = LEAVING;
			cprintf(YELLOW, "t=%d: Person %s is leaving due to the bad defensive performance of his team\n", get_time(), p->name);
			sem_post(&zones[p->zone_id].free);
			if(p->type == ZONE_H)
				pthread_cond_broadcast(&MatchInfo.HN_free);
			else
				pthread_cond_broadcast(&MatchInfo.A_free);
			break;
		}
		if(p->type == ZONE_A){
			if(pthread_cond_timedwait(&MatchInfo.home_c, &MatchInfo.lock, &endspec) != 0){
				p->state = LEAVING;
				cprintf(BLUE, "t=%d: Person %s watched the match for %d seconds and is leaving\n", get_time(), p->name, spectating_time);
				sem_post(&zones[p->zone_id].free);
				pthread_cond_broadcast(&MatchInfo.A_free);
			}
			pthread_mutex_unlock(&MatchInfo.lock);
		}
		else if(p->type == ZONE_H){
			if(pthread_cond_timedwait(&MatchInfo.away_c, &MatchInfo.lock, &endspec) != 0){
				p->state = LEAVING;
				cprintf(BLUE, "t=%d: Person %s watched the match for %d seconds and is leaving\n", get_time(), p->name, spectating_time);
				sem_post(&zones[p->zone_id].free);
				pthread_cond_broadcast(&MatchInfo.HN_free);
			}
			pthread_mutex_unlock(&MatchInfo.lock);
		}
	}

	pthread_mutex_t redundant_l;
	pthread_cond_t redundant_c;
	pthread_mutex_init(&redundant_l, NULL);
	pthread_cond_init(&redundant_c, NULL);

	if(p->state == SPECTATING && p->type == ZONE_N){
		pthread_mutex_lock(&redundant_l);
		// Will timeout
		pthread_cond_timedwait(&redundant_c, &redundant_l, &endspec);
		pthread_mutex_unlock(&redundant_l);
		sem_post(&zones[p->zone_id].free);
		cprintf(BLUE, "t=%d: Person %s watched the match for %d seconds and is leaving\n", get_time(), p->name, spectating_time);
		pthread_cond_broadcast(&MatchInfo.HAN_free);
		p->state = LEAVING;
	}

	sem_post(p->semptr);
	// cprintf(PINK, "t=%d: Person %s is leaving for dinner\n", get_time(), p->name);
	return NULL;	
}

void *spawn_spec(void *arg){
	pair *parg = (pair*) arg;
	Group *group = parg->first;
	Zone *zones = parg->second;

	int cur = 0;
	for(int time = 0; ; time++, sleep(1)){

		if(cur == group->size) break;

		while(cur < group->size && group->people[cur].arrival_time == time){
			pthread_t *sim_spec_t = malloc(sizeof(pthread_t));
			pair *argptr = malloc(sizeof(pair));
			argptr->first = &(group->people[cur]);
			argptr->second = zones;
			pthread_create(sim_spec_t, NULL, sim_spec, argptr);
			cur++;
		}
	}

	int ct = 0;
	while(sem_wait(&group->people_left) == 0){
		ct++;
		if(ct == group->size) break;
	}
	cprintf(YELLOW, "t=%d: Group %d is leaving for dinner\n", get_time(), group->id);
	pthread_exit(NULL);
}