#ifndef __SIM_ZONES
#define __SIM_ZONES

enum { ZONE_H, ZONE_A, ZONE_N };

typedef struct Zone{
	int capacity;
	sem_t free;
} Zone;

void read_zones(Zone *Zones);

#endif