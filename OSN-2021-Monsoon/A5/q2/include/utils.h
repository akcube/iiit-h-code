#ifndef __SIM_UTILS
#define __SIM_UTILS

typedef struct pair{
	void *first;
	void *second;
} pair;

int get_time();
struct timespec getTimespec(int t);

#endif