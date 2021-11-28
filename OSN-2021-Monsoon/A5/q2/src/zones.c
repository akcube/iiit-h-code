#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "../include/global.h"
#include "../include/matchsim.h"
#include "../include/person.h"
#include "../include/zones.h"

void read_zones(Zone *Zones){
	scanf("%d", &Zones[ZONE_H].capacity);
	sem_init(&Zones[ZONE_H].free, 0, Zones[ZONE_H].capacity);
	Zones[ZONE_H].name = 'H';

	scanf("%d", &Zones[ZONE_A].capacity);
	sem_init(&Zones[ZONE_A].free, 0, Zones[ZONE_A].capacity);
	Zones[ZONE_A].name = 'A';

	scanf("%d", &Zones[ZONE_N].capacity);
	sem_init(&Zones[ZONE_N].free, 0, Zones[ZONE_N].capacity);
	Zones[ZONE_N].name = 'N';
}

